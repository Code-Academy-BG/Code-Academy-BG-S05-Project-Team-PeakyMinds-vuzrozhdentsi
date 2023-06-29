#include"FileManager.hpp"
#include"HardwareComponent.hpp"
#include"ClientOrder.hpp"
#include<vector>
#include<set>
#include<map>
// IMPORTANT
// This class is only committed and pushed to repo as per CA request for visibility on the progress. 

class Volt
{
private:
    FileManager fm;
    std::vector<ClientOrder> ordersFromClient; // maybe priority queue DOWNLOADABLE from client_orders.txt
    // std::map<Hardware component id, quantity> completedHardwareComponents; //completed requests from production. DOWNLOADABLE from production.txt to be matched with client order and completed order to be logged
    // std::map<ElectronicComponent id, quantity> electronicComponentsOnStock; ordersFromElectronicComponentInventory; DOWNLOADABLE from inventory.txt
    // std::map<Hardware component id, quantity>  pendingElectronicComponentsForPrinting; request for printing DOWNLOADABLE from print_job.txt and updated with available components from new orders
    // std::map<ElectronicComponent id, quantity> electronicComponentsForAdditionalPurchasing; ordersForElectronicComponentInventory additional quantities above the minimum; CREATED ON THE SPOT
    std::vector<ClientOrder> ordersForHistory; // maybe priority queue filtered by status CREATED ON THE SPOT
 


public:
    Volt(/* args */);
    ~Volt();
    // void loadClientOrders(Status, Priority); // open ClientOrders.txt and get orders
    void getRequestsForPrint(); // open print_jobs.txt and get number of Components to print
    void getInventory(); //get inventory.txt
    void getLibrabiesSets(); // get Libraries
    void createNewRequestsForPrint(); // check which orders are missing and for each missing  take necessaty components 
    void sendRequestForPrint(); // update print_jobs.txt with new requests (ClientOrder + Innventory Components)
    void updateInventory(); // provide new quantities to the library
    void getReadyOrders(); // read from production.txt and get ready orders
    void updateClientOrders(); // update ClientOrders.txt
    void logCompletedClientOrders(); // send client history (client name + order)
    void updateDesignLibraries(); // check for both if vector with new is not empty, update it?? shoukd volt do it?
};

Volt::Volt(/* args */)
{
}

Volt::~Volt()
{
}
