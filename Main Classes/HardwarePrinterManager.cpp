#include<iostream>
#include"HardwarePrinterManager.hpp"
#include "PrinterJob.h"
#include "FileManager.hpp"
#include<fstream>
#include <sstream>
#include<string>

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

void HardwarePrinterManager::runASAPMLBit()
{
     HardwarePrinterManager hwp;
   std::vector<PrinterJob> vec = hwp.getComponentRequests();
   

}
