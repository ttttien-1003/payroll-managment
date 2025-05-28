#ifndef _SALARY_H_
#define _SALARY_H_

#include "GlobalDefinitions.h" // Bao gồm SalaryDetails
#include "Attendance.h" // Cần Attendance để lấy dữ liệu chấm công

/**
 * @brief Lớp tính lương dựa trên dữ liệu chấm công và các khoản phúc lợi.
 *
 * Lớp này chịu trách nhiệm tính toán các thành phần khác nhau của lương
 * như lương cơ bản, lương tăng ca, lương ngày lễ, và kết hợp với thưởng,
 * phụ cấp, và các khoản khấu trừ để ra tổng lương cuối cùng.
 */
class SalaryCalculator {
private:
    double hourlyRate;       // Lương theo giờ làm việc bình thường
    double overtimeRate;     // Lương làm thêm giờ
    double holidayRate;      // Lương làm trong ngày lễ

public:
    /**
     * @brief Constructor cho SalaryCalculator.
     *
     * Khởi tạo đối tượng tính toán lương với các mức lương theo giờ làm việc
     * bình thường, tăng ca và ngày lễ.
     *
     * @param hrRate Mức lương theo giờ làm việc bình thường.
     * @param otRate Mức lương theo giờ làm thêm.
     * @param hdRate Mức lương theo giờ làm việc trong ngày lễ.
     */
    SalaryCalculator(double hrRate, double otRate, double hdRate);

    /**
     * @brief Tính lương của nhân viên dựa trên thông tin chấm công và các khoản phúc lợi.
     *
     * Phương thức này nhận vào đối tượng Attendance để lấy dữ liệu chấm công,
     * cùng với các khoản thưởng, phụ cấp và khấu trừ đã được tổng hợp từ WelfareManager,
     * để tính toán chi tiết và tổng lương.
     *
     * @param attendance Tham chiếu hằng đến đối tượng Attendance quản lý chấm công.
     * @param employeeId Mã nhân viên cần tính lương.
     * @param bonuses Các khoản thưởng.
     * @param allowances Các khoản trợ cấp.
     * @param deductions Các khoản khấu trừ.
     * @return Trả về đối tượng SalaryDetails chứa thông tin chi tiết về lương.
     */
    SalaryDetails calculateSalary(const Attendance& attendance, const std::string& employeeId,
        double bonuses, double allowances, double deductions);
};

/**
 * @brief Lớp hỗ trợ hiển thị thông tin lương.
 *
 * Lớp này có một phương thức tĩnh hoặc phương thức thành viên để in ra
 * các chi tiết của một đối tượng SalaryDetails.
 */
class ShowSalary {
public:
    /**
     * @brief Hiển thị chi tiết lương của nhân viên lên console.
     *
     * In ra các thành phần lương như lương cơ bản, lương tăng ca,
     * lương ngày lễ, thưởng, phụ cấp, khấu trừ và tổng lương.
     *
     * @param details Tham chiếu hằng đến đối tượng SalaryDetails cần hiển thị.
     */
    void showSalary(const SalaryDetails& details);
};

#endif // _SALARY_H_