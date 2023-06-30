// #include "HardwareComponent.hpp"
#include "Board.hpp"
#include "Point.hpp"
#include "Pin.hpp"
#include "HardwareComponent.hpp"
#include "HardwarePrinterManager.hpp"
#include "ElectronicComponent.hpp"
#include <iostream>
#include<vector>
int main()
{
    Board board("board1",16,16);
    Point point;
     Pin pin1(1,1,1);
    Pin pin2(1,3,1);
    Pin pin3(1,5,1);
    Pin pin4(1, 9, 3);
    Pin pin5(1, 9, 1);
    ElectronicComponent ec1("2N3904",3,7,0,point);
    ec1.addPin(1,1);
    ec1.addPin(3,1);
    ec1.addPin(5,1);
     ElectronicComponent ec2("2N3905", 3, 7, 1, point);
    ElectronicConnection elconn(ec1,pin3,ec2,pin4);
    ElectronicConnection elconn2(ec1, pin1, ec2, pin5);
    /*
        ec.printElComp();
          ec.rotateThePins(90);
          ec.printElComp();
          ec.rotateThePins(90);
          ec.printElComp();
          ec.rotateThePins(180);
          ec.printElComp();
          ec.rotateThePins(180);
          ec.printElComp();
          ec.rotateThePins(270);
          ec.printElComp();
      */
    /* ec.rotate(180);
    ec.printElComp();
    ec.rotate(270);
    ec.printElComp(); */
    std::vector<ElectronicComponent> components;
    std::vector<ElectronicConnection> connections;
    components.push_back(ec1);
    components.push_back(ec2);
    connections.push_back(elconn);
    connections.push_back(elconn2);
    HardwareComponent hc("id", board, components, connections);
    hc.addElectronicComponent(ec1, point, 0);
    hc.addElectronicComponent(ec2, point, 1);
    hc.addConnection(ec1, pin3, ec2, pin4);

    // board.printBoard();
    /* std::cout<< '\n' << board.getHeight() << '\n';
     std::cout<< point.toString() << '\n';
     std::cout<< pin1.toMachineLevelFormatString() << '\n';
     std::cout<< pin1.toString() << '\n';
     std::cout<< hc.toMachineLevelFormatSting() << '\n';
     std::cout<< hc.toDecsriptionFormatSting() << '\n';*/
    HardwarePrinterManager hwp;
    /*
    std::vector<PrinterJob> vec = hwp.getComponentRequests();

    for (int i = 0; i < vec.size(); i++)
    {
      std::cout << vec[i].toString();
    }

      std::cout<<"Pin1 to machine string:"<< pin1.toMachineLevelFormatString() << '\n';
     std::cout<<"Pin1 to string:"<< pin1.toString() << '\n';
     std::cout<<"HC to machine string:"<< hc.toMachineLevelFormatSting() << '\n';
     std::cout<<"Pin to description string:"<< hc.toDecsriptionFormatSting() << '\n';
 */

    std::cout << "Test" << std::endl;
    hwp.cutBoardToFitHardwareComponent(hc);

    hwp.printConnectionsBetweenPins(hc);
    return 0;
}
