#include "PayrollPrinter.h"
#include <iostream>
#include <fstream>
#include <iomanip> // Để dùng std::setw
#include "utils.h" // Để dùng gotoXY
#include "CultureInfo.h"

/**
 * @brief Constructor, khởi tạo CultureInfo dựa trên locale.
 */
PayrollPrinter::PayrollPrinter(const std::string& locale) {
    _culture = CultureInfo::get(locale);
}

/**
 * @brief In thông tin chi tiết của một nhân viên.
 */
void PayrollPrinter::printEmployeeDetails(const std::shared_ptr<IEmployee>& emp, int contentX, int contentY, int contentWidth) const {
    if (!emp) return;

    int currentLineY = contentY;
    int labelWidth = 18; // Tăng độ rộng cho nhãn
    // int valueX = contentX + labelWidth; // Không cần nếu mỗi giá trị xuống dòng mới

    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Ma NV         :" << emp->getEmployeeId();
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Ten           :" << emp->getName();
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Loai NV       :" << emp->getEmployeeType();
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Dia chi       :" << emp->getAddress();
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "SDT           :" << emp->getPhone();
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Email         :" << emp->getEmail();
    
    // Hiển thị lương cơ bản với định dạng
    std::string formattedBaseSalary = _formatter.format(emp->getBaseSalary(), _culture) + " VND";
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Luong co ban  :" << formattedBaseSalary;
    
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Thong tin them:" << emp->getAdditionInfo();
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Han hop dong  :" << emp->getFormattedExpiryDate();
    gotoXY(contentX + 55, currentLineY++); std::cout << std::left << std::setw(labelWidth) << "Tham nien     :" << emp->getMonthsWorked() << " thang";
}


/**
 * @brief In phiếu lương chi tiết của một nhân viên ra console.
 */
void PayrollPrinter::printPaySlip(const std::shared_ptr<IEmployee>& emp, const SalaryDetails& details) const {
    if (!emp) return;

    // Tọa độ này là tương đối với màn hình đã được EmployeeManager::printPayroll chuẩn bị
    // EmployeeManager::printPayroll vẽ khung và tiêu đề "PHIEU LUONG NHAN VIEN"
    // Giả sử tiêu đề và gạch ngang chiếm đến dòng Y=3 (tính từ 0), thì nội dung phiếu lương bắt đầu từ Y=5
    int currentLineY = 5; 
    int col1X = FRAME_MARGIN_X + FRAME_CONTENT_START_X_OFFSET + 2; // Cách lề khung một chút
    int col2X_label = col1X; // Nhãn
    int col2X_value = col1X + 25; // Giá trị
    int valueWidth = 15;

    int w=0, h=0;
    getConsoleWindowSize(w, h);
    int tab = w/4 +2;

    gotoXY(col2X_label+tab, currentLineY++); std::cout << "Ma NV: " << emp->getEmployeeId() << " | Ten: " << emp->getName();
    gotoXY(col2X_label+tab, currentLineY++); std::cout << std::string(59, '-'); // Điều chỉnh độ dài

    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "Luong co ban:"; // Tăng setw
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(emp->getBaseSalary(), _culture) << " VND";
    
    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "Luong lam viec BT:"; 
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(details.basicSalary, _culture) << " VND";
    
    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "Luong tang ca:";
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(details.overtimeSalary, _culture) << " VND";
    
    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "Luong ngay le:";
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(details.holidaySalary, _culture) << " VND";
    
    currentLineY++; 
    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "(+) Thuong:";
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(details.bonuses, _culture) << " VND";
    
    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "(+) Phu cap:";
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(details.allowances, _culture) << " VND";
    
    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "(-) Khau tru:";
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(details.deductions, _culture) << " VND";

    currentLineY++; 
    gotoXY(col2X_label+tab, currentLineY++); std::cout << std::string(59, '-');
    
    gotoXY(col2X_label+tab, currentLineY); std::cout << std::left << std::setw(23) << "TONG LUONG (RONG):";
    gotoXY(col2X_value+tab+15, currentLineY++); std::cout << std::right << std::setw(valueWidth) << _formatter.format(details.totalSalary, _culture) << " VND";
}

