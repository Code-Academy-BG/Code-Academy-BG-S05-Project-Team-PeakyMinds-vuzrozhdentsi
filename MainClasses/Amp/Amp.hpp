/*Програма, която дава възможност за автоматизирано следене на складовата наличност (в
inventory.txt) и правене на поръчки на ресурси.
В конфигурационния файл на програмата има настройки за минималните количества, които
трябва да се поддържат налични.
Програмата трябва да дава възможност за:
● Извеждане на текущия инвентар на екрана.
● Проверка за достатъчна наличност в инвентара.
● Поръчка на ресурси (след което обновява inventory.txt с новите количества).
● Настройка на минималните количества от страна на потребителя.
Параметри, които приема по командния ред:
● релативния път от data директорията до cfg_amp.txt, конкатениран с името на файла.
● релативния път от data директорията до inventory.txt, конкатениран с името на файла*/
#include "../srcCommon/FileManager.hpp"
#include <map>
#include <fstream>
#include <string>
#include <iostream>
#include <cmath>
#include <limits>
#include <functional>
#include<algorithm>
class Amp
{
private:
    // TODO vargs file path name
    std::map<std::string, int> m_currentQuantity = {};
    std::map<std::string, int> m_minQuantity = {};
    unsigned int m_defaultMinQuantityForNewComponents = 5;
    std::string inventory_name = "../textFiles/Inventory.txt";
    std::string cfg_name = "../textFiles/cfg_amp.txt";

public:
    Amp(std::map<std::string, int> currentQuantity = {}, std::map<std::string, int> minQuantity = {}) : m_currentQuantity(currentQuantity), m_minQuantity(minQuantity) {}

    void AmpMenu(std::istream &strm);
    void CheckForNewComponentsFromVolt();
    void getCurrentInventory();
    void getMinQuantity();
    void getInfofromInvertory();
    void printInventory();
    bool sufficientQuantityPresent(const std::string &componentName);
    void orderResources(const std::string &id);
    void minQuantitySettingsMenu(std::istream &strm);
    void setDefaultMinQuantity(std::istream &strm);
    void setComponentMinQuantity(std::istream &strm);
    void updateInvertory();
    void Run();
<<<<<<< Updated upstream
};
=======
    
};
>>>>>>> Stashed changes
