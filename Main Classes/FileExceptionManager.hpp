#ifndef FILE_EXCEPTION_MANAGER_H
#define FILE_EXCEPTION_MANAGER_H
#include<iostream>
class FileExceptionManager
{
    private:
    std::string exceptionMessage;
    public:
    virtual  std::string printMessage() const throw();
    void setMessage(const std::string message);
};

#endif