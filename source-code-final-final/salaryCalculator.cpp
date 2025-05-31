#include "SalaryCalculator.h"
#include "AttendanceManager.h"
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <iostream>
#include "utils.h" // Để sử dụng parseWorkDate

// Constructor
SalaryCalculator::SalaryCalculator(double hrRate, double otRate, double hdRate)
    : _hourlyRate(hrRate), _overtimeRate(otRate), _holidayRate(hdRate) {
}

/**
 * @brief Tính lương chi tiết cho nhân viên, có xét ngày lễ.
 */
SalaryDetails SalaryCalculator::calculateSalary(const AttendanceManager& attendance, const std::string& employeeId, 
                                              int targetMonth, int targetYear, double baseSalary,
                                              double bonuses, double allowances, double deductions) {
    SalaryDetails details;
    details.basicSalary = 0.0;
    details.overtimeSalary = 0.0;
    details.holidaySalary = 0.0;

    const auto& allRecords = attendance.getRecords();
    // std::cout << "SalaryCalculator: Tinh luong cho NV " << employeeId << " Thang: " << targetMonth << " Nam: " << targetYear << ". So records tong: " << allRecords.size() << std::endl;


    for (const auto& record : allRecords) {
        if (record.employeeId != employeeId) {
            continue;
        }

        // std::cout << "  Dang xet record: Date '" << record.workDate << "', Type '" << record.dayType << "'" << std::endl;

        int recYear = 0, recMonth = 0; // Không cần recDay nếu chỉ lọc theo tháng/năm

        // Trích xuất năm và tháng từ chuỗi YYYY-MM-DD
        if (record.workDate.length() == 10 && record.workDate[4] == '-' && record.workDate[7] == '-') {
            try {
                recYear = std::stoi(record.workDate.substr(0, 4));
                recMonth = std::stoi(record.workDate.substr(5, 2));
            } catch (const std::exception& e) {
                std::cerr << "LOI phan tich ngay (YYYY-MM-DD) '" << record.workDate << "': " << e.what() << std::endl;
                continue; // Bỏ qua bản ghi nếu không parse được năm/tháng
            }
        } else {
            // std::cerr << "CANH BAO: Dinh dang ngay trong record khong dung YYYY-MM-DD: " << record.workDate << ". Bo qua." << std::endl;
            continue; // Bỏ qua bản ghi nếu định dạng không phải YYYY-MM-DD
        }
        
        // std::cout << "    -> Record Parsed: Year=" << recYear << ", Month=" << recMonth << std::endl;

        if (recYear != targetYear || recMonth != targetMonth) {
            // std::cout << "    -> KHONG KHOP THANG/NAM TARGET." << std::endl;
            continue; // Bỏ qua các bản ghi không thuộc tháng/năm cần tính
        }

        // std::cout << "    -> KHOP THANG/NAM. CheckIn: " << record.checkInTime << ", CheckOut: " << record.checkOutTime << std::endl;
        double dailyTotalHours = (AttendanceManager::timeToSeconds(record.checkOutTime) - AttendanceManager::timeToSeconds(record.checkInTime)) / 3600.0;
        // std::cout << "    -> dailyTotalHours: " << dailyTotalHours << std::endl;

        if (dailyTotalHours < 0) dailyTotalHours = 0; // Xử lý trường hợp giờ check out < check in (dữ liệu lỗi)

        // attendance.isHoliday sẽ hoạt động đúng nếu record.workDate là YYYY-MM-DD
        if (attendance.isHoliday(record.workDate) || record.dayType == "holiday") {
            // std::cout << "      -> La ngay le HOAC dayType holiday. Cong vao holidaySalary." << std::endl;
            details.holidaySalary += dailyTotalHours * _holidayRate;
        } else {
            if (record.dayType == "normal") {
                // std::cout << "      -> La ngay normal. Cong vao basicSalary." << std::endl;
                details.basicSalary += dailyTotalHours * _hourlyRate;
            } else if (record.dayType == "overtime") {
                // std::cout << "      -> La ngay overtime. Cong vao overtimeSalary." << std::endl;
                details.overtimeSalary += dailyTotalHours * _overtimeRate;
            }
        }
    }

    details.bonuses = bonuses;
    details.allowances = allowances;
    details.deductions = deductions;

    details.totalSalary = baseSalary + details.basicSalary + details.overtimeSalary + details.holidaySalary
                        + details.bonuses + details.allowances - details.deductions;
    
    // std::cout << "  SalaryCalculator KET QUA: Basic=" << details.basicSalary 
    //           << ", OT=" << details.overtimeSalary 
    //           << ", Holiday=" << details.holidaySalary 
    //           << ", Total=" << details.totalSalary << std::endl;

    return details;
}