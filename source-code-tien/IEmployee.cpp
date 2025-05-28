#include "IEmployee.h"

IEmployee::IEmployee(std::string id, std::string n, std::string addr, std::string p,
    std::string expiryDateString)
    : employeeId(id), name(n), address(addr), phone(p), expiryDate(expiryDateString)
{
}

const std::string& IEmployee::getEmployeeId() const {
    return employeeId;
}

const std::string& IEmployee::getName() const {
    return name;
}

const std::string& IEmployee::getAddress() const {
    return address;
}

const std::string& IEmployee::getPhone() const {
    return phone;
}