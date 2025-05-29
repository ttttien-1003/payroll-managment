#include "PayrollPrinter.h"
#include <iostream>
#include <fstream>
#include <iomanip> // Để dùng std::setw

/**
 * @brief Constructor, khởi tạo CultureInfo dựa trên locale.
 */
PayrollPrinter::PayrollPrinter(const std::string& locale) {
    _culture = CultureInfo::get(locale);
}

/**
 * @brief In thông tin chi tiết của một nhân viên.
 */
void PayrollPrinter::printEmployeeDetails(const std::shared_ptr<IEmployee>& emp) const {
    if (!emp) return;

    std::cout << "\n--- CHI TIET NHAN VIEN ---\n";
    std::cout << "Ma NV:       " << emp->getEmployeeId() << std::endl;
    std::cout << "Ten:         " << emp->getName() << std::endl;
    std::cout << "Loai NV:     " << emp->getEmployeeType() << std::endl;
    std::cout << "Dia chi:     " << emp->getAddress() << std::endl;
    std::cout << "SDT:         " << emp->getPhone() << std::endl;
    std::cout << "Email:       " << emp->getEmail() << std::endl;
    // Sử dụng formatter để hiển thị lương cơ bản/trợ cấp
    std::cout << "Luong co ban: " << _formatter.format(emp->getBaseSalary(), _culture) << " VND" << std::endl;
    std::cout << "---------------------------\n";
}

/**
 * @brief In phiếu lương chi tiết của một nhân viên ra console.
 */
void PayrollPrinter::printPaySlip(const std::shared_ptr<IEmployee>& emp, const SalaryDetails& details) const {
    if (!emp) return;

    std::cout << "\n========================================" << std::endl;
    std::cout << "        PHIEU LUONG NHAN VIEN" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Ma NV: " << emp->getEmployeeId() << " | Ten: " << emp->getName() << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // Sử dụng formatter cho tất cả các giá trị tiền tệ
    std::cout << std::left << std::setw(20) << "Luong co ban:" << std::right << std::setw(15) << _formatter.format(emp->getBaseSalary(), _culture) << " VND" << std::endl;
    if (emp->getEmployeeType() == "Intern")
    {
        std::cout << std::left << std::setw(20) << "Luong lam viec:" << std::right << std::setw(15) << _formatter.format(0, _culture) << " VND" << std::endl;
    }
    else
    {
        std::cout << std::left << std::setw(20) << "Luong lam viec:" << std::right << std::setw(15) << _formatter.format(details.basicSalary, _culture) << " VND" << std::endl;
    }
    std::cout << std::left << std::setw(20) << "Luong tang ca:" << std::right << std::setw(15) << _formatter.format(details.overtimeSalary, _culture) << " VND" << std::endl;
    std::cout << std::left << std::setw(20) << "Luong ngay le:" << std::right << std::setw(15) << _formatter.format(details.holidaySalary, _culture) << " VND" << std::endl;
    std::cout << std::left << std::setw(20) << "(+) Thuong:" << std::right << std::setw(15) << _formatter.format(details.bonuses, _culture) << " VND" << std::endl;
    std::cout << std::left << std::setw(20) << "(+) Phu cap:" << std::right << std::setw(15) << _formatter.format(details.allowances, _culture) << " VND" << std::endl;
    std::cout << std::left << std::setw(20) << "(-) Khau tru:" << std::right << std::setw(15) << _formatter.format(details.deductions, _culture) << " VND" << std::endl;

    std::cout << "----------------------------------------" << std::endl;
    std::cout << std::left << std::setw(20) << "TONG LUONG (RONG):" << std::right << std::setw(15) << _formatter.format(details.totalSalary, _culture) << " VND" << std::endl;
    std::cout << "========================================" << std::endl;
}

/**
 * @brief In phiếu lương của tất cả nhân viên ra file.
 */
void PayrollPrinter::printToFile(const std::vector<std::pair<std::shared_ptr<IEmployee>, SalaryDetails>>& payrollData, const std::string& filename) const {
    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Loi: Khong the mo file de ghi: " << filename << std::endl;
        return;
    }

    outFile << "BANG LUONG TONG HOP\n";
    outFile << "------------------------------------------------------------------------------------------------------------------\n";
    outFile << std::left
        << std::setw(8) << "Ma NV"
        << std::setw(25) << "Ho Ten"
        << std::setw(18) << "Luong CB"
        << std::setw(15) << "Thuong"
        << std::setw(15) << "Phu Cap"
        << std::setw(18) << "Khau Tru"
        << std::setw(20) << "LUONG RONG"
        << "\n";
    outFile << "------------------------------------------------------------------------------------------------------------------\n";

    for (const auto& data : payrollData) {
        const auto& emp = data.first;
        const auto& details = data.second;
        outFile << std::left
            << std::setw(8) << emp->getEmployeeId()
            << std::setw(25) << emp->getName()
            // Sử dụng formatter khi ghi file
            << std::setw(18) << _formatter.format(details.basicSalary + details.overtimeSalary + details.holidaySalary, _culture)
            << std::setw(15) << _formatter.format(details.bonuses, _culture)
            << std::setw(15) << _formatter.format(details.allowances, _culture)
            << std::setw(18) << _formatter.format(details.deductions, _culture)
            << std::setw(20) << _formatter.format(details.totalSalary, _culture)
            << "\n";
    }

    outFile.close();
}