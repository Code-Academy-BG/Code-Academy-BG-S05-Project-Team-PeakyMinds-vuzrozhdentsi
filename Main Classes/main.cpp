// #include "HardwareComponent.hpp"
#include "Board.hpp"
#include "Point.hpp"
#include "Pin.hpp"
#include "HardwareComponent.hpp"
#include "HardwarePrinterManager.hpp"
#include <iostream>
#include<vector>
int main()
{
   /* Board board;
    Point point;
    Pin pin;
    HardwareComponent hc{};
    std::cout<< board.getHeight() << '\n';
    std::cout<< point.toString() << '\n';
    std::cout<< pin.toMachineLevelFormatString() << '\n';
    std::cout<< pin.toString() << '\n';
    std::cout<< hc.toMachineLevelFormatSting() << '\n';
    std::cout<< hc.toDecsriptionFormatSting() << '\n';
    */
   HardwarePrinterManager hwp;
   std::vector<PrinterJob> vec = hwp.getComponentRequests();
  
   for (int i = 0; i < vec.size(); i++)
   {
     std::cout << vec[i].toString();
   }
   
    return 0;
}
