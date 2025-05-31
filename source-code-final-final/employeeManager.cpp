#include "EmployeeManager.h"
#include "FulltimeEmployee.h"
#include "Intern.h"
#include "ContractualEmployee.h"
#include "SocialInsuranceWelfare.h"
#include "BonusWelfare.h"
#include "transportationWelfare.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.h"
#include <conio.h>

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
bool EmployeeManager::addEmployee(std::shared_ptr<IEmployee> emp) {
    if (!emp) { // Kiểm tra con trỏ null
        std::cerr << "LOI: Khong the them nhan vien null." << std::endl;
        return false;
    }
    if (findEmployeeById(emp->getEmployeeId()) != nullptr) {
        std::cerr << "LOI: Ma nhan vien " << emp->getEmployeeId() << " da ton tai." << std::endl;
        return false; // Thêm không thành công do trùng ID
    }
    _employeeList.push_back(emp);
    return true; // Thêm thành công
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

// /**
//  * @brief Hiển thị thông tin cơ bản của tất cả nhân viên.
//  */
// void EmployeeManager::displayAllEmployees(int frameX, int frameY, int frameWidth, int frameHeight) const {
//     int titleY = frameY + FRAME_TITLE_Y_OFFSET; // Tiêu đề "DANH SACH NHAN VIEN" do App::run in
//     int headerY = titleY + 2; // Dòng cho tiêu đề cột
//     int contentStartX = frameX + FRAME_CONTENT_START_X_OFFSET;
//     int currentDataY = headerY + 2; // Dòng bắt đầu in dữ liệu nhân viên

//     // In tiêu đề cột
//     // (frameWidth - 10 - 25 - (2*FRAME_CONTENT_START_X_OFFSET)) > 20 ? (frameWidth - 10 - 25 - (2*FRAME_CONTENT_START_X_OFFSET)) : 20
//     gotoXY(contentStartX, headerY); 
//     std::cout << std::left 
//               << std::setw(10) << "Ma NV"
//               << std::setw(35) << "Ho Ten" // Ước lượng độ rộng cột
//               << std::setw(30) << "Dia Chi"
//               << std::setw(30) << "Email"
//               << std::setw(25) << "Loai NV";
    
//     gotoXY(contentStartX, headerY + 1);
//     std::cout << std::string(frameWidth - (2*FRAME_CONTENT_START_X_OFFSET) + (FRAME_CONTENT_START_X_OFFSET/2) , '-');


//     if (_employeeList.empty()) {
//         gotoXY(contentStartX, currentDataY); std::cout << "Danh sach nhan vien trong.";
//         return;
//     }

//     int linesPrintedOnPage = 0;
//     // Số dòng tối đa cho nội dung dữ liệu trên một trang
//     int maxLinesPerPage = frameHeight - (headerY + 2 - frameY) // Khoảng cách từ đỉnh khung đến bắt đầu dữ liệu
//                            - FRAME_FOOTER_Y_OFFSET -1; // Trừ footer của App và 1 dòng đệm


//     for (const auto& emp : _employeeList) {
//         if (linesPrintedOnPage >= maxLinesPerPage || currentDataY >= frameY + frameHeight - FRAME_FOOTER_Y_OFFSET -1 ) {
//             gotoXY(contentStartX, frameY + frameHeight - FRAME_FOOTER_Y_OFFSET); 
//             std::cout << "Nhan phim bat ky de xem tiep...";
//             getch();
            
//             // Xóa phần nội dung cũ của danh sách để vẽ trang mới
//             for(int i = 0; i < linesPrintedOnPage; ++i) {
//                 gotoXY(contentStartX, (headerY + 2) + i); 
//                 std::cout << std::string(frameWidth - (2*FRAME_CONTENT_START_X_OFFSET) + (FRAME_CONTENT_START_X_OFFSET/2), ' ');
//             }
//             currentDataY = headerY + 2; // Đặt lại Y cho dữ liệu trang mới
//             linesPrintedOnPage = 0;
//         }
//         gotoXY(contentStartX, currentDataY++);
//         std::cout << std::left 
//                   << std::setw(10) << emp->getEmployeeId()
//                   << std::setw(35) << emp->getName()
//                   << std::setw(30) << emp->getAddress()
//                   << std::setw(30) << emp->getEmail()
//                   << std::setw(25) << emp->getEmployeeType();
//         linesPrintedOnPage++;
//     }
// }

const int APP_TITLE_Y_OFFSET_FOR_EMP_MGR = 1; 
const int TABLE_CONTENT_START_X_OFFSET = 3;
const int APP_FOOTER_Y_OFFSET_FOR_EMP_MGR = 1;

void EmployeeManager::displayAllEmployees(int frameX, int frameY, int frameWidth, int frameHeight) const {
    // Tiêu đề "DANH SACH NHAN VIEN" (ví dụ) đã được App::run() in ở 
    // frameY + APP_TITLE_Y_OFFSET_FOR_EMP_MGR (hoặc tương tự)
    
    // Dòng Y cho tiêu đề cột (Ma NV, Ho Ten, ...)
    // Phải tính toán dựa trên frameY và các offset tiêu đề của App::run()
    // Giả sử App::run() đã in tiêu đề ở frameY + 1, gạch ngang ở frameY + 2
    // thì header của bảng sẽ bắt đầu từ frameY + 4 hoặc frameY + 5
    int tableHeaderY = frameY + APP_TITLE_Y_OFFSET_FOR_EMP_MGR + 2; // Điều chỉnh dựa trên tiêu đề của App::run()
    
    int contentTableStartX = frameX + TABLE_CONTENT_START_X_OFFSET;
    int dataDisplayStartY = tableHeaderY + 2; // Dòng Y bắt đầu in dữ liệu nhân viên thực tế

    // Chiều rộng tối đa có thể dùng cho các cột bên trong vùng content của khung
    int actualTableWidth = frameWidth - (2 * TABLE_CONTENT_START_X_OFFSET);
    if (actualTableWidth < 75) actualTableWidth = 75; // Đảm bảo chiều rộng tối thiểu cho 4 cột

    // --- Định nghĩa độ rộng cho các cột ---
    int maNvColWidth = 10;
    int loaiNvColWidth = 24; // Cho "Contractual Employee"
    int emailColWidth = 28;  // Ước lượng cho email
    int spacingBetweenCols = 3 * 1; // 3 khoảng cách giữa 4 cột, mỗi khoảng 1 ký tự
    
    // Tính toán độ rộng còn lại cho "Ho Ten"
    int hoTenColWidth = actualTableWidth - maNvColWidth - emailColWidth - loaiNvColWidth - spacingBetweenCols;

    if (hoTenColWidth < 15) { // Nếu Ho Ten quá hẹp
        int deficit = 15 - hoTenColWidth;
        hoTenColWidth = 15;
        // Cố gắng giảm ở Email trước nếu Email vẫn còn rộng hơn mức tối thiểu (ví dụ 20)
        if (emailColWidth - deficit >= 20) {
            emailColWidth -= deficit;
        } else {
            // Nếu không đủ, có thể cần giảm ở LoaiNV hoặc chấp nhận
            int oldEmailWidth = emailColWidth;
            emailColWidth = 20;
            deficit -= (oldEmailWidth - emailColWidth); // Phần thiếu còn lại
            if (deficit > 0 && loaiNvColWidth - deficit >= 20) {
                loaiNvColWidth -= deficit;
            }
        }
    }
    // Đảm bảo không cột nào có độ rộng âm sau khi điều chỉnh
    if (hoTenColWidth < 0) hoTenColWidth = 0;
    if (emailColWidth < 0) emailColWidth = 0;
    if (loaiNvColWidth < 0) loaiNvColWidth = 0;

    // Tổng độ rộng thực tế của các cột dữ liệu và khoảng cách
    int totalUsedWidth = maNvColWidth + hoTenColWidth + emailColWidth + loaiNvColWidth + spacingBetweenCols;


    // In tiêu đề cột
    gotoXY(contentTableStartX, tableHeaderY); 
    std::cout << std::left 
              << std::setw(10) << "Ma NV"
              << std::setw(35) << "Ho Ten" // Ước lượng độ rộng cột
              << std::setw(30) << "Dia Chi"
              << std::setw(30) << "Email"
              << std::setw(25) << "Loai NV";
    
    gotoXY(contentTableStartX, tableHeaderY + 1);
    // Vẽ đường gạch ngang bằng tổng độ rộng các cột đã tính, không vượt quá actualTableWidth
    std::cout << std::string((std::min)(actualTableWidth -1, totalUsedWidth -1) , '-');


    if (_employeeList.empty()) {
        gotoXY(contentTableStartX, dataDisplayStartY); std::cout << "Danh sach nhan vien trong.";
        return;
    }

    int linesPrintedOnPage = 0;
    // Dòng Y mà thông báo "Nhấn phím..." của App::run() sẽ xuất hiện (đây là footer của App::run)
    int appRunFooterLineY = frameY + frameHeight - APP_FOOTER_Y_OFFSET_FOR_EMP_MGR;
    // Dòng Y dành cho thông báo "Nhấn phím để xem tiep..." của hàm này (nếu phân trang)
    // Sẽ đặt ngay trên appRunFooterLineY
    int paginationPromptY = appRunFooterLineY - 1; 

    int maxLinesPerPage = paginationPromptY - dataDisplayStartY;
    if (maxLinesPerPage < 1) {
        maxLinesPerPage = 1; // Đảm bảo ít nhất 1 dòng có thể hiển thị
        if (dataDisplayStartY >= paginationPromptY) {
             // Trường hợp khung quá hẹp, không đủ chỗ cho cả header và 1 dòng dữ liệu + prompt
             gotoXY(contentTableStartX, dataDisplayStartY); std::cout << "Khung hien thi qua hep!";
             return;
        }
    }


    int currentDataPrintY = dataDisplayStartY; 

    for (const auto& emp : _employeeList) {
        if (!emp) continue; // Bỏ qua nếu con trỏ null

        if (linesPrintedOnPage >= maxLinesPerPage) {
            gotoXY(contentTableStartX, paginationPromptY-2); 
            std::cout << "Nhan phim bat ky de xem tiep...";
            _getch(); // Từ Utils.h hoặc <conio.h>
            
            // Xóa phần nội dung dữ liệu cũ của danh sách để vẽ trang mới
            for(int i = 0; i < linesPrintedOnPage; ++i) {
                if (dataDisplayStartY + i < paginationPromptY) { // Chỉ xóa những dòng thuộc về dữ liệu
                    gotoXY(contentTableStartX, dataDisplayStartY + i); 
                    std::cout << std::string(actualTableWidth, ' '); 
                }
            }
            currentDataPrintY = dataDisplayStartY; // Đặt lại Y cho dữ liệu trang mới
            linesPrintedOnPage = 0;
        }

        // Đảm bảo không vẽ đè lên dòng paginationPromptY trừ khi đó là dòng cuối cùng cho phép
        if (currentDataPrintY < paginationPromptY || (linesPrintedOnPage < maxLinesPerPage && currentDataPrintY == paginationPromptY )) {
            gotoXY(contentTableStartX, currentDataPrintY++);
            std::cout << std::left 
                  << std::setw(10) << emp->getEmployeeId()
                  << std::setw(35) << emp->getName()
                  << std::setw(30) << emp->getAddress()
                  << std::setw(30) << emp->getEmail()
                  << std::setw(25) << emp->getEmployeeType();
        linesPrintedOnPage++;
            linesPrintedOnPage++;
        } else { // Không còn đủ chỗ, chờ vòng lặp sau để xử lý phân trang
            // Điều này không nên xảy ra nếu logic maxLinesPerPage đúng
        }
    }
    // Footer "Nhan phim bat ky de quay lai Menu..." sẽ do App::run() hiển thị
}

void EmployeeManager::displayEmployeeDetails(const std::string& empId) const {
    auto emp = findEmployeeById(empId);

    clearScreen(); // Xóa màn hình hiện tại (màn hình nhập liệu của App::run)
    int windowWidth, windowHeight;
    getConsoleWindowSize(windowWidth, windowHeight);

    // Vẽ khung cho màn hình chi tiết nhân viên
    int detailFrameX1 = FRAME_MARGIN_X;
    int detailFrameY1 = FRAME_MARGIN_Y;
    int detailFrameX2 = windowWidth - 1 - FRAME_MARGIN_X;
    int detailFrameY2 = windowHeight - 1 - FRAME_MARGIN_Y; // Chừa dòng cho footer của App::run

    if (detailFrameX2 <= detailFrameX1 + 40) detailFrameX2 = detailFrameX1 + 40;
    if (detailFrameX2 >= windowWidth) detailFrameX2 = windowWidth - 1;
    if (detailFrameY2 <= detailFrameY1 + 15) detailFrameY2 = detailFrameY1 + 15;
    if (detailFrameY2 >= windowHeight -1) detailFrameY2 = windowHeight - 2; // Chừa 1 dòng cho footer "Nhấn phím"


    drawBorder(detailFrameX1, detailFrameY1, detailFrameX2, detailFrameY2);
    printCenteredText("CHI TIET NHAN VIEN", detailFrameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
    std::string separator(40, '-'); // Đường gạch ngang
    printCenteredText(separator, detailFrameY1 + FRAME_SEPARATOR_Y_OFFSET, windowWidth);

    if (!emp) {
        gotoXY(detailFrameX1 + FRAME_CONTENT_START_X_OFFSET, detailFrameY1 + FRAME_CONTENT_START_Y_OFFSET);
        std::cout << "Khong tim thay nhan vien voi ma ID: " << empId;
        // App::run() sẽ hiển thị "Nhan phim bat ky..." sau khi hàm này kết thúc
    } else {
        // Tọa độ và chiều rộng cho nội dung chi tiết bên trong khung
        int contentX = detailFrameX1 + FRAME_CONTENT_START_X_OFFSET;
        int contentY = detailFrameY1 + FRAME_CONTENT_START_Y_OFFSET;
        int contentWidth = detailFrameX2 - detailFrameX1 - (2 * FRAME_CONTENT_START_X_OFFSET) + 1;
        
        _payrollPrinter.printEmployeeDetails(emp, contentX, contentY-1, contentWidth);
    }
    // Không cần getch() hay cDelay() ở đây, App::run sẽ xử lý
}

bool EmployeeManager::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Khong the mo file " << filename << " de doc trong EmployeeManager." << std::endl;
        return false; // Hoặc ném ngoại lệ
    }

    _employeeList.clear(); // Xóa danh sách cũ trước khi tải danh sách mới

    std::string line;
    // Bỏ qua dòng tiêu đề nếu có (dựa trên file employee_list.txt của bạn có dòng comment #)
    if (std::getline(inFile, line) && !line.empty() && line[0] == '#') {
        // Dòng tiêu đề đã được bỏ qua
    } else {
        // Nếu không có dòng tiêu đề hoặc file trống, xử lý dòng đầu tiên (nếu có)
        // Hoặc tua lại nếu dòng đầu tiên là dữ liệu
        if (!line.empty() && line[0] != '#') {
            inFile.clear(); // Xóa cờ EOF/failbit
            inFile.seekg(0, std::ios::beg); // Quay lại đầu file
        }
    }


    while (std::getline(inFile, line)) {
        if (line.empty()) continue; // Bỏ qua dòng trống
        
        std::stringstream ss(line);
        std::string type, id, name, address, phone, email, info, expiryDateStr, baseSalaryStr, monthsWorkedStr;
        
        // Đọc các trường từ CSV
        std::getline(ss, type, ',');
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, address, ',');
        std::getline(ss, phone, ',');
        std::getline(ss, email, ',');
        std::getline(ss, info, ',');
        std::getline(ss, expiryDateStr, ','); // Đây là HanHopDong
        std::getline(ss, baseSalaryStr, ',');
        std::getline(ss, monthsWorkedStr, '\n'); // Đây là ThamNien

        // Kiểm tra xem có đọc thiếu trường nào không
        if (ss.fail() && !ss.eof() && type.empty()) { // Nếu type rỗng và ss fail (trừ eof) -> dòng lỗi
            std::cerr << "Loi doc dong: " << line << std::endl;
            continue; 
        }


        double baseSalary = 0.0;
        int monthsWorked = stoi(monthsWorkedStr);

        try {
            if (!baseSalaryStr.empty()) {
                baseSalary = std::stod(baseSalaryStr);
            }
        } catch (const std::invalid_argument& ia) {
            std::cerr << "CANH BAO: Luong co ban khong hop le cho MaNV " << id << ": '" << baseSalaryStr << "'. Dat bang 0." << std::endl;
            baseSalary = 0.0;
        } catch (const std::out_of_range& oor) {
            std::cerr << "CANH BAO: Luong co ban qua lon cho MaNV " << id << ": '" << baseSalaryStr << "'. Dat bang 0." << std::endl;
            baseSalary = 0.0;
        }
        
        std::shared_ptr<IEmployee> emp = nullptr;
        if (type == "Full-time Employee") { // So sánh với chuỗi đầy đủ trong file
            emp = std::make_shared<FulltimeEmployee>(id, name, address, phone, email, info, expiryDateStr, baseSalary, monthsWorked);
        } else if (type == "Intern") { //
            emp = std::make_shared<Intern>(id, name, address, phone, email, info, expiryDateStr, baseSalary, monthsWorked);
        } else if (type == "Contractual Employee") { //
            emp = std::make_shared<ContractualEmployee>(id, name, address, phone, email, info, expiryDateStr, baseSalary, monthsWorked);
        } else {
            std::cerr << "Loai nhan vien khong duoc ho tro: " << type << " cho ID: " << id << std::endl;
            continue;
        }

        if (emp) {
            // Thay vì gọi this->addEmployee (có thể in ra thông báo không mong muốn ở đây),
            // chúng ta trực tiếp thêm vào danh sách. Việc kiểm tra trùng ID khi tải file
            // thường không cần thiết nếu file được coi là nguồn đáng tin cậy.
            // Nếu muốn kiểm tra, bạn có thể gọi findEmployeeById trước.
            if (this->findEmployeeById(emp->getEmployeeId()) == nullptr) {
                 _employeeList.push_back(emp);
            } else {
                std::cerr << "Canh bao: Ma nhan vien " << emp->getEmployeeId() << " bi trung khi tai file. Bo qua ban ghi trung." << std::endl;
            }
        }
    }
    inFile.close();
    return true;
}

