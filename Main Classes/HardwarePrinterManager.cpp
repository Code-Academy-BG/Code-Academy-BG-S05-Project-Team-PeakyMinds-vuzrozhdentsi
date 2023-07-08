#include<iostream>
#include"HardwarePrinterManager.hpp"
#include "PrinterJob.h"
#include "FileManager.hpp"
#include<fstream>
#include <sstream>
#include<string>
#include "Board.hpp"
#include "Pin.hpp"
#include <cmath>
#include<vector>
#include"ElectronicComponentFactory.hpp"
#include"HardwareComponent.hpp"
#include<map>

static unsigned int HardwareComponentMeasuresInDecimal = 0;
static std::vector<unsigned int> coordinatesOfPointsOfConnections;
static std::map<unsigned int,unsigned int> binaryNumsFromMatrixxMask;
static unsigned int steps = 0;
static unsigned int pairConnectionNumber = 49;

void HardwarePrinterManager::getHardwareComponentModel(const std::string& hardwareComponentModel)
{
    std::string line;
    std::string hardwareComponentId;
    bool isMachineFormatReached = false;
    std::fstream hardwareLibrary;
   hardwareLibrary.open ("Hardware Componentes Library.txt");
  if ( hardwareLibrary.is_open())
  {
    while (std::getline ( hardwareLibrary,line) )
    {
      
    
        std::cout << line;
      
      
      
    }
    hardwareLibrary.close();
  }

  else std::cout << "Unable to open file"; 
    

}

std::vector<PrinterJob> HardwarePrinterManager::getComponentRequests()
{
   std::string line;
   std::fstream file;
   std::vector<PrinterJob> printerRequests;
   std::string word;
   std::string hardwareComponentModel;
   FileManager fm("");
   fm.setFilename("print_jobs.txt");
   int countOfComponentsToPrint = 0;
    file.open("print_jobs.txt");
   if (file.is_open())
   {
    while (std::getline(file,line))
    {
      std::stringstream ss(line);
       ss >> hardwareComponentModel;
       ss >> word;
      
       countOfComponentsToPrint = stoi(word);
      PrinterJob printerJob(hardwareComponentModel,countOfComponentsToPrint);
    
      printerRequests.push_back(printerJob);
    }
  
    file.close();
   }
   
   
  
   
   
   return printerRequests;
}

unsigned int get16BitBinNumInDecimal(int a, int b)
{
   return (a << 8) | b;
}
void HardwarePrinterManager::cutBoardToFitHardwareComponent(HardwareComponent& hardwareComponent)
{
  
   
   //Board board("board1", 16, 16);
   Board board(16, 16);
   std::cout << hardwareComponent.getId() << std::endl;
   board.printBoard();
  int height = 7;
  int width = 11;
  board.setHeight(7);
  board.setWidth(11);
  //hardwareComponent.setBoard(board);
  std::cout << std::endl << "----------------- STEP 0: Cut board" << std::endl;

  HardwareComponentMeasuresInDecimal = get16BitBinNumInDecimal(height,width);
  std::cout << hardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal  << std::endl;
  board.printBoard();
}

void printBoardWithConnection(std::pair<Pin,Pin> connection,Board board)
{
  
  int height = board.getHeight();
  int width = board.getWidth();
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      if (((i == connection.first.getPoint().getY()) && (j == connection.first.getPoint().getX()))
       || ((i == connection.second.getPoint().getY()) && (j == connection.second.getPoint().getX())))
      {
        std::cout << '1';
      }
      else
      {
        std::cout << '*';
      }
    }
    std::cout << std::endl;
  }
}

void HardwarePrinterManager::printConnectionsBetweenPins(HardwareComponent hardwareComponent)
{
   Board board = hardwareComponent.getBoard();
  
   //board.printBoard();
   std::vector<ElectronicConnection> elConnections = hardwareComponent.getConnections();

   int size = elConnections.size();
   int i;
   for (i = 0; i <size ; i++)
   {
     std::pair<Pin,Pin> connection = elConnections[i].getPinConnection();
     std::cout << std::endl
               << "----------------- STEP" << ++steps << ": Connection "<< i << std::endl;
               std::cout << hardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
              coordinatesOfPointsOfConnections.push_back(get16BitBinNumInDecimal(connection.first.getPoint().getX(),connection.first.getPoint().getY()));
              coordinatesOfPointsOfConnections.push_back(get16BitBinNumInDecimal(connection.second.getPoint().getX(), connection.second.getPoint().getY()));
              for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
              {
                std::cout << coordinatesOfPointsOfConnections[j] << ' ';
              }
              std::cout << std::endl;
              
              printBoardWithConnection(connection, board);
   }
   
}
void printMatrix(std::vector<std::vector<char>>& matrixMask)
{
  
  
   for (int i = 0; i < matrixMask.size(); i++)
   {
              std::vector<char> vec = matrixMask[i];
            
              for (int j = 0; j < matrixMask[i].size(); j++)
              {
                
                std::cout << vec[j];
                // std::cout << '-';
              }
             std::cout << std::endl;
   }
}

