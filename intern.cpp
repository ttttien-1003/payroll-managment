#include "intern.h"

Intern::Intern(std::string id, std::string n, std::string addr, std::string p,
    std::string info, const std::string& expiryDateString)
    : IEmployee(id, n, addr, p, info, expiryDateString)
{
}

std::string Intern::getEmployeeType() const 
{
    return "Intern";
}
