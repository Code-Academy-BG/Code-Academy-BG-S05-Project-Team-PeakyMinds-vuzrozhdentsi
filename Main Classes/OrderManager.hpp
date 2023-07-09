#ifndef ORDERMANAGER_HPP
#define ORDERMANAGER_HPP
 
#include <string>
#include <iostream>
#include <vector>
#include "ClientOrder.hpp"
#include "FileManager.hpp"
#include <chrono>
#include <random>
#include <fstream>
#include <functional>
#include "HardwareComponentManager.hpp"
#include "ElectronicComponentsManager.hpp"

class OrderManager
{
public: 
    OrderManager (){};
 
    //read from std::cin(we read clientOrder)
    void addOrder(); 
    //when creating an order ask for client name 
 
    std::vector<ClientOrder> &getOrders(){
        return orders;
 
    };
 
    void getOrdersFromConsole();
    void getOrdersFromFile();
 
 
    void displayOrders(std::vector<ClientOrder> orders); //check containers, algorithm library lection, sorting and lambda
    
    void displayOrdersByHistory();
    void displayOrdersByPriority();
    void cancelOrder();
    //check status before canceling the order  if-else   orderId
 
    void showMenu();
 
 
 
 
private:
    static const std::string ORDERS_FILE;
    std::vector<ClientOrder> orders;
 
    //create order id in hex format(new function), create a random generator for the id(chrono ms)
    std::string generateRandomId(); // Function declaration for random ID generation
};
#endif  