#ifndef ATTENDANCE_MANAGER_H
#define ATTENDANCE_MANAGER_H

#include "globaldefinitions.h" // Đảm bảo đường dẫn này đúng
#include <string>
#include <vector>

/**
 * @class AttendanceManager
 * @brief Lớp quản lý dữ liệu chấm công của tất cả nhân viên.
 * Hoạt động với AttendanceRecord mới bao gồm dayType.
 */
class AttendanceManager {
private:
    std::vector<AttendanceRecord> _records;
    static std::vector<std::string> _holidays; // Danh sách ngày lễ cố định

public:
    /**
     * @brief Constructor mặc định.
     */
    AttendanceManager() = default;

    /**
     * @brief Chuyển đổi chuỗi thời gian "HH:MM:SS" thành tổng số giây.
     * Hàm này public static để các lớp khác có thể sử dụng khi cần.
     */
    static int timeToSeconds(const std::string& timeStr);

    /**
     * @brief Thêm một bản ghi chấm công.
     */
    void addRecord(const AttendanceRecord& record);

    /**
     * @brief Lấy tất cả các bản ghi chấm công hiện có.
     */
    const std::vector<AttendanceRecord>& getRecords() const;

    /**
     * @brief Tải dữ liệu chấm công từ file CSV.
     * File CSV cần có các cột: EmployeeID,WorkDate,CheckInTime,CheckOutTime,DayType
     */
    void loadFromFile(const std::string& filename);

    /**
     * @brief Kiểm tra xem một ngày (theo chuỗi "YYYY-MM-DD") có phải là ngày lễ cố định không.
     */
    bool isHoliday(const std::string& date) const;

    // --- CÁC HÀM LẤY DỮ LIỆU CHẤM CÔNG THEO LOGIC CŨ CỦA BẠN ---
    // Các hàm này sẽ sử dụng 'dayType' và tính toán thời gian dựa trên string

    /**
     * @brief Lấy tổng giờ làm việc bình thường của nhân viên.
     * Dựa vào dayType == "normal" và tính thời gian.
     */
    int getTotalWorkHours(const std::string& employeeId) const;

    /**
     * @brief Lấy tổng giờ tăng ca của nhân viên.
     * Dựa vào dayType == "overtime" và tính thời gian.
     */
    int getOvertimeHours(const std::string& employeeId) const;

    /**
     * @brief Lấy số ngày làm việc trong ngày lễ của nhân viên.
     * Dựa vào dayType == "holiday".
     */
    int getHolidayWorkDays(const std::string& employeeId) const;

    /**
     * @brief Lấy số ngày nghỉ không phép (không lương) của nhân viên.
     * Dựa vào dayType == "leave_unpaid".
     */
    int getLeaveUnpaidDays(const std::string& employeeId) const;

    /**
     * @brief Lấy số ngày nghỉ phép có lương của nhân viên (nếu bạn cần).
     * Dựa vào dayType == "leave".
     */
    int getLeavePaidDays(const std::string& employeeId) const; // Thêm hàm này nếu cần
};

#endif // ATTENDANCE_MANAGER_H