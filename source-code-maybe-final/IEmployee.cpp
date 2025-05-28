#include "IEmployee.h"
#include <sstream>

/**
 * @brief Constructor cho IEmployee, phân tích chuỗi ngày tháng.
 */
IEmployee::IEmployee(std::string id, std::string name, std::string addr, std::string phone,
    std::string email, std::string info, std::string expiryDate)
    : _employeeId(id), _name(name), _address(addr), _phone(phone),
    _email(email), _additionalInfo(info) {
    // Phân tích chuỗi ngày hết hạn từ định dạng "YYYY-MM-DD"
    if (!expiryDate.empty()) {
        std::stringstream ss(expiryDate);
        char token;
        ss >> _expYear >> token >> _expMonth >> token >> _expDay;
    }
}

// --- Implementations for Getters ---
const std::string& IEmployee::getEmployeeId() const 
{ 
    return _employeeId; 
}

const std::string& IEmployee::getName() const 
{ 
    return _name; 
}

const std::string& IEmployee::getAddress() const 
{ 
    return _address; 
}

const std::string& IEmployee::getPhone() const 
{ 
    return _phone; 
}

const std::string& IEmployee::getEmail() const 
{ 
    return _email; 
}

int IEmployee::getExpDay() const 
{ 
    return _expDay; 
}

int IEmployee::getExpMonth() const 
{ 
    return _expMonth; 
}

int IEmployee::getExpYear() const 
{ 
    return _expYear; 
}