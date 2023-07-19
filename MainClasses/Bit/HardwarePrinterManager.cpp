#include<iostream>
#include"HardwarePrinterManager.hpp"
#include "..\srcCommon\PrinterJob.h"
#include "..\srcCommon\FileManager.hpp"
#include<fstream>
#include <sstream>
#include<string>
#include "..\srcCommon\Board.hpp"
#include "..\srcCommon\Pin.hpp"
#include <cmath>
#include<vector>
#include"..\srcCommon\ElectronicComponentFactory.hpp"
#include"..\srcCommon\HardwareComponent.hpp"
#include<map>
#include <chrono>
#include <thread>
#include <windows.h>
#include "..\Lib\HardwareComponentManager.hpp"
#include "..\Lib\ElectronicComponentsManager.hpp"

static unsigned int HardwareComponentMeasuresInDecimal = 0;
static std::vector<unsigned int> coordinatesOfPointsOfConnections;
static std::map<unsigned int,unsigned int> binaryNumsFromMatrixxMask;
static unsigned int steps = 0;
static unsigned int pairConnectionNumber = 49;
static std::fstream productionFile("../textFiles/production.txt");
void printBoard(Board board)
{
 int height = board.getHeight();
 int width = board.getWidth();
  for (int i = 0; i < height; i++)
  {
    productionFile << '\n';
    for (int j = 0; j < width; j++)
    {
      productionFile << '*';
    }
  }
  productionFile << std::endl;
}
HardwareComponent& HardwarePrinterManager::getHardwareComponentModel(const std::string &hardwareComponentModel)
{
  HardwareComponentsManager hcm;
  HardwareComponent hc = hcm.getHardwareComponent(hardwareComponentModel);
  return hc;
}

std::vector<PrinterJob> HardwarePrinterManager::getComponentRequests()
{
   std::string line;
   std::fstream file;
   std::vector<PrinterJob> printerRequests;
   std::string word;
   std::string hardwareComponentModel;
  //  FileManager fm("../textFiles/print_jobs.txt");
  //  fm.setFilename("../textFiles/print_jobs.txt");
   int countOfComponentsToPrint = 0;
    file.open("../textFiles/print_jobs.txt");
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
void delete_line(const char *file_name, int n)
{
   // open file in read mode or in mode
   std::ifstream is(file_name);

   // open file in write mode or out mode
   std::ofstream ofs;
   ofs.open("temp.txt", std::ofstream::out);

   // loop getting single characters
   char c;
   int line_no = 1;
   while (is.get(c))
   {
    // if a newline character
    if (c == '\n')
      line_no++;

    // file content not to be deleted
    if (line_no != n)
      ofs << c;
   }

   // closing output file
   ofs.close();

   // closing input file
   is.close();

   // remove the original file
   remove(file_name);

   // rename the file
   rename("temp.txt", file_name);
}

unsigned int get16BitBinNumInDecimal(int a, int b)
{
   return (a << 8) | b;
}
void HardwarePrinterManager::cutBoardToFitHardwareComponent(HardwareComponent& hardwareComponent)
{
  
   
   //Board board("board1", 16, 16);
   Board board(16, 16);
   productionFile << hardwareComponent.getId() << std::endl;
   printBoard(board);
  int height = 7;
  int width = 11;
  board.setHeight(7);
  board.setWidth(11);
  hardwareComponent.setBoard(board);
  productionFile << std::endl
                 << "----------------- STEP 0: Cut board" << std::endl;

  HardwareComponentMeasuresInDecimal = get16BitBinNumInDecimal(height,width);
  productionFile << hardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
  printBoard(board);
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
        productionFile << '1';
      }
      else
      {
        productionFile << '*';
      }
    }
    productionFile << std::endl;
  }
}

