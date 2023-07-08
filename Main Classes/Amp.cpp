#include "Amp.hpp"

void Amp::AmpMenu()
{
    /* Извеждане на текущия инвентар на екрана.
●       Проверка за достатъчна наличност в инвентара.
●       Поръчка на ресурси (след което обновява inventory.txt с новите количества).
●       Настройка на минималните количества от страна на потребителя*/
    std::cout << "\n\n"
              << "******************************************************************************";
    std::cout << '\n'
              << "                                   AMP MENU";
    std::cout << '\n'
              << "******************************************************************************";
    std::cout << "\n1. View Current Inventory and Auto Order Components if Necessary";
    std::cout << "\n2. Minimum Quantity Settings";
    std::cout << "\n3. Exit AMP";

    int choice = 0;
    while (choice < 1 || choice > 3)
    {
        std::cin >> choice;
        if (choice < 1 || choice > 3)
        {
            std::cout << "Enter a valid choice!";
            std::cin >> choice;
        }
    }

    if (choice == 1)
    {
        printInventory();
        AmpMenu();
    }
    else if (choice == 2)
    {
        minQuantitySettingsMenu();
        AmpMenu();
    }
    else
    {
        return;
    }
}
void Amp::CheckForNewComponentsFromVolt()
{
    // if (currentQuantity.empty())
    if (m_currentQuantity.begin()->first == "")
    {
        std::cout << "CRITICAL ERROR! NO DATA IN INVERTORY!";
        return;
    }

    // else if (minQuantity.empty())
    else if (m_minQuantity.begin()->first == "")
    {
        std::cout << "AMP_CFG IS EMPTY. SETTING DEFAULT MIN QUANTITY FOR ALL ITEMS";
        for (auto iter = m_currentQuantity.begin(); iter != m_currentQuantity.end(); ++iter)
        {
            m_minQuantity[iter->first] = m_defaultMinQuantityForNewComponents;
        }
        updateInvertory();
        return;
    }

    else
    {
        bool newFound = false;
        for (auto iter = m_currentQuantity.begin(); iter != m_currentQuantity.end(); ++iter)
        {
            bool found = false;
            for (auto iter2 = m_minQuantity.begin(); iter2 != m_minQuantity.end(); ++iter2)
            {
                if (iter->first == iter2->first)
                {
                    found = true;
                    newFound = true;
                }
            }
            if (!found)
            {
                std::cout << "New Component from Volt Detected! Name:" << iter->first << " Def.Min.Quant:" << m_defaultMinQuantityForNewComponents;
                m_minQuantity[iter->first] = m_defaultMinQuantityForNewComponents;
            }
        }
        if (newFound)
        {
            updateInvertory();
        }
    }
}
void Amp::getCurrentInventory()
{
    m_currentQuantity = {};
    FileManager fm("textFiles/Inventory.txt");

    std::string id = "";
    int quantity = 0;

    while (!fm.get().eof())
    {
        fm.get() >> id >> quantity;
        m_currentQuantity[id] = quantity;
    }
}
void Amp::getMinQuantity()
{
    m_minQuantity = {};

    FileManager fm("textFiles/cfg_amp.txt");

    std::string id = "";
    int quantity = 0;

    while (!fm.get().eof())
    {
        fm.get() >> id >> quantity;
        m_minQuantity[id] = quantity;
    }
}
void Amp::getInfofromInvertory()
{
    getCurrentInventory();
    getMinQuantity();
}

void Amp::printInventory()
{

    getInfofromInvertory();
    CheckForNewComponentsFromVolt();
    for (auto iter = m_currentQuantity.begin(); iter != m_currentQuantity.end(); ++iter)
    {
        std::cout << '\n'
                  << "Component ID:" << iter->first << ' ' << "Available Quantity:" << iter->second << ' ';

        auto iter2 = m_minQuantity.begin();
        while (iter2->first != iter->first)
        {
            ++iter2;
        }
        std::cout << "Min Quantity:" << iter2->second;

        if (!sufficientQuantityPresent(iter->first))
        {
            std::cout << " Insufficient quantity!";
            orderResources(iter->first);
        }
        else
        {
            std::cout << " Sufficient quantity.";
        }
    }
}

bool Amp::sufficientQuantityPresent(const std::string &componentName)
{
    auto iter = m_currentQuantity.begin();
    auto iter2 = m_minQuantity.begin();

    while (iter->first != componentName)
    {
        ++iter;
    }
    while (iter2->first != iter->first)
    {
        ++iter2;
    }
    if (iter->second >= iter2->second)
    {
        return true;
    }

    return false;
}

