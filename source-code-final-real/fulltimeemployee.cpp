#include "FulltimeEmployee.h"
#include "SalaryCalculator.h"
#include "AttendanceManager.h"
#include <sstream>

/**
 * @brief Constructor cho FulltimeEmployee.
 */
FulltimeEmployee::FulltimeEmployee(std::string id, std::string name, std::string addr, std::string phone,
    std::string email, std::string info, std::string expiryDate,
    double baseSalary, int monthsWorked)
    : IEmployee(id, name, addr, phone, email, info, expiryDate),
    _baseSalary(baseSalary), _monthsWorked(monthsWorked) {
}

/**
 * @brief Trả về loại nhân viên là "Full-time Employee".
 */
std::string FulltimeEmployee::getEmployeeType() const {
    return "Full-time Employee";
}

/**
 * @brief Lấy lương cơ bản.
 */
double FulltimeEmployee::getBaseSalary() const {
    return _baseSalary;
}

/**
 * @brief Lấy số tháng đã làm việc.
 */
int FulltimeEmployee::getMonthsWorked() const {
    return _monthsWorked;
}

/**
 * @brief Tính lương cho nhân viên chính thức.
 */
SalaryDetails FulltimeEmployee::calculateSalary(const AttendanceManager& attendance, double bonuses, double allowances, double deductions) const {
    // Giả định mức lương giờ cho nhân viên chính thức
    const double hourlyRate = 23800;
    const double overtimeRate = hourlyRate * 1.5;
    const double holidayRate = hourlyRate * 3.0;

    SalaryCalculator calculator(hourlyRate, overtimeRate, holidayRate);
    return calculator.calculateSalary(attendance, _employeeId, _baseSalary, bonuses, allowances, deductions);
}

std::string FulltimeEmployee::toCsvString() const {
    std::stringstream ss;
    ss << getEmployeeType() << ","
        << _employeeId << ","
        << _name << ","
        << _address << ","
        << _phone << ","
        << _email << ","
        << _additionalInfo << "," // Experience
        << getFormattedExpiryDate() << "," // Contract End Date
        << static_cast<long long>(_baseSalary);
    return ss.str();
}