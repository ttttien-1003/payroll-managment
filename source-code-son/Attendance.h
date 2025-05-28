#ifndef ATTENDANCE_H
#define ATTENDANCE_H

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <fstream>

/**
 * @class Attendance
 * @brief Lớp quản lý thông tin chấm công của nhân viên.
 *
 * Lớp này lưu trữ thông tin chấm công của nhân viên, bao gồm mã nhân viên,
 * ngày làm việc, giờ check-in, giờ check-out. Nó cũng cung cấp các phương thức
 * để tính toán số giờ làm việc và chuyển đổi dữ liệu sang định dạng CSV.
 */
class Attendance {
private:
    std::string employeeId;  ///< Mã nhân viên
    std::string workDate;    ///< Ngày làm việc (định dạng YYYY-MM-DD)
    std::string checkInTime; ///< Giờ check-in (định dạng HH:MM:SS)
    std::string checkOutTime; ///< Giờ check-out (định dạng HH:MM:SS)

public:
    /**
     * @brief Constructor khởi tạo đối tượng Attendance.
     *
     * @param employeeId Mã nhân viên.
     * @param workDate Ngày làm việc (định dạng YYYY-MM-DD).
     * @param checkInTime Giờ check-in (định dạng HH:MM:SS).
     * @param checkOutTime Giờ check-out (định dạng HH:MM:SS).
     */
    Attendance(const std::string& employeeId, const std::string& workDate,
        const std::string& checkInTime, const std::string& checkOutTime);

    /**
     * @brief Lấy mã nhân viên.
     *
     * @return Mã nhân viên.
     */
    const std::string& getEmployeeId() const;

    /**
     * @brief Lấy ngày làm việc.
     *
     * @return Ngày làm việc (định dạng YYYY-MM-DD).
     */
    const std::string& getWorkDate() const;

    /**
     * @brief Lấy giờ check-in.
     *
     * @return Giờ check-in (định dạng HH:MM:SS).
     */
    const std::string& getCheckInTime() const;

    /**
     * @brief Lấy giờ check-out.
     *
     * @return Giờ check-out (định dạng HH:MM:SS).
     */
    const std::string& getCheckOutTime() const;

    /**
     * @brief Cập nhật giờ check-out.
     *
     * @param checkOutTime Giờ check-out mới (định dạng HH:MM:SS).
     */
    void setCheckOutTime(const std::string& checkOutTime);

    /**
     * @brief Tính số giờ làm việc trong ngày.
     *
     * @return Số giờ làm việc (tính bằng giờ, dạng số thực).
     */
    double calculateWorkHours() const;

    /**
     * @brief Chuyển đổi đối tượng Attendance thành chuỗi CSV.
     *
     * @return Chuỗi CSV chứa thông tin chấm công.
     */
    std::string toCSV() const;

    /**
     * @brief Tạo đối tượng Attendance từ một chuỗi CSV.
     *
     * @param csvLine Chuỗi CSV chứa thông tin chấm công.
     * @return Đối tượng Attendance được tạo từ chuỗi CSV.
     */
    static Attendance fromCSV(const std::string& csvLine);
};

std::vector<Attendance> loadAttendanceFromFile(const std::string& filename);

void saveAttendanceToFile(const std::string& filename, const std::vector<Attendance>& attendanceRecords);


#endif