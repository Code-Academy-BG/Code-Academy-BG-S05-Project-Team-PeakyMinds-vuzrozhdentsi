#ifndef CLIENT_HPP
#define CLIENT_HPP

#include "ClientOrder.hpp"
#include "OrderManager.hpp"
#include <string>
#include <vector>

class Client
{
private:
    int id;
    std::string name;
    std::vector<ClientOrder> orders;
    OrderManager orderManager;

public:
    Client();
    Client getById(int id);
    Client getByName(const std::string& givenName);
    std::vector<ClientOrder> getOrders();
    void setName(const std::string& newName);
    void addOrder(ClientOrder co);
    void updateOrder(ClientOrder co);
    void deleteOrder(ClientOrder co);
};

#endif
