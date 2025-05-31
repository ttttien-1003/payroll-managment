#ifndef _FULLTIMEEMPLOYEE_H_
#define _FULLTIMEEMPLOYEE_H_

#include "IEmployee.h"

/**
 * @brief Lớp đại diện cho Nhân viên chính thức.
 */
class FulltimeEmployee : public IEmployee {
private:
    double _baseSalary;     // Lương cơ bản
    int _monthsWorked;      // Số tháng đã làm việc

public:
    /**
     * @brief Constructor cho FulltimeEmployee.
     */
    FulltimeEmployee(std::string id, std::string name, std::string addr, std::string phone,
        std::string email, std::string info, std::string expiryDate,
        double baseSalary, int monthsWorked);

    // Override các phương thức thuần ảo
    SalaryDetails calculateSalary(const AttendanceManager& attendance, int month, int year, double bonuses, double allowances, double deductions) const override;
    double getBaseSalary() const override;
    int getMonthsWorked() const override;
    std::string toCsvString() const override;

    void setMonthsWorked(int months) override;
    void setBaseSalary(double salary) override; // Thêm override này

};

#endif // _FULLTIMEEMPLOYEE_H_