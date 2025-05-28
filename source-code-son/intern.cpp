#include "Intern.h"

// Constructor gọi constructor lớp cơ sở
Intern::Intern(std::string id, std::string name, std::string address, std::string phone,
    std::string info, std::string email, std::string expiryDate)
    : IEmployee(id, name, address, phone, info, email, expiryDate) {
}

// Trả về loại nhân viên
std::string Intern::getEmployeeType() const {
    return "Intern";
}

// Các setter đơn giản

void Intern::setId(const std::string& newId) {
	employeeId = newId;
}

void Intern::setName(const std::string& newName) {
    name = newName;
}

void Intern::setAddress(const std::string& newAddress) {
    address = newAddress;
}

void Intern::setPhone(const std::string& newPhone) {
    phone = newPhone;
}

void Intern::setEmail(const std::string& newEmail) {
    email = newEmail;
}

void Intern::setAdditionalInfo(const std::string& info) {
    additionalInfo = info;
}

void Intern::setContractExpiry(int d, int m, int y) {
    _d = d;
    _m = m;
    _y = y;
}
