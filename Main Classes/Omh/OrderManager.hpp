#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP

#include <string>

class OrderManager
{
public:
    void addOrder(const std::string& filename);
    void displayOrders(const std::string& filename);
    void displayOrdersByPriority(const std::string& filename, ClientOrder::Priority priority);
    void cancelOrder(const std::string& filename, int orderId);
};

#endif  