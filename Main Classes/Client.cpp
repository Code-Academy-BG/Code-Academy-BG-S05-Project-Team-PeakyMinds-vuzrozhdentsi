#include "Client.hpp"

Client::Client() {
    
}

Client Client::getById(int id) {
    
}

Client Client::getByName(const std::string& givenName) {

}
    

std::vector<ClientOrder> Client::getOrders() {
    
}

void Client::setName(const std::string& newName) {
}
    

void Client::addOrder(ClientOrder co) {
    //orderManager.addOrder();  
    orders.push_back(co);       
}

void Client::updateOrder(ClientOrder co) {
    
}

void Client::deleteOrder(ClientOrder co) {
}
