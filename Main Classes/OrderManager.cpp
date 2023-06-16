#include "OrderManager.hpp"

void OrderManager::run() {
    std::string input;

    while (true) {
        std::cout << "Menu:\n";
        std::cout << "1. Add new order\n";
        std::cout << "2. Display orders\n";
        std::cout << "3. Display orders by priority\n";
        std::cout << "4. Cancel an order\n";
        std::cout << "5. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> input;


        if (input == "1") {
            addOrder();
        } else if (input == "2") {
            displayOrders();
        } else if (input == "3") {
            //displayOrdersByPriority();
        } else if (input == "4") {
            std::cout << "Enter order name: ";
            std::cin >> input;
            cancelOrder(input);
        } else if (input == "5") {
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }

        std::cout << std::endl;
    }
}


void OrderManager::addOrder() {
    std::ofstream file(filename, std::ios::app); 

    if (file.is_open()) {
        std::string order;
        std::cout << "Enter the order: ";
        std::cin.ignore(); // Ignore any remaining newline characters in the input buffer
        std::getline(std::cin, order);
        file << order << " - unprocessed\n"; // Marking the order as "unprocessed" !!
        file.close();
        std::cout << "Order placed successfully!\n";
    } else {
        std::cout << "Unable to open orders file.\n";
    }
}

void OrderManager::displayOrders() {
    std::ifstream inFile(filename); // read from the filename file.
    if (!inFile) {
        std::cerr << "Unable to open file for reading.\n";
        return;
    }
    if (inFile.is_open()) {
        std::cout << "Orders:\n";
        std::string line; //store each line read from the file
        //read each line from the inFile object
        while (std::getline(inFile, line)) {
            std::cout << line << std::endl;
        }
        inFile.close();
    }
}

// void OrderManager::displayOrdersByPriority() {}

void OrderManager::cancelOrder(const std::string& orderName) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        std::vector<std::string> orders; //store all the lines read from the file
        std::string line;                //store each line read from the file
        while (std::getline(inFile, line)) {
            orders.push_back(line);     // each line gets added to the file
        }
        inFile.close();

        std::ofstream outFile(filename, std::ios::app);
        if (outFile.is_open()) {
            for (const std::string& order : orders) { //iterates over each order stored in the orders vector
                std::string name;
                int orderPriority;
                std::istringstream iss(order);
                if (iss >> name >> orderPriority && name != orderName) { //
                    outFile << order << std::endl;
                }
            }
            outFile.close();
            std::cout << "Order canceled successfully!\n";
        } else {
            std::cerr << "Unable to open file for writing!\n";
        }
    } else {
        std::cerr << "Unable to open file for reading!\n";
    }
}
