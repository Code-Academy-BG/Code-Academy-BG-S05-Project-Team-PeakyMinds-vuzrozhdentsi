#include<iostream>
#include"FileExceptionManager.hpp"

std::string FileExceptionManager::printMessage() const throw()
{
    return "Exception opening/reading/closing file\n";
}


 void FileExceptionManager::setMessage(const std::string message)
 {
    this->exceptionMessage = message;

 }