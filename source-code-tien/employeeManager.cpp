#include "employeeManager.h"

// Constructor: Khởi tạo các phúc lợi mặc định
EmployeeManager::EmployeeManager() {
    // Thêm các phúc lợi vào WelfareManager
    welfareManager.addWelfare(std::make_unique<SocialInsuranceWelfare>(0.105)); // 10.5% của nhân viên
    welfareManager.addWelfare(std::make_unique<BonusWelfare>(static_cast<double>(2000000))); // Chỉ còn thưởng doanh thu: 2tr
    welfareManager.addWelfare(std::make_unique<TransportationWelfare>(4000)); // 4000 VND/km
}

/**
 * @brief Thêm nhân viên mới vào danh sách.
 * @param emp Con trỏ shared_ptr đến đối tượng IEmployee cần thêm.
 */
void EmployeeManager::addEmployee(const std::shared_ptr<IEmployee>& emp) {
    employeeList.push_back(emp);
    std::cout << "Đã thêm nhân viên: " << emp->getName() << std::endl;
}

/**
 * @brief Sửa hồ sơ nhân viên.
 * @param empId ID nhân viên cần sửa.
 * @param updatedEmp Con trỏ shared_ptr đến đối tượng IEmployee đã cập nhật.
 */
void EmployeeManager::modifyEmployee(const std::string& empId, const std::shared_ptr<IEmployee>& updatedEmp) {
    for (auto& emp : employeeList) {
        if (emp->getEmployeeId() == empId) {
            emp = updatedEmp; // Thay thế đối tượng cũ bằng đối tượng mới
            std::cout << "Hồ sơ nhân viên với mã ID " << empId << " đã được cập nhật." << std::endl;
            return;
        }
    }
    std::cout << "Không tìm thấy nhân viên với mã ID: " << empId << std::endl;
}

/**
 * @brief Xóa hồ sơ nhân viên khỏi danh sách.
 * @param empId ID nhân viên cần xóa.
 */
void EmployeeManager::deleteEmployee(const std::string& empId) {
    auto it = std::remove_if(employeeList.begin(), employeeList.end(),
        [&empId](const std::shared_ptr<IEmployee>& emp) { return emp->getEmployeeId() == empId; });
    if (it != employeeList.end()) {
        employeeList.erase(it, employeeList.end());
        std::cout << "Đã xóa nhân viên với mã ID: " << empId << std::endl;
    }
    else {
        std::cout << "Không tìm thấy nhân viên với mã ID: " << empId << std::endl;
    }
}

/**
 * @brief Hiển thị hồ sơ của một nhân viên cụ thể.
 * @param empId ID nhân viên cần hiển thị.
 */
void EmployeeManager::displayEmployeeById(const std::string& empId) const {
    for (const auto& emp : employeeList) {
        if (emp->getEmployeeId() == empId) {
            displayEmployee(emp);
            return;
        }
    }
    std::cout << "Không tìm thấy nhân viên với mã ID: " << empId << std::endl;
}

/**
 * @brief Hiển thị danh sách toàn bộ nhân viên.
 */
void EmployeeManager::displayAllEmployees() const {
    std::cout << "Danh sách toàn bộ nhân viên:" << std::endl;
    if (employeeList.empty()) {
        std::cout << "Danh sách nhân viên trống." << std::endl;
        return;
    }
    for (const auto& emp : employeeList) {
        displayEmployee(emp);
        std::cout << "------------------------" << std::endl;
    }
}

/**
 * @brief In phiếu lương cho một nhân viên cụ thể.
 * @param empId ID nhân viên cần in phiếu lương.
 */
void EmployeeManager::printPayroll(const std::string& empId) const {
    for (const auto& emp : employeeList) {
        if (emp->getEmployeeId() == empId) {
            std::cout << "Phiếu lương của nhân viên: " << emp->getName() << " (ID: " << emp->getEmployeeId() << ")" << std::endl;

            // Tính toán tổng phúc lợi và khấu trừ từ WelfareManager
            // (totalWelfareImpact sẽ là tổng của bonuses, allowances, và -deductions)
            double totalWelfareImpact = welfareManager.calculateTotalWelfareImpactForEmployee(*emp);

            double bonuses = 0.0;
            double allowances = 0.0;
            double deductions = 0.0;

            for (const auto& welfare : welfareManager.getAllWelfares()) {
                if (welfare->isEligible(*emp)) {
                    double impact = welfare->calculateImpact(*emp);
                    if (impact > 0) {
                        // Phân loại thưởng và phụ cấp
                        if (welfare->getDetails().type == WelfareType::Bonus) {
                            bonuses += impact;
                        }
                        else if (welfare->getDetails().type == WelfareType::Transportation) {
                            allowances += impact;
                        }
                    }
                    else if (impact < 0) {
                        deductions += std::abs(impact); // Khấu trừ là số dương
                    }
                }
            }

            // Gọi phương thức calculateSalary của đối tượng IEmployee (đã được ghi đè bởi lớp con)
            // Phương thức này giờ đây trả về SalaryDetails
            SalaryDetails details = emp->calculateSalary(attendance, bonuses, allowances, deductions);

            ShowSalary showSalary;
            showSalary.showSalary(details);
            std::cout << "Tổng tác động phúc lợi (bao gồm thưởng, phụ cấp, khấu trừ): " << totalWelfareImpact << std::endl;
            std::cout << "Lương ròng cuối cùng: " << details.totalSalary << std::endl;
            return;
        }
    }
    std::cout << "Không tìm thấy nhân viên với mã ID: " << empId << std::endl;
}

/**
 * @brief Hiển thị thông tin chi tiết của một nhân viên.
 * @param emp Con trỏ shared_ptr đến đối tượng IEmployee.
 */
void EmployeeManager::displayEmployee(const std::shared_ptr<IEmployee>& emp) const {
    std::cout << "ID: " << emp->getEmployeeId() << "\n"
        << "Name: " << emp->getName() << "\n"
        << "Address: " << emp->getAddress() << "\n"
        << "Phone: " << emp->getPhone() << "\n"
        << "Employee Type: " << emp->getEmployeeType() << "\n"
        << "Base Salary: " << emp->getBaseSalary() << "\n" // Hiển thị lương cơ bản
        << "Months Worked: " << emp->getMonthsWorked() << std::endl; // Hiển thị số tháng làm việc
}

/**
 * @brief Thêm một bản ghi chấm công.
 * @param record Bản ghi chấm công.
 */
void EmployeeManager::addAttendanceRecord(const AttendanceRecord& record) {
    attendance.addRecord(record);
    std::cout << "Đã thêm bản ghi chấm công cho nhân viên ID: " << record.employeeId << std::endl;
}