#ifndef _CONTRACTUAL_EMPLOYEE_H_
#define _CONTRACTUAL_EMPLOYEE_H_

#include "IEmployee.h"

/**
 * @brief Lớp đại diện cho Nhân viên Hợp đồng.
 *
 * Nhân viên hợp đồng có một khoản lương thỏa thuận trong hợp đồng.
 * Lương được tính dựa trên giờ làm việc thực tế.
 */
class ContractualEmployee : public IEmployee {
private:
    double _contractAmount;  // Số tiền lương thỏa thuận trong hợp đồng
    int _monthsWorked;       // Số tháng đã làm việc

public:
    /**
     * @brief Constructor cho lớp ContractualEmployee.
     * @param id Mã nhân viên.
     * @param name Tên đầy đủ.
     * @param addr Địa chỉ.
     * @param phone SĐT.
     * @param email Email.
     * @param info Thông tin bổ sung.
     * @param expiryDate Ngày hết hạn hợp đồng "YYYY-MM-DD".
     * @param contractAmount Số tiền lương theo hợp đồng.
     * @param monthsWorked Số tháng đã làm việc.
     */
    ContractualEmployee(std::string id, std::string name, std::string addr, std::string phone,
        std::string email, std::string info, std::string expiryDate,
        double contractAmount, int monthsWorked);

    // Override các phương thức từ lớp cơ sở IEmployee
    std::string getEmployeeType() const override;
    SalaryDetails calculateSalary(const AttendanceManager& attendance, double bonuses, double allowances, double deductions) const override;
    double getBaseSalary() const override;
    int getMonthsWorked() const override;
    std::string toCsvString() const override;
};

#endif // _CONTRACTUAL_EMPLOYEE_H_