void Amp::orderResources(const std::string &id)
{
    auto iter = m_currentQuantity.begin();
    auto iter2 = m_minQuantity.begin();

    while (iter->first != id)
    {
        ++iter;
    }
    while (iter2->first != iter->first)
    {
        ++iter2;
    }
    if (iter->first == iter2->first && iter->second < iter2->second)
    {
        if (iter->second < 0)
        {
            std::cout << " extra quantities required.";
            int extraQuantity = 0 - iter->second;
            std::cout << " extra " << extraQuantity << " required.";
            iter->second = iter2->second + extraQuantity;
        }
        else
        {
            iter->second = iter2->second;
        }
    }
    updateInvertory();
}

void Amp::minQuantitySettingsMenu()
{
    std::cout << "\n\n"
              << "************************************************************************************";
    std::cout << '\n'
              << "                           MINMINAL QUANTITY SETTINGS";
    std::cout << '\n'
              << "************************************************************************************";

    std::cout << "\n1. Change the Default Min. Quantity for New Items";
    std::cout << "\n2. View or Change the Min. Quantity for Components";
    std::cout << "\n3. Go Back";
    std::cout << "Enter your choice:";

    int choice = 0;
    while (choice < 1 || choice > 3)
    {
        std::cin >> choice;
        if (choice < 1 || choice > 3)
        {
            std::cout << "Enter a valid choice!";
            std::cin >> choice;
        }
    }

    if (choice == 1)
    {
        setDefaultMinQuantity();
    }
    else if (choice == 2)
    {
        setComponentMinQuantity();
    }
    else
    {
        return;
    }
}
void Amp::setDefaultMinQuantity()
{
    std::cout << "\n\n"
              << "***********************************************************************************";
    std::cout << '\n'
              << "                           DEFAULT MIN QUANTITY SETTINGS";
    std::cout << '\n'
              << "***********************************************************************************";
    std::cout << "\nDefault Min. Quantity for New Items - " << m_defaultMinQuantityForNewComponents;
    int n = -1;

    while (n < 0)
    {
        std::cout << "\nEnter the New Default Min. Quantity for New Items\nOR\nEnter 0 to Go Back:";
        std::cin >> n;

        if (n == 0)
        {
            return;
        }
        else if (n < 0)
        {
            std::cout << "Enter either a Positive Number or a Zero:";
        }
    }

    m_defaultMinQuantityForNewComponents = n;
    std::cout << "\nSuccessfully changed Default Min Quantity to " << m_defaultMinQuantityForNewComponents;
}
void Amp::setComponentMinQuantity()
{
    getInfofromInvertory();

    std::cout << "\n\n"
              << "*********************************************************************************";
    std::cout << '\n'
              << "                    MINMINAL QUANTITY SETTINGS FOR COMPONENTS";
    std::cout << '\n'
              << "*********************************************************************************";

    std::cout << "\nDefault Min. Quantity for New Items - " << m_defaultMinQuantityForNewComponents;
    std::cout << "\nGo back if you wish to change it";

    std::string componentName = "";
    while (componentName == "")
    {
        auto iter = m_minQuantity.begin();
        for (iter = m_minQuantity.begin(); iter != m_minQuantity.end(); ++iter)
        {
            std::cout << '\n'
                      << "Component ID:" << iter->first << ' ' << "Min Quantity:" << iter->second;
        }

        std::cout << "\nEnter a Component's name Accurately to adjust its settings:";
        std::cout << "\nAlternatively, enter '0' to Go Back:\n";
        componentName = "";
        bool validNameEntered = false;
        while (!validNameEntered)
        {
            std::cin >> componentName;
            if (componentName == "0")
            {
                std::cout << "Going Back.";
                return;
            }

            for (iter = m_minQuantity.begin(); iter != m_minQuantity.end(); ++iter)
            {
                if (iter->first == componentName)
                {
                    validNameEntered = true;
                    break;
                }
            }

            if (!validNameEntered)
            {
                std::cout << "Invalid input entered! Try Again.";
            }
        }

        std::cout << "You've selected the following: " << '\n';
        std::cout << "Component ID:" << iter->first << ' ' << "Current Min Quantity:" << iter->second << " Enter New Min Quantity:" << '\n';

        int newQuantity = 0;
        while (newQuantity <= 0)
        {
            std::cin >> newQuantity;
            if (newQuantity <= 0)
            {
                std::cout << "Please enter a quantity above 0!";
                std::cin >> newQuantity;
            }
        }
        iter->second = newQuantity;
        std::cout << "\nSuccessfully changed min Quantity!";
        updateInvertory();
    }

    return;
}

void Amp::updateInvertory()
{
    FileManager Inventory("textFiles/Inventory.txt");
    FileManager cfg_amp("textFiles/cfg_amp.txt");

    for (auto iter = m_currentQuantity.begin(); iter != m_currentQuantity.end(); ++iter)
    {
        auto iter2 = m_minQuantity.begin();
        while (iter2->first != iter->first)
        {
            ++iter2;
        }

        Inventory.get() << iter->first << ' ' << iter->second << '\n';
        cfg_amp.get() << iter2->first << ' ' << iter2->second << '\n';
    }

    std::cout << "\nUpdated inventory.";
}