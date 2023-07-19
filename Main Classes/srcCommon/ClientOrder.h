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
    HardwareComponentID hardwareComp;
    // std::vector<HardwareComponentID> hardwareComponents;
    // std::vector<HardwareComponent> newHardwareComponentsWithDesign;
    // std::vector<ElectronicComponentID> electronicComponents;
    // std::vector<ElectronicComponent> newElectronicComponentsWithDesign;

public:
    ClientOrder(int orderId, int incomePriority, std::string incomeName): id{orderId}, status{Status::UNPROCESSED}, priority{static_cast<Priority>(incomePriority)}, clientName {incomeName} {};
    ClientOrder(std::istream & stream)
    {
        stream >> *this;
    }
    HardwareComponentID setHardwareComponentID(HardwareComponentID hCID) {hardwareComp = hCID;}
    int getId() const;
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
    // void addHCDesign(const HardwareComponent& hc)
    // {
    //     newHardwareComponentsWithDesign.push_back(hc);
    // }
    // void addElCDesign(const ElectronicComponent& ec)
    // {
    //     newElectronicComponentsWithDesign.push_back(ec);
    // }
    // void addHC(const std::string& hc)
    // {
    //     hardwareComponents.push_back(hc);
    // }
    // void addElC(const std::string& ec)
    // {
    //     electronicComponents.push_back(ec);
    // }
    void setHardwareComponents(const std::vector<HardwareComponentID>& components);
    std::vector<ElectronicComponentID> getElectronicComponents() const;
    std::vector<ElectronicComponent> getElectronicComponentsWithDesign() const;
    void setElectronicComponents(const std::vector<ElectronicComponentID>& components);   
    friend std::ostream& operator<<(std::ostream & stream, const ClientOrder& order);
    friend std::istream& operator>>(std::istream & stream, ClientOrder& order);
};

#endif
