#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H
#include<iostream>
#include<string>
#include<fstream>
#include "./ClientOrder.h"

class FileManager
{
    private:
    std::fstream file;
    std::string filename;
    public:
    void CheckForFileExceptions();
    void setFilename(const std::string name);
    void write(const ClientOrder& order);

    explicit FileManager(const std::string & filename)
    {
        try
        {
            file.open(filename, std::fstream::in | std::fstream::out);
            if (!file)
            {
                throw std::invalid_argument("file is not open, Check the file, it may not be found");
            }
            std::cout << filename << " is opened\n";
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        } 
    };
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;
    ~FileManager()
    {
        file.close();
    }
    std::fstream & get(){
        return file;
    }
};
#endif