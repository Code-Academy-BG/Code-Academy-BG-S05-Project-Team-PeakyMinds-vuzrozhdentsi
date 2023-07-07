#include"FileManager.hpp"
#include"HardwareComponent.hpp"
#include"ClientOrder.hpp"
#include<vector>
#include<set>
#include<queue>
#include<map>
#include <memory>
// IMPORTANT
// This class is only committed and pushed to repo as per CA request for visibility on the progress. 

class Volt
{
private:
    static const std::string PRINT_JOB_FILE;
    static const std::string INVENTORY_FILE;
    static const std::string CLIENT_ORDERS_FILE;
    static const std::string PRODUCTION_FILE;
    static const std::string HISTORY_FILE;

    using hardwareComponentID = std::string;
    using electronincComponentID = std::string;
    using quantity = unsigned int;
    
    std::vector<ClientOrder> ordersFromClient; // maybe priority queue DOWNLOADABLE from client_orders.txt
    std::map<hardwareComponentID, quantity> completedHardwareComponents; //completed requests from production. DOWNLOADABLE from production.txt to be matched with client order and completed order to be logged
    std::map<electronincComponentID, quantity> electronicComponentsOnStock; //ordersFromElectronicComponentInventory; DOWNLOADABLE from inventory.txt
    std::map<hardwareComponentID, quantity>  pendingHardwareComponentsForPrinting; // request for printing DOWNLOADABLE from print_job.txt and updated with available components from new orders
    std::map<electronincComponentID, quantity> electronicComponentsForAdditionalPurchasing; //ordersForElectronicComponentInventory additional quantities above the minimum; CREATED ON THE SPOT
    std::vector<ClientOrder> ordersForHistory; // maybe priority queue filtered by status CREATED ON THE SPOT
    std::map<int, std::vector<ElectronicComponent>> pendingOrdersWithMissingComponents;
    // making Volt Singleton
    static std::unique_ptr<Volt> voltPtr;
    Volt();

    void getClientOrders(); 
    void getPendingRequestsForPrint(); 
    void getInventory(); 
    void getProduction(); 
    void updateClientOrders(); 
    void updateProduction();
    void updateInventory(); 
    void updatePendingRequestsForPrint();
    void processingUnprocessedOrdersForPrinting(ClientOrder & order);
    void processingPendingOrdersForPrinting(ClientOrder & order);
    void processingInProgressOrdersFromProduction(ClientOrder & order);
public:
    void run();
    static Volt* get(){
        if(!voltPtr){
            voltPtr = std::unique_ptr<Volt>(new Volt());
        }
        return voltPtr.get();
    }
    Volt(const Volt&) =delete;
    Volt(Volt&&) =delete;
    Volt& operator=(const Volt&) =delete;
    Volt& operator=(Volt&&) = delete;
    ~Volt();
};