void PayrollPrinter::printPaySlipToFile(const std::shared_ptr<IEmployee>& emp, const SalaryDetails& details, const std::string& filename) const {
    if (!emp) return;

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "LOI: Khong the mo file '" << filename << "' de ghi phieu luong." << std::endl;
        return;
    }

    outFile << "========================================\n";
    outFile << "        PHIEU LUONG NHAN VIEN\n";
    outFile << "----------------------------------------\n";
    outFile << "Ma NV: " << emp->getEmployeeId() << " | Ten: " << emp->getName() << "\n";
    outFile << "----------------------------------------\n";

    outFile << std::left << std::setw(20) << "Luong co ban:" << std::right << std::setw(15) << _formatter.format(emp->getBaseSalary(), _culture) << " VND\n";
    outFile << std::left << std::setw(20) << "Luong lam viec BT:" << std::right << std::setw(15) << _formatter.format(details.basicSalary, _culture) << " VND\n";
    outFile << std::left << std::setw(20) << "Luong tang ca:" << std::right << std::setw(15) << _formatter.format(details.overtimeSalary, _culture) << " VND\n";
    outFile << std::left << std::setw(20) << "Luong ngay le:" << std::right << std::setw(15) << _formatter.format(details.holidaySalary, _culture) << " VND\n";
    outFile << "\n";
    outFile << std::left << std::setw(20) << "(+) Thuong:" << std::right << std::setw(15) << _formatter.format(details.bonuses, _culture) << " VND\n";
    outFile << std::left << std::setw(20) << "(+) Phu cap:" << std::right << std::setw(15) << _formatter.format(details.allowances, _culture) << " VND\n";
    outFile << std::left << std::setw(20) << "(-) Khau tru:" << std::right << std::setw(15) << _formatter.format(details.deductions, _culture) << " VND\n";
    outFile << "\n";
    outFile << "----------------------------------------\n";
    outFile << std::left << std::setw(20) << "TONG LUONG (RONG):" << std::right << std::setw(15) << _formatter.format(details.totalSalary, _culture) << " VND\n";
    outFile << "========================================\n";

    outFile.close();
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
    // Điều chỉnh độ rộng cột cho phù hợp với các cột mới
    outFile << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n"; // Tăng độ rộng dòng gạch
    outFile << std::left
            << std::setw(8) << "Ma NV"
            << std::setw(25) << "Ho Ten"
            << std::setw(18) << "Luong CB"             // Lương cơ bản cố định
            << std::setw(18) << "L.Lam Viec BT"      // Lương giờ làm việc bình thường
            << std::setw(15) << "L.Tang Ca"          // Lương tăng ca
            << std::setw(15) << "L.Ngay Le"          // Lương ngày lễ
            << std::setw(15) << "Thuong"
            << std::setw(15) << "Phu Cap"
            << std::setw(18) << "Khau Tru"
            << std::setw(20) << "LUONG RONG"
            << "\n";
    outFile << "-------------------------------------------------------------------------------------------------------------------------------------------------------\n"; // Tăng độ rộng dòng gạch

    for (const auto& data : payrollData) {
        const auto& emp = data.first;
        const auto& details = data.second;
        outFile << std::left
                << std::setw(8) << emp->getEmployeeId()
                << std::setw(25) << emp->getName()
                // Hiển thị Lương Cơ Bản cố định từ đối tượng Employee
                << std::setw(18) << _formatter.format(emp->getBaseSalary(), _culture)
                // Hiển thị các thành phần lương từ SalaryDetails
                << std::setw(18) << _formatter.format(details.basicSalary, _culture)    // Lương giờ làm việc bình thường
                << std::setw(15) << _formatter.format(details.overtimeSalary, _culture) // Lương tăng ca
                << std::setw(15) << _formatter.format(details.holidaySalary, _culture)  // Lương ngày lễ
                << std::setw(15) << _formatter.format(details.bonuses, _culture)
                << std::setw(15) << _formatter.format(details.allowances, _culture)
                << std::setw(18) << _formatter.format(details.deductions, _culture)
                << std::setw(20) << _formatter.format(details.totalSalary, _culture)
                << "\n";
    }

    outFile.close();
    //std::cout << "Da xuat bang luong ra file: " << filename << std::endl; // Thêm thông báo này nếu muốn
}