#include"FileManager.hpp"
#include"HardwareComponent.hpp"
#include "HardwareComponentManager.hpp"
#include "ElectronicComponentsManager.hpp"
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
    static const std::string ELECTRONIC_COMPONENT_LIBRARY_FILE;
    static const std::string HARDWARE_COMPONENT_LIBRARY_FILE;

    static const std::string HARDWARE_COMPONENT_FOR_PRINTING_MSG;
    static const std::string INVALID_CHOICE_ERROR;
    static const std::string RUN_CHOICE_INSTRUCTIONS_MSG;
    using hardwareComponentID = std::string;
    using electronincComponentID = std::string;
    using quantity = unsigned int;
    using orderID = int;
    HardwareComponentsManager hcLibrary;
    ElectronicComponentsManager ecLibrary;
    std::vector<ClientOrder> ordersFromClient; // maybe priority queue DOWNLOADABLE from client_orders.txt
    std::map<hardwareComponentID, quantity> completedHardwareComponents; //completed requests from production. DOWNLOADABLE from production.txt to be matched with client order and completed order to be logged
    std::map<electronincComponentID, quantity> electronicComponentsOnStock; //ordersFromElectronicComponentInventory; DOWNLOADABLE from inventory.txt
    std::map<hardwareComponentID, quantity>  pendingHardwareComponentsForPrinting; // request for printing DOWNLOADABLE from print_job.txt and updated with available components from new orders
    std::map<electronincComponentID, quantity> electronicComponentsForAdditionalPurchasing; //ordersForElectronicComponentInventory additional quantities above the minimum; CREATED ON THE SPOT
    std::vector<ClientOrder> ordersForHistory; // maybe priority queue filtered by status CREATED ON THE SPOT
    std::map<orderID, std::vector<ElectronicComponent>> pendingOrdersWithMissingComponents;

    // making Volt Singleton
    static std::unique_ptr<Volt> voltPtr;
    Volt() : hcLibrary{}, ecLibrary{} {};
    bool getLibraries();
    void getClientOrders(); 
    void getPendingRequestsForPrint(); 
    void getInventory(); 
    void getProduction(); 
    void updateClientOrders(); 
    void updateProduction();
    void updateInventory(); 
    void updateHistory();
    void updatePendingRequestsForPrint();
    void processingUnprocessedOrdersForPrinting(ClientOrder & order);
    void processingPendingOrdersForPrinting(ClientOrder & order);
    void processingInProgressOrdersFromProduction(ClientOrder & order);
    void checkForNewDesigns();
    void printPrintJobs();
    void processOrders();
public:
    int run();
    static Volt& get()
    {
        if(!voltPtr){
            voltPtr = std::unique_ptr<Volt>(new Volt());
        }
        return *voltPtr;
    }
    Volt(const Volt&) =delete;
    Volt(Volt&&) =delete;
    Volt& operator=(const Volt&) =delete;
    Volt& operator=(Volt&&) = delete;
    ~Volt();
};

