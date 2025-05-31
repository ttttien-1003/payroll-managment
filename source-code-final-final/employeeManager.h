#ifndef EMPLOYEE_MANAGER_H
#define EMPLOYEE_MANAGER_H

#include "IEmployee.h"
#include "AttendanceManager.h"
#include "WelfareManager.h"
#include "PayrollPrinter.h"
#include <vector>
#include <memory>
#include <string>

/**
 * @brief Lớp chính quản lý tất cả các hoạt động liên quan đến nhân viên.
 */
class EmployeeManager {
private:
    std::vector<std::shared_ptr<IEmployee>> _employeeList; // Danh sách nhân viên
    AttendanceManager _attendanceManager;                   // Quản lý chấm công
    WelfareManager _welfareManager;                         // Quản lý phúc lợi
    PayrollPrinter _payrollPrinter;                         // Dùng để in phiếu lương

public:
    // Constructor
    EmployeeManager();

    // --- Quản lý Nhân viên (CRUD) ---
    bool addEmployee(std::shared_ptr<IEmployee> emp);
    std::shared_ptr<IEmployee> findEmployeeById(const std::string& empId) const;
    void displayAllEmployees(int frameX, int frameY, int frameWidth, int frameHeight) const;
    void displayEmployeeDetails(const std::string& empId) const;
    const std::vector<std::shared_ptr<IEmployee>>& getEmployees() const;

    // --- Phương thức mới để tải dữ liệu từ file ---
    /**
     * @brief Tải danh sách nhân viên từ file, thay thế danh sách hiện tại.
     * @param filename Tên file chứa dữ liệu nhân viên.
     * @return true nếu tải thành công, false nếu có lỗi.
     */
    bool loadFromFile(const std::string& filename);

    /**
     * @brief Xóa nhân viên theo ID.
     * @param empId Mã nhân viên cần xóa.
     * @return true nếu xóa thành công, false nếu không tìm thấy nhân viên.
     */
    bool deleteEmployee(const std::string& empId); // Thay đổi từ void sang bool

    // --- Quản lý Chấm công ---
    void addAttendanceRecord(const AttendanceRecord& record);
    void loadAttendanceFromFile(const std::string& filename);

    // --- Tính toán & In Lương ---
    void printPayroll(const std::string& empId, int month, int year); // Thêm month, year
    void printAllPayrolls(const std::string& filename, int month, int year); // Thêm month, year

};

#endif // EMPLOYEE_MANAGER_H