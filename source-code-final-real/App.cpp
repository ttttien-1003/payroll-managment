#include "App.h"
#include "FulltimeEmployee.h"
#include "Intern.h"
#include "ContractualEmployee.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>

/**
 * @brief Constructor, gọi hàm khởi tạo dữ liệu mẫu.
 */
App::App() {
    seedData();
}

/**
 * @brief Khởi tạo một vài nhân viên mẫu để có dữ liệu làm việc.
 */
//void App::seedData() {
//    // Sử dụng _empManager để thêm nhân viên
//    _empManager.addEmployee(std::make_shared<FulltimeEmployee>(
//        "FT001", "Nguyen Van An", "Quan 1, TP.HCM", "0901234567", "a.nguyen@email.com",
//        "Kinh nghiem 5 nam", "2026-12-31", 2340000, 24));
//    _empManager.addEmployee(std::make_shared<Intern>(
//        "IT001", "Le Thi Binh", "Quan 7, TP.HCM", "0912345678", "b.le@email.com",
//        "Sinh vien nam cuoi", "2025-08-31", 1170000, 3)); 
//    _empManager.addEmployee(std::make_shared<ContractualEmployee>(
//        "CT001", "Tran Van Cuong", "Di An, Binh Duong", "0987654321", "c.tran@email.com",
//        "Hop dong 1 nam", "2025-05-31", 2106000, 10));
//}
void App::seedData() {
    std::ifstream inFile("employee_list.txt");
    if (!inFile) {
        std::cerr << "Khong the mo file employee_list.txt de doc." << std::endl;
        return;
    }

    std::string line;
    // Bỏ qua dòng tiêu đề
    std::getline(inFile, line);

    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string type, id, name, address, phone, email, info, expiryDate, baseSalaryStr, monthsWorkedStr;
        double baseSalary;
        int monthsWorked;

        std::getline(ss, type, ',');
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, address, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, email, ',');
        std::getline(ss, info, ',');
        std::getline(ss, expiryDate, ',');
        std::getline(ss, baseSalaryStr, ',');
        std::getline(ss, monthsWorkedStr, ',');

        baseSalary = std::stod(baseSalaryStr);
        monthsWorked = std::stoi(monthsWorkedStr);

        if (type == "fulltime") {
            _empManager.addEmployee(std::make_shared<FulltimeEmployee>(id, name, address, phone, email, info, expiryDate, baseSalary, monthsWorked));
        }
        else if (type == "intern") {
            _empManager.addEmployee(std::make_shared<Intern>(id, name, address, phone, email, info, expiryDate, baseSalary, monthsWorked));
        }
        else if (type == "contract") {
            _empManager.addEmployee(std::make_shared<ContractualEmployee>(id, name, address, phone, email, info, expiryDate, baseSalary, monthsWorked));
        }
    }

    inFile.close();
}

void App::saveData() {
    // Xóa file cũ
    if (std::remove("employee_list.txt") != 0) {
        // Có thể file không tồn tại, không sao cả
    }

    std::ofstream outFile("employee_list.txt");
    if (!outFile) {
        std::cerr << "Khong the mo file employee_list.txt de ghi." << std::endl;
        return;
    }

    // Ghi dòng tiêu đề
    outFile << "#LoaiNhanVien,MaNV,HoTen,DiaChi,SoDienThoai,Email,ThongTinThem,HanHopDong,LuongCoBan,ThamNien\n";

    for (const auto& emp : _empManager.getEmployees()) { // Giả sử có hàm getEmployees()
        outFile << emp->getEmployeeType() << ","
            << emp->getEmployeeId() << ","
            << emp->getName() << ","
            << emp->getAddress() << ","
            << emp->getPhone() << ","
            << emp->getEmail() << ","
            << emp->getAdditionInfo() << "," // Cần thêm getter cho _additionalInfo
            << emp->getExpYear() << "-" << emp->getExpMonth() << "-" << emp->getExpDay() << ","
            << emp->getBaseSalary() << ","
            << emp->getMonthsWorked() << "\n";
    }

    outFile.close();
}

/**
 * @brief Hiển thị menu chính.
 */
