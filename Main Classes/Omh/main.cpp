#include <iostream>
#include "OrderManager.hpp"

/*
 g++ .\main.cpp .\OrderManager.cpp ..\srcCommon\ClientOrder.cpp ..\srcCommon\HardwareComponent.cpp ..\srcCommon\ElectronicComponent.cpp ..\srcCommon\FileExceptionManager.cpp ..\srcCommon\FileManager.cpp ..\srcCommon\Board.cpp ..\srcCommon\Pin.cpp ..\srcCommon\PrinterJob.cpp ..\Lib\HardwareComponentManager.cpp ..\Lib\ElectronicComponentsManager.cpp -o main.exe
*/


int main(){
    OrderManager ordManager;
    ordManager.addOrder();
    return 0;
}