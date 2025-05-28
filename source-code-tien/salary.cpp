#include "Salary.h"

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
SalaryCalculator::SalaryCalculator(double hrRate, double otRate, double hdRate)
    : hourlyRate(hrRate), overtimeRate(otRate), holidayRate(hdRate) {
}

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
SalaryDetails SalaryCalculator::calculateSalary(const Attendance& attendance, const std::string& employeeId,
    double bonuses, double allowances, double deductions) {
    SalaryDetails details;

    // Lấy các thông tin chấm công từ Attendance
    int workHours = attendance.getTotalWorkHours(employeeId);      // Tổng giờ làm việc
    int overtimeHours = attendance.getOvertimeHours(employeeId);   // Tổng giờ tăng ca
    int holidayDays = attendance.getHolidayWorkDays(employeeId);   // Tổng số ngày làm ngày lễ
    int leaveUnpaidDays = attendance.getLeaveUnpaidDays(employeeId); // Số ngày nghỉ không phép

    // Tính lương cơ bản (giờ làm việc * đơn giá theo giờ)
    details.basicSalary = workHours * hourlyRate;

    // Tính lương tăng ca (giờ tăng ca * đơn giá tăng ca)
    details.overtimeSalary = overtimeHours * overtimeRate;

    // Tính lương làm việc trong ngày lễ (ngày lễ * đơn giá ngày lễ * số giờ làm trung bình một ngày, giả định 8 giờ)
    details.holidaySalary = holidayDays * holidayRate * 8; // Assuming 8 hours for a holiday work day.

    // Tính khấu trừ cho những ngày nghỉ không phép (ngày nghỉ * giờ làm * đơn giá)
    details.deductions = leaveUnpaidDays * hourlyRate * 8; // Assuming 8 hours lost per unpaid leave day.

    // Gán các khoản thưởng và trợ cấp
    details.bonuses = bonuses;
    details.allowances = allowances;

    // Tính tổng lương
    details.totalSalary = details.basicSalary + details.overtimeSalary + details.holidaySalary
        + details.bonuses + details.allowances - details.deductions;

    // Trả về chi tiết lương sau khi tính toán
    return details;
}

/**
 * @brief Hiển thị chi tiết lương của nhân viên lên console.
 *
 * In ra các thành phần lương như lương cơ bản, lương tăng ca,
 * lương ngày lễ, thưởng, phụ cấp, khấu trừ và tổng lương.
 *
 * @param details Tham chiếu hằng đến đối tượng SalaryDetails cần hiển thị.
 */
void ShowSalary::showSalary(const SalaryDetails& details) {
    std::cout << "Basic Salary: " << details.basicSalary << std::endl;
    std::cout << "Overtime Salary: " << details.overtimeSalary << std::endl;
    std::cout << "Holiday Salary: " << details.holidaySalary << std::endl;
    std::cout << "Bonuses: " << details.bonuses << std::endl;
    std::cout << "Allowances: " << details.allowances << std::endl;
    std::cout << "Deductions: " << details.deductions << std::endl;
    std::cout << "------------------------" << std::endl;
    std::cout << "Total Salary: " << details.totalSalary << std::endl;
}