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
#include "HardwareComponentManager.hpp"
#include "FileManager.hpp"
#include <fstream>
#include <string>
#include <iostream>

class Amp
{
private:
    // TODO vargs file path name
    std::map<std::string, int> m_currentQuantity = {};
    std::map<std::string, int> m_minQuantity = {};
    unsigned int m_defaultMinQuantityForNewComponents = 5;

public:
    Amp(std::map<std::string, int> currentQuantity = {}, std::map<std::string, int> minQuantity = {},
    unsigned int defaultMinQuantityForNewComponents = 5) : m_currentQuantity(currentQuantity), m_minQuantity(m_minQuantity),
    m_defaultMinQuantityForNewComponents(m_defaultMinQuantityForNewComponents)
    {}
    void AmpMenu();
    void CheckForNewComponentsFromVolt();
    void getCurrentInventory();
    void getMinQuantity();
    void getInfofromInvertory();
    void printInventory();
    bool sufficientQuantityPresent(const std::string &componentName);
    void orderResources(const std::string &id);
    void minQuantitySettingsMenu();
    void setDefaultMinQuantity();
    void setComponentMinQuantity();
    void updateInvertory();
};
