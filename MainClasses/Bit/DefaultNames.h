#ifndef DEFAULT_NAMES_H
#define DEFAULT_NAMES_H
#include <string>

//includes all text used in bit
namespace bit{
    const char ZERO = '0';
    const char ONE = '1';
    const char AST = '*';

    const std::string ID = "id: ";
    const std::string WIDHT = "width: " ;
    const std::string HEIGHT = "height: ";
    const std::string COMPONENTS = "components: ";

    const std::string PRODUCTION_FILE = "../textFiles/production.txt";
    const std::string PRINTJOBS_FILE = "../textFiles/print_jobs.txt";
    const std::string PRODUCTION_FILE_VOLT = "../textFiles/productionForVolt.txt"; 
    const std::string CFG_FILE = "../textFiles/cfg_bit.txt";
    const char* TEMP_FILE = "temp.txt";
    const std::string STEP = "----------------- STEP";
    const std::string STEP_0 = "----------------- STEP 0: Cut board";
    const std::string STEP_3 = "----------------- STEP 3: COMPONENTS MASK - ";
    const std::string STEP_4 = "----------------- STEP 4: COMPONENTS - ";
    const std::string STEP_5 = "----------------- STEP 5: FINAL RESULT FROM BIT IN ALL 3 FORMATS";
    const std::string SPACE = "space: ";
    const std::string CONNECTION = ": Connection"; 
    const std::string CONNECTIONS = "connections: ";
}

#endif // DEFAULT_NAMES_H