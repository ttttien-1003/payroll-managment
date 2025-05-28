#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
#include <vector>
#include <unordered_map>
#include "globalDefinitions.h"


// Lớp quản lý chấm công của nhân viên
class Attendance {
public:
    std::vector<AttendanceRecord> records;  // Danh sách các bản ghi chấm công

    // Thêm một bản ghi chấm công
    void addRecord(const AttendanceRecord& record);

    // Lấy tổng giờ làm việc của nhân viên
    int getTotalWorkHours(const std::string& employeeId) const;

    // Lấy tổng giờ tăng ca của nhân viên
    int getOvertimeHours(const std::string& employeeId) const;

    // Lấy số ngày làm việc trong ngày lễ
    int getHolidayWorkDays(const std::string& employeeId) const;

    // Lấy số ngày nghỉ phép hợp lệ (có lương)
    int getLeavePaidDays(const std::string& employeeId) const;

    // Lấy số ngày nghỉ không phép (không có lương)
    int getLeaveUnpaidDays(const std::string& employeeId) const;
};

#endif
