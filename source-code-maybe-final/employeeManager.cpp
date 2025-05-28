#include "EmployeeManager.h"
#include "SocialInsuranceWelfare.h"
#include "BonusWelfare.h"
#include "transportationWelfare.h"
#include <algorithm>
#include <iostream>

/**
 * @brief Constructor, khởi tạo các phúc lợi mặc định.
 */
EmployeeManager::EmployeeManager() : _payrollPrinter("vi-VN") {
    // Khởi tạo các phúc lợi mặc định cho toàn hệ thống
    _welfareManager.addWelfare(std::make_unique<SocialInsuranceWelfare>(0.105)); // 10.5% BHXH
    _welfareManager.addWelfare(std::make_unique<BonusWelfare>(2000000.0)); // Thưởng 2 triệu
    _welfareManager.addWelfare(std::make_unique<TransportationWelfare>(4000.0)); // Phụ cấp 4000 VND/km
}

/**
 * @brief Thêm một nhân viên mới.
 */
void EmployeeManager::addEmployee(std::shared_ptr<IEmployee> emp) {
    if (findEmployeeById(emp->getEmployeeId()) != nullptr) {
        std::cerr << "Loi: Ma nhan vien " << emp->getEmployeeId() << " da ton tai." << std::endl;
        return;
    }
    _employeeList.push_back(emp);
    std::cout << "Da them nhan vien: " << emp->getName() << std::endl;
}

/**
 * @brief Xóa nhân viên theo ID.
 */
void EmployeeManager::deleteEmployee(const std::string& empId) {
    auto it = std::remove_if(_employeeList.begin(), _employeeList.end(),
        [&empId](const auto& emp) {
            return emp->getEmployeeId() == empId;
        });

    if (it != _employeeList.end()) {
        _employeeList.erase(it, _employeeList.end());
        std::cout << "Da xoa nhan vien voi ma ID: " << empId << std::endl;
    }
    else {
        std::cerr << "Khong tim thay nhan vien voi ma ID: " << empId << std::endl;
    }
}

/**
 * @brief Tìm nhân viên theo ID.
 * @return Con trỏ shared_ptr đến nhân viên, hoặc nullptr nếu không tìm thấy.
 */
std::shared_ptr<IEmployee> EmployeeManager::findEmployeeById(const std::string& empId) const {
    for (const auto& emp : _employeeList) {
        if (emp->getEmployeeId() == empId) {
            return emp;
        }
    }
    return nullptr;
}

/**
 * @brief Hiển thị thông tin cơ bản của tất cả nhân viên.
 */
void EmployeeManager::displayAllEmployees() const {
    std::cout << "\n--- DANH SACH NHAN VIEN ---\n";
    if (_employeeList.empty()) {
        std::cout << "Danh sach trong.\n";
        return;
    }
    for (const auto& emp : _employeeList) {
        std::cout << "ID: " << emp->getEmployeeId()
            << ", Ten: " << emp->getName()
            << ", Loai: " << emp->getEmployeeType() << std::endl;
    }
    std::cout << "---------------------------\n";
}

/**
 * @brief Hiển thị thông tin chi tiết của một nhân viên.
 */
void EmployeeManager::displayEmployeeDetails(const std::string& empId) const {
    auto emp = findEmployeeById(empId);
    if (emp) {
        _payrollPrinter.printEmployeeDetails(emp);
    }
    else {
        std::cerr << "Khong tim thay nhan vien voi ma ID: " << empId << std::endl;
    }
}


/**
 * @brief Thêm một bản ghi chấm công.
 */
void EmployeeManager::addAttendanceRecord(const AttendanceRecord& record) {
    _attendanceManager.addRecord(record);
}

/**
 * @brief Tải dữ liệu chấm công từ file CSV.
 */
void EmployeeManager::loadAttendanceFromFile(const std::string& filename) {
    _attendanceManager.loadFromFile(filename);
}

/**
 * @brief In phiếu lương cho một nhân viên cụ thể ra console.
 */
void EmployeeManager::printPayroll(const std::string& empId) {
    auto emp = findEmployeeById(empId);
    if (!emp) {
        std::cerr << "Khong the in phieu luong. Khong tim thay nhan vien voi ma ID: " << empId << std::endl;
        return;
    }

    // Tính toán các khoản phúc lợi
    double bonuses = 0.0, allowances = 0.0, deductions = 0.0;
    _welfareManager.calculateAllWelfareForEmployee(*emp, bonuses, allowances, deductions);

    // Tính lương
    SalaryDetails details = emp->calculateSalary(_attendanceManager, bonuses, allowances, deductions);

    // In ra
    _payrollPrinter.printPaySlip(emp, details);
}

/**
 * @brief In phiếu lương của tất cả nhân viên ra file.
 */
void EmployeeManager::printAllPayrolls(const std::string& filename) {
    std::vector<std::pair<std::shared_ptr<IEmployee>, SalaryDetails>> payrollData;
    for (const auto& emp : _employeeList) {
        double bonuses = 0.0, allowances = 0.0, deductions = 0.0;
        _welfareManager.calculateAllWelfareForEmployee(*emp, bonuses, allowances, deductions);
        SalaryDetails details = emp->calculateSalary(_attendanceManager, bonuses, allowances, deductions);
        payrollData.push_back({ emp, details });
    }
    _payrollPrinter.printToFile(payrollData, filename);
}