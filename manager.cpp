#include "manager.h"

Manager::Manager(std::string id, std::string n, std::string addr, std::string p,
    std::string info, const std::string& expiryDateString)
    : IEmployee(id, n, addr, p, info, expiryDateString)
{
}

std::string Manager::getEmployeeType() const
{
    return "Manager";
}
