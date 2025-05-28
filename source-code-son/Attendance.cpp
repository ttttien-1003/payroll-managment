#include "Attendance.h"
#include <iomanip>

// Constructor
Attendance::Attendance(const std::string& employeeId, const std::string& workDate,
    const std::string& checkInTime, const std::string& checkOutTime)
    : employeeId(employeeId), workDate(workDate), checkInTime(checkInTime), checkOutTime(checkOutTime) {
}

// Getters
const std::string& Attendance::getEmployeeId() const { return employeeId; }
const std::string& Attendance::getWorkDate() const { return workDate; }
const std::string& Attendance::getCheckInTime() const { return checkInTime; }
const std::string& Attendance::getCheckOutTime() const { return checkOutTime; }

// Setters
void Attendance::setCheckOutTime(const std::string& checkOutTime) { this->checkOutTime = checkOutTime; }

// Helper function to convert time string to seconds
static int timeToSeconds(const std::string& timeStr) {
    std::istringstream ss(timeStr);
    int hours, minutes, seconds;
    char colon;
    ss >> hours >> colon >> minutes >> colon >> seconds;
    return hours * 3600 + minutes * 60 + seconds;
}

// Tính số giờ làm việc
double Attendance::calculateWorkHours() const {
    int checkInSeconds = timeToSeconds(checkInTime);
    int checkOutSeconds = timeToSeconds(checkOutTime);
    return (checkOutSeconds - checkInSeconds) / 3600.0; // Chuyển đổi từ giây sang giờ
}

// Chuyển đổi đối tượng thành chuỗi CSV
std::string Attendance::toCSV() const {
    std::ostringstream oss;
    oss << employeeId << "," << workDate << "," << checkInTime << "," << checkOutTime;
    return oss.str();
}

// Tạo đối tượng từ chuỗi CSV
Attendance Attendance::fromCSV(const std::string& csvLine) {
    std::istringstream ss(csvLine);
    std::string employeeId, workDate, checkInTime, checkOutTime;

    std::getline(ss, employeeId, ',');
    std::getline(ss, workDate, ',');
    std::getline(ss, checkInTime, ',');
    std::getline(ss, checkOutTime, ',');

    return Attendance(employeeId, workDate, checkInTime, checkOutTime);
}