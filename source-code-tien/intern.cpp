#include "intern.h"
#include "Salary.h"    // Bao gồm SalaryCalculator
#include "Attendance.h" // Bao gồm Attendance

/**
 * @brief Constructor cho lớp Intern.
 *
 * Khởi tạo một đối tượng Nhân viên Thực tập với các thông tin cơ bản
 * và ngày hết hạn hợp đồng.
 * Constructor này gọi constructor của lớp cơ sở IEmployee để khởi tạo
 * các thuộc tính chung.
 *
 * @param id ID duy nhất của nhân viên thực tập.
 * @param n Tên đầy đủ của nhân viên thực tập.
 * @param addr Địa chỉ liên lạc.
 * @param p Số điện thoại liên lạc.
 * @param stipend Tiền trợ cấp hàng tháng.
 * @param monthsWorked Số tháng đã làm việc.
 * @param expiryDateString Chuỗi ngày hết hạn hợp đồng thực tập theo định dạng "YYYY-MM-DD".
 */
Intern::Intern(std::string id, std::string n, std::string addr, std::string p,
    double stipend, int monthsWorked, const std::string& expiryDateString)
    : IEmployee(id, n, addr, p, expiryDateString), // Gọi constructor của lớp cơ sở, không còn info
    _stipend(stipend), _monthsWorked(monthsWorked)
{
}

/**
 * @brief Lấy loại nhân viên là "Nhân viên Thực tập".
 *
 * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
 * từ lớp cơ sở IEmployee cho loại nhân viên Thực tập.
 *
 * @return Chuỗi "Nhân viên Thực tập".
 * @override
 */
std::string Intern::getEmployeeType() const
{
    return "Nhân viên thực tập";
}

/**
 * @brief Tính toán chi tiết lương của nhân viên Thực tập.
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
SalaryDetails Intern::calculateSalary(const Attendance& attendance, double bonuses, double allowances, double deductions) const
{
    // Tạo một đối tượng SalaryCalculator với các rate của nhân viên thực tập
    SalaryCalculator calculator(_hourlyRate, _overtimeRate, _holidayRate);

    // Tính toán lương chi tiết và trả về
    return calculator.calculateSalary(attendance, employeeId, bonuses, allowances, deductions);
}