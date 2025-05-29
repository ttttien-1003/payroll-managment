#include "Intern.h"
#include "AttendanceManager.h"
#include <sstream>

/**
 * @brief Constructor cho lớp Intern.
 */
Intern::Intern(std::string id, std::string name, std::string addr, std::string phone,
    std::string email, std::string info, std::string expiryDate,
    double stipend, int monthsWorked)
    : IEmployee(id, name, addr, phone, email, info, expiryDate),
    _stipend(stipend), _monthsWorked(monthsWorked) {
}

/**
 * @brief Trả về loại nhân viên là "Intern".
 */
std::string Intern::getEmployeeType() const {
    return "Intern";
}

/**
 * @brief Lấy mức lương cơ bản, đối với thực tập sinh chính là trợ cấp.
 */
double Intern::getBaseSalary() const {
    return _stipend;
}

/**
 * @brief Lấy số tháng đã làm việc.
 */
int Intern::getMonthsWorked() const {
    return _monthsWorked;
}

/**
 * @brief Tính lương cho nhân viên thực tập.
 * Lương của thực tập sinh là một khoản trợ cấp cố định, cộng với các khoản thưởng
 * và phụ cấp khác nếu có.
 * @return Đối tượng SalaryDetails chứa thông tin lương chi tiết.
 */
SalaryDetails Intern::calculateSalary(const AttendanceManager& attendance, double bonuses, double allowances, double deductions) const {
    
    SalaryDetails details;
    details.basicSalary = _stipend; // Lương cơ bản chính là trợ cấp
    details.bonuses = bonuses;
    details.allowances = allowances;
    details.deductions = deductions; // Giả sử thực tập sinh không có các khoản khấu trừ phức tạp

    // Lương cuối cùng
    details.totalSalary = details.basicSalary + details.bonuses + details.allowances - details.deductions;

    return details;
}

std::string Intern::toCsvString() const {
    std::stringstream ss;
    ss << getEmployeeType() << ","
        << _employeeId << ","
        << _name << ","
        << _address << ","
        << _phone << ","
        << _email << ","
        << _additionalInfo << "," // University Name
        << _monthsWorked << "," // Internship Duration string
        << static_cast<long long>(_stipend);
    return ss.str();
}