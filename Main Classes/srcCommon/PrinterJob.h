#ifndef PRINTER_JOB_H
#define PRINTER_JOB_H

#include<iostream>
#include<vector>
#include "HardwareComponent.hpp"
#include "Board.hpp"

 class PrinterJob
{
	 private:
	 std::string hardwareComponentModel;
	 int numberOfHardwareComponentsToBePrinted = 0;
	 public:
	 PrinterJob();
	 PrinterJob(const std::string& hardwareComponent, int numberOfHardwareComponentsToBePrinted);
	 std::string getHardwareComponentModel() const;
	 int getNumberOfHardwareComponentsToBePrinted();
	 std::string toString();
};

#endif
