#include "App.h"
#include <iostream>
#include <memory> // For std::make_shared

// Include specific employee types and other necessary components
#include "fulltimeemployee.h"
#include "contractualemployee.h"
#include "intern.h"
#include "Attendance.h" // For AttendanceRecord struct
#include "Salary.h"     // For SalaryDetails and ShowSalary (if needed directly)

/**
 * @brief Constructor mặc định cho lớp App.
 * Khởi tạo EmployeeManager.
 */
App::App() {
    // EmployeeManager is already initialized as a member, its constructor handles welfare setup.
    // Không cần thêm logic khởi tạo đặc biệt ở đây, vì empManager là một thành viên và
    // constructor mặc định của nó (EmployeeManager::EmployeeManager()) đã được gọi.
}

/**
 * @brief Chạy ứng dụng.
 * Phương thức này chứa luồng chính của chương trình, bao gồm
 * thêm nhân viên, thêm chấm công, in phiếu lương, sửa và xóa.
 */
void App::run() {
    // --- 1. Thêm nhân viên ---
    std::cout << "--- Thêm nhân viên ---" << std::endl;

    // Fulltime Employee
    auto emp1 = std::make_shared<FulltimeEmployee>("EMP001", "Nguyen Van A", "Quan 1, TP.HCM", "0901234567", 24, 15000000.0);
    empManager.addEmployee(emp1);

    // Contractual Employee
    auto emp2 = std::make_shared<ContractualEmployee>("EMP002", "Tran Thi B", "Di An, Binh Duong", "0908765432", 8000000.0, 10, "2025-12-31");
    empManager.addEmployee(emp2);

    // Intern
    auto emp3 = std::make_shared<Intern>("EMP003", "Le Van C", "Quan 7, TP.HCM", "0912345678", 3000000.0, 3, "2024-08-31");
    empManager.addEmployee(emp3);

    std::cout << "\n--- Danh sách tất cả nhân viên ---" << std::endl;
    empManager.displayAllEmployees();

    // --- 2. Thêm bản ghi chấm công ---
    std::cout << "\n--- Thêm bản ghi chấm công ---" << std::endl;

    // Attendance for EMP001 (Fulltime Employee)
    empManager.addAttendanceRecord({ "EMP001", "2024-05-01", 8, 17, "normal" }); // 9 hours normal work
    empManager.addAttendanceRecord({ "EMP001", "2024-05-02", 8, 19, "overtime" }); // 2 hours overtime
    empManager.addAttendanceRecord({ "EMP001", "2024-05-03", 8, 17, "normal" });
    empManager.addAttendanceRecord({ "EMP001", "2024-05-04", 0, 0, "leave" }); // Paid leave (no work hours, but not unpaid deduction)

    // Attendance for EMP002 (Contractual Employee)
    empManager.addAttendanceRecord({ "EMP002", "2024-05-01", 8, 17, "normal" });
    empManager.addAttendanceRecord({ "EMP002", "2024-05-02", 8, 17, "normal" });
    empManager.addAttendanceRecord({ "EMP002", "2024-05-03", 0, 0, "leave_unpaid" }); // Unpaid leave (will be deducted)
    empManager.addAttendanceRecord({ "EMP002", "2024-05-04", 8, 17, "normal" });

    // Attendance for EMP003 (Intern)
    empManager.addAttendanceRecord({ "EMP003", "2024-05-01", 8, 17, "normal" });
    empManager.addAttendanceRecord({ "EMP003", "2024-05-02", 8, 17, "normal" });

    // Attendance for EMP004 (Director)
    empManager.addAttendanceRecord({ "EMP004", "2024-05-01", 9, 18, "normal" });
    empManager.addAttendanceRecord({ "EMP004", "2024-05-02", 9, 18, "normal" });


    // --- 3. In phiếu lương ---
    std::cout << "\n--- In phiếu lương nhân viên EMP001 ---" << std::endl;
    empManager.printPayroll("EMP001");

    std::cout << "\n--- In phiếu lương nhân viên EMP002 ---" << std::endl;
    empManager.printPayroll("EMP002");

    std::cout << "\n--- In phiếu lương nhân viên EMP003 ---" << std::endl;
    empManager.printPayroll("EMP003");

    std::cout << "\n--- In phiếu lương nhân viên EMP004 ---" << std::endl;
    empManager.printPayroll("EMP004");

    // --- 4. Sửa thông tin nhân viên ---
    std::cout << "\n--- Sửa thông tin nhân viên EMP001 ---" << std::endl;
    // Tạo một shared_ptr mới với thông tin cập nhật cho EMP001
    auto updatedEmp1 = std::make_shared<FulltimeEmployee>("EMP001", "Nguyen Van A (Updated)", "Quan 3, TP.HCM", "0900000000", 25, 16000000.0);
    empManager.modifyEmployee("EMP001", updatedEmp1);
    empManager.displayEmployeeById("EMP001"); // Hiển thị thông tin đã cập nhật

    // --- 5. Xóa nhân viên ---
    std::cout << "\n--- Xóa nhân viên EMP003 ---" << std::endl;
    empManager.deleteEmployee("EMP003");
    std::cout << "\n--- Danh sách tất cả nhân viên sau khi xóa ---" << std::endl;
    empManager.displayAllEmployees();

    std::cout << "\nChương trình kết thúc." << std::endl;
}
