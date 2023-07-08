#include "ClientOrder.hpp"

const std::string ClientOrder::NO_SUCH_STATUS_ERROR = "There is no such status";
const std::string ClientOrder::NO_SUCH_PRIORITY_ERROR = "There is no such priority";

int ClientOrder::getId() const
{
    return id;
}

ClientOrder::Status ClientOrder::getStatus() const
{
    return status;
}

ClientOrder::Priority ClientOrder::getPriority() const
{
    return priority;
}

const std::string ClientOrder::getClientName() const
{
    return clientName;
}

void ClientOrder::setClientName(const std::string &name)
{
    clientName = name;
}

std::vector<ClientOrder::HardwareComponentID> ClientOrder::getHardwareComponents() const
{
    return hardwareComponents;
}

std::vector<ClientOrder::ElectronicComponentID> ClientOrder::getElectronicComponents() const
{
    return electronicComponents;
}

void ClientOrder::setId(int orderId)
{
    id = orderId;
}

void ClientOrder::setStatus(Status orderStatus)
{
    status = orderStatus;
}

void ClientOrder::setStatus(int orderStatus)
{
    switch (orderStatus)
    {
    case 1:
        status = Status::UNPROCESSED;
        break;
    case 2:
        status = Status::PENDING;
        break;
    case 3:
        status = Status::InPROGRESS;
        break;
    case 4:
        status = Status::COMPLETED;
        break;
    default:
        throw std::invalid_argument(NO_SUCH_STATUS_ERROR);
        break;
    }
}

void ClientOrder::setPriority(Priority orderPriority)
{
    priority = orderPriority;
}

void ClientOrder::setPriority(int orderPriority)
{
    switch (orderPriority)
    {
    case 1:
        priority = Priority::HIGH;
        break;
    case 2:
        priority = Priority::NORMAL;
        break;
    default:
        throw std::invalid_argument(NO_SUCH_PRIORITY_ERROR);
        break;
    }
}

void ClientOrder::setHardwareComponents(const std::vector<HardwareComponentID> &components)
{
    hardwareComponents = components;
}

void ClientOrder::setElectronicComponents(const std::vector<ElectronicComponentID> &components)
{
    electronicComponents = components;
}

std::vector<ElectronicComponent> ClientOrder::getElectronicComponentsWithDesign() const
{
    return this->newElectronicComponentsWithDesign;
}

std::vector<HardwareComponent> ClientOrder::getHardwareComponentsWithDesign() const
{
    return this->newHardwareComponentsWithDesign;
}

int ClientOrder::getStatusAsInt() const
{
    switch (getStatus())
    {
    case Status::UNPROCESSED:
        return 1;
        break;
    case Status::PENDING:
        return 2;
        break;
    case Status::InPROGRESS:
        return 3;
        break;
    case Status::COMPLETED:
        return 4;
        break;
    }
    throw std::invalid_argument(NO_SUCH_STATUS_ERROR);
}

int ClientOrder::getPriorityAsInt() const
{
    switch (getPriority())
    {
    case Priority::HIGH:
        return 1;
        break;
    case Priority::NORMAL:
        return 2;
        break;
    }
    throw std::invalid_argument(NO_SUCH_PRIORITY_ERROR);
}

std::ostream &operator<<(std::ostream &stream, const ClientOrder &order)
{
    stream << order.getId() << ' ' << order.getPriorityAsInt() << ' ' << order.getStatusAsInt() << ' '
           << order.getClientName() << ' ' << order.getHardwareComponents().size() << ' ';
    for (size_t i = 0; i < order.getHardwareComponents().size(); i++)
    {
        stream << order.getHardwareComponents()[i] << ' ';
    }
    stream << order.getElectronicComponents().size() << ' ';
    for (size_t i = 0; i < order.getElectronicComponents().size(); i++)
    {
        stream << order.getElectronicComponents()[i] << ' ';
    }
    stream << order.getHardwareComponentsWithDesign().size() << ' ';
    for (size_t i = 0; i < order.getHardwareComponentsWithDesign().size(); i++)
    {
        stream << order.getHardwareComponentsWithDesign()[i] << ' ';
    }
    stream << order.getElectronicComponentsWithDesign().size() << ' ';
    for (size_t i = 0; i < order.getElectronicComponentsWithDesign().size(); i++)
    {
        stream << order.getElectronicComponentsWithDesign()[i] << ' ';
    }
    stream << '\n';
    return stream;
}

std::istream &operator>>(std::istream &stream, ClientOrder &order)
{
    size_t hardwareComponentsSize{0};
    size_t electronicComponentsSize{0};
    int priorityInt{0};
    int statusInt{0};
    stream >> order.id >> priorityInt >> statusInt >> order.clientName >> hardwareComponentsSize;
    order.setPriority(priorityInt);
    order.setStatus(statusInt);
    for (size_t i = 0; i < hardwareComponentsSize; i++)
    {
        ClientOrder::HardwareComponentID hc;
        stream >> hc;
        order.getHardwareComponents().push_back(hc);
    }
    stream >> electronicComponentsSize;
    for (size_t i = 0; i < electronicComponentsSize; i++)
    {
        ClientOrder::ElectronicComponentID ec;
        stream >> ec;
        order.getElectronicComponents().push_back(ec);
    }
    stream >> hardwareComponentsSize;
    for (size_t i = 0; i < hardwareComponentsSize; i++)
    {
        HardwareComponent hc;
        stream >> hc;
        order.getHardwareComponentsWithDesign().push_back(hc);
    }
    stream >> electronicComponentsSize;
    for (size_t i = 0; i < electronicComponentsSize; i++)
    {
        ElectronicComponent ec;
        stream >> ec;
        order.getElectronicComponentsWithDesign().push_back(ec);
    }
    return stream;
}
