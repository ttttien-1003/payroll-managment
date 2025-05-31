// App.cpp
#include "App.h"
#include "FulltimeEmployee.h"
#include "Intern.h"
#include "ContractualEmployee.h"
#include "utils.h" // Nếu bạn đã tạo file này theo hướng dẫn trước
#include <iostream>
#include <limits>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>       // Cho std::vector
#include <memory>       // Cho std::shared_ptr
#include <algorithm>    // Cho std::all_of
#include <cctype>       // Cho std::isdigit
#include <iomanip>      // Cho std::setw, std::setfill
#include <set>          // Cho std::set để quản lý các số đã dùng
#include <conio.h>
#include "IEmployee.h"
#include <limits>

const int FRAME_MARGIN_X_LOGIN = 10; // Khung login có thể có lề lớn hơn
const int FRAME_MARGIN_Y_LOGIN = 5;
const int FRAME_TITLE_Y_OFFSET_LOGIN = 1;
const int FRAME_CONTENT_START_X_OFFSET_LOGIN = 4;
const int FRAME_CONTENT_START_Y_OFFSET_LOGIN = 3; // Sau tiêu đề và 1 dòng trống
const int FRAME_FOOTER_Y_OFFSET_LOGIN = 1;

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
    if (!_empManager.loadFromFile("employee_list.txt")) { //
        std::cerr << "Khong the tai du lieu ban dau tu employee_list.txt." << std::endl;
        // Có thể quyết định thoát chương trình hoặc tiếp tục với danh sách rỗng
    } else {
        std::cout << "Du lieu nhan vien da duoc tai." << std::endl; // Thông báo tùy chọn
    }
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
    clearScreen();

    int windowWidth, windowHeight;
    getConsoleWindowSize(windowWidth, windowHeight);

    // --- Định nghĩa kích thước và vị trí cho khung menu ---
    int frameWidth = 80; // Bạn có thể tăng chiều rộng khung, ví dụ 90 hoặc 100
    int frameHeight = 20; // Chiều cao khung, ví dụ 22 hoặc 24

    // Tính toán để khung nằm giữa cửa sổ console
    int frameX1 = (windowWidth > frameWidth) ? (windowWidth - frameWidth) / 2 : 0;
    int frameY1 = (windowHeight > frameHeight) ? (windowHeight - frameHeight) / 2 : 2; // Để cách lề trên 2 dòng

    // Đảm bảo frameX1 không âm nếu cửa sổ quá hẹp
    if (frameX1 < 0) frameX1 = 0;

    int frameX2 = frameX1 + frameWidth - 1;
    int frameY2 = frameY1 + frameHeight - 1;

    // Điều chỉnh nếu khung vượt quá kích thước cửa sổ thực tế
    if (frameX2 >= windowWidth) {
        frameX2 = windowWidth - 1;
        if (frameX1 > 0) frameX1 = (windowWidth - frameWidth > 0) ? (windowWidth - frameWidth) / 2 : 0; // Căn giữa lại nếu được
    }
    if (frameY2 >= windowHeight) {
        frameY2 = windowHeight - 1;
        // Không cần căn lại frameY1 nếu nó đã được đặt cách lề trên
    }
    
    // Vẽ khung
    drawBorder(frameX1, frameY1, frameX2, frameY2);

    // In tiêu đề ra giữa (dựa vào chiều rộng thực của cửa sổ)
    std::string title = "HE THONG QUAN LY LUONG";
    printCenteredText(title, frameY1 + 2, windowWidth);
    
    std::string separator(title.length() + 4, '='); // Tạo đường gạch ngang dài hơn tiêu đề một chút
    if (separator.length() > frameWidth - 4) { // Đảm bảo đường gạch không tràn khung
        separator = std::string(frameWidth - 6 > 0 ? frameWidth - 6 : 10, '=');
    }
    printCenteredText(separator, frameY1 + 3, windowWidth);

    // In các mục menu, căn lề trái bên trong khung
    int menuStartX = frameX1 + 15; // Cách lề trái của khung 5 ký tự
    int menuY = frameY1 + 6;     // Bắt đầu từ dòng Y này

    // Đảm bảo menuStartX không bị tràn nếu khung quá hẹp
    if (menuStartX + 35 > frameX2) { // 35 là ước lượng chiều dài của một mục menu
        menuStartX = frameX1 + 2;
    }


    gotoXY(menuStartX, menuY++); std::cout << "I. Them nhan vien moi";
    gotoXY(menuStartX, menuY++); std::cout << "S. Sua thong tin nhan vien";
    gotoXY(menuStartX, menuY++); std::cout << "X. Xoa nhan vien";
    gotoXY(menuStartX, menuY++); std::cout << "L. Hien thi danh sach nhan vien";
    gotoXY(menuStartX, menuY++); std::cout << "C. Hien thi chi tiet nhan vien";
    // Dòng "Tai du lieu cham cong" đã bị xóa
    gotoXY(menuStartX, menuY++); std::cout << "P. In phieu luong mot nhan vien";
    gotoXY(menuStartX, menuY++); std::cout << "A. In phieu luong toan bo nhan vien";
    gotoXY(menuStartX, menuY++); std::cout << "Q. Thoat";

    gotoXY(menuStartX, menuY + 2); std::cout << "Chon chuc nang: ";
}


/**
 * @brief Vòng lặp chính của ứng dụng.
 */
