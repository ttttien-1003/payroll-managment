#include "director.h"

Director::Director(std::string id, std::string n, std::string addr, std::string p,
    std::string info, const std::string& expiryDateString)
    : IEmployee(id, n, addr, p, info, expiryDateString)
{
}

std::string Director::getEmployeeType() const
{
    return "Director";
}
