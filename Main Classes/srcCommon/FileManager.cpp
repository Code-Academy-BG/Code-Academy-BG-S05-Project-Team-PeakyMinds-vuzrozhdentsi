#include <iostream>
#include "FileManager.hpp"
#include "FileExceptionManager.hpp"

void FileManager::CheckForFileExceptions()
{
    this->file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try
    {
        this->file.open(this->filename);
        while (!file.eof())
        {
            file.get();
        }
        file.close();
        

    }
    catch(const FileExceptionManager& e)
    {
      std::cout << "Hi"; //e.printMessage();
       
    }
     catch (std::ifstream::failure e) {
    std::cout << "Exception opening/reading/closing file\n";
  }

    
}

 
void FileManager::setFilename(const std::string name)
{
    this->filename = name;
}

void FileManager::write(const ClientOrder& order)
{
    try
    {
        file << order;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to write order to file: " << e.what() << '\n';
    }
}
