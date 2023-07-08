#ifndef CLIENT_ORDER_H
#define CLIENT_ORDER_H

#include "HardwareComponent.hpp"
#include "ElectronicComponent.hpp"
#include <string>
#include <vector>

class ClientOrder
{
public:
    enum class Status {
        UNPROCESSED = 1,
        PENDING,
        InPROGRESS,
        COMPLETED
    };

    enum class Priority {
        HIGH = 1,
        NORMAL, 
    };
    static const std::string NO_SUCH_STATUS_ERROR;
    static const std::string NO_SUCH_PRIORITY_ERROR;
private:
    using ElectronicComponentID = std::string;
    using HardwareComponentID = std::string;

    int id;
    Status status;
    Priority priority;
    std::string clientName;
    std::vector<HardwareComponentID> hardwareComponents;
    std::vector<HardwareComponent> newHardwareComponentsWithDesign;
    std::vector<ElectronicComponentID> electronicComponents;
    std::vector<ElectronicComponent> newElectronicComponentsWithDesign;

public:
    ClientOrder(): id{0}, status{Status::UNPROCESSED}, priority{Priority::NORMAL}, clientName {""} {};
    ClientOrder(std::istream & stream)
    {
        stream >> *this;
    }
    int getId() const;
    void setId(int orderId);
    const std::string getClientName() const;
    void setClientName(const std::string & name);
    Status getStatus() const;
    int getStatusAsInt() const;
    void setStatus(Status orderStatus);
    void setStatus(int orderStatus);
    Priority getPriority() const;
    int getPriorityAsInt() const;
    void setPriority(Priority orderPriority);
    void setPriority(int orderPriority);
    std::vector<HardwareComponentID> getHardwareComponents() const;
    std::vector<HardwareComponent> getHardwareComponentsWithDesign() const;
    void setHardwareComponents(const std::vector<HardwareComponentID>& components);
    std::vector<ElectronicComponentID> getElectronicComponents() const;
    std::vector<ElectronicComponent> getElectronicComponentsWithDesign() const;
    void setElectronicComponents(const std::vector<ElectronicComponentID>& components);   
    friend std::ostream& operator<<(std::ostream & stream, const ClientOrder& order);
    friend std::istream& operator>>(std::istream & stream, ClientOrder& order);
};

#endif
