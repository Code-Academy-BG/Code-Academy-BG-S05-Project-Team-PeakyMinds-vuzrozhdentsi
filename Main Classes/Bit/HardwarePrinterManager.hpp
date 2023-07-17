#ifndef HARDWARE_PRINTER_MANAGER_H
#define HARDWARE_PRINTER_MANAGER_H
#include<iostream>
#include<vector>
#include "..\srcCommon\HardwareComponent.hpp"
#include "..\srcCommon\Board.hpp"
#include "..\srcCommon\PrinterJob.h"
typedef unsigned char u8;
class HardwarePrinterManager
{
	private:
	using ElectronicComponentContainer = HardwareComponent::ElectronicComponentContainer;

    public:
	std::vector<u8> matrixMask;
	std::vector<PrinterJob> getComponentRequests();
	HardwareComponent &getHardwareComponentModel(const std::string &hardwareComponentModel);
	void cutBoardToFitHardwareComponent(HardwareComponent& hardwareComponent);
	void printConnectionsBetweenPins(HardwareComponent hardwareComponent);
	void printComponentsMask(HardwareComponent &HardwareComponent, std::vector<std::vector<char>>& matrixMask);
	void printFinalResults(HardwareComponent &HardwareComponent, std::vector<std::vector<char>> &matrixMask);
	void removeOrderFromPrintJobs(HardwareComponent hardwareComponent);
	void addNewProductToProduction(HardwareComponent hardwareComponent);
    void runASAPMLBit();
	void printHardwareComponent();
};



#endif