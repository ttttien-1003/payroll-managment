#include "IEmployee.h"

IEmployee::IEmployee(std::string id, std::string n, std::string addr, std::string p,
     std::string info, std::string email, std::string expiryDate)
	: employeeId(id), name(n), address(addr), phone(p), additionalInfo(info), email(email)
{
    std::stringstream ss(expiryDate);
    char token1, token2;
    ss >> _y >> token1 >> _m >> token2 >> _d;
}

IEmployee::~IEmployee() = default;

const std::string& IEmployee::getEmployeeId() { 
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

const std::string& IEmployee::getEmail() const {
	return email;
}

const std::string& IEmployee::getAdditionalInfo() const { 
    return additionalInfo; 
}

const int& IEmployee::getExpiredDay() { 
    return _d; 
}

const int& IEmployee::getExpiredMonth() { 
    return _m; 
}

const int& IEmployee::getExpiredYear() { 
    return _y; 
}