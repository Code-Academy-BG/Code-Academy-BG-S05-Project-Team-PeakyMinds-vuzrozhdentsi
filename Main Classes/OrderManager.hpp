#ifndef ORDER_MANAGER_HPP
#define ORDER_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

//client order
class OrderManager {
private:
    std::string filename;

public:
    OrderManager(const std::string& filename = "orders.txt") : filename(filename) {}

    void run();

private:
    void addOrder();
    void displayOrders();
    //void displayOrdersByPriority();
    void cancelOrder(const std::string& orderName);
};

#endif 
