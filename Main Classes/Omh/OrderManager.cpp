#include "OrderManager.hpp"
const std::string OrderManager::ORDERS_FILE = "orders.txt";
// Stream operator overload for displaying a ClientOrder object
//std::ostream &operator<<(std::ostream &os, const ClientOrder &order)
std::string generateRandomId()
{
    // Generate a random number using <chrono> for the seed
    auto currentTime = std::chrono::system_clock::now();
    auto seed = currentTime.time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<uint64_t> distribution(0, std::numeric_limits<uint64_t>::max());
    uint64_t randomNumber = distribution(generator);
    // Convert the random number to hexadecimal format
    std::string randomId = std::to_string(randomNumber);
    randomId = "0x" + randomId; // Add "0x" prefix to indicate hexadecimal format

    return randomId;
}

// void checkInput() // проверка за валидност на входа
// {
//     if (std::cin.fail()) // if the previous extraction failed,
//     {
//         std::cin.clear();                                                   // reset the state bits back to goodbit so you can use ignore
//         std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the rest of the line
//     }
// }

void OrderManager::showMenu()
{
    int choice;
    do
    {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Order\n";
        std::cout << "2. Display Orders\n";
        std::cout << "3. Display Orders by Priority\n";
        std::cout << "4. Cancel Order\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            //Not implemented
            //addOrder(ORDERS_FILE);
            break;
        case 2:
            displayOrdersByHistory();
            break;
        case 3:
            displayOrdersByPriority();
            break;
        case 4:
            // first see all the orders then delete
            cancelOrder();
            break;
        case 5:
            std::cout << "Exiting the program...\n";
            break;
        default:
            std::cout << "Invalid choice. Try again.\n";
            break;
        }
    } while (choice != 5);
}

/* void OrderManager::addOrder()
{
    int choice;
    std::cout << "Add Order:\n";
    std::cout << "1. Enter information in the console\n";
    std::cout << "2. Read information from a file\n";
    std::cout << "Enter your choice: ";
    std::cin >> choice;
​
    if (choice == 1)
    {
        getOrder();
    }
    else if (choice == 2)
    {
        getOrdersFromFile();
    }
    else
    {
        std::cout << "Invalid choice. Order not added.\n"; // option 3 for cancel \make them type again
        return;
    }
​
    std::ofstream outputFile("orders.txt", std::ios::app);
    if (!outputFile)
    {
        std::cout << "Failed to open output file.\n";
        return;
    }
​
    // how do i print them?
    outputFile << "Client Name: ";
    outputFile << "Order ID: ";
    outputFile << "Width: ";
    outputFile << "Height: ";
​
    outputFile << "Components:\n";
    const auto &components = order.getComponents();
    for (const auto &component : components)
    {
        outputFile << "components: " << component.first << "\n";
        outputFile << component.second.first << "\n";
        outputFile << component.second.second << "\n";
    }
​
    outputFile << "connections:\n";
    const auto &connections = order.getConnections();
    for (const auto &connection : connections)
    {
        outputFile << connection.first << "\n";
        outputFile << connection.second << "\n";
    }
​
    outputFile << "-------------------------\n";
    outputFile.close();
​
    std::cout << "Order added successfully.\n";
} 

/* void OrderManager::getOrder()
{
    std::string orderInfo = "";
​
    std::string clientName = "";
    std::string componentId = "";
    int width = 0;
    int height = 0;
    // can use map instead of pair
    std::vector<std::pair<std::string, std::pair<int, int>>> components;
    std::vector<std::pair<double, double>> connections;
​
    while (!std::getline(std::cin, orderInfo, ':').eof())
    {
        std::istringstream lineStream(orderInfo);
        std::string key, value;
​
        // how to get the lines to print w/o whitespace
​
        if (orderInfo == "client")
        {
            std::cin>>clientName;
        }
        else if (orderInfo == "id")
        {
            std::cin>>componentId;
        }
        else if (orderInfo == "width")
        {
            std::cin>>width;
        }
        else if (orderInfo == "height")
        {
            std::cin>>height;
        }
        else if (orderInfo == "components")
        {
            while (std::getline(ss, line, ','))
            {
                // push_back the components
            }
        }
    }
​
    if (orderId.empty())
    {
        orderId = generateRandomId();
    } 
​
    int priorityChoice;
    std::cout << "Select priority:\n";
    std::cout << "1. High\n";
    std::cout << "2. Normal\n";
    std::cout << "Enter your choice: ";
    std::cin >> priorityChoice;
​
    ClientOrder::Priority priority;
    if (priorityChoice == 1)
    {
        priority = ClientOrder::Priority::HIGH;
    }
    else if (priorityChoice == 2)
    {
        priority = ClientOrder::Priority::NORMAL;
    }
    else
    {
        // modify later cancel and add the priorities again again
        std::cout << "Invalid priority choice. Order not added.\n";
        return;
    }
​
    // Created a new ClientOrder object with the updated constructor
    ClientOrder order;
    order.setClientName(clientName);
    order.setPriority(priority);
​
    orders.push_back(order);
​
    std::cout << "Order added successfully.\n";
} */