void HardwarePrinterManager::printConnectionsBetweenPins(HardwareComponent hardwareComponent)
{
   Board board = hardwareComponent.getBoard();
 
   //board.printBoard();
   std::vector<ElectronicConnection> elConnections = hardwareComponent.getConnections();
   productionFile << "space: " << elConnections.size() << std::endl;
   int size = elConnections.size();
   int i;
   for (i = 0; i <size ; i++)
   {
     std::pair<Pin,Pin> connection = elConnections[i].getPinConnection();
     productionFile << std::endl
                    << "----------------- STEP" << ++steps << ": Connection " << i << std::endl;
     productionFile << hardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
     coordinatesOfPointsOfConnections.push_back(get16BitBinNumInDecimal(connection.first.getPoint().getY(), connection.first.getPoint().getX()));
     coordinatesOfPointsOfConnections.push_back(get16BitBinNumInDecimal(connection.second.getPoint().getY(), connection.second.getPoint().getX()));
     for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
     {
      productionFile << coordinatesOfPointsOfConnections[j] << ' ';
              }
              productionFile << std::endl;

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

      productionFile << vec[j];
      // std::cout << '-';
              }
              productionFile << std::endl;
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
    productionFile << matrixMask.size();

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
 
  
}

void printBinaryNumsFromMatrixxMask()
{
   std::map<unsigned int, unsigned int>::iterator it = binaryNumsFromMatrixxMask.begin();

   while (it != binaryNumsFromMatrixxMask.end())
   {
    productionFile << it->second << ' ';
    ++it;
    productionFile << it->second << std::endl;
    ++it;
   }
}   
 void HardwarePrinterManager::printComponentsMask(HardwareComponent &HardwareComponent, std::vector<std::vector<char>> &matrixMask)
{
   
  
   const Board &board = HardwareComponent.getBoard();
   productionFile << "----------------- STEP 3: COMPONENTS MASK - " << std::endl;
   int size = HardwareComponent.getComponents().size();
   HardwareComponent::ElectronicComponentContainer elcomps = HardwareComponent.getComponents();

   productionFile << HardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
   for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
   {
    productionFile << coordinatesOfPointsOfConnections[j] << ' ';
   }
   productionFile << std::endl;

   for (int i = 0; i <size ; i++)
   {
      fillUpMatrixMask(board, elcomps[i], matrixMask);
   }
   printMatrix(matrixMask);
   saveBinaryNumsFromMatrixMask(matrixMask);
   printBinaryNumsFromMatrixxMask();
  

   // fillUpMatrixMask(HardwareComponent.getBoard(), *(elcomps[0]));
}
int findNumberOfSameElcomps(HardwareComponent &HardwareComponent, const std::string &id)
{
   std::vector<ElectronicComponent> elcomp = HardwareComponent.getComponents();
   int counter = 0;
   for (int i = 0; i < elcomp.size(); i++)
   {
      if (elcomp[i].getId() == id)
      {
      counter++;
      }
   }
   return counter;
}
void fillTheMatrixWithZerosInTheElCompPositions(std::vector<std::vector<char>> &matrixMask,HardwareComponent& hc)
{

   productionFile << "----------------- STEP 4: COMPONENTS - " << std::endl;
   std::vector<ElectronicComponent> components = hc.getComponents();
   productionFile << hc.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
   for (int i = 0; i < components.size() ; i++)
   {
      productionFile << components[i].getId() << ' ';
      productionFile << findNumberOfSameElcomps(hc, components[i].getId()) << ' ' << components[i].getStartingPosition().getY()
                     << ' ' << components[i].getStartingPosition().getX() << ' ' << components[i].getRotation() << std::endl;
   }
   productionFile << std::endl;
   

   for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
   {
      productionFile << coordinatesOfPointsOfConnections[j] << ' ';
   }

   productionFile << std::endl;
   productionFile << hc.getId() << std::endl;
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

bool hasElcompGotPin(const ElectronicComponent &elcom, const Pin &pin)
{
  std::vector<Pin> pins = elcom.getPins();
     for (int i = 0; i <pins.size(); i++)
     {
       if (pins[i] == pin)
       {
        return true;
       }
       
     }
     return false;
     
}
int getNumOfPinFromElectronicComponent(const ElectronicComponent& elcom,const Pin& pin)
{
   std::vector<Pin> pins = elcom.getPins();
   for (int i = 0; i < pins.size(); i++)
   {
     if (pins[i] == pin)
     {
      return (i+1);
     }
     
   }
   return -1;
   
    
}

void printConnectionsForFinalResult(HardwareComponent &HardwareComponent)
{

   std::vector<ElectronicComponent> comps = HardwareComponent.getComponents();
   std::vector<ElectronicConnection> cons = HardwareComponent.getConnections();
   for (int i = 0; i < cons.size(); i++)
   {
    
     int numOfElcomp1 = 0;
     int numOfElcomp2 = 0;
     for (int j = 0; j < comps.size(); j++)
     {
        if (hasElcompGotPin(comps[j],cons[i].getPinConnection().first))
        {
          numOfElcomp1 = j + 1;
          break;
        }
        
     }
      for (int k = 0; k < comps.size(); k++)
      {
         if (hasElcompGotPin(comps[k], cons[i].getPinConnection().second))
         {
           numOfElcomp2 = k + 1;
           break;
         }
      }
      productionFile << '(' << numOfElcomp1 << '.' << getNumOfPinFromElectronicComponent(comps[numOfElcomp1 - 1], cons[i].getPinConnection().first)
                     << ',' << numOfElcomp2 << '.' << getNumOfPinFromElectronicComponent(comps[numOfElcomp2 - 1], cons[i].getPinConnection().second) << ')';
      if (i == cons.size() - 1)
      {
         productionFile << ' ';
      }
      else
      {
         productionFile << ", ";
      }
   }
}

void HardwarePrinterManager::printFinalResults(HardwareComponent &HardwareComponent, std::vector<std::vector<char>> &matrixMask)
{
        productionFile << "----------------- STEP 5: FINAL RESULT FROM BIT IN ALL 3 FORMATS" << std::endl
                       << std::endl;
        productionFile << "id: " << HardwareComponent.getId() << std::endl;
        productionFile << "width: " << HardwareComponent.getBoard().getWidth() << std::endl;
        productionFile << "height: " << HardwareComponent.getBoard().getHeight() << std::endl;
        productionFile << "components: " << std::endl;
        std::vector<ElectronicComponent> components = HardwareComponent.getComponents();
        int size = components.size();
        for (int i = 0; i < size; i++)
        {
       productionFile << components[i].getId() << ": (" << components[i].getStartingPosition().getX() << ',' << components[i].getStartingPosition().getY()
                      << ')' << components[i].getRotation() << std::endl;
    }
    productionFile << "connections: ";
   printConnectionsForFinalResult(HardwareComponent);
   productionFile <<  std::endl;
   for (int i = 0; i < components.size(); i++)
   {
       productionFile << components[i].getId() << ' ';
       productionFile << findNumberOfSameElcomps(HardwareComponent,components[i].getId()) << ' ' << components[i].getStartingPosition().getY()
       << ' ' << components[i].getStartingPosition().getX() << ' ' << components[i].getRotation() << std::endl;
   }
   productionFile << std::endl;
   productionFile << HardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;

   for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
   {
       productionFile << coordinatesOfPointsOfConnections[j] << ' ';
   }

   productionFile << std::endl;
   productionFile << HardwareComponent.getId() << std::endl;
   productionFile << std::endl;
   std::vector<ElectronicConnection> connections = HardwareComponent.getConnections();
   placeConnectionPinsOnMatrix(HardwareComponent, matrixMask);
   printMatrix(matrixMask);
}
void HardwarePrinterManager::runASAPMLBit()
{
   
   Board board(16, 16);
   Point point(0,0);
   Point point2(8,0);
   Pin pin1(2, 1, 1);
   Pin pin2(1, 3, 1);
   Pin pin3(1, 5, 1);
   Pin pin4(1, 9, 3);
   Pin pin5(2, 9, 1);
   
  ElectronicComponent ec1("2N3904", 7, 3, 1, point);
  ec1.setRotation(1);
   ec1.addPin2(1, 1);
   ec1.addPin2(3, 1);
   ec1.addPin2(5, 1);
   ElectronicComponent ec2("2N3905", 7, 3, 1, point2);
   ec2.addPin2(9,3);
   ec2.addPin2(9,1);
   ec2.setRotation(2);
   ElectronicConnection elconn(ec1.getBoardOrderNumber(), pin3, ec2.getBoardOrderNumber(), pin4);
   ElectronicConnection elconn2(ec1.getBoardOrderNumber(), pin1, ec2.getBoardOrderNumber(), pin5);
   
   std::vector<ElectronicComponent> components;
   std::vector<ElectronicConnection> connections;
  // std::shared_ptr<ElectronicComponent> ptr_ec1 = std::make_shared<ElectronicComponent>(ec1);
  // std::shared_ptr<ElectronicComponent> ptr_ec2 = std::make_shared<ElectronicComponent>(ec2);

   components.push_back(ec1);
   components.push_back(ec2);
   connections.push_back(elconn);
   connections.push_back(elconn2);
   HardwarePrinterManager hwp;
   HardwareComponent hc("id", board, components, connections);
   std::vector<PrinterJob> vec = getComponentRequests();
// std::map<std::string,int > production;
 for (int i = 0; i < vec.size(); i++)
 {

       HardwareComponent hc("id", board, components, connections);
       FileManager fmproductionForVolt("../textFiles/productionForVolt.txt");
       fmproductionForVolt.get() << vec[i].getHardwareComponentModel() << ' ' << vec[i].getNumberOfHardwareComponentsToBePrinted() << std::endl;
       // delete_line("textFiles/print_jobs.txt",1);

       FileManager fm1("../textFiles/cfg_bit.txt");
       std::fstream sleepFile("../textFiles/cfg_bit.txt");
       unsigned int prod_period_for_cutting_board = 1;
       unsigned int prod_period_for_printing_connections = 1;
       unsigned int prod_period_for_printing_component_mask = 1;
       unsigned int prod_period_for_printing_matrix_with_zeros = 1;
       unsigned int prod_period_for_printing_final_results = 1;
       std::string word;
       if (sleepFile.is_open())
       {
         sleepFile >> word;
         prod_period_for_cutting_board = stoi(word) * 1000;
         std::cout << prod_period_for_cutting_board << std::endl;
         sleepFile >> word;
         prod_period_for_printing_connections = stoi(word) * 1000;
         sleepFile >> word;
         prod_period_for_printing_component_mask = stoi(word) * 1000;
         sleepFile >> word;
         prod_period_for_printing_matrix_with_zeros = stoi(word) * 1000;
         sleepFile >> word;
         prod_period_for_printing_final_results = stoi(word) * 1000;
         sleepFile.close();
}

   FileManager fm("../textFiles/production.txt");
   if (productionFile.is_open())
   {
  Sleep(prod_period_for_cutting_board);
  cutBoardToFitHardwareComponent(hc);
  Sleep(prod_period_for_printing_connections);
  printConnectionsBetweenPins(hc);
  Sleep(prod_period_for_printing_component_mask);

  static std::vector<std::vector<char>> matrixMask = InitializeMatrixMask(hc.getBoard());

  printComponentsMask(hc, matrixMask);
  Sleep(prod_period_for_printing_matrix_with_zeros);
  fillTheMatrixWithZerosInTheElCompPositions(matrixMask, hc);

  printMatrix(matrixMask);
  Sleep(prod_period_for_printing_final_results);

  printFinalResults(hc, matrixMask);
  fmproductionForVolt.~FileManager();
  productionFile.close();
   }
   
 }
}
