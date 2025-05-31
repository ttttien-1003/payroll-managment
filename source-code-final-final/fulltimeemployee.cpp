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
    : IEmployee(id, name, addr, phone, email, info, expiryDate, "Full-time Employee"),
    _baseSalary(baseSalary), _monthsWorked(monthsWorked) {
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
SalaryDetails FulltimeEmployee::calculateSalary(const AttendanceManager& attendance, int month, int year, double bonuses, double allowances, double deductions) const {
    const double hourlyRate = 23800; //
    const double overtimeRate = hourlyRate * 1.5; //
    const double holidayRate = hourlyRate * 3.0; //

    SalaryCalculator calculator(hourlyRate, overtimeRate, holidayRate); //
    // Truyền month, year vào SalaryCalculator
    return calculator.calculateSalary(attendance, _employeeId, month, year, _baseSalary, bonuses, allowances, deductions);
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

void FulltimeEmployee::setMonthsWorked(int months) {
    _monthsWorked = months;
}

void FulltimeEmployee::setBaseSalary(double salary) {
    _baseSalary = salary;
}