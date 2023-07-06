#include"Volt.hpp"

Volt::Volt(){};
const std::string Volt::PRINT_JOB_FILE  = "print_jobs.txt";
const std::string Volt::INVENTORY_FILE = "inventory.txt";
const std::string Volt::CLIENT_ORDERS_FILE = "client_orders.txt";
const std::string Volt::PRODUCTION_FILE = "production.txt";
const std::string Volt::HISTORY_FILE = "history.txt";

void Volt::getPendingRequestsForPrint()
{
    FileManager fm{PRINT_JOB_FILE};
    Volt::hardwareComponentID id{""};
    while (!fm.get().eof())
    {
        fm.get()>> id >> pendingHardwareComponentsForPrinting[id];
    }    
}

void Volt::getInventory()
{
    FileManager fm{INVENTORY_FILE};
    Volt::electronincComponentID id{""};
    while (!fm.get().eof())
    {
        fm.get()>> id >> electronicComponentsOnStock[id];
    }
}

void Volt::getProduction()
{
    FileManager fm{PRODUCTION_FILE};
    Volt::hardwareComponentID id{""};
    while (!fm.get().eof())
    {
        fm.get()>> id >> completedHardwareComponents[id];
    }    
} 

void Volt::getClientOrders()
{
     FileManager fm{CLIENT_ORDERS_FILE};
    
    ClientOrder temp;
    while (!fm.get().eof())
    {
        // fm.get() >> temp;  //TODO
        ordersFromClient.emplace_back(temp);
    } 
}

void Volt::processingUnprocessedOrdersForPrinting(ClientOrder & order)
{    
    if(order.getStatus() == ClientOrder::Status::UNPROCESSED){
        bool areAllHrdwareComponentsReadyForPrinting{true};
        for (auto & hComponent : order.getHardwareComponents())
        {

            bool areAllElectronicComponentsTaken{true};
            for (auto & elComponent : hComponent.getComponents())
            {
                auto & currentElComponentID = (*elComponent).getId();
                if (electronicComponentsOnStock[currentElComponentID] > 0)
                {
                    electronicComponentsOnStock[currentElComponentID]--;
                }else{
                    areAllHrdwareComponentsReadyForPrinting =false;
                    areAllElectronicComponentsTaken = false;
                    electronicComponentsForAdditionalPurchasing[currentElComponentID]++;
                    pendingOrdersWithMissingComponents[order.getId()].push_back(currentElComponentID);
                }     
            }

            if (areAllHrdwareComponentsReadyForPrinting)
            {
                order.setStatus(ClientOrder::Status::InPROGRESS);
                for(auto iter = order.getHardwareComponents().begin(); iter != order.getHardwareComponents().end(); iter++)
                {
                    pendingHardwareComponentsForPrinting[(*iter).getId()]++;
                }
            }else{
                order.setStatus(ClientOrder::Status::PENDING);
            }               
        }
    }   
}

void Volt::processingPendingOrdersForPrinting(ClientOrder & order)
{
    if(order.getStatus() == ClientOrder::Status::PENDING){
        for(auto & elComponent : pendingOrdersWithMissingComponents[order.getId()]){
            if (electronicComponentsOnStock[elComponent.getId()] > 0)
            {
                electronicComponentsOnStock[elComponent.getId()]--;
            } 
        }
        if (pendingOrdersWithMissingComponents[order.getId()].empty())
        {
            order.setStatus(ClientOrder::Status::InPROGRESS);
            for(auto iter = order.getHardwareComponents().begin(); iter != order.getHardwareComponents().end(); iter++)
            {
                pendingHardwareComponentsForPrinting[(*iter).getId()]++;
            }
        }  
    }
}

void Volt::processingInProgressOrdersFromProduction(ClientOrder & order)
{   
    if(order.getStatus() == ClientOrder::Status::InPROGRESS){
        bool areAllComponentPresent{true};
        for (auto & hComponent : order.getHardwareComponents())
        {
            if(completedHardwareComponents[hComponent.getId()] == 0){
                areAllComponentPresent = false;
                break;
            }
        }
        
        if(areAllComponentPresent){
            for (auto & hComponent : order.getHardwareComponents())
            {
                completedHardwareComponents[hComponent.getId()]--;
            }
            ordersForHistory.push_back(order);
            order.setStatus(ClientOrder::Status::COMPLETED);
        }
    }
}

// TODO to implement shift operator for the Client Order;
// void Volt::updateClientOrders()
// {
//     FileManager fm{CLIENT_ORDERS_FILE};
//     ordersFromClient.erase( 
//         std::remove_if(ordersFromClient.begin(),ordersFromClient.end(),
//         [](ClientOrder& order){return order.getStatus() == ClientOrder::Status::COMPLETED;}), 
//         ordersFromClient.end());
//     std::for_each(ordersFromClient.begin(), ordersFromClient.end(),
//         [&](ClientOrder & order){ fm.get()<<order;})
// }

void Volt::updateProduction()
{
    FileManager fm{PRODUCTION_FILE};
    std::for_each(pendingHardwareComponentsForPrinting.begin(), pendingHardwareComponentsForPrinting.end(),
    [&](std::pair<Volt::electronincComponentID, Volt::quantity> & p)
    {fm.get()<<p.first<<' '<<p.second<<'\n';}); 
}

void Volt::updateInventory()
{
    FileManager fm{INVENTORY_FILE};
    std::for_each(electronicComponentsOnStock.begin(), electronicComponentsOnStock.end(),
    [&](std::pair<Volt::electronincComponentID, Volt::quantity> & p)
    {fm.get()<<p.first<<' '<<p.second<<'\n';});  
}

void Volt::updatePendingRequestsForPrint()
{
    FileManager fm{PRINT_JOB_FILE};
    std::for_each(pendingHardwareComponentsForPrinting.begin(), pendingHardwareComponentsForPrinting.end(),
    [&](std::pair<Volt::hardwareComponentID, Volt::quantity> & p)
    {fm.get()<<p.first<<' '<<p.second<<'\n';});  
}
void Volt::run()
{
    getInventory();
    getPendingRequestsForPrint();
    getClientOrders();
    for(auto iter = ordersFromClient.begin(); iter != ordersFromClient.end(); iter++)
    {
        switch ((*iter).getStatus())
        {
        case ClientOrder::Status::UNPROCESSED:
            processingUnprocessedOrdersForPrinting(*iter);
            break;
        case ClientOrder::Status::PENDING:
            processingUnprocessedOrdersForPrinting(*iter);
            break;
        default:
            break;
        }
    }
    
    getProduction();
    for(auto iter = ordersFromClient.begin(); iter != ordersFromClient.end(); iter++)
    {
        processingInProgressOrdersFromProduction(*iter);
    }
    //TODO update
}
