#ifndef _SALARY_CALCULATOR_H_
#define _SALARY_CALCULATOR_H_

#include "GlobalDefinitions.h"

class AttendanceManager; // Khai báo chuyển tiếp

/**
 * @brief Lớp tính toán lương chi tiết.
 * Chịu trách nhiệm tính các thành phần lương dựa trên giờ công và các khoản khác.
 */
class SalaryCalculator {
private:
    double _hourlyRate;   // Lương giờ làm việc bình thường
    double _overtimeRate; // Lương giờ làm thêm
    double _holidayRate;  // Lương giờ làm ngày lễ

public:
    /**
     * @brief Constructor.
     * @param hrRate Mức lương giờ bình thường.
     * @param otRate Mức lương giờ tăng ca.
     * @param hdRate Mức lương giờ ngày lễ.
     */
    SalaryCalculator(double hrRate, double otRate, double hdRate);

    /**
     * @brief Tính lương chi tiết cho nhân viên.
     * @param attendance Tham chiếu đến đối tượng quản lý chấm công.
     * @param employeeId Mã nhân viên cần tính lương.
     * @param baseSalary Lương cơ bản (nếu có, dùng cho các loại trừ lương).
     * @param bonuses Tổng thưởng.
     * @param allowances Tổng phụ cấp.
     * @param deductions Tổng khấu trừ (từ phúc lợi).
     * @return Đối tượng SalaryDetails chứa thông tin lương chi tiết.
     */
    SalaryDetails calculateSalary(const AttendanceManager& attendance, const std::string& employeeId, double baseSalary,
        double bonuses, double allowances, double deductions);
};

#endif // _SALARY_CALCULATOR_H_