std::vector<std::vector<char>> InitializeMatrixMask(const Board &board)
{
   
    int height = board.getHeight();
   int width = board.getWidth();
   std::vector<std::vector<char>> matrixMask;

   for (int i = 0; i < height; i++)
   {
    std::vector<char> vec;

     for (int j = 0; j < width; j++)
     {
      vec.push_back('*');
              
                // std::cout << vec[j];
    }
             
       matrixMask.push_back(vec);
             
    }
      std::cout << matrixMask.size();

      return matrixMask;
}

void fillUpMatrixMask(Board board, ElectronicComponent &elcomp, std::vector<std::vector<char>>& matrixMask)
{
  int cols = board.getWidth();
  int rows = board.getHeight();
  Point startingPoint = elcomp.getStartingPosition();
  int rotation = elcomp.getRotation();
  int rot = 0;
  if (rotation == 1)
  {
    rot = 0;
  }
  else{
    rot = 90;
  }
  
  elcomp.rotateThePins(rot);
  int elcompHeight = elcomp.getHeight();
  int elcompWidth = elcomp.getWidth();

  int x = startingPoint.getX();
  int y = startingPoint.getY();
  std::cout << std::endl
            << elcompHeight << ' ' << elcompWidth << std::endl;
  for (int i = y; i < rows; i++)
  {
    for (int j = x; j < cols; j++)
    {
      if ((i < elcompHeight + y && j < elcompWidth + x) || (i > elcompHeight + y && j > elcompWidth + x))
      {
        matrixMask[i][j] = '1';
      }
    }
  }
}

void saveBinaryNumsFromMatrixMask(std::vector<std::vector<char>> &matrixMask)
{

  unsigned char num = 0;
  unsigned int counter = 0;
  unsigned int i;
  unsigned int j;
  unsigned int key = 1;
  const unsigned int numberOfBitsInNum = 8;
  for (i = 0; i < matrixMask.size(); i++)
  {
    unsigned int size = matrixMask[i].size();

    for (j = 0; j < size; j++)
    {
      if (matrixMask[i][j] == '1')
      {
        num |= 1;
        num <<= 1;
        counter++;
     
        if (j == (size - 1))
        {
         
          for (int k = 0; k < numberOfBitsInNum - counter - 1; k++)
          {
            num <<= 1;
          }
          
          binaryNumsFromMatrixxMask[key] = (unsigned int)num;
          key++;
          num = 0;
        }
      }
      else if (matrixMask[i][j] == '*' && matrixMask[i][j+1] == '1')
      {
        binaryNumsFromMatrixxMask[key] = (unsigned int)num;
        key++;
       
        num = 0;
        
        counter = 0;
      }
    }
    num = 0;
    counter = 0;
  }
 
  std::cout << num << std::endl;
}

void printBinaryNumsFromMatrixxMask()
{
   std::map<unsigned int, unsigned int>::iterator it = binaryNumsFromMatrixxMask.begin();

   while (it != binaryNumsFromMatrixxMask.end())
   {
    std::cout << it->second << ' ';
    ++it;
    std::cout << it->second << std::endl;
    ++it;
   }
}   
 void HardwarePrinterManager::printComponentsMask(HardwareComponent &HardwareComponent, std::vector<std::vector<char>> &matrixMask)
{
   
   std::cout << matrixMask.size();
   const Board &board = HardwareComponent.getBoard();
   std::cout << "----------------- STEP 3: COMPONENTS MASK - ";
   int size = HardwareComponent.getComponents().size();
   HardwareComponent::ElectronicComponentContainer elcomps = HardwareComponent.getComponents();
  
   std::cout << HardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
   for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
   {
      std::cout << coordinatesOfPointsOfConnections[j] << ' ';
   }
   std::cout << std::endl;

   for (int i = 0; i <size ; i++)
   {
      fillUpMatrixMask(board, *elcomps[i], matrixMask);
   }
   printMatrix(matrixMask);
   saveBinaryNumsFromMatrixMask(matrixMask);
   printBinaryNumsFromMatrixxMask();
  

   // fillUpMatrixMask(HardwareComponent.getBoard(), *(elcomps[0]));
}

void fillTheMatrixWithZerosInTheElCompPositions(std::vector<std::vector<char>> &matrixMask,HardwareComponent& hc)
{

   std::cout << "----------------- STEP 4: COMPONENTS - ";
   std::vector<std::shared_ptr<ElectronicComponent>> components = hc.getComponents();
   for (int i = 0; i < components.size() ; i++)
   {
     std::cout << components[i]->getId() << ' ';
   }
   std::cout << std::endl;
   std::cout << hc.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
  
   
   for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
   {
     std::cout << coordinatesOfPointsOfConnections[j] << ' ';
   }

   std::cout << std::endl;
   std::cout << hc.getId() << std::endl;
    for (int i = 0; i < matrixMask.size(); i++)
   {
      int size = matrixMask[i].size();
      for (int j = 0; j < size; j++)
      {
        if (matrixMask[i][j] == '1')
        {
          matrixMask[i][j] = '0';
        }
        
      }
      
    }
    


}

