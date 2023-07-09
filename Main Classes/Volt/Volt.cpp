#include "Volt.hpp"
std::unique_ptr<Volt> Volt::voltPtr =  std::unique_ptr<Volt>(new Volt());
const std::string Volt::PRINT_JOB_FILE = "../textFiles/print_jobs.txt";
const std::string Volt::INVENTORY_FILE = "../textFiles/inventory.txt";
const std::string Volt::CLIENT_ORDERS_FILE = "../textFiles/client_orders.txt";
const std::string Volt::PRODUCTION_FILE = "../textFiles/production.txt";
const std::string Volt::HISTORY_FILE = "../textFiles/history.txt";
const std::string Volt::ELECTRONIC_COMPONENT_LIBRARY_FILE = "../textFiles/ElectronicComponentLibrary.txt";
const std::string Volt::HARDWARE_COMPONENT_LIBRARY_FILE = "../textFiles/HardwareComponentLibrary.txt";
const std::string Volt::HARDWARE_COMPONENT_FOR_PRINTING_MSG = "Current hardware components to be printed:\n";
const std::string Volt::INVALID_CHOICE_ERROR = "Invalid choice";
const std::string Volt::RUN_CHOICE_INSTRUCTIONS_MSG = "Press 0 for processing OR 1 for printing currently pending,\n anythingelse will end the program\n";

bool Volt::getLibraries()
{
    try
    {
        hcLibrary.load(HARDWARE_COMPONENT_LIBRARY_FILE);
        ecLibrary.load(ELECTRONIC_COMPONENT_LIBRARY_FILE);
        return true;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return false;
    }
    
}

void Volt::getPendingRequestsForPrint()
{
    FileManager fm{PRINT_JOB_FILE};
    Volt::hardwareComponentID id{""};
    while (!(fm.get()>>std::ws).eof())
    {
        fm.get() >> id >> pendingHardwareComponentsForPrinting[id];
    }
}

void Volt::getInventory()
{
    FileManager fm{INVENTORY_FILE};
    Volt::electronincComponentID id{""};
    while (!(fm.get()>>std::ws).eof())
    {
        fm.get() >> id >> electronicComponentsOnStock[id];
    }
}

void Volt::getProduction()
{
    FileManager fm{PRODUCTION_FILE};
    Volt::hardwareComponentID id{""};
    while (!(fm.get()>>std::ws).eof())
    {
        fm.get() >> id >> completedHardwareComponents[id];
    }
}

void Volt::getClientOrders()
{
    FileManager fm{CLIENT_ORDERS_FILE};

    while (!(fm.get()>>std::ws).eof())
    {
        ordersFromClient.emplace_back(ClientOrder(fm.get()));
        if (fm.get().fail())
        {
            std::cout << "Volt fails reading client orders\n";
            break;
        }
        
    }
}

void Volt::processingUnprocessedOrdersForPrinting(ClientOrder &order)
{
    std::cout << "Starting handling UMPROCESSED\n";
    if (order.getStatus() == ClientOrder::Status::UNPROCESSED)
    {
        bool areAllHrdwareComponentsReadyForPrinting{true};
        for (auto &hComponent : order.getHardwareComponents())
        {

            for (auto &elComponent : hcLibrary.getHardwareComponent(hComponent).getComponents())
            {
                const auto &currentElComponentID = (elComponent).getId();
                if (electronicComponentsOnStock[currentElComponentID] > 0)
                {
                    electronicComponentsOnStock[currentElComponentID]--;
                }
                else
                {
                    areAllHrdwareComponentsReadyForPrinting = false;
                    electronicComponentsForAdditionalPurchasing[currentElComponentID]++;
                    pendingOrdersWithMissingComponents[order.getId()].push_back(currentElComponentID);
                }
            }

            if (areAllHrdwareComponentsReadyForPrinting)
            {
                order.setStatus(ClientOrder::Status::InPROGRESS);
                for (auto iter = order.getHardwareComponents().begin(); iter != order.getHardwareComponents().end(); iter++)
                {
                    pendingHardwareComponentsForPrinting[(*iter)]++;
                }
            }
            else
            {
                order.setStatus(ClientOrder::Status::PENDING);
            }
        }
    }
    std::cout << "Handling UMPROCESSED ended\n";

}

void Volt::processingPendingOrdersForPrinting(ClientOrder &order)
{
    std::cout << "Starting handling PENDING\n";
    if (order.getStatus() == ClientOrder::Status::PENDING)
    {
        for (auto iter = pendingOrdersWithMissingComponents[order.getId()].begin(); iter != pendingOrdersWithMissingComponents[order.getId()].end();)
        {
            if (electronicComponentsOnStock[(*iter).getId()] > 0)
            {
                electronicComponentsOnStock[(*iter).getId()]--;
                iter = pendingOrdersWithMissingComponents[order.getId()].erase(iter);
            }
            else
            {
                iter++;
            }
        }
        if (pendingOrdersWithMissingComponents[order.getId()].empty())
        {
            order.setStatus(ClientOrder::Status::InPROGRESS);
            for (auto iter = order.getHardwareComponents().begin(); iter != order.getHardwareComponents().end(); iter++)
            {
                pendingHardwareComponentsForPrinting[(*iter)]++;
            }
        }
    }
    std::cout << "Handling PENDING ended\n";
}