void App::showMenu() const {
    std::cout << "\n=======================================\n";
    std::cout << "     HE THONG QUAN LY LUONG\n";
    std::cout << "=======================================\n";
    std::cout << "1. Them nhan vien moi\n";
    std::cout << "2. Xoa nhan vien\n";
    std::cout << "3. Hien thi danh sach nhan vien\n";
    std::cout << "4. Hien thi chi tiet nhan vien\n";
    std::cout << "5. Tai du lieu cham cong (tu data/attendance.csv)\n";
    std::cout << "6. In phieu luong mot nhan vien\n";
    std::cout << "7. In phieu luong toan bo nhan vien (ra file)\n";
    std::cout << "8. Thoat\n";
    std::cout << "=======================================\n";
    std::cout << "Chon chuc nang: ";
}


/**
 * @brief Vòng lặp chính của ứng dụng.
 */
void App::run() {
    int choice;
    std::string empId;
    std::string filename;

    while (true) {
        showMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "Lua chon khong hop le. Vui long nhap so.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
        case 1:
            handleAddEmployee();
            break;
        case 2:
            handleDeleteEmployee();
            break;
        case 3:
            _empManager.displayAllEmployees();
            break;
        case 4:
            handleShowEmployeeDetails();
            break;
        case 5:
            filename = "attendance.csv";
            _empManager.loadAttendanceFromFile(filename);
            break;
        case 6:
            std::cout << "Nhap ma nhan vien can in phieu luong: ";
            std::getline(std::cin, empId);
            _empManager.printPayroll(empId);
            break;
        case 7:
            filename = "payroll_export.txt";
            _empManager.printAllPayrolls(filename);
            std::cout << "Da xuat phieu luong ra file: " << filename << std::endl;
            break;
        case 8:
            saveData();
            std::cout << "Cam on da su dung chuong trinh!\n";
            return; // Thoát khỏi hàm run() và kết thúc chương trình
        default:
            std::cout << "Lua chon khong hop le. Vui long chon lai.\n";
            break;
        }
    }
}

// --- Triển khai các hàm xử lý private ---

void App::handleAddEmployee() {
    std::string type, id, name, address, phone, email, info, expiryDate, baseSalaryStr, monthsWorkedStr;
    double baseSalary;
    int monthsWorked;

    std::cout << "Chon loai nhan vien (fulltime, intern, contract): ";
    std::getline(std::cin, type);
    std::cout << "Nhap ma NV: ";
    std::getline(std::cin, id);
    std::cout << "Nhap ten: ";
    std::getline(std::cin, name);
    std::cout << "Nhap dia chi: ";
    std::getline(std::cin, address);
    std::cout << "Nhap SDT: ";
    std::getline(std::cin, phone);
    std::cout << "Nhap email: ";
    std::getline(std::cin, email);
    std::cout << "Nhap thong tin them (hoac nhap \"Khong co\"): ";
    std::getline(std::cin, info);
    std::cout << "Nhap han hop dong (YYYY-MM-DD): ";
    std::getline(std::cin, expiryDate);
    std::cout << "Nhap luong co ban: ";
    std::getline(std::cin, baseSalaryStr);
    std::cout << "Nhap tham nien (so thang): ";
    std::getline(std::cin, monthsWorkedStr);

    baseSalary = std::stod(baseSalaryStr);
    monthsWorked = std::stoi(monthsWorkedStr);

    if (type == "fulltime") {
        _empManager.addEmployee(std::make_shared<FulltimeEmployee>(id, name, address, phone, email, info, expiryDate, baseSalary, monthsWorked));
    }
    else if (type == "intern") {
        _empManager.addEmployee(std::make_shared<Intern>(id, name, address, phone, email, info, expiryDate, baseSalary, monthsWorked));
    }
    else if (type == "contract") {
        _empManager.addEmployee(std::make_shared<ContractualEmployee>(id, name, address, phone, email, info, expiryDate, baseSalary, monthsWorked));
    }
    else {
        std::cout << "Loai nhan vien khong hop le.\n";
    }
}

void App::handleDeleteEmployee() {
    std::string empId;
    std::cout << "Nhap ma nhan vien can xoa: ";
    std::getline(std::cin, empId);
    _empManager.deleteEmployee(empId);
}

void App::handleShowEmployeeDetails() {
    std::string empId;
    std::cout << "Nhap ma nhan vien can xem chi tiet: ";
    std::getline(std::cin, empId);
    _empManager.displayEmployeeDetails(empId);
}