void placeConnectionPinsOnMatrix(HardwareComponent &HardwareComponent, std::vector<std::vector<char>> &matrixMask)
{
    std::vector<ElectronicConnection> connections = HardwareComponent.getConnections();
    for (int i = 0; i < connections.size(); i++)
    {
       Pin pin1 = connections[i].getPinConnection().first;
       Pin pin2 = connections[i].getPinConnection().second;
      // std::cout << "pin1: " << pin1.getPoint().getX() << ' ' << pin1.getPoint().getY() << std::endl;
      // std::cout << "pin2: " << pin2.getPoint().getX() << ' ' << pin2.getPoint().getY() << std::endl;
       matrixMask[pin1.getPoint().getY()][pin1.getPoint().getX()] = (char)(pin1.getId() + 48);
       matrixMask[pin2.getPoint().getY()][pin2.getPoint().getX()] = (char)(pin2.getId() + 48);
        }
    
}

void HardwarePrinterManager::printFinalResults(HardwareComponent &HardwareComponent, std::vector<std::vector<char>> &matrixMask)
{
    std::cout << "----------------- STEP 5: FINAL RESULT FROM BIT IN ALL 3 FORMATS" << std::endl << std::endl;
    std::cout << "id: " << HardwareComponent.getId() << std::endl;
    std::cout << "width: " << HardwareComponent.getBoard().getWidth() << std::endl;
    std::cout << "height: " << HardwareComponent.getBoard().getHeight() << std::endl;
    std::cout << "components: " << std::endl;
    std::vector<std::shared_ptr<ElectronicComponent>> components = HardwareComponent.getComponents();
    int size = components.size();
    for (int i = 0; i <size ; i++)
    {
      std::cout << components[i]->getId() << ": (" << components[i]->getStartingPosition().getX() << ',' << components[i]->getStartingPosition().getY()
      << ')' << components[i]->getRotation() << std::endl;
    }
    std::cout << "connections: ";
    std::cout << std::endl;
    std::vector<ElectronicConnection> connections = HardwareComponent.getConnections();
    placeConnectionPinsOnMatrix(HardwareComponent, matrixMask);
    printMatrix(matrixMask);
}
void HardwarePrinterManager::runASAPMLBit()
{
   //Board board("board1", 16, 16);
   Board board(16, 16);
   Point point(0,0);
   Point point2(8,0);
   Pin pin1(2, 1, 1);
   Pin pin2(1, 3, 1);
   Pin pin3(1, 5, 1);
   Pin pin4(1, 9, 3);
   Pin pin5(2, 9, 1);
   // ElectronicComponent* ec1 = new ElectronicComponent("2N3904",3,7,0,point);
   ElectronicComponent ec1("2N3904", 3, 7, 0, point);
  ec1.setRotation(1);
   ec1.addPin(1, 1);
   ec1.addPin(3, 1);
   ec1.addPin(5, 1);
   ElectronicComponent ec2("2N3905", 3, 7, 1, point2);
   ec2.setRotation(2);
   //ElectronicConnection elconn(ec1, pin3, ec2, pin4);
   //ElectronicConnection elconn2(ec1, pin1, ec2, pin5);
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
   std::vector<std::shared_ptr<ElectronicComponent>> components;
   std::vector<ElectronicConnection> connections;
   std::shared_ptr<ElectronicComponent> ptr_ec1 = std::make_shared<ElectronicComponent>(ec1);
   std::shared_ptr<ElectronicComponent> ptr_ec2 = std::make_shared<ElectronicComponent>(ec2);

   components.push_back(ptr_ec1);
   components.push_back(ptr_ec2);
   //connections.push_back(elconn);
   //connections.push_back(elconn2);
   HardwareComponent hc("id", board, components, connections);
   // hc.addElectronicComponent(ec1, point, 0);
   // hc.addElectronicComponent(ec2, point, 1);
   //hc.addConnection(ec1, pin3, ec2, pin4);

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
   cutBoardToFitHardwareComponent(hc);

   printConnectionsBetweenPins(hc);
   std::cout << "Test" << std::endl;
   std::cout << "Test" << std::endl;
   std::cout << "Test" << std::endl;
   static std::vector<std::vector<char>> matrixMask = InitializeMatrixMask(hc.getBoard());
   
   printComponentsMask(hc, matrixMask);
   fillTheMatrixWithZerosInTheElCompPositions(matrixMask,hc);
   printMatrix(matrixMask);
  
  
  printFinalResults(hc, matrixMask);
   
}