void App::run() {
    if (!handleLogin()) { // Bạn sẽ tạo hàm này sau nếu muốn có màn hình đăng nhập
         return;
    }
    char choice_char;
    std::string empId_str;
    std::string filename_str;
    int month_val, year_val;
    int windowWidth, windowHeight;

    while (true) {
        showMenu(); 
        choice_char = _getch();
        choice_char = toupper(choice_char);

        clearScreen();
        getConsoleWindowSize(windowWidth, windowHeight);

        int frameX1 = FRAME_MARGIN_X;
        int frameY1 = FRAME_MARGIN_Y;
        int frameX2 = windowWidth - 1 - FRAME_MARGIN_X;
        int frameY2 = windowHeight - 1 - FRAME_MARGIN_Y;
        if (frameX2 <= frameX1 + 40) frameX2 = frameX1 + 40;
        if (frameX2 >= windowWidth) frameX2 = windowWidth - 1;
        if (frameY2 <= frameY1 + 15) frameY2 = frameY1 + 15; // Tăng chiều cao tối thiểu cho các màn hình chức năng
        if (frameY2 >= windowHeight) frameY2 = windowHeight -1;

        drawBorder(frameX1, frameY1, frameX2, frameY2);

        int contentStartX = frameX1 + FRAME_CONTENT_START_X_OFFSET;
        int contentStartY = frameY1 + FRAME_CONTENT_START_Y_OFFSET;
        int contentInnerWidth = frameX2 - frameX1 - (2 * FRAME_CONTENT_START_X_OFFSET) + 1;
        // contentFrameY2 là giới hạn dưới của vùng nội dung bên trong khung
        int contentMaxY = frameY2 - FRAME_FOOTER_Y_OFFSET -1; // Dòng cuối cùng có thể dùng cho nội dung, trước footer

        switch (choice_char) {
            case 'I': {
                printCenteredText("THEM NHAN VIEN MOI", frameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
                handleAddEmployee(contentStartX, contentStartY, contentInnerWidth, contentMaxY);
                break;
            }
            case 'S': {
                printCenteredText("SUA THONG TIN NHAN VIEN", frameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
                handleEditEmployee(contentStartX, contentStartY, contentInnerWidth, contentMaxY);
                break;
            }
            case 'X': {
                printCenteredText("XOA NHAN VIEN", frameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
                handleDeleteEmployee(contentStartX, contentStartY, contentInnerWidth, contentMaxY);
                break;
            }
            case 'L': {
                printCenteredText("DANH SACH NHAN VIEN", frameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
                _empManager.displayAllEmployees(frameX1, frameY1, 
                                                frameX2 - frameX1 + 1, 
                                                frameY2 - frameY1 + 1);
                break;
            }
            case 'C': {
                printCenteredText("CHI TIET NHAN VIEN", frameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
                handleShowEmployeeDetails(contentStartX, contentStartY, contentInnerWidth, contentMaxY);
                break;
            }
            case 'P': {
                printCenteredText("IN PHIEU LUONG CA NHAN", frameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
                int inputY = contentStartY;
                
                gotoXY(contentStartX + 55, inputY++); std::cout << "Nhap thang (1-12): ";
                while (!(std::cin >> month_val) || month_val < 1 || month_val > 12) { 
                    gotoXY(contentStartX + 55, inputY - 1 ); std::cout << std::string(30, ' '); // Xóa lỗi cũ
                    gotoXY(contentStartX + 55, inputY - 1 ); std::cout << "Thang KL. Nhap lai: "; 
                    std::cin.clear(); std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

                }
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

                gotoXY(contentStartX + 20 + 25, inputY ); std::cout << std::string(20, ' '); 

                gotoXY(contentStartX + 55, inputY++); std::cout << "Nhap nam (YYYY): ";
                while (!(std::cin >> year_val) || year_val < 2000 || year_val > 2100) { 
                     gotoXY(contentStartX + 55, inputY - 1 ); std::cout << std::string(30, ' '); // Xóa lỗi cũ
                     gotoXY(contentStartX + 55, inputY - 1 ); std::cout << "Nam KL. Nhap lai: "; 
                     std::cin.clear(); std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

                }
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

                gotoXY(contentStartX + 18 + 25, inputY ); std::cout << std::string(20, ' '); 

                gotoXY(contentStartX + 55, inputY++); std::cout << "Nhap ma nhan vien: ";
                std::getline(std::cin, empId_str);
                
                _empManager.printPayroll(empId_str, month_val, year_val);
                
                // EmployeeManager::printPayroll sẽ tự quản lý màn hình và chờ getch
                // Vì vậy, chúng ta không cần footer chung ở đây nữa
                break; // Bỏ qua footer chung của App::run
            }
            case 'A': { // In phiếu lương toàn bộ
            printCenteredText("IN PHIEU LUONG TOAN BO & HIEN THI", frameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
            int inputY = contentStartY;
            // ... (logic nhập tháng, năm như cũ) ...
            gotoXY(contentStartX, inputY++); std::cout << "Nhap thang (1-12): ";
            while (!(std::cin >> month_val) || month_val < 1 || month_val > 12) { 
                gotoXY(contentStartX + 20, inputY - 1 ); std::cout << std::string(30, ' '); 
                gotoXY(contentStartX + 20, inputY - 1 ); std::cout << "Thang KL. Nhap lai: "; 
                std::cin.clear(); std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            }
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            gotoXY(contentStartX + 20 + 25, inputY -1 ); std::cout << std::string(20, ' '); 

            gotoXY(contentStartX, inputY++); std::cout << "Nhap nam (YYYY): ";
            while (!(std::cin >> year_val) || year_val < 2000 || year_val > 2100) { 
                 gotoXY(contentStartX + 18, inputY - 1 ); std::cout << std::string(30, ' '); 
                 gotoXY(contentStartX + 18, inputY - 1 ); std::cout << "Nam KL. Nhap lai: "; 
                 std::cin.clear(); std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            }
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            gotoXY(contentStartX + 18 + 25, inputY -1 ); std::cout << std::string(20, ' '); 


            filename_str = "payroll_export.txt";
            _empManager.printAllPayrolls(filename_str, month_val, year_val); 

            // Xóa các dòng nhập liệu để hiển thị nội dung file
            for(int i=0; i < 5; ++i) { // Xóa khoảng 5 dòng
                gotoXY(contentStartX, contentStartY + i);
                std::cout << std::string(contentInnerWidth, ' ');
            }

            gotoXY(contentStartX, contentStartY); 
            std::cout << "Da xuat bang luong thang " << month_val << "/" << year_val 
                                              << " ra file: " << filename_str;
            gotoXY(contentStartX, contentStartY + 1); 
            std::cout << "Noi dung file " << filename_str << ":";

            // Đọc và hiển thị nội dung file
            std::ifstream inFile(filename_str);
            if (inFile) {
                std::string fileLine;
                int displayLineY = contentStartY + 3; // Bắt đầu hiển thị nội dung file
                int linesInFrame = contentMaxY - displayLineY; // Số dòng còn lại trong khung
                int linesDisplayed = 0;

                while (std::getline(inFile, fileLine)) {
                    if (linesDisplayed >= linesInFrame) {
                        gotoXY(contentStartX, contentMaxY); // Dòng cuối trong content
                        std::cout << "-- Nhan phim de xem tiep --";
                        _getch();
                        // Xóa nội dung đã hiển thị để vẽ trang mới
                        for (int i=0; i<linesDisplayed; ++i) {
                            gotoXY(contentStartX, displayLineY + i);
                            std::cout << std::string(contentInnerWidth, ' ');
                        }
                        linesDisplayed = 0;
                    }
                    gotoXY(contentStartX, displayLineY + linesDisplayed);
                    // Cắt bớt dòng nếu quá dài so với contentInnerWidth
                    if (fileLine.length() > static_cast<size_t>(contentInnerWidth-1)) {
                        std::cout << fileLine.substr(0, contentInnerWidth - 4) << "...";
                    } else {
                        std::cout << fileLine;
                    }
                    linesDisplayed++;
                }
                inFile.close();
            } else {
                gotoXY(contentStartX, contentStartY + 3);
                std::cout << "LOI: Khong the mo file " << filename_str << " de doc lai.";
            }
            break; // break của case 'A'
        }
            case 'Q':
                saveData();
                clearScreen();
                getConsoleWindowSize(windowWidth, windowHeight);
                printCenteredText("Cam on da su dung chuong trinh!", windowHeight / 2, windowWidth);
                cDelay(2000);
                return;
            default:
                printCenteredText("Lua chon khong hop le.", contentStartY, windowWidth);
                break; 
        }
        
        if (choice_char != 'Q') { 
            gotoXY(frameX1 + FRAME_CONTENT_START_X_OFFSET + 20, frameY2 - FRAME_FOOTER_Y_OFFSET-1); 
            std::cout << "Nhan phim bat ky de quay lai Menu...";
            _getch();
        }
    } 
}

// --- Triển khai các hàm xử lý private ---

void App::handleAddEmployee(int contentX, int contentY, int contentWidth, int contentFrameY2) {
    int currentLineY = contentY; 
    int labelX = contentX;
    int inputX = labelX + 30; 
    if (inputX >= contentX + contentWidth - 20) { 
        inputX = labelX + (contentWidth / 3); // Điều chỉnh nếu quá sát
        if (inputX <= labelX + 5) inputX = labelX + 5; // Đảm bảo có khoảng cách tối thiểu
    }
    int remainingLines = contentFrameY2 - currentLineY - 1; // Trừ 1 cho dòng thông báo cuối cùng

    std::string type_str, name_str, address_str, phone_str, email_str, info_str, expiryDate_str, monthsWorkedStr_val;
    
    if (remainingLines < 9) { gotoXY(labelX, currentLineY); std::cout << "Khong du khong gian hien thi."; cDelay(1500); return;}

    std::string finalMessage = "";

    // --- 1. Nhập và kiểm tra Loại Nhân Viên ---
    std::string idPrefix; double defaultBaseSalary = 0.0;
    bool validType = false;
    int typeInputY = currentLineY;

    int Wwidth=0, Wheight=0;
    getConsoleWindowSize(Wwidth, Wheight);
    int tab = Wwidth / 4;
    
    int spaceToEnd = 0; // Khoảng trống từ label đến cuối dòng

    do {
        gotoXY(labelX+tab, currentLineY); std::cout << "Loai NV (fulltime,intern,contract):";
        gotoXY(inputX+tab+6, currentLineY); std::cout << std::string(spaceToEnd, ' '); 
        gotoXY(inputX+tab+6, currentLineY); std::getline(std::cin, type_str);

        if (type_str == "fulltime") { idPrefix = "FT"; defaultBaseSalary = 2340000; validType = true; }
        else if (type_str == "intern") { idPrefix = "IT"; defaultBaseSalary = 1170000; validType = true; }
        else if (type_str == "contract") { idPrefix = "CT"; defaultBaseSalary = 2106000; validType = true; }
        else {
            gotoXY(labelX+tab, contentFrameY2); std::cout << "Loai NV khong hop le. Nhap lai!"; 
            cDelay(1500);
            gotoXY(labelX+tab, contentFrameY2); std::cout << std::string(40, ' '); 
            spaceToEnd = type_str.length() + 6;
            if (spaceToEnd > contentWidth - 6) spaceToEnd = contentWidth - 6; // Không vượt quá chiều rộng
            validType = false;
        }
    } while (!validType);
    currentLineY++;

    if (!_empManager.loadFromFile("employee_list.txt")) { // Tải lại trước khi sinh ID
        gotoXY(labelX+tab, contentFrameY2); std::cout << "LOI: Khong tai duoc danh sach NV.";
        cDelay(1500); return;
    }
    std::string newEmployeeId = generateAndValidateNewEmployeeId(idPrefix);
    if (newEmployeeId.empty()) {
        gotoXY(labelX+tab, contentFrameY2); std::cout << "Khong the tao ma NV moi.";
        cDelay(1500); return;
    }
    gotoXY(labelX+tab, currentLineY++); std::cout << "Ma NV duoc cap: " << newEmployeeId;
    
    gotoXY(labelX+tab, currentLineY); std::cout << "Ten NV: ";
    gotoXY(inputX+tab+6, currentLineY++); std::getline(std::cin, name_str);
    
    gotoXY(labelX+tab, currentLineY); std::cout << "Dia chi: ";
    gotoXY(inputX+tab+6, currentLineY++); std::getline(std::cin, address_str);

    int phoneInputY = currentLineY;
    bool validPhone = false;
    do {
        gotoXY(labelX+tab, currentLineY); std::cout << "So Dien Thoai (10 so): ";
        gotoXY(inputX+tab+6, currentLineY); std::cout << std::string(spaceToEnd, ' '); 
        gotoXY(inputX+tab+6, currentLineY); std::getline(std::cin, phone_str);
        
        bool isNumericPhone = true;
        if(phone_str.length() == 10) {
            for(char const &c : phone_str) { if(!std::isdigit(c)) { isNumericPhone = false; break; } }
        } else { isNumericPhone = false; }

        if (phone_str.length() == 10 && isNumericPhone) { validPhone = true; } 
        else {
            gotoXY(labelX+tab, contentFrameY2); std::cout << "SDT phai la 10 chu so. Nhap lai!";
            spaceToEnd = phone_str.length() + 6; // Cập nhật khoảng trống
            if (spaceToEnd > contentWidth - 6) spaceToEnd = contentWidth - 6; // Không vượt quá chiều rộng
            cDelay(1500);
            gotoXY(labelX+tab, contentFrameY2); std::cout << std::string(40, ' ');
        }
    } while (!validPhone);
    currentLineY++;

    gotoXY(labelX+tab, currentLineY); std::cout << "Email: ";
    gotoXY(inputX+tab+6, currentLineY++); std::getline(std::cin, email_str);
    
    gotoXY(labelX+tab, currentLineY); std::cout << "Thong tin them: ";
    gotoXY(inputX+tab+6, currentLineY++); std::getline(std::cin, info_str);

    int expiryDateInputY = currentLineY;
    bool validExpiryDate = false;
    do {
        gotoXY(labelX+tab, currentLineY); std::cout << "Han hop dong (YYYY-MM-DD): ";
        gotoXY(inputX+tab+6, currentLineY); std::cout << std::string(spaceToEnd, ' '); 
        gotoXY(inputX+tab+6, currentLineY); std::getline(std::cin, expiryDate_str);

        if (expiryDate_str.empty() || expiryDate_str == "0-0-0" || expiryDate_str == "N/A") { validExpiryDate = true; } 
        else if (expiryDate_str.length() == 10 && expiryDate_str[4] == '-' && expiryDate_str[7] == '-') {
            try {
                int y_ex = std::stoi(expiryDate_str.substr(0, 4));
                int m_ex = std::stoi(expiryDate_str.substr(5, 2));
                int d_ex = std::stoi(expiryDate_str.substr(8, 2));
                if (y_ex >= 1900 && y_ex <= 2100 && m_ex >= 1 && m_ex <= 12 && d_ex >= 1 && d_ex <= 31) {
                    validExpiryDate = true;
                } else { throw std::out_of_range("Ngay thang khong hop le."); }
            } catch (const std::exception&) { validExpiryDate = false; }
        } else { validExpiryDate = false; }

        if (!validExpiryDate) {
            gotoXY(labelX+tab, contentFrameY2); std::cout << "Han HD phai la YYYY-MM-DD hop le. Nhap lai!";
            spaceToEnd = expiryDate_str.length() + 6; // Cập nhật khoảng trống
            if (spaceToEnd > contentWidth - 6) spaceToEnd = contentWidth - 6; // Không vượt quá chiều rộng
            cDelay(1500);
            gotoXY(labelX+tab, contentFrameY2); std::cout << std::string(60, ' ');
        }
    } while (!validExpiryDate);
    currentLineY++;

    gotoXY(labelX+tab, currentLineY); std::cout << "Tham nien (so thang): ";
    gotoXY(inputX+tab+6, currentLineY++); std::getline(std::cin, monthsWorkedStr_val);

    int monthsWorked_val = 0;
    try {
        if(!monthsWorkedStr_val.empty()) {
            bool isMonthsNumeric = true;
            for (char const &c : monthsWorkedStr_val) { if (!std::isdigit(c)) {isMonthsNumeric = false; break;}}
            if (isMonthsNumeric) monthsWorked_val = std::stoi(monthsWorkedStr_val);
            else throw std::invalid_argument("Tham nien phai la so.");
        }
        
        std::shared_ptr<IEmployee> newEmp = nullptr;
        if (type_str == "fulltime") { 
            newEmp = std::make_shared<FulltimeEmployee>(newEmployeeId, name_str, address_str, phone_str, email_str, info_str, expiryDate_str, defaultBaseSalary, monthsWorked_val);
        } else if (type_str == "intern") { 
             newEmp = std::make_shared<Intern>(newEmployeeId, name_str, address_str, phone_str, email_str, info_str, expiryDate_str, defaultBaseSalary, monthsWorked_val);
        } else if (type_str == "contract") { 
            newEmp = std::make_shared<ContractualEmployee>(newEmployeeId, name_str, address_str, phone_str, email_str, info_str, expiryDate_str, defaultBaseSalary, monthsWorked_val);
        }

        if (newEmp) {
            if (_empManager.addEmployee(newEmp)) { // Sử dụng giá trị trả về của addEmployee
                 saveData();
                 finalMessage = "Da them NV " + name_str + " voi ma " + newEmployeeId + ".";
            } else {
                finalMessage = "LOI: Them nhan vien that bai (MaNV co the da ton tai).";
            }
        } else { // Sẽ không vào đây nếu type_str hợp lệ
            finalMessage = "LOI: Khong tao duoc doi tuong nhan vien (loai khong xac dinh).";
        }
    } catch (const std::invalid_argument& ia) { 
        finalMessage = "Loi dau vao (tham nien): " + std::string(ia.what());
    } catch (const std::out_of_range& oor ) {
         finalMessage = "Loi dau vao (tham nien qua lon): " + std::string(oor.what());
    } catch (const std::exception& e) { 
        finalMessage = "Loi khong xuac dinh: " + std::string(e.what());
    }

    gotoXY(labelX+tab, contentFrameY2 - 2); 
    std::cout << finalMessage;
    
    cDelay(2500); 
}

void App::handleDeleteEmployee(int contentX, int contentY, int contentWidth, int contentFrameY2) {
     int Wwidth=0, Wheight=0;
    getConsoleWindowSize(Wwidth, Wheight);
    int tab = Wwidth / 4;

    int currentLineY = contentY;
    std::string empId;
    gotoXY(contentX + tab, currentLineY++); std::cout << "Nhap ma nhan vien can xoa: ";
    std::getline(std::cin, empId);

    if (!_empManager.loadFromFile("employee_list.txt")) { // Tải lại trước khi xóa
         gotoXY(contentX + tab, contentFrameY2); std::cout << "LOI: Khong the tai danh sach NV.";
         cDelay(1500); return;
    }

    if (_empManager.deleteEmployee(empId)) { 
        saveData(); 
        gotoXY(contentX + tab, contentFrameY2); std::cout << "Da xoa thanh cong NV " << empId << ". Du lieu da luu.";
    } else {
        gotoXY(contentX + tab, contentFrameY2); std::cout << "Khong tim thay NV " << empId << ". Xoa that bai.";
    }
    cDelay(2000);
}

void App::handleEditEmployee(int contentX, int contentY, int contentWidth, int messageDisplayY) {

    int Wwidth=0, Wheight=0;
    getConsoleWindowSize(Wwidth, Wheight);
    int tab = Wwidth / 4;

    int currentLineY = contentY; 
    int labelX = contentX;
    
    // Tính toán vị trí X cho cột hiển thị giá trị và cột nhập liệu
    int fieldLabelWidth = 25; // Độ rộng cho nhãn (ví dụ: "1. Ho Ten          ")
    int valueDisplayX = labelX + fieldLabelWidth + 2; // X cho giá trị hiện tại, cách nhãn 2 ký tự
    int inputDataX = labelX + fieldLabelWidth + 2;    // X cho vùng nhập dữ liệu mới

    // Đảm bảo các cột không bị quá sát lề phải
    if (valueDisplayX + 20 > contentX + contentWidth) { // 20 là ước lượng chiều rộng tối thiểu cho giá trị
        valueDisplayX = contentX + contentWidth - 20 -1;
        if (valueDisplayX <= labelX + fieldLabelWidth +1) valueDisplayX = labelX + fieldLabelWidth + 2;
    }
    if (inputDataX + 20 > contentX + contentWidth) {
        inputDataX = contentX + contentWidth - 20 -1;
         if (inputDataX <= labelX + fieldLabelWidth +1) inputDataX = labelX + fieldLabelWidth + 2;
    }

    gotoXY(labelX+5, messageDisplayY); std::cout << std::string(contentWidth-10, ' '); // Xóa thông báo cũ (nếu có)

    if (!_empManager.loadFromFile("employee_list.txt")) {
        gotoXY(labelX, currentLineY++); 
        std::cout << "LOI: Khong the tai lai du lieu nhan vien tu file.";
        cDelay(2000);
        return;
    }

    std::string empIdToEdit;
    std::shared_ptr<IEmployee> emp = nullptr; // Khai báo emp ở ngoài vòng lặp
    int idPromptY = currentLineY;

    int spaceToEnd = 0; // Khoảng trống từ label đến cuối dòng
    // Vòng lặp cho phép nhập lại Mã NV nếu sai
    do {
        gotoXY(labelX+tab, idPromptY); std::cout << "Nhap Ma NV can sua: ";
        gotoXY(labelX+tab + 20, idPromptY); std::cout << std::string(spaceToEnd, ' '); // Xóa input cũ
        gotoXY(labelX+tab + 20, idPromptY);
        std::getline(std::cin, empIdToEdit);

        if (empIdToEdit.empty()){ // Nếu người dùng không nhập gì mà Enter thì coi như hủy
            gotoXY(labelX+tab, messageDisplayY); std::cout << "Da huy thao tac sua.";
            cDelay(1500);
            return;
        }

        emp = _empManager.findEmployeeById(empIdToEdit);

        if (!emp) {
            gotoXY(labelX+tab, idPromptY + 1); 
            std::cout << "Khong tim thay NV '" << empIdToEdit << "'. Nhap lai hoac de trong roi Enter de huy.";
            spaceToEnd = empIdToEdit.length() + 5; // Cập nhật khoảng trống
            if (spaceToEnd > contentWidth - 10) spaceToEnd = contentWidth - 10; // Không vượt quá chiều rộng
            cDelay(2000);
            gotoXY(labelX+20, idPromptY + 1); std::cout << std::string(spaceToEnd, ' '); // Xóa thông báo lỗi
        }
    } while (!emp);
    currentLineY = idPromptY + 1; // Cập nhật currentLineY sau khi có ID hợp lệ
    
    // Xóa dòng nhập MaNV và thông báo lỗi (nếu có) để chuẩn bị hiển thị thông tin
    gotoXY(labelX, idPromptY); std::cout << std::string(contentWidth, ' ');
    if (idPromptY + 1 < currentLineY) { // Nếu có dòng thông báo lỗi đã được in
         gotoXY(labelX, idPromptY + 1); std::cout << std::string(contentWidth, ' ');
    }
    
    bool continueEditing = true;
    bool anyChangeMadeOverall = false;
    bool userCancelledOperation = false; 
    std::string tempUserMessage = ""; // Thông báo tạm thời cho người dùng

    while(continueEditing) {
        // Xóa vùng nội dung cũ trước khi hiển thị menu chọn trường
        for (int y_clear = currentLineY; y_clear <= messageDisplayY; ++y_clear) {
            gotoXY(labelX, y_clear); std::cout << std::string(contentWidth, ' ');
        }
        
        int menuDisplayY = currentLineY; 

        gotoXY(labelX+tab, menuDisplayY++); std::cout << "Chon thong tin can sua cho NV: " << emp->getName() 
                                                 << " (" << emp->getEmployeeId() << ")";
        gotoXY(labelX+tab, menuDisplayY++); std::cout << std::string((std::min)(contentWidth - 2, 60), '-');

        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "1. Ho Ten"; std::cout << ": "; 
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getName();
        
        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "2. Dia Chi"; std::cout << ": ";
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getAddress();

        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "3. SDT"; std::cout << ": ";
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getPhone();

        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "4. Email"; std::cout << ": ";
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getEmail();

        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "5. Thong Tin Them"; std::cout << ": ";
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getAdditionInfo();

        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "6. Han Hop Dong"; std::cout << ": ";
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getFormattedExpiryDate();

        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "7. Tham Nien (thang)"; std::cout << ": ";
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getMonthsWorked();
        
        gotoXY(labelX+tab, menuDisplayY); std::cout << std::left << std::setw(fieldLabelWidth) << "8. Loai Nhan Vien"; std::cout << ": ";
        gotoXY(valueDisplayX+tab, menuDisplayY++); std::cout << emp->getEmployeeType();
        
        gotoXY(labelX+tab, menuDisplayY++); std::cout << std::string((std::min)(contentWidth - 2, 60), '-');
        gotoXY(labelX+tab, menuDisplayY++); std::cout << "9. LUU VA KET THUC SUA";
        gotoXY(labelX+tab, menuDisplayY++); std::cout << "0. HUY VA THOAT (khong luu thay doi)";
        
        int choiceInputY = menuDisplayY; 
        gotoXY(labelX+tab, choiceInputY); std::cout << "Lua chon cua ban (0-9): ";
        
        char fieldChoice_char = _getch();
        bool currentFieldModified = false; 
        tempUserMessage = ""; // Reset thông báo tạm thời

        // Xóa phần menu chọn trường để chuẩn bị cho việc nhập liệu
        for (int y_clear = currentLineY; y_clear < choiceInputY + 1; ++y_clear) {
            gotoXY(labelX+tab, y_clear); std::cout << std::string(contentWidth-50, ' ');
        }
        int promptY = currentLineY; // Reset Y cho phần nhập liệu mới

        std::string newValue_str;
        int newValue_int;
        
        // Các lời nhắc sẽ được đặt tại labelX, và ô nhập liệu sẽ ở inputDataX
        // Thông báo lỗi tạm thời cho từng trường sẽ ở promptY + 1

        switch (fieldChoice_char) {
            case '1': // Ho Ten
                gotoXY(labelX+tab+10, promptY); std::cout << "Ho Ten hien tai: " << emp->getName();
                promptY++;
                gotoXY(labelX+tab+10, promptY); std::cout << "Nhap Ho Ten moi: ";
                gotoXY(inputDataX+tab+10, promptY); std::getline(std::cin, newValue_str);
                if (!newValue_str.empty() && newValue_str != emp->getName()) { 
                    emp->setName(newValue_str); currentFieldModified = true; 
                }
                break;
            case '2': // Dia chi
                gotoXY(labelX+tab+10, promptY); std::cout << "Dia Chi hien tai: " << emp->getAddress();
                promptY++;
                gotoXY(labelX+tab+10, promptY); std::cout << "Nhap Dia Chi moi: ";
                gotoXY(inputDataX+tab+10, promptY); std::getline(std::cin, newValue_str);
                if (!newValue_str.empty() && newValue_str != emp->getAddress()) { 
                    emp->setAddress(newValue_str); currentFieldModified = true; 
                }
                break;
            case '3': { // SDT
                spaceToEnd=0;
                bool validPhoneEdit = false;
                int phoneEditPromptY = promptY;
                do {
                    gotoXY(labelX+tab+10, phoneEditPromptY); std::cout << "SDT hien tai: " << emp->getPhone();
                    gotoXY(labelX+tab+10, phoneEditPromptY + 1); std::cout << "Nhap SDT moi (10 so): ";
                    gotoXY(inputDataX+tab+10, phoneEditPromptY + 1); std::cout << std::string(spaceToEnd, ' '); // Xóa input cũ
                    gotoXY(inputDataX+tab+10, phoneEditPromptY + 1);
                    std::getline(std::cin, newValue_str);

                    if (newValue_str.empty()) { validPhoneEdit = true; break;} // Cho phép không đổi

                    bool isNumericPhone = true;
                    if(newValue_str.length() == 10) {
                        for(char const &c : newValue_str) { if(!std::isdigit(c)) { isNumericPhone = false; break; } }
                    } else { isNumericPhone = false; }

                    if (isNumericPhone) { 
                        if(newValue_str != emp->getPhone()) {emp->setPhone(newValue_str); currentFieldModified = true;}
                        validPhoneEdit = true; 
                    } else {
                        tempUserMessage = "SDT phai la 10 CHU SO. Nhap lai hoac Enter de bo qua.";
                        gotoXY(labelX+tab+10, phoneEditPromptY + 2); std::cout << tempUserMessage;
                        spaceToEnd = tempUserMessage.length() + 5; // Khoảng trống để xóa
                        if (spaceToEnd > contentWidth - 10) spaceToEnd = contentWidth - 10; // Không vượt quá chiều rộng
                        cDelay(2500);
                        gotoXY(labelX+tab, phoneEditPromptY + 2); std::cout << std::string(tempUserMessage.length() + 30, ' ');
                    }
                } while (!validPhoneEdit);
                break;
            }
            case '4': // Email
                gotoXY(labelX+tab+10, promptY); std::cout << "Email hien tai: " << emp->getEmail();
                promptY++;
                gotoXY(labelX+tab+10, promptY); std::cout << "Nhap Email moi: ";
                gotoXY(inputDataX+tab+10, promptY); std::getline(std::cin, newValue_str);
                if (!newValue_str.empty() && newValue_str != emp->getEmail()) { emp->setEmail(newValue_str); currentFieldModified = true; }
                break;
            case '5': // Thong Tin Them
                gotoXY(labelX+tab+10, promptY); std::cout << "TT Them hien tai: " << emp->getAdditionInfo();
                promptY++;
                gotoXY(labelX+tab+10, promptY); std::cout << "Nhap TT Them moi: ";
                gotoXY(inputDataX+tab+10, promptY); std::getline(std::cin, newValue_str);
                if (!newValue_str.empty() && newValue_str != emp->getAdditionInfo()) { emp->setAdditionalInfo(newValue_str); currentFieldModified = true; }
                break;
            case '6': { // Han Hop Dong
                bool validExpiryEdit = false;
                int expiryEditPromptY = promptY;
                do {
                    gotoXY(labelX+tab+10, expiryEditPromptY); std::cout << "Han HD hien tai: " << emp->getFormattedExpiryDate();
                    expiryEditPromptY++;
                    gotoXY(labelX+tab+10, expiryEditPromptY); std::cout << "Nhap Han HD moi (YYYY-MM-DD): ";
                    gotoXY(inputDataX+tab+20, expiryEditPromptY); std::cout << std::string(spaceToEnd+5, ' ');
                    gotoXY(inputDataX+tab+20, expiryEditPromptY);
                    std::getline(std::cin, newValue_str);

                    if (newValue_str.empty()) { validExpiryEdit = true; break; } // Cho phép bỏ qua

                    if (newValue_str == "0-0-0" || newValue_str == "N/A") {
                         if(newValue_str != emp->getFormattedExpiryDate()) {emp->setExpiryDate(newValue_str); currentFieldModified = true;}
                         validExpiryEdit = true;
                    } else if (newValue_str.length() == 10 && newValue_str[4] == '-' && newValue_str[7] == '-') {
                        try {
                            int y = std::stoi(newValue_str.substr(0,4)); int m = std::stoi(newValue_str.substr(5,2)); int d = std::stoi(newValue_str.substr(8,2));
                            if(y>=1900 && y<=2100 && m>=1 && m<=12 && d>=1 && d<=31){
                                if(newValue_str != emp->getFormattedExpiryDate()) {emp->setExpiryDate(newValue_str); currentFieldModified = true;}
                                validExpiryEdit = true;
                            } else throw std::out_of_range("Ngay khong hop le");
                        } catch (const std::exception&) { validExpiryEdit = false; }
                    } else { validExpiryEdit = false; }

                    if (!validExpiryEdit) {
                        tempUserMessage = "Han HD phai YYYY-MM-DD hop le. Nhap lai hoac Enter de bo qua.";
                        gotoXY(labelX+tab+10, expiryEditPromptY + 1); std::cout << tempUserMessage;
                        int spaceToEnd = tempUserMessage.length() + 5; // Khoảng trống để xóa
                        cDelay(2000);
                        gotoXY(labelX+tab, expiryEditPromptY + 1); std::cout << std::string(tempUserMessage.length() + 30, ' ');
                        expiryEditPromptY--; // Để hiển thị lại lời nhắc đúng dòng
                    }
                } while (!validExpiryEdit);
                break;
            }
            case '7': { // Tham Nien
                int currentMonthsWorked = emp->getMonthsWorked();
                gotoXY(labelX+tab+10, promptY); std::cout << "Tham Nien hien tai (thang): " << currentMonthsWorked;
                promptY++;
                gotoXY(labelX+tab+10, promptY); std::cout << "Nhap Tham Nien moi (thang): ";
                gotoXY(inputDataX+tab+10, promptY);
                std::string monthsStr;
                std::getline(std::cin, monthsStr); // Đọc bằng getline để cho phép Enter bỏ qua

                if (!monthsStr.empty()) {
                    try {
                        bool isNum = true; for(char c : monthsStr) if(!isdigit(c)) {isNum=false; break;}
                        if (!isNum) throw std::invalid_argument("Phai la so.");
                        newValue_int = std::stoi(monthsStr);
                        if (newValue_int != currentMonthsWorked) {
                            emp->setMonthsWorked(newValue_int);
                            currentFieldModified = true;
                        }
                    } catch (const std::invalid_argument& ) {
                        tempUserMessage = "Tham nien phai la so nguyen. ";
                    } catch (const std::out_of_range& ) {
                        tempUserMessage = "Tham nien qua lon/nho. ";
                    }
                } // Nếu monthsStr rỗng thì không làm gì, giữ giá trị cũ
                break;
            }
            case '8': { // Sửa Loại Nhân Viên
                gotoXY(labelX+tab, promptY); std::cout << "Loai NV hien tai: " << emp->getEmployeeType();
                promptY++;
                gotoXY(labelX+tab, promptY); std::cout << "Loai NV moi (fulltime, intern, contract): ";
                gotoXY(inputDataX+tab+20, promptY++);
                std::string newEmpTypeInput;
                std::getline(std::cin, newEmpTypeInput);

                gotoXY(labelX, promptY);
                if (!newEmpTypeInput.empty()) {
                    std::string newLogicalType = ""; std::string newIdPrefix = ""; double newDefaultBaseSalary = 0.0;
                    if (newEmpTypeInput == "fulltime")      { newLogicalType = "Full-time Employee"; newIdPrefix = "FT"; newDefaultBaseSalary = 2340000; } 
                    else if (newEmpTypeInput == "intern")   { newLogicalType = "Intern"; newIdPrefix = "IT"; newDefaultBaseSalary = 1170000; } 
                    else if (newEmpTypeInput == "contract"){ newLogicalType = "Contractual Employee"; newIdPrefix = "CT"; newDefaultBaseSalary = 2106000; } 
                    else { tempUserMessage = "Loai nhan vien moi khong hop le.";}

                    if (!newLogicalType.empty()) {
                        if (emp->getEmployeeType() == newLogicalType) {
                            tempUserMessage = "Nhan vien da thuoc loai nay.";
                        } else {
                            std::string newGeneratedId = generateAndValidateNewEmployeeId(newIdPrefix);
                            if (newGeneratedId.empty()) {
                                tempUserMessage = "Khong the tao ma NV moi cho loai '" + newEmpTypeInput + "'.";
                            } else {
                                emp->setLogicalEmployeeType(newLogicalType);
                                emp->setEmployeeId(newGeneratedId);
                                emp->setBaseSalary(newDefaultBaseSalary);
                                currentFieldModified = true; 
                                tempUserMessage = "Da cap nhat Loai NV, Ma NV moi: " + newGeneratedId;
                            }
                        }
                    }
                } else { // Nếu người dùng không nhập gì, coi như không đổi
                    tempUserMessage = "Loai NV khong thay doi.";
                }
                break;
            }
            case '9': 
                continueEditing = false;
                break;
            case '0': 
                anyChangeMadeOverall = false; 
                continueEditing = false;
                userCancelledOperation = true; 
                break;
            default:
                tempUserMessage = "Lua chon khong hop le.";
                break;
        }
        
        // Hiển thị thông báo tạm thời
        if (!tempUserMessage.empty()) {
             gotoXY(labelX+tab, promptY + 1); std::cout << tempUserMessage;
        }

        if (currentFieldModified) {
            anyChangeMadeOverall = true;
            gotoXY(labelX+tab, (promptY + (tempUserMessage.empty() ? 1 : 2)) - 2 ); 
            std::cout << "Da cap nhat. Chon muc khac hoac '9' de Luu & Thoat.";
        }
        
        if (continueEditing) {
             cDelay(2000); 
             // currentInputLineY không cần reset vì vòng lặp sẽ xóa và vẽ lại từ currentInputLineY (là contentY)
        }
    } // end while(continueEditing)

    // Xóa toàn bộ vùng nội dung trước khi in thông báo cuối cùng
    for (int y_clear = contentY; y_clear <= messageDisplayY; ++y_clear) {
        gotoXY(labelX, y_clear); std::cout << std::string(contentWidth, ' ');
    }

    if (userCancelledOperation) {
         gotoXY(labelX+tab+10, messageDisplayY-2); std::cout << "Da huy thao tac sua. Khong co thay doi nao duoc luu.";
    } else if (anyChangeMadeOverall) { 
        saveData();
        gotoXY(labelX+tab+10, messageDisplayY-2); 
        std::cout << "Tat ca thay doi cho NV " << emp->getEmployeeId() << " da duoc luu!";
    } else { 
        gotoXY(labelX+tab+10, messageDisplayY-2); 
        std::cout << "Khong co thay doi nao duoc thuc hien.";
    }
    // App::run() sẽ chờ getch() sau đó
}

void App::handleShowEmployeeDetails(int contentX, int contentY, int contentWidth, int contentFrameY2) {
    int currentLineY = contentY; // Y bắt đầu cho các dòng nhập/hiển thị trong vùng content
    std::string empId;
    int Wwidth=0, Wheight=0;
    getConsoleWindowSize(Wwidth, Wheight);
    int tab = Wwidth / 4;

    gotoXY(contentX + tab, currentLineY++); 
    std::cout << "Nhap ma nhan vien can xem chi tiet: ";
    std::getline(std::cin, empId);

    // Xóa dòng nhập liệu sau khi đã lấy empId
    gotoXY(contentX + tab, currentLineY - 1); 
    std::cout << std::string(contentWidth, ' '); 

    // EmployeeManager sẽ chịu trách nhiệm clear screen và hiển thị chi tiết
    _empManager.displayEmployeeDetails(empId); 

}

bool App::handleLogin() {
    clearScreen();
    int windowWidth, windowHeight;
    getConsoleWindowSize(windowWidth, windowHeight);

    int frameWidth = 60; // Tăng chiều rộng khung login một chút
    int frameHeight = 11; 
    
    int frameX1 = (windowWidth - frameWidth) / 2;
    if (frameX1 < FRAME_MARGIN_X_LOGIN) frameX1 = FRAME_MARGIN_X_LOGIN;
    
    int frameY1 = (windowHeight - frameHeight) / 2;
    if (frameY1 < FRAME_MARGIN_Y_LOGIN) frameY1 = FRAME_MARGIN_Y_LOGIN;

    int frameX2 = frameX1 + frameWidth - 1;
    if (frameX2 >= windowWidth - FRAME_MARGIN_X_LOGIN) frameX2 = windowWidth - 1 - FRAME_MARGIN_X_LOGIN;
    
    int frameY2 = frameY1 + frameHeight - 1;
    if (frameY2 >= windowHeight - FRAME_MARGIN_Y_LOGIN) frameY2 = windowHeight - 1 - FRAME_MARGIN_Y_LOGIN;
    
    if (frameX2 < frameX1 + 20) frameX2 = frameX1 + 20;
    if (frameY2 < frameY1 + 7) frameY2 = frameY1 + 7;


    std::string username, password_str;
    int ch_input_raw; // Đọc getch() vào int để xử lý các mã mở rộng
    int attempts = 0;
    
    int labelX = frameX1 + FRAME_CONTENT_START_X_OFFSET_LOGIN;
    int inputX = labelX + 11; 
    int currentInputY; 

    int messageY = frameY2 - FRAME_FOOTER_Y_OFFSET_LOGIN; // Dòng cho thông báo

    while (attempts < 3) {
        clearScreen(); 
        drawBorder(frameX1, frameY1, frameX2, frameY2);
        printCenteredText("DANG NHAP HE THONG", frameY1 + FRAME_TITLE_Y_OFFSET_LOGIN, windowWidth);

        currentInputY = frameY1 + FRAME_CONTENT_START_Y_OFFSET_LOGIN;

        // Nhập Username
        gotoXY(labelX, currentInputY); std::cout << "Username: ";
        gotoXY(inputX, currentInputY); std::cout << std::string(frameWidth - (inputX - frameX1) - FRAME_CONTENT_START_X_OFFSET_LOGIN , ' '); 
        gotoXY(inputX, currentInputY); 
        std::cin >> username; 
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); 

        currentInputY++; 

        // Nhập Password
        gotoXY(labelX, currentInputY); std::cout << "Password: ";
        gotoXY(inputX, currentInputY); std::cout << std::string(frameWidth - (inputX - frameX1) - FRAME_CONTENT_START_X_OFFSET_LOGIN, ' '); 
        gotoXY(inputX, currentInputY); 
        
        password_str = ""; 
        while (true) {
            ch_input_raw = _getch(); // Đọc ký tự đầu tiên

            if (ch_input_raw == 0 || ch_input_raw == 0xE0) { // Nếu là ký tự đặc biệt (mũi tên, F-keys,...)
                _getch(); // Đọc và bỏ qua byte thứ hai của ký tự đặc biệt
                continue; // Bỏ qua, không xử lý
            }

            if (ch_input_raw == '\r' || ch_input_raw == '\n') { // Enter hoặc Newline
                break; 
            }
            
            if (ch_input_raw == 8) { // Mã ASCII cho Backspace
                if (!password_str.empty()) {
                    password_str.pop_back();
                    std::cout << "\b \b"; 
                }
            } 
            // Chỉ chấp nhận các ký tự in được (alphanumeric và các ký tự đặc biệt phổ biến)
            else if (isprint(static_cast<char>(ch_input_raw))) { 
                if (password_str.length() < (size_t)(frameX2 - inputX -1) ) { 
                    password_str += static_cast<char>(ch_input_raw);
                    std::cout << '*';
                }
            }
            // Các ký tự điều khiển khác (ngoài Enter, Backspace, 0, 0xE0) cũng sẽ bị bỏ qua
        }

        // Xóa dòng thông báo cũ (nếu có) từ lần thử trước
        gotoXY(frameX1 + 1, messageY); 
        std::cout << std::string(frameWidth - 2, ' '); // Xóa toàn bộ dòng thông báo bên trong khung

        if (username == "admin" && password_str == "password") {
            std::string successMsg = "Dang nhap thanh cong!";
            printCenteredText(successMsg, messageY, windowWidth);
            cDelay(1500);
            return true;
        } else {
            attempts++;
            std::string errorMsg = "Sai Username/Password! (" + std::to_string(attempts) + "/3)";
            printCenteredText(errorMsg, messageY, windowWidth);
            cDelay(1500);
            
            if (attempts >= 3) {
                // Xóa thông báo lỗi cũ
                gotoXY(frameX1 + 1, messageY); std::cout << std::string(frameWidth - 2, ' '); 

                std::string failMsg = "Dang nhap that bai 3 lan. Thoat...";
                printCenteredText(failMsg, messageY, windowWidth);
                cDelay(2000);
                return false;
            }
            // Không cần reset currentInputY ở đây vì vòng lặp while sẽ vẽ lại toàn bộ
        }
    }
    return false; 
}

std::string App::generateAndValidateNewEmployeeId(const std::string& prefix) {
    const auto& employees = _empManager.getEmployees(); // Lấy danh sách nhân viên hiện tại
    std::set<int> usedNumbers;

    for (const auto& emp : employees) {
        const std::string& empId = emp->getEmployeeId(); //
        // Kiểm tra xem ID có bắt đầu bằng prefix và có độ dài là prefix + 3 ký tự số không
        if (empId.rfind(prefix, 0) == 0 && empId.length() == prefix.length() + 3) {
            try {
                std::string numPart = empId.substr(prefix.length());
                // Đảm bảo phần số thực sự là số và có 3 chữ số
                if (numPart.length() == 3 && std::all_of(numPart.begin(), numPart.end(), ::isdigit)) {
                     usedNumbers.insert(std::stoi(numPart));
                }
            } catch (const std::out_of_range& oor) {
                // Bỏ qua nếu không phải số hợp lệ
            } catch (const std::invalid_argument& ia) {
                // Bỏ qua nếu không phải số hợp lệ
            }
        }
    }

    for (int i = 1; i <= 999; ++i) { // Tìm số nhỏ nhất từ 001 đến 999 chưa được sử dụng
        if (usedNumbers.find(i) == usedNumbers.end()) {
            std::ostringstream oss;
            oss << prefix << std::setw(3) << std::setfill('0') << i; // Định dạng thành XXX, ví dụ FT001
            return oss.str();
        }
    }
    return ""; // Trả về chuỗi rỗng nếu không tìm thấy mã phù hợp (ví dụ: đã hết 999 mã)
}