g++ .\main.cpp .\HardwarePrinterManager.cpp ..\Lib\ElectronicComponentsManager.cpp ..\Lib\HardwareComponentManager.cpp ..\srcCommon\FileManager.cpp ..\srcCommon\PrinterJob.cpp ..\srcCommon\Board.cpp ..\srcCommon\Pin.cpp ..\srcCommon\HardwareComponent.cpp ..\srcCommon\ElectronicComponentFactory.hpp ..\srcCommon\ElectronicComponent.cpp  -o bit.exe
CC=g++
CCFLAGS = -std=c++14 -Wall -Wextra

TARGET = bit.exe
SRC = ./main.cpp ./HardwarePrinterManager.cpp ./../Lib/ElectronicComponentsManager.cpp ./../Lib/HardwareComponentManager.cpp ./../srcCommon/FileManager.cpp ../srcCommon/PrinterJob.cpp ../srcCommon/Board.cpp ../srcCommon/Pin.cpp ../srcCommon/HardwareComponent.cpp ../srcCommon/ElectronicComponentFactory.hpp  -o bit.exe

$(TARGET): $(SRC)
	$(CC) $(CCFLAGS) $(SRC) -o $(TARGET)
