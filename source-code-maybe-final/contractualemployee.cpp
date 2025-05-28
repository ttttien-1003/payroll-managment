#include "contractualemployee.h"
#include "SalaryCalculator.h"
#include "AttendanceManager.h"

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
    // Giả định một tháng có 26 ngày công, mỗi ngày 8 giờ
    const double standardWorkHoursPerMonth = 26.0 * 8.0;
    const double hourlyRate = _contractAmount / standardWorkHoursPerMonth;

    // Nhân viên hợp đồng có thể không có lương tăng ca hoặc ngày lễ (tùy chính sách)
    // Ở đây giả định họ được hưởng như nhân viên chính thức
    const double overtimeRate = hourlyRate * 1.5;
    const double holidayRate = hourlyRate * 3.0;

    // Sử dụng SalaryCalculator để tính toán chi tiết
    SalaryCalculator calculator(hourlyRate, overtimeRate, holidayRate);
    return calculator.calculateSalary(attendance, _employeeId, _contractAmount, bonuses, allowances, deductions);
}