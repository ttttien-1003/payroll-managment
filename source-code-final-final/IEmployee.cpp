#include "IEmployee.h"
#include <sstream>
#include <iomanip>

/**
 * @brief Constructor cho IEmployee, phân tích chuỗi ngày tháng.
 */
IEmployee::IEmployee(std::string id, std::string name, std::string addr, std::string phone,
    std::string email, std::string info, std::string expiryDate, std::string logicalType)
    : _employeeId(id), _name(name), _address(addr), _phone(phone),
    _email(email), _additionalInfo(info), _logicalEmployeeType(logicalType) {
    // Phân tích chuỗi ngày hết hạn từ định dạng "YYYY-MM-DD"
    if (!expiryDate.empty()) {
        std::stringstream ss(expiryDate);
        char token;
        ss >> _expYear >> token >> _expMonth >> token >> _expDay;
    }
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

std::string IEmployee::getEmployeeType() const { return _logicalEmployeeType; }

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

const std::string& IEmployee::getAdditionInfo() const
{
    return _additionalInfo;
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

std::string IEmployee::getFormattedExpiryDate() const {
    if (_expYear == 0 && _expMonth == 0 && _expDay == 0) return _additionalInfo; // Or specific handling for non-date strings
    if (_expYear == 0) return "N/A";
    std::stringstream ss;
    ss << _expYear << "-"
        << std::setfill('0') << std::setw(2) << _expMonth << "-"
        << std::setfill('0') << std::setw(2) << _expDay;
    return ss.str();
}

void IEmployee::setExpiryDate(const std::string& expiryDateStr) {
    // Xóa ngày tháng cũ trước khi đặt ngày mới
    _expYear = 0; _expMonth = 0; _expDay = 0;

    if (!expiryDateStr.empty() && expiryDateStr.length() >= 10 &&
        expiryDateStr[4] == '-' && expiryDateStr[7] == '-') {
        try {
            _expYear = std::stoi(expiryDateStr.substr(0, 4));
            _expMonth = std::stoi(expiryDateStr.substr(5, 2));
            _expDay = std::stoi(expiryDateStr.substr(8, 2));
            // Thêm kiểm tra tính hợp lệ của ngày tháng ở đây nếu cần
        } catch (const std::exception& e) {
            // Nếu chuỗi không hợp lệ, ngày tháng sẽ vẫn là 0,0,0
            // Hoặc bạn có thể in ra lỗi: std::cerr << "Loi dinh dang ngay: " << e.what() << std::endl;
            _expYear = 0; _expMonth = 0; _expDay = 0; // Đảm bảo reset nếu lỗi
        }
    }
    // Nếu expiryDateStr rỗng hoặc không đúng định dạng cơ bản, ngày tháng sẽ là 0,0,0
}