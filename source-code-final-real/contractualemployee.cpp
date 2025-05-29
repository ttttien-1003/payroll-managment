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
    : IEmployee(id, name, addr, phone, email, info, expiryDate),
    _contractAmount(contractAmount), _monthsWorked(monthsWorked) {
}

/**
 * @brief Trả về loại nhân viên là "Contractual Employee".
 */
std::string ContractualEmployee::getEmployeeType() const {
    return "Contractual Employee";
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
SalaryDetails ContractualEmployee::calculateSalary(const AttendanceManager& attendance, double bonuses, double allowances, double deductions) const {

    const double hourlyRate = 23800;

    // Nhân viên hợp đồng không có lương tăng ca hoặc ngày lễ (bất kể có đi làm hay không)
    const double overtimeRate = 0.0;
    const double holidayRate = 0.0;

    // Sử dụng SalaryCalculator để tính toán chi tiết
    SalaryCalculator calculator(hourlyRate, overtimeRate, holidayRate);
    return calculator.calculateSalary(attendance, _employeeId, _contractAmount, bonuses, allowances, deductions);
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