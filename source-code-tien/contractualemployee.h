#ifndef _CONTRACTUALEMPLOYEE_H_
#define _CONTRACTUALEMPLOYEE_H_

#include "IEmployee.h"
#include "Salary.h"     // Cần để tính lương
#include "Attendance.h" // Cần để truyền vào calculateSalary

/**
 * @file contractualEmployee.h
 * @brief Khai báo lớp ContractualEmployee kế thừa từ IEmployee.
 * @details Định nghĩa cấu trúc và giao diện cho đối tượng Nhân viên Hợp đồng.
 * Lớp này cụ thể hóa các phương thức trừu tượng từ IEmployee
 * phù hợp với đặc thù của nhân viên hợp đồng.
 */
class ContractualEmployee : public IEmployee
{
private:
    double _contractAmount; ///< Tiền lương của nhân viên hợp đồng.
    // Các rate cụ thể cho nhân viên hợp đồng (có thể khác Fulltime)
    double _hourlyRate = 45000;  // Ví dụ: 45,000 VND/giờ
    double _overtimeRate = 67500; // Ví dụ: 67,500 VND/giờ tăng ca
    double _holidayRate = 90000; // Ví dụ: 90,000 VND/giờ làm ngày lễ
    int _monthsWorked; ///< Số tháng đã làm việc.

public:
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
    ContractualEmployee(std::string id, std::string n, std::string addr, std::string p,
        double contractAmount, int monthsWorked, const std::string& expiryDateString);

    /**
     * @brief Lấy loại nhân viên là "Nhân viên Hợp đồng".
     *
     * Đây là cài đặt cụ thể của phương thức thuần ảo getEmployeeType()
     * từ lớp cơ sở IEmployee cho loại Nhân viên Hợp đồng.
     *
     * @return Chuỗi "Nhân viên Hợp đồng".
     * @override
     */
    std::string getEmployeeType() const override;

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
    SalaryDetails calculateSalary(const Attendance& attendance, double bonuses, double allowances, double deductions) const override;

    /**
     * @brief Lấy lương cơ bản của nhân viên Hợp đồng.
     * Triển khai phương thức thuần ảo getBaseSalary() từ IEmployee.
     * @return double Giá trị lương cơ bản của nhân viên Hợp đồng.
     * @override
     */
    double getBaseSalary() const override { return _contractAmount; }

    /**
     * @brief Lấy số tháng nhân viên đã làm việc.
     * @return int Số tháng đã làm việc.
     * @override
     */
    int getMonthsWorked() const override { return _monthsWorked; }
};

#endif // _CONTRACTUALEMPLOYEE_H_