#ifndef HARDWARE_PRINTER_MANAGER_H
#define HARDWARE_PRINTER_MANAGER_H
#include<iostream>
#include<vector>
#include "HardwareComponent.hpp"
#include "Board.hpp"
#include "PrinterJob.h"
typedef unsigned char u8;
class HardwarePrinterManager
{

    public:
	std::vector<u8> matrixMask;
	std::vector<PrinterJob> getComponentRequests();
	void getHardwareComponentModel(const std::string& hardwareComponentModel);
	Board cutBoardToFitHardwareComponent(HardwareComponent hardwareComponent);
	void printConnectionsBetweenPins(HardwareComponent hardwareComponent);
	void removeOrderFromPrintJobs(HardwareComponent hardwareComponent);
	void addNewProductToProduction(HardwareComponent hardwareComponent);
    void runASAPMLBit();
	void printHardwareComponent();
};



#endif