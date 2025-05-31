#include "contractualemployee.h"
#include "SalaryCalculator.h"
#include "AttendanceManager.h"
#include <sstream>

/**
 * @brief Constructor cho lớp ContractualEmployee.
 */
ContractualEmployee::ContractualEmployee(std::string id, std::string name, std::string addr, std::string phone,
    std::string email, std::string info, std::string expiryDate,
    double contractAmount, int monthsWorked)
    : IEmployee(id, name, addr, phone, email, info, expiryDate, "Contractual Employee"),
    _contractAmount(contractAmount), _monthsWorked(monthsWorked) {
}

/**
 * @brief Lấy mức lương cơ bản theo hợp đồng.
 */
double ContractualEmployee::getBaseSalary() const {
    return _contractAmount;
}

/**
 * @brief Lấy số tháng đã làm việc.
 */
int ContractualEmployee::getMonthsWorked() const {
    return _monthsWorked;
}

/**
 * @brief Tính lương cho nhân viên hợp đồng.
 * Lương được tính dựa trên giờ làm việc thực tế với một mức lương giờ
 * được quy đổi từ lương hợp đồng.
 * @return Đối tượng SalaryDetails chứa thông tin lương chi tiết.
 */
SalaryDetails ContractualEmployee::calculateSalary(const AttendanceManager& attendance, int month, int year, double bonuses, double allowances, double deductions) const {
    const double hourlyRate = 23800; //
    const double overtimeRate = 0.0; //
    const double holidayRate = 0.0;  //

    SalaryCalculator calculator(hourlyRate, overtimeRate, holidayRate); //
    // Truyền month, year vào hàm của SalaryCalculator
    return calculator.calculateSalary(attendance, _employeeId, month, year, _contractAmount, bonuses, allowances, deductions);
}

std::string ContractualEmployee::toCsvString() const {
    std::stringstream ss;
    ss << getEmployeeType() << ","
        << _employeeId << ","
        << _name << ","
        << _address << ","
        << _phone << ","
        << _email << ","
        << _additionalInfo << "," // Project Name
        << getFormattedExpiryDate() << "," // Contract End Date
        << static_cast<long long>(_contractAmount);
    return ss.str();
}

void ContractualEmployee::setMonthsWorked(int months) {
    _monthsWorked = months;
}

// Cài đặt setBaseSalary
void ContractualEmployee::setBaseSalary(double salary) {
    _contractAmount = salary; // ContractualEmployee lưu lương vào _contractAmount
}