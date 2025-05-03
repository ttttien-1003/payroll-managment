#include "IEmployee.h"

IEmployee::IEmployee(std::string id, std::string n, std::string addr, std::string p,
     std::string info, std::string expiryDate)
{
    employeeId = id;
    name = n;
    address = addr;
    phone = p;
    additionalInfo = info;
    std::stringstream ss(expiryDate);
    char token1, token2;
    ss >> _y;
    ss >> token1;
    ss >> _m;
    ss >> token2;
    ss >> _d;
}

IEmployee::~IEmployee() = default;

const std::string& IEmployee::getEmployeeId()
{
    return employeeId;
}
const std::string& IEmployee::getName() 
{ 
    return name; 
}
const std::string& IEmployee::getAddress()
{ 
    return address; 
}
const std::string& IEmployee::getPhone()  
{ 
    return phone; 
}
const std::string& IEmployee::getAdditionalInfo() 
{ 
    return additionalInfo; 
}