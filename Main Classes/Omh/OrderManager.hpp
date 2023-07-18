#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <functional>
#include <algorithm>
#include <sstream>
#include <chrono>
#include <random>

#include "../srcCommon/ClientOrder.h"
#include "../srcCommon/FileManager.hpp"

class OrderManager
{
public:
    std::vector<ClientOrder> orders;

    void showMenu();
    void addOrder();
    void getOrdersFromFile();
    void displayOrdersByHistory();
    void displayOrdersByPriority();
    void cancelOrder();
    void getOrder();

private:
    static const std::string ORDERS_FILE;

    void checkInput();
    std::string generateRandomId();
    void saveOrderToFile(const ClientOrder& order);
    void displayOrders(const std::vector<ClientOrder>& orders);
};

#endif  
