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

static unsigned int HardwareComponentMeasuresInDecimal = 0;
static std::vector<unsigned int> coordinatesOfPointsOfConnections;
static unsigned int steps = 0;
static std::vector<std::vector<char>> matrixMask;
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
   FileManager fm;
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
  
   
   Board board("board1", 16, 16);
   std::cout << hardwareComponent.getId() << std::endl;
   board.printBoard();
  int height = 7;
  int width = 11;
  board.setHeight(7);
  board.setWidth(11);
  hardwareComponent.setBoard(board);
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
void fillUpMatrixMask(Board board,ElectronicComponent elcomp)
{
  int cols = board.getWidth();
  int rows = board.getHeight();
    for (int i = 0; i < cols; i++)
    {
      for (int j = 0; j < rows; j++)
      {
        
      }
      
    }
    

}

void HardwarePrinterManager::printComponentsMask(HardwareComponent &HardwareComponent)
{
   std::cout << "----------------- STEP 3: COMPONENTS MASK - ";
   int size = HardwareComponent.getComponents().size();
   std::vector<ElectronicComponent> elcomps = HardwareComponent.getComponents();
   for (int i = 0; i <size ; i++)
   {
     std::cout << elcomps[i].getId() << std::endl;
     std::cout << HardwareComponent.getId() << ' ' << HardwareComponentMeasuresInDecimal << std::endl;
     for (int j = 0; j < coordinatesOfPointsOfConnections.size(); j++)
     {
                std::cout << coordinatesOfPointsOfConnections[j] << ' ';
     }
     std::cout << std::endl;
   }
   
}

void HardwarePrinterManager::runASAPMLBit()
{
     HardwarePrinterManager hwp;
   std::vector<PrinterJob> vec = hwp.getComponentRequests();
   

}
