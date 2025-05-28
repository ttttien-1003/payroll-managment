#ifndef _INTERN_H_
#define _INTERN_H_

#include "IEmployee.h"
#include "Salary.h"     // Cần để tính lương
#include "Attendance.h" // Cần để truyền vào calculateSalary

/**
 * @file Intern.h
 * @brief Khai báo lớp Intern kế thừa từ IEmployee.
 * @details Định nghĩa cấu trúc và giao diện cho đối tượng Nhân viên Thực tập.
 * Lớp này cụ thể hóa các phương thức trừu tượng từ IEmployee
 * phù hợp với đặc thù của nhân viên thực tập.
 */
class Intern : public IEmployee
{
private:
    double _stipend; ///< Tiền trợ cấp của nhân viên thực tập.
    // Các rate cụ thể cho nhân viên thực tập (thường thấp hơn hoặc cố định)
    double _hourlyRate = 25000;  // Ví dụ: 30,000 VND/giờ
    double _overtimeRate = 37500; // Ví dụ: 37,500 VND/giờ tăng ca
    double _holidayRate = 50000; // Ví dụ: 50,000 VND/giờ làm ngày lễ
    int _monthsWorked; ///< Số tháng đã làm việc.

public:
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
    Intern(std::string id, std::string n, std::string addr, std::string p,
        double stipend, int monthsWorked, const std::string& expiryDateString);

    /**
     * @brief Lấy loại nhân viên là "Nhân viên Thực tập".
     *
     * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
     * từ lớp cơ sở IEmployee cho loại nhân viên Thực tập.
     *
     * @return Chuỗi "Nhân viên Thực tập".
     * @override
     */
    std::string getEmployeeType() const override;

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
    SalaryDetails calculateSalary(const Attendance& attendance, double bonuses, double allowances, double deductions) const override;

    /**
     * @brief Lấy lương cơ bản của nhân viên Thực tập.
     * Triển khai phương thức thuần ảo getBaseSalary() từ IEmployee.
     * @return double Giá trị lương cơ bản của nhân viên Thực tập.
     * @override
     */
    double getBaseSalary() const override { return _stipend; }

    /**
     * @brief Lấy số tháng nhân viên đã làm việc.
     * @return int Số tháng đã làm việc.
     * @override
     */
    int getMonthsWorked() const override { return _monthsWorked; }
};

#endif // _INTERN_H_