void Volt::processingInProgressOrdersFromProduction(ClientOrder &order)
{
    std::cout << "Starting handling InPROGRESS\n";
    if (order.getStatus() == ClientOrder::Status::InPROGRESS)
    {
        bool areAllComponentPresent{true};
        for (auto &hComponent : order.getHardwareComponents())
        {
            if (completedHardwareComponents[hComponent] == 0)
            {
                areAllComponentPresent = false;
                break;
            }
        }

        if (areAllComponentPresent)
        {
            for (auto &hComponent : order.getHardwareComponents())
            {
                completedHardwareComponents[hComponent]--;
            }
            ordersForHistory.push_back(order);
            order.setStatus(ClientOrder::Status::COMPLETED);
        }
    }
    std::cout << "Handling InPROGRESS ended\n";
}

void Volt::updateClientOrders()
{
    FileManager fm{CLIENT_ORDERS_FILE};
    ordersFromClient.erase(
        std::remove_if(ordersFromClient.begin(), ordersFromClient.end(),
                       [](ClientOrder &order)
                       { return order.getStatus() == ClientOrder::Status::COMPLETED; }),
        ordersFromClient.end());
    std::for_each(ordersFromClient.begin(), ordersFromClient.end(),
                  [&](ClientOrder &order)
                  { fm.get() << order; });
    std::cout << "Client orders saved\n";
}

void Volt::updateProduction()
{
    FileManager fm{PRODUCTION_FILE};
    std::for_each(pendingHardwareComponentsForPrinting.begin(), pendingHardwareComponentsForPrinting.end(),
                  [&](const std::pair<Volt::electronincComponentID, Volt::quantity> &p)
                  { fm.get() << p.first << ' ' << p.second << '\n'; });
    std::cout << "Production saved\n";

}

void Volt::updateInventory()
{
    FileManager fm{INVENTORY_FILE};
    std::for_each(electronicComponentsOnStock.begin(), electronicComponentsOnStock.end(),
                  [&](const std::pair<Volt::electronincComponentID, Volt::quantity> &p)
                  { fm.get() << p.first << ' ' << p.second << '\n'; });
    std::for_each(electronicComponentsForAdditionalPurchasing.begin(), electronicComponentsForAdditionalPurchasing.end(),
                  [&](const std::pair<Volt::electronincComponentID, Volt::quantity> &p)
                  { fm.get() << p.first << ' ' << '-' << p.second << '\n'; });
    std::cout << "Inventory saved\n";

}

void Volt::updatePendingRequestsForPrint()
{
    FileManager fm{PRINT_JOB_FILE};
    std::for_each(pendingHardwareComponentsForPrinting.begin(), pendingHardwareComponentsForPrinting.end(),
                  [&](const std::pair<Volt::hardwareComponentID, Volt::quantity> &p)
                  { fm.get() << p.first << ' ' << p.second << '\n'; });
    std::cout << "Requests for print saved\n";

}

void Volt::updateHistory()
{
    FileManager fm(HISTORY_FILE);
    std::vector<ClientOrder> currentHistory;
    while (!fm.get().eof())
    {
        currentHistory.emplace_back(ClientOrder(fm.get()));
    }
    std::for_each(currentHistory.begin(), currentHistory.end(),
                  [&](const ClientOrder &order)
                  { fm.get() << order; });

    std::for_each(ordersForHistory.begin(), ordersForHistory.end(),
                  [&](const ClientOrder &order)
                  { fm.get() << order; });
    std::cout << "History saved\n";
}

void Volt::checkForNewDesigns()
{
    std::for_each(ordersFromClient.begin(), ordersFromClient.end(),
                  [&](const ClientOrder &o)
                  {
                      std::for_each(o.getHardwareComponentsWithDesign().begin(), o.getHardwareComponentsWithDesign().end(),
                                    [&](const HardwareComponent &hc)
                                    { hcLibrary.addHardwareComponent(hc); });
                      std::for_each(o.getElectronicComponentsWithDesign().begin(), o.getElectronicComponentsWithDesign().end(),
                                    [&](const ElectronicComponent &ec)
                                    { ecLibrary.addComponent(ec); });
                  });
    std::cout << "New designs saved\n";
    hcLibrary.save(HARDWARE_COMPONENT_LIBRARY_FILE);
    ecLibrary.save(ELECTRONIC_COMPONENT_LIBRARY_FILE);
}

void Volt::processOrders()
{
    getLibraries();
    getInventory();
    getPendingRequestsForPrint();
    getClientOrders();
    checkForNewDesigns();

    for (auto iter = ordersFromClient.begin(); iter != ordersFromClient.end(); iter++)
    {
        switch ((*iter).getStatus())
        {
        case ClientOrder::Status::UNPROCESSED:
            processingUnprocessedOrdersForPrinting(*iter);
            break;
        case ClientOrder::Status::PENDING:
            processingPendingOrdersForPrinting(*iter);
            break;
        default:
            break;
        }
    }

    getProduction();
    for (auto iter = ordersFromClient.begin(); iter != ordersFromClient.end(); iter++)
    {
        processingInProgressOrdersFromProduction(*iter);
    }
    updateProduction();
    updateClientOrders();
    updateInventory();
    updatePendingRequestsForPrint();
}

void Volt::printPrintJobs()
{
    std::cout << HARDWARE_COMPONENT_FOR_PRINTING_MSG << std::endl;
    getPendingRequestsForPrint();
    for (auto iter = pendingHardwareComponentsForPrinting.begin(); iter != pendingHardwareComponentsForPrinting.end(); iter++)
    {
        std::cout << (*iter).first << ' ' << (*iter).second << std::endl;
    }
}

int Volt::run()
{
    int choice{0};
    try
    {

        std::cout << RUN_CHOICE_INSTRUCTIONS_MSG << std::endl;
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            printPrintJobs();
            break;
        case 0:
            processOrders();
            break;
        default:
            throw std::invalid_argument(INVALID_CHOICE_ERROR);
        }
        return 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }
}