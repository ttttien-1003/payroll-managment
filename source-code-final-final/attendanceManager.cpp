#include "AttendanceManager.h" // Hoặc "Attendance.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath> // Để dùng floor
#include "utils.h"

// Khởi tạo danh sách ngày lễ cố định (MM-DD)
std::vector<std::string> AttendanceManager::_holidays = {
    "01-01", "04-30", "05-01", "09-02"
};

/**
 * @brief Chuyển đổi chuỗi thời gian "HH:MM:SS" thành tổng số giây.
 */
int AttendanceManager::timeToSeconds(const std::string& timeStr) {
    if (timeStr.empty() || timeStr.find(':') == std::string::npos) {
        // Trả về 0 hoặc ném lỗi nếu định dạng thời gian không hợp lệ / rỗng
        return 0;
    }
    std::stringstream ss(timeStr);
    int hours = 0, minutes = 0, seconds = 0;
    char colon;
    ss >> hours >> colon >> minutes >> colon >> seconds;
    return hours * 3600 + minutes * 60 + seconds;
}

/**
 * @brief Thêm một bản ghi chấm công.
 */
void AttendanceManager::addRecord(const AttendanceRecord& record) {
    _records.push_back(record);
}

/**
 * @brief Lấy danh sách tất cả các bản ghi.
 */
const std::vector<AttendanceRecord>& AttendanceManager::getRecords() const {
    return _records;
}

/**
 * @brief Tải dữ liệu chấm công từ file CSV.
 * Định dạng CSV: EmployeeID,WorkDate,CheckInTime,CheckOutTime,DayType
 */
void AttendanceManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Loi: Khong the mo file cham cong: " << filename << std::endl;
        _records.clear(); // Đảm bảo records rỗng nếu không mở được file
        return;
    }
    _records.clear(); // Xóa dữ liệu cũ trước khi tải
    std::string line;
    std::getline(inFile, line); // Bỏ qua dòng tiêu đề (EmployeeID,WorkDate,...)

    int count = 0;
    while (std::getline(inFile, line)) {
        if (line.empty()) continue; // Bỏ qua dòng trống

        std::stringstream ss(line);
        AttendanceRecord rec;
        
        std::getline(ss, rec.employeeId, ',');
        std::getline(ss, rec.workDate, ','); // Đọc trực tiếp YYYY-MM-DD
        std::getline(ss, rec.checkInTime, ',');
        std::getline(ss, rec.checkOutTime, ',');
        std::getline(ss, rec.dayType); // Đọc đến hết dòng cho dayType

        // Xóa khoảng trắng thừa nếu có (ví dụ từ cuối dòng)
        rec.employeeId.erase(rec.employeeId.find_last_not_of(" \n\r\t") + 1);
        rec.workDate.erase(rec.workDate.find_last_not_of(" \n\r\t") + 1);
        rec.checkInTime.erase(rec.checkInTime.find_last_not_of(" \n\r\t") + 1);
        rec.checkOutTime.erase(rec.checkOutTime.find_last_not_of(" \n\r\t") + 1);
        rec.dayType.erase(rec.dayType.find_last_not_of(" \n\r\t") + 1);

        // Kiểm tra cơ bản định dạng ngày YYYY-MM-DD (tùy chọn, nhưng nên có)
        if (rec.workDate.length() == 10 && rec.workDate[4] == '-' && rec.workDate[7] == '-') {
            // Định dạng có vẻ đúng
        } else {
            std::cerr << "CANH BAO: Dinh dang ngay khong dung YYYY-MM-DD trong attendance.csv: "
                      << rec.workDate << " cho NV " << rec.employeeId << ". Bo qua ban ghi." << std::endl;
            continue; // Bỏ qua bản ghi có ngày không đúng định dạng mong muốn
        }

        if (!rec.employeeId.empty()) {
            _records.push_back(rec);
            count++;
        }
    }
    inFile.close();
    //std::cout << "Da tai " << count << " ban ghi cham cong tu file " << filename << std::endl;
}

/**
 * @brief Kiểm tra xem một ngày có phải là ngày lễ cố định không.
 */
bool AttendanceManager::isHoliday(const std::string& date) const {
    if (date.length() < 10) return false;
    std::string monthDay = date.substr(5, 5);
    return std::find(_holidays.begin(), _holidays.end(), monthDay) != _holidays.end();
}

// --- CÁC HÀM TÍNH TOÁN THEO LOGIC CŨ CỦA BẠN (ĐÃ SỬA) ---

int AttendanceManager::getTotalWorkHours(const std::string& employeeId) const {
    double totalHours = 0;
    for (const auto& record : _records) {
        if (record.employeeId == employeeId && record.dayType == "normal") {
            // Tính toán thời gian từ string
            if (!record.checkInTime.empty() && !record.checkOutTime.empty()) {
                totalHours += (timeToSeconds(record.checkOutTime) - timeToSeconds(record.checkInTime)) / 3600.0;
            }
        }
    }
    return static_cast<int>(floor(totalHours));
}

int AttendanceManager::getOvertimeHours(const std::string& employeeId) const {
    double overtimeHours = 0;
    for (const auto& record : _records) {
        if (record.employeeId == employeeId && record.dayType == "overtime") {
            // Tính toán thời gian từ string
            if (!record.checkInTime.empty() && !record.checkOutTime.empty()) {
                overtimeHours += (timeToSeconds(record.checkOutTime) - timeToSeconds(record.checkInTime)) / 3600.0;
            }
        }
    }
    return static_cast<int>(floor(overtimeHours));
}

int AttendanceManager::getHolidayWorkDays(const std::string& employeeId) const {
    int holidayDays = 0;
    for (const auto& record : _records) {
        if (record.employeeId == employeeId && record.dayType == "holiday") {
            holidayDays++;
        }
    }
    return holidayDays;
}

int AttendanceManager::getLeaveUnpaidDays(const std::string& employeeId) const {
    int unpaidDays = 0;
    for (const auto& record : _records) {
        if (record.employeeId == employeeId && record.dayType == "leave_unpaid") {
            unpaidDays++;
        }
    }
    return unpaidDays;
}

int AttendanceManager::getLeavePaidDays(const std::string& employeeId) const {
    int leaveDays = 0;
    for (const auto& record : _records) {
        if (record.employeeId == employeeId && record.dayType == "leave") {
            leaveDays++;
        }
    }
    return leaveDays;
}