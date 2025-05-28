#include "Manager.h"

// Gọi constructor lớp cha
Manager::Manager(std::string id, std::string name, std::string address, std::string phone,
    std::string info, std::string email, std::string expiryDate)
    : IEmployee(id, name, address, phone, info, email, expiryDate) {
}

// Trả về loại nhân viên
std::string Manager::getEmployeeType() const {
    return "Manager";
}

// Các setter đơn giản
void Manager::setId(const std::string& newId) {
	employeeId = newId;
}

void Manager::setName(const std::string& newName) {
    name = newName;
}

void Manager::setAddress(const std::string& newAddress) {
    address = newAddress;
}

void Manager::setPhone(const std::string& newPhone) {
    phone = newPhone;
}

void Manager::setEmail(const std::string& newEmail) {
    email = newEmail;
}

void Manager::setAdditionalInfo(const std::string& info) {
    additionalInfo = info;
}

void Manager::setContractExpiry(int d, int m, int y) {
    _d = d;
    _m = m;
    _y = y;
}
