#include "Client.hpp"

// IMPORTANT
// This class is only committed and pushed to repo as per CA request for visibility on the progress. 


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
