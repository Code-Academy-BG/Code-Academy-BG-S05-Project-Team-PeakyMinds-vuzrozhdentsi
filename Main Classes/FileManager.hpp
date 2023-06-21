#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include<iostream>
#include<fstream>

class FileManager
{
    private:
    std::fstream file;
    std::string filename;
    public:
    void CheckForFileExceptions();
    void setFilename(const std::string name);
};
#endif