bool EmployeeManager::deleteEmployee(const std::string& empId) { //
    auto it = std::remove_if(_employeeList.begin(), _employeeList.end(),
        [&empId](const auto& emp) {
            return emp->getEmployeeId() == empId;
        });

    if (it != _employeeList.end()) {
        _employeeList.erase(it, _employeeList.end());
        // std::cout << "Da xoa nhan vien voi ma ID: " << empId << std::endl; // App sẽ xử lý thông báo này
        return true; // Xóa thành công
    } else {
        // std::cerr << "Khong tim thay nhan vien voi ma ID: " << empId << std::endl; // App sẽ xử lý thông báo này
        return false; // Không tìm thấy để xóa
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

void EmployeeManager::printPayroll(const std::string& empId, int month, int year) {
    _attendanceManager.loadFromFile("attendance.csv");

    auto emp = findEmployeeById(empId);
    // ... (phần kiểm tra emp và báo lỗi nếu không tìm thấy như cũ) ...
    if (!emp) {
        clearScreen(); 
        int w, h;
        getConsoleWindowSize(w, h);
        int frameX1 = FRAME_MARGIN_X; /* ... (tính toán khung như cũ) ... */
        int frameY1 = FRAME_MARGIN_Y;
        int frameX2 = w - 1 - FRAME_MARGIN_X;
        int frameY2 = h - 1 - FRAME_MARGIN_Y -1;
        if (frameX2 <= frameX1+10) frameX2 = frameX1+10;
        if (frameY2 <= frameY1+5) frameY2 = frameY1+5;
        if (frameX2 >= w) frameX2 = w-1;
        if (frameY2 >= h-1) frameY2 = h-2;


        drawBorder(frameX1, frameY1, frameX2, frameY2);
        printCenteredText("LOI: IN PHIEU LUONG", frameY1 + FRAME_TITLE_Y_OFFSET, w);
        gotoXY(frameX1 + FRAME_CONTENT_START_X_OFFSET, frameY1 + FRAME_CONTENT_START_Y_OFFSET +1); 
        std::cout << "Khong tim thay nhan vien voi ma ID: " << empId;
        cDelay(2000);
        return; 
    }


    double bonuses = 0.0, allowances = 0.0, deductions = 0.0;
    _welfareManager.calculateAllWelfareForEmployee(*emp, _attendanceManager, month, year, bonuses, allowances, deductions);
    SalaryDetails details = emp->calculateSalary(_attendanceManager, month, year, bonuses, allowances, deductions);

    // Chuẩn bị màn hình cho phiếu lương console
    clearScreen(); 
    int windowWidth, windowHeight;
    getConsoleWindowSize(windowWidth, windowHeight);
    int payslipFrameX1 = FRAME_MARGIN_X; /* ... (tính toán khung phiếu lương như cũ) ... */
    int payslipFrameY1 = FRAME_MARGIN_Y;
    int payslipFrameX2 = windowWidth - 1 - FRAME_MARGIN_X;
    int payslipFrameY2 = windowHeight - 1 - FRAME_MARGIN_Y -1; // Trừ 1 dòng cho footer

    if (payslipFrameX2 <= payslipFrameX1 + 55) payslipFrameX2 = payslipFrameX1 + 55; 
    if (payslipFrameY2 <= payslipFrameY1 + 18) payslipFrameY2 = payslipFrameY1 + 18; 
    if (payslipFrameX2 >= windowWidth) payslipFrameX2 = windowWidth -1;
    if (payslipFrameY2 >= windowHeight -1) payslipFrameY2 = windowHeight -2;

    drawBorder(payslipFrameX1, payslipFrameY1, payslipFrameX2, payslipFrameY2);
    printCenteredText("PHIEU LUONG NHAN VIEN", payslipFrameY1 + FRAME_TITLE_Y_OFFSET, windowWidth);
    std::string separator(40, '-'); 
    printCenteredText(separator, payslipFrameY1 + FRAME_TITLE_Y_OFFSET + 1, windowWidth); // +1 để xuống dòng

    // In ra console
    _payrollPrinter.printPaySlip(emp, details); 

    // Tạo tên file và xuất ra file txt
    std::ostringstream ossFilename;
    ossFilename << emp->getEmployeeId() << "_" << month << "_" << year << ".txt";
    _payrollPrinter.printPaySlipToFile(emp, details, ossFilename.str());

    // Hiển thị thông báo đã xuất file ở cuối màn hình console, bên trong khung

    int tab = windowWidth / 4 + 2 ;

    gotoXY(payslipFrameX1 + FRAME_CONTENT_START_X_OFFSET + tab, payslipFrameY2 - 10); // Gần cuối khung
    std::string exportMsg = "Da xuat phieu luong ra file: " + ossFilename.str();
    // Tính toán vị trí X để căn giữa thông báo này, hoặc đặt ở vị trí cố định
    int msgX = payslipFrameX1 + FRAME_CONTENT_START_X_OFFSET;
    if (payslipFrameY2 -1 > payslipFrameY1 + 18) { // Đảm bảo có chỗ cho thông báo
         gotoXY(msgX+tab, payslipFrameY2 - 10 ); // Gần cuối khung
         std::cout << exportMsg; // Xóa phần dư
    }
    // App::run() sẽ chờ getch()
}

const std::vector<std::shared_ptr<IEmployee>>& EmployeeManager::getEmployees() const { //
    return _employeeList;
}

void EmployeeManager::printAllPayrolls(const std::string& filename, int month, int year) {
    // 1. Tải dữ liệu chấm công mới nhất
    //    Hàm loadFromFile của AttendanceManager sẽ in ra thông báo "Da tai X ban ghi..."
    _attendanceManager.loadFromFile("attendance.csv");

    std::vector<std::pair<std::shared_ptr<IEmployee>, SalaryDetails>> payrollData;

    if (_employeeList.empty()) {
        // std::cout << "Khong co nhan vien nao trong danh sach de tinh luong." << std::endl;
        // Ghi file rỗng hoặc file chỉ có tiêu đề
    }

    // 2. Lặp qua từng nhân viên để tính lương
    for (const auto& emp : _employeeList) {
        if (!emp) continue; // Bỏ qua nếu con trỏ null (dù không nên xảy ra)

        // 3. Tính toán các khoản phúc lợi cho tháng/năm cụ thể
        double bonuses = 0.0, allowances = 0.0, deductions = 0.0;
        // Giả định WelfareManager::calculateAllWelfareForEmployee đã được cập nhật để nhận month, year
        _welfareManager.calculateAllWelfareForEmployee(*emp, _attendanceManager, month, year, bonuses, allowances, deductions);
        
        // 4. Tính toán chi tiết lương cho tháng/năm cụ thể
        // Giả định các lớp con của IEmployee đã cập nhật calculateSalary để nhận month, year
        SalaryDetails details = emp->calculateSalary(_attendanceManager, month, year, bonuses, allowances, deductions);
        
        payrollData.push_back({emp, details});
    }

    // 5. Gọi PayrollPrinter để xuất dữ liệu ra file
    // Hàm printToFile của PayrollPrinter đã được sửa để in thêm các cột lương giờ, OT, lễ.
    _payrollPrinter.printToFile(payrollData, filename);
    
    // App.cpp sẽ hiển thị thông báo "Da xuat file..." sau khi hàm này trả về.
}