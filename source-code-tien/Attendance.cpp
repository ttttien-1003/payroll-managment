#include "Attendance.h"

// Hàm thêm một bản ghi chấm công vào danh sách
void Attendance::addRecord(const AttendanceRecord& record) {
    records.push_back(record);
}

// Hàm lấy tổng giờ làm việc bình thường của nhân viên
int Attendance::getTotalWorkHours(const std::string& employeeId) const {
    int totalHours = 0;
    for (const auto& record : records) {
        if (record.employeeId == employeeId && record.dayType == "normal") {
            totalHours += record.checkOutHour - record.checkInHour;
        }
    }
    return totalHours;
}

// Hàm lấy tổng giờ tăng ca của nhân viên
int Attendance::getOvertimeHours(const std::string& employeeId) const {
    int overtimeHours = 0;
    for (const auto& record : records) {
        if (record.employeeId == employeeId && record.dayType == "overtime") {
            overtimeHours += record.checkOutHour - record.checkInHour;
        }
    }
    return overtimeHours;
}

// Hàm lấy số ngày làm việc trong ngày lễ của nhân viên
int Attendance::getHolidayWorkDays(const std::string& employeeId) const {
    int holidayDays = 0;
    for (const auto& record : records) {
        if (record.employeeId == employeeId && record.dayType == "holiday") {
            holidayDays++;
        }
    }
    return holidayDays;
}

// Hàm lấy số ngày nghỉ phép có lương của nhân viên
int Attendance::getLeavePaidDays(const std::string& employeeId) const {
    int leaveDays = 0;
    for (const auto& record : records) {
        if (record.employeeId == employeeId && record.dayType == "leave") {
            leaveDays++;
        }
    }
    return leaveDays;
}

// Hàm lấy số ngày nghỉ không phép (không lương) của nhân viên
int Attendance::getLeaveUnpaidDays(const std::string& employeeId) const {
    int unpaidDays = 0;
    for (const auto& record : records) {
        if (record.employeeId == employeeId && record.dayType == "leave_unpaid") {
            unpaidDays++;
        }
    }
    return unpaidDays;
}
