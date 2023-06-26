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
<<<<<<< Updated upstream
   /* Board board;
=======
    Board board("board1",3,7);
>>>>>>> Stashed changes
    Point point;
    /* Pin pin1(1,1,1);
    Pin pin2(1,3,1);
    Pin pin3(1,5,1); */

    ElectronicComponent ec("2N3904",3,7,0,point);
    ec.addPin(1,1);
    ec.addPin(3,1);
    ec.addPin(5,1);
    ec.rotate(90);
    ec.printElComp();
    ec.rotate(180);
    ec.printElComp();
    ec.rotate(270);
    ec.printElComp();
    

   /*  HardwareComponent hc{};
    hc.addElectronicComponent(ec,point,0);
    //board.printBoard();
    std::cout<< '\n' << board.getHeight() << '\n';
    std::cout<< point.toString() << '\n';
<<<<<<< Updated upstream
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
   
=======
    std::cout<<"Pin1 to machine string:"<< pin1.toMachineLevelFormatString() << '\n';
    std::cout<<"Pin1 to string:"<< pin1.toString() << '\n';
    std::cout<<"HC to machine string:"<< hc.toMachineLevelFormatSting() << '\n';
    std::cout<<"Pin to description string:"<< hc.toDecsriptionFormatSting() << '\n'; */

>>>>>>> Stashed changes
    return 0;
}
