#include "fulltimeemployee.h"
#include "Salary.h"    // Bao gồm SalaryCalculator
#include "Attendance.h" // Bao gồm Attendance

/**
 * @brief Constructor cho lớp FulltimeEmployee.
 *
 * Khởi tạo một đối tượng Nhân viên Chính thức với các thông tin cơ bản.
 * Constructor này gọi constructor của lớp cơ sở IEmployee để khởi tạo
 * các thuộc tính chung.
 *
 * @param id ID duy nhất của nhân viên chính thức.
 * @param n Tên đầy đủ của nhân viên chính thức.
 * @param addr Địa chỉ liên lạc.
 * @param p Số điện thoại liên lạc.
 * @param monthsWorked Số tháng đã làm việc (để tính thưởng thâm niên, v.v.).
 * @param baseSalary Lương cơ bản của nhân viên chính thức.
 */
FulltimeEmployee::FulltimeEmployee(std::string id, std::string n, std::string addr, std::string p,
    int monthsWorked, double baseSalary)
    : IEmployee(id, n, addr, p), // Gọi constructor của lớp cơ sở, không còn info
    _baseSalary(baseSalary), _monthsWorked(monthsWorked)
{
}

/**
 * @brief Lấy loại nhân viên là "Nhân viên Chính thức".
 *
 * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
 * từ lớp cơ sở IEmployee cho loại nhân viên Chính thức.
 *
 * @return Chuỗi "Nhân viên Chính thức".
 * @override
 */
std::string FulltimeEmployee::getEmployeeType() const
{
    return "Nhân viên Chính thức";
}

/**
 * @brief Tính toán chi tiết lương của nhân viên Chính thức.
 *
 * Triển khai phương thức thuần ảo calculateSalary() từ IEmployee.
 * Sử dụng SalaryCalculator để tính toán dựa trên chấm công và các khoản phúc lợi/khấu trừ.
 *
 * @param attendance Đối tượng Attendance chứa thông tin chấm công.
 * @param bonuses Tổng các khoản thưởng.
 * @param allowances Tổng các khoản phụ cấp.
 * @param deductions Tổng các khoản khấu trừ.
 * @return SalaryDetails Đối tượng chứa thông tin chi tiết về lương đã tính toán.
 * @override
 */
SalaryDetails FulltimeEmployee::calculateSalary(const Attendance& attendance, double bonuses, double allowances, double deductions) const
{
    // Tạo một đối tượng SalaryCalculator với các rate của nhân viên chính thức
    SalaryCalculator calculator(_hourlyRate, _overtimeRate, _holidayRate);

    // Tính toán lương chi tiết và trả về
    return calculator.calculateSalary(attendance, employeeId, bonuses, allowances, deductions);
}