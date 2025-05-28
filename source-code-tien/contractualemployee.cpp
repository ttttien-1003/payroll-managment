#include "contractualemployee.h"
#include "Salary.h"    // Bao gồm SalaryCalculator
#include "Attendance.h" // Bao gồm Attendance

/**
 * @brief Constructor cho lớp ContractualEmployee.
 *
 * Khởi tạo một đối tượng Nhân viên Hợp đồng với các thông tin cơ bản
 * và ngày hết hạn hợp đồng.
 * Constructor này gọi constructor của lớp cơ sở IEmployee để khởi tạo
 * các thuộc tính chung.
 *
 * @param id ID duy nhất của Nhân viên Hợp đồng.
 * @param n Tên đầy đủ của Nhân viên Hợp đồng.
 * @param addr Địa chỉ liên lạc.
 * @param p Số điện thoại liên lạc.
 * @param contractAmount Số tiền hợp đồng (lương).
 * @param monthsWorked Số tháng đã làm việc.
 * @param expiryDateString Chuỗi ngày hết hạn hợp đồng theo định dạng "YYYY-MM-DD".
 */
ContractualEmployee::ContractualEmployee(std::string id, std::string n, std::string addr, std::string p,
    double contractAmount, int monthsWorked, const std::string& expiryDateString)
    : IEmployee(id, n, addr, p, expiryDateString), // Gọi constructor của lớp cơ sở, không còn info
    _contractAmount(contractAmount), _monthsWorked(monthsWorked)
{
}

/**
 * @brief Lấy loại nhân viên là "Nhân viên Hợp đồng".
 *
 * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
 * từ lớp cơ sở IEmployee cho loại Nhân viên Hợp đồng.
 *
 * @return Chuỗi "Nhân viên Hợp đồng".
 * @override
 */
std::string ContractualEmployee::getEmployeeType() const
{
    return "Nhân viên Hợp đồng";
}

/**
 * @brief Tính toán chi tiết lương của nhân viên Hợp đồng.
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
SalaryDetails ContractualEmployee::calculateSalary(const Attendance& attendance, double bonuses, double allowances, double deductions) const
{
    // Tạo một đối tượng SalaryCalculator với các rate của nhân viên hợp đồng
    SalaryCalculator calculator(_hourlyRate, _overtimeRate, _holidayRate);

    // Tính toán lương chi tiết và trả về
    return calculator.calculateSalary(attendance, employeeId, bonuses, allowances, deductions);
}