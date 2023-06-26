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
        PENDING
    };

    enum class Priority {
        HIGH = 1,
        NORMAL
    };

private:
    int id;
    Status status;
    Priority priority;
    std::vector<HardwareComponent> hardwareComponents;
    std::vector<ElectronicComponent> electronicComponents;

public:
    ClientOrder();

    int getId() const;
    void setId(int orderId);
    Status getStatus() const;
    void setStatus(Status orderStatus);
    Priority getPriority() const;
    void setPriority(Priority orderPriority);
    std::vector<HardwareComponent> getHardwareComponents() const;
    void setHardwareComponents(const std::vector<HardwareComponent>& components);
    std::vector<ElectronicComponent> getElectronicComponents() const;
    void setElectronicComponents(const std::vector<ElectronicComponent>& components);
};

#endif
