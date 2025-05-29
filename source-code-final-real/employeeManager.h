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
    void addEmployee(std::shared_ptr<IEmployee> emp);
    void deleteEmployee(const std::string& empId);
    std::shared_ptr<IEmployee> findEmployeeById(const std::string& empId) const;
    void displayAllEmployees() const;
    void displayEmployeeDetails(const std::string& empId) const;
    const std::vector<std::shared_ptr<IEmployee>>& getEmployees() const;

    // --- Quản lý Chấm công ---
    void addAttendanceRecord(const AttendanceRecord& record);
    void loadAttendanceFromFile(const std::string& filename);

    // --- Tính toán & In Lương ---
    void printPayroll(const std::string& empId);
    void printAllPayrolls(const std::string& filename);
};

#endif // EMPLOYEE_MANAGER_H