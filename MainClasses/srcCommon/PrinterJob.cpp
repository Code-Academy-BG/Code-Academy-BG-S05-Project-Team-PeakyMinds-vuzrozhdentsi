#include "PrinterJob.h"
#include<iostream>
#include<string>  


 PrinterJob::PrinterJob()
{
	
}
PrinterJob::PrinterJob(const std::string& hardwareComponent, int numberOfHardwareComponentsToBePrinted)
{
	this->hardwareComponentModel = hardwareComponent;
	this->numberOfHardwareComponentsToBePrinted = numberOfHardwareComponentsToBePrinted;
}

std::string PrinterJob::getHardwareComponentModel() const
{
	return this->hardwareComponentModel;
}
int PrinterJob::getNumberOfHardwareComponentsToBePrinted()
{
    return this->numberOfHardwareComponentsToBePrinted;

}

std::string PrinterJob::toString()
{
	std::string count = std::to_string(this->numberOfHardwareComponentsToBePrinted);
	return this->hardwareComponentModel + " " +  count + '\n';
}