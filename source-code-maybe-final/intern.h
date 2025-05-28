#ifndef _INTERN_H_
#define _INTERN_H_

#include "IEmployee.h"

/**
 * @brief Lớp đại diện cho Nhân viên thực tập.
 *
 * Nhân viên thực tập nhận một khoản trợ cấp cố định hàng tháng.
 * Lương của họ không dựa trên giờ làm việc mà là khoản trợ cấp này.
 */
class Intern : public IEmployee {
private:
    double _stipend;         // Trợ cấp hàng tháng
    int _monthsWorked;       // Số tháng đã thực tập

public:
    /**
     * @brief Constructor cho lớp Intern.
     * @param id Mã nhân viên.
     * @param name Tên đầy đủ.
     * @param addr Địa chỉ.
     * @param phone SĐT.
     * @param email Email.
     * @param info Thông tin bổ sung.
     * @param expiryDate Ngày hết hạn hợp đồng "YYYY-MM-DD".
     * @param stipend Mức trợ cấp hàng tháng.
     * @param monthsWorked Số tháng đã làm việc.
     */
    Intern(std::string id, std::string name, std::string addr, std::string phone,
        std::string email, std::string info, std::string expiryDate,
        double stipend, int monthsWorked);

    // Override các phương thức từ lớp cơ sở IEmployee
    std::string getEmployeeType() const override;
    SalaryDetails calculateSalary(const AttendanceManager& attendance, double bonuses, double allowances, double deductions) const override;
    double getBaseSalary() const override;
    int getMonthsWorked() const override;
};

#endif // _INTERN_H_