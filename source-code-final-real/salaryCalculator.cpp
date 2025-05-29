#include "SalaryCalculator.h"
#include "AttendanceManager.h"
#include <algorithm>

// Constructor
SalaryCalculator::SalaryCalculator(double hrRate, double otRate, double hdRate)
    : _hourlyRate(hrRate), _overtimeRate(otRate), _holidayRate(hdRate) {
}

/**
 * @brief Tính lương chi tiết cho nhân viên, có xét ngày lễ.
 */
SalaryDetails SalaryCalculator::calculateSalary(const AttendanceManager& attendance, const std::string& employeeId, double baseSalary,
    double bonuses, double allowances, double deductions) {
    SalaryDetails details;
    const auto& allRecords = attendance.getRecords();

    for (const auto& record : allRecords) {
        if (record.employeeId != employeeId) {
            continue; // Bỏ qua nếu không phải bản ghi của nhân viên này
        }

        double dailyTotalHours = (AttendanceManager::timeToSeconds(record.checkOutTime) - AttendanceManager::timeToSeconds(record.checkInTime)) / 3600.0;

        // KIỂM TRA NGÀY LỄ KHI TÍNH LƯƠNG
        if (attendance.isHoliday(record.workDate) || record.dayType == "holiday") {
            details.holidaySalary += dailyTotalHours * _holidayRate;
        }
        else {
            // Nếu không phải ngày lễ, tính lương bình thường và tăng ca
            if (record.dayType == "normal") {
                details.basicSalary += dailyTotalHours * _hourlyRate;
            }
            else if (record.dayType == "overtime") {
                details.overtimeSalary += dailyTotalHours * _overtimeRate;
            }
        }
    }

    // Gán các khoản thưởng, phụ cấp, và khấu trừ
    details.bonuses = bonuses;
    details.allowances = allowances;
    details.deductions = deductions;

    // Tính tổng lương cuối cùng
    details.totalSalary = baseSalary + details.basicSalary + details.overtimeSalary + details.holidaySalary
        + details.bonuses + details.allowances - details.deductions;

    return details;
}