#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

#include "ClientOrder.hpp"
#include "OrderManager.hpp"

// Stream operator overload for displaying a ClientOrder object
std::ostream &operator<<(std::ostream &os, const ClientOrder &order)
{
    os << "Order ID: " << order.getId() << std::endl;

    static const std::unordered_map<ClientOrder::Status, std::string> statusStrings = {
        {ClientOrder::Status::UNPROCESSED, "UNPROCESSED"}};

    // Converting the status to string representation
    const auto it = statusStrings.find(order.getStatus());
    if (it != statusStrings.end())
    {
        os << "Status: " << it->second << std::endl;
    }
    else
    {
        os << "Status: Unknown" << std::endl;
    }

    os << "Priority: " << static_cast<int>(order.getPriority()) << std::endl;
    os << "Hardware Components: ";
    const std::vector<HardwareComponent> &hardwareComponents = order.getHardwareComponents();
    for (const auto &component : hardwareComponents)
    {
        os << component.getId() << ", ";
    }
    os << std::endl;
    os << "Electronic Components: ";
    const std::vector<ElectronicComponent> &electronicComponents = order.getElectronicComponents();
    for (const auto &component : electronicComponents)
    {
        os << component.getId() << ", ";
    }
    os << std::endl;

    return os;
}

// Input stream operator overload for reading a ClientOrder::Priority object
std::istream &operator>>(std::istream &is, ClientOrder::Priority &priority)
{
    int priorityValue;
    is >> priorityValue;
    priority = static_cast<ClientOrder::Priority>(priorityValue);
    return is;
}

// Inputing stream operator overload for reading a ClientOrder object
std::istream &operator>>(std::istream &is, ClientOrder &order)
{
    int id;
    int status;
    int priority;
    std::vector<HardwareComponent> hardwareComponents;
    std::vector<ElectronicComponent> electronicComponents;

    is >> id;
    is >> status;
    is >> priority;

    order.setId(id);
    order.setStatus(static_cast<ClientOrder::Status>(status));
    order.setPriority(static_cast<ClientOrder::Priority>(priority));
    order.setHardwareComponents(hardwareComponents);
    order.setElectronicComponents(electronicComponents);

    return is;
}

void OrderManager::addOrder(const std::string &filename)
{
    std::ofstream file(filename, std::ios::app);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    int id;
    int orderStatus; // Changed variable name from "status" to "orderStatus"
    int priority;
    std::vector<HardwareComponent> hardwareComponents;
    std::vector<ElectronicComponent> electronicComponents;

    std::cout << "Enter order ID: ";
    std::cin >> id;

    ClientOrder::Status status = ClientOrder::Status::UNPROCESSED;

    std::cout << "Enter order priority (1 for HIGH, 2 for NORMAL): ";
    std::cin >> priority;

    // TODO: Read hardware and electronic components from blueprint file or the console

    // Creating the client order
    ClientOrder order;
    order.setId(id);
    order.setStatus(static_cast<ClientOrder::Status>(orderStatus)); // Changed variable name from "status" to "orderStatus"
    order.setPriority(static_cast<ClientOrder::Priority>(priority));
    order.setHardwareComponents(hardwareComponents);
    order.setElectronicComponents(electronicComponents);

    // Saveing the order to the file
    file << order << std::endl;
    file.close();

    std::cout << "Order placed successfully." << std::endl;
}

void OrderManager::displayOrders(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::vector<ClientOrder> orders;
    ClientOrder order;
    while (file >> order)
    {
        orders.push_back(order);
    }
    file.close();

    // Sort orders by their order of placement
    std::sort(orders.begin(), orders.end(), [](const ClientOrder &a, const ClientOrder &b)
              { return a.getId() < b.getId(); });

    // Displaying the orders
    for (const auto &order : orders)
    {
        std::cout << order << std::endl;
    }
}

void OrderManager::displayOrdersByPriority(const std::string &filename, ClientOrder::Priority priority)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::vector<ClientOrder> orders;
    ClientOrder order;
    while (file >> order)
    {
        if (order.getPriority() == priority)
        {
            orders.push_back(order);
        }
    }
    file.close();

    // Sort orders by their order of placement
    std::sort(orders.begin(), orders.end(), [](const ClientOrder &a, const ClientOrder &b)
              { return a.getId() < b.getId(); });

    // Displaying the orders with the priority
    for (const auto &order : orders)
    {
        std::cout << order << std::endl;
    }
}

void OrderManager::cancelOrder(const std::string &filename, int orderId)
{
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::vector<ClientOrder> orders;
    ClientOrder order;
    while (file >> order)
    {
        if (order.getId() != orderId)
        {
            orders.push_back(order);
        }
    }
    file.close();

    std::ofstream outFile(filename);
    if (!outFile)
    {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Save the remaining orders back to the file
    for (const auto &order : orders)
    {
        outFile << order << std::endl;
    }
    outFile.close();

    std::cout << "Order canceled successfully." << std::endl;
}

int main(int argc, char *argv[])
{
    OrderManager orderManager;

    // Checks if the correct number of command-line arguments is provided
    if (argc != 3)
    {
        std::cerr << "Usage: ./OrderManager cfg_ohm.txt orders.txt\n";
        return 1;
    }

    std::string cfgOhmPath = "data/" + std::string(argv[1]);
    std::string ordersPath = "data/" + std::string(argv[2]);

    // Use cfgOhmPath and ordersPath in your code as needed

    int choice;
    do
    {
        std::cout << "1. Add new order" << std::endl;
        std::cout << "2. Display orders" << std::endl;
        std::cout << "3. Display orders by priority" << std::endl;
        std::cout << "4. Cancel order" << std::endl;
        std::cout << "5. Quit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            orderManager.addOrder(ordersPath);
            break;
        case 2:
            orderManager.displayOrders(ordersPath);
            break;
        case 3:
            ClientOrder::Priority priorityChoice;
            std::cout << "Enter priority (1 for HIGH, 2 for NORMAL): ";
            std::cin >> priorityChoice;
            orderManager.displayOrdersByPriority(ordersPath, priorityChoice);
            break;
        case 4:
            int orderId;
            std::cout << "Enter order ID to cancel: ";
            std::cin >> orderId;
            orderManager.cancelOrder(ordersPath, orderId);
            break;
        case 5:
            std::cout << "Goodbye!" << std::endl;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
        }

        std::cout << std::endl;

    } while (choice != 5);

    return 0;
}
