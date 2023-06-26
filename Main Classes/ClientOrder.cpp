#include "ClientOrder.hpp"

int ClientOrder::getId() const {
    return id;
}

ClientOrder::Status ClientOrder::getStatus() const {
    return status;
}

ClientOrder::Priority ClientOrder::getPriority() const {
    return priority;
}

std::vector<HardwareComponent> ClientOrder::getHardwareComponents() const {
    return hardwareComponents;
}

std::vector<ElectronicComponent> ClientOrder::getElectronicComponents() const {
    return electronicComponents;
}

void ClientOrder::setId(int orderId) {
    id = orderId;
}

void ClientOrder::setStatus(Status orderStatus) {
    status = orderStatus;
}

void ClientOrder::setPriority(Priority orderPriority) {
    priority = orderPriority;
}

void ClientOrder::setHardwareComponents(const std::vector<HardwareComponent>& components) {
    hardwareComponents = components;
}

void ClientOrder::setElectronicComponents(const std::vector<ElectronicComponent>& components) {
    electronicComponents = components;
}
