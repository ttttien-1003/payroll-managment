#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "IEmployee.h"
#include "Attendance.h"     // Cần để quản lý chấm công
#include "IWelfare.h"       // Cần để quản lý phúc lợi
#include "Salary.h"         // Cần để hiển thị chi tiết lương
#include <vector>
#include <memory>
#include <iostream>
#include <algorithm>

// Bao gồm các header phúc lợi cụ thể để có thể tạo đối tượng
#include "bonusWelfare.h"
#include "socialinsuranceWelfare.h"
#include "transportationWelfare.h"

class EmployeeManager {
private:
    std::vector<std::shared_ptr<IEmployee>> employeeList; // Danh sách nhân viên
    Attendance attendance;                                // Đối tượng quản lý chấm công
    WelfareManager welfareManager;                        // Đối tượng quản lý phúc lợi

public:
    /**
     * @brief Constructor mặc định cho EmployeeManager.
     * Khởi tạo các phúc lợi mặc định cho hệ thống.
     */
    EmployeeManager();

    // Thêm nhân viên mới
    void addEmployee(const std::shared_ptr<IEmployee>& emp);

    // Sửa hồ sơ nhân viên
    // Lưu ý: Việc modify một shared_ptr cần cẩn thận để không làm mất dữ liệu
    // hoặc gây lỗi nếu đối tượng cũ vẫn đang được tham chiếu ở nơi khác.
    // Trong ví dụ này, chúng ta sẽ thay thế hoàn toàn đối tượng.
    void modifyEmployee(const std::string& empId, const std::shared_ptr<IEmployee>& updatedEmp);

    // Xóa hồ sơ nhân viên
    void deleteEmployee(const std::string& empId);

    // Hiển thị hồ sơ nhân viên cụ thể
    void displayEmployeeById(const std::string& empId) const;

    // Hiển thị danh sách toàn bộ nhân viên
    void displayAllEmployees() const;

    /**
     * @brief In phiếu lương nhân viên.
     * Phương thức này sẽ tính toán lương dựa trên chấm công và các phúc lợi.
     * @param empId ID nhân viên cần in phiếu lương.
     */
    void printPayroll(const std::string& empId) const;

    /**
     * @brief Hiển thị thông tin chi tiết của một nhân viên.
     * @param emp Con trỏ shared_ptr đến đối tượng IEmployee.
     */
    void displayEmployee(const std::shared_ptr<IEmployee>& emp) const;

    /**
     * @brief Thêm một bản ghi chấm công.
     * @param record Bản ghi chấm công.
     */
    void addAttendanceRecord(const AttendanceRecord& record);
};

#endif // EMPLOYEE_MANAGER_H