#ifndef CONSTANT_MSG_H
#define CONSTANT_MSG_H

#include <string>

const std::string MENU = "\nMenu:\n1. Add Order\n2. Display Orders\n3. Display Orders by Priority\n4. Cancel Order\n5. Exit\nEnter your choice: ";
const std::string EXITING_MSG = "Exiting the program...\n";
const std::string INVALID_CHOICE_MSG = "Invalid choice. Try again.\n";
const std::string ORDERS_ARE_CORRECTLY_ADD = "Orders are correctly add in ";
const std::string NO_ORDER_TO_DISPLAY ="No orders to display.\n";
const std::string ORDERS = "Orders:\n";
const std::string CLIENT_NAME = "Client Name:";
const std::string ORDER_ID = "Order ID: ";
const std::string HARDWARE_ID = "Hardware ID: ";
const std::string ORDERS_LINE_DELIMITER = "-------------------------\n";
   
const std::string SELECT_PRIORITY_MENU = "Select priority:\n1. High\n2. Normal\nEnter your choice: ";
const std::string INVALID_PRIORITY_CHOICE_MSG = "Invalid priority choice.\n";

const std::string CANCELATION_MSG =  "\nPlease enter order ID for Cancellation:";
const std::string ORDER_WITH_ID = "Order with ID ";
const std::string IS_CANCELED = " is cancelled.\n";
const std::string CAN_NOT_BE_CANCEL = " cannot be cancelled. It is in progress or completed.\n";

#endif