void OrderManager::addOrder(){
    std::ofstream orderTXTfile(ORDERS_FILE);

    if (!orderTXTfile.is_open()) {
        std::cout << "Can't open " << ORDERS_FILE << " .\n";
        return;
    }


    std::ifstream fileWithCfgOrders("test_orders.txt");

    std::string line;
    while (std::getline(std::cin, line) || std::getline(fileWithCfgOrders, line)) {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string data = line.substr(colonPos + 1);
            orderTXTfile << data << '\n';
        }
    }

    fileWithCfgOrders.close();

    orderTXTfile.close();

    std::cout << "Orders are correctly add in " << ORDERS_FILE << " .\n";
}

void OrderManager::getOrdersFromFile()
{
    FileManager fm(ORDERS_FILE);
    while(!fm.get().eof())
    {
        orders.emplace_back(ClientOrder(fm.get()));
    }
}

void OrderManager::displayOrders(const std::vector<ClientOrder>& orders)
{
    if (orders.empty())
    {
        std::cout << "No orders to display.\n";
        return;
    }

    std::cout << "Orders:\n";
    for (const auto &order : orders)
    {                                     // how?
        std::cout << "Client Name: "; // TODO clientName
        std::cout << "Order ID: " <<order.getId() ;    // getId

        std::cout << "Components:\n";
        const auto &components = order.getHardwareComponents();
        for (const auto &component : components)
        {
            std::cout << component<<' ';
        }

        std::cout << "-------------------------\n";
    }
}

void OrderManager::displayOrdersByHistory()
{
    displayOrders(this->orders);
}
void OrderManager::displayOrdersByPriority()
{
    int priorityChoice;
    std::vector<ClientOrder> orderedOrders = orders;

    std::cout << "Select priority:\n";
    std::cout << "1. High\n";
    std::cout << "2. Normal\n";
    std::cout << "Enter your choice: ";
    std::cin >> priorityChoice;

    std::function priorityPredicate = [](const ClientOrder& o1, const ClientOrder& o2) {return o1.getStatusAsInt() < o2.getStatusAsInt();};

    ClientOrder::Priority priority;
    if (priorityChoice == 1)
    {
        priority = ClientOrder::Priority::HIGH;
    }
    else if (priorityChoice == 2)
    {
        priority = ClientOrder::Priority::NORMAL;
        priorityPredicate = [](const ClientOrder& o1, const ClientOrder& o2) {return o1.getStatusAsInt() > o2.getStatusAsInt();};

    }
    else
    {
        std::cout << "Invalid priority choice.\n";
        return;
    }

    std::stable_sort(orderedOrders.begin(), orderedOrders.end(), priorityPredicate);
    displayOrders(orderedOrders);
}

void OrderManager::cancelOrder()
{

    int orderId = 0;
    std::cout << "\nPlease enter order ID for Cancellation:";
    std::cin >> orderId;
    //checkInput();

    for (auto iter = orders.begin(); iter != orders.end(); ++iter)
    {
        if (iter->getId() == orderId)
        {
            ClientOrder::Status status = iter->getStatus();
            if (status == ClientOrder::Status::UNPROCESSED || status == ClientOrder::Status::PENDING)
            {
                orders.erase(iter);
                std::cout << "Order with ID " << orderId << " is cancelled.\n";
            }
            else
            {
                std::cout << "Order with ID " << orderId << " cannot be cancelled. It is in progress or completed.\n";
            }
            return;
        }
    }

        /* int x{0}, y{0};
        bool isX{true}, isY{false}, isPoint{false};
        std::string num{""};
​
        for (size_t i = 0; i < orderInfo.size(); i++)
        {
            if (std::isdigit(orderInfo[i]))
            {
                num += orderInfo[i];
            }
​
            if ((std::ispunct(orderInfo[i]) || (i == orderInfo.size() - 1)) && !num.empty())
            {
                if (isX)
                {
                    isY = true;
                    isX = false;
                    x = std::stoi(num);
                    num.clear();
                    continue;
                }
                if (isY)
                {
                    isPoint = true;
                    isY = false;
                    y = std::stoi(num);
                    num.clear();
                    if (i != orderInfo.size() - 1)
                    {
                        continue;
                    }
                }
            }
            if (isPoint)
            {
                isX = true;
                isPoint = false;
                ec.addPin(x,y);
                num.clear();
            }
        }
    }
    return s; */
}