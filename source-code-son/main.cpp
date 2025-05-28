// Các chức năng của chương trình quản lý nhân viên
#include "IEmployee.h"
#include "EmployeeAdder.h"
#include "EmployeeManager.h"
#include "EmployeeRemover.h"
#include "EmployeeFinder.h"
#include "EmployeeEditor.h"

// Các loại nhân viên
#include "intern.h"
#include "officialemployee.h"
#include "manager.h"

// Các chức năng in thông tin nhân viên
#include "EmployeePrinter.h"

// Các loại phúc lợi
#include "bonusWelfare.h"
#include "concreteWelfare.h"
#include "healthinsuranceWelfare.h"
#include "IWelfare.h"
#include "transportationWelfare.h"
#include "socialinsuranceWelfare.h"

// Tính lương
#include "PaySlip.h"
#include "Attendance.h"
#include "PayRollCalculator.h"
#include "SalaryPayment.h"
#include "PayRollPrinter.h"

// Các chức năng khác
#include "CultureInfo.h"
#include "NumberFormatter.h"

using std::cin;
using std::cout;
using std::endl;

int main() {
    EmployeeManager manager;

    while (1) {
        cout << "\n========================\n";
        cout << "Quản lý nhân viên\n";
        cout << "========================\n";
        cout << "1. Thêm nhân viên\n";
        cout << "2. Xoá nhân viên\n";
        cout << "3. Tìm kiếm nhân viên để xem thông tin\n";
        cout << "4. Chỉnh sửa thông tin nhân viên\n";
        cout << "5. Hiển thị danh sách nhân viên\n";
        cout << "6. Xem lương nhân viên\n";
        cout << "7. Thoát\n";
        cout << "========================\n";

        cout << "Chọn chức năng: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Để bỏ qua ký tự newline sau khi nhập số
        if (choice < 1 || choice > 7) {
            cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
            continue;
        }

        if (choice == 7) {
            cout << "Cảm ơn bạn đã sử dụng chương trình!\n";
            break;
        }

        switch (choice) {
        case 1: {
            system("cls");
            cout << "Chọn loại nhân viên để thêm:\n";
            cout << "1. Nhân viên chính thức\n";
            cout << "2. Nhân viên thực tập\n";
            cout << "3. Nhân viên quản lý\n";
            int type;
            cin >> type;
            cin.ignore(); // Bỏ qua ký tự newline sau khi nhập số

            switch (type) {
            case 1: {
                auto emp = std::make_unique<OfficialEmployee>("", "", "", "", "", "", "");
                cout << "Nhập thông tin nhân viên chính thức:\n";
                cout << "Họ tên: ";
                std::string name;
                std::getline(cin, name);
                emp->setName(name);
                cout << "Mã nhân viên: ";
                std::string id;
                std::getline(cin, id);
                emp->setId(id);
                cout << "Địa chỉ: ";
                std::string address;
                std::getline(cin, address);
                emp->setAddress(address);
                cout << "Số điện thoại: ";
                std::string phone;
                std::getline(cin, phone);
                emp->setPhone(phone);
                cout << "Email: ";
                std::string email;
                std::getline(cin, email);
                emp->setEmail(email);
                cout << "Thông tin bổ sung: ";
                std::string additionalInfo;
                std::getline(cin, additionalInfo);
                emp->setAdditionalInfo(additionalInfo);
                cout << "Ngày hết hạn hợp đồng (dd mm yyyy): ";
                int day, month, year;
                cin >> day >> month >> year;
                cin.ignore(); // Bỏ qua ký tự newline sau khi nhập số
                emp->setContractExpiry(day, month, year);
                EmployeeAdder adder;
                adder.add(manager, std::move(emp));
                break;
            }
            case 2: {
                auto emp = std::make_unique<Intern>("", "", "", "", "", "", "");
                cout << "Nhập thông tin nhân viên thử việc:\n";
                cout << "Họ tên: ";
                std::string name;
                std::getline(cin, name);
                emp->setName(name);
                cout << "Mã nhân viên: ";
                std::string id;
                std::getline(cin, id);
                emp->setId(id);
                cout << "Địa chỉ: ";
                std::string address;
                std::getline(cin, address);
                emp->setAddress(address);
                cout << "Số điện thoại: ";
                std::string phone;
                std::getline(cin, phone);
                emp->setPhone(phone);
                cout << "Email: ";
                std::string email;
                std::getline(cin, email);
                emp->setEmail(email);
                cout << "Thông tin bổ sung: ";
                std::string additionalInfo;
                std::getline(cin, additionalInfo);
                emp->setAdditionalInfo(additionalInfo);
                cout << "Ngày hết hạn hợp đồng (dd mm yyyy): ";
                int day, month, year;
                cin >> day >> month >> year;
                cin.ignore(); // Bỏ qua ký tự newline sau khi nhập số
                emp->setContractExpiry(day, month, year);
                EmployeeAdder adder;
                adder.add(manager, std::move(emp));
                break;
            }
            case 3: {
                auto emp = std::make_unique<Manager>("", "", "", "", "", "", "");
                cout << "Nhập thông tin nhân viên quản lý:\n";
                cout << "Họ tên: ";
                std::string name;
                std::getline(cin, name);
                emp->setName(name);
                cout << "Mã nhân viên: ";
                std::string id;
                std::getline(cin, id);
                emp->setId(id);
                cout << "Địa chỉ: ";
                std::string address;
                std::getline(cin, address);
                emp->setAddress(address);
                cout << "Số điện thoại: ";
                std::string phone;
                std::getline(cin, phone);
                emp->setPhone(phone);
                cout << "Email: ";
                std::string email;
                std::getline(cin, email);
                emp->setEmail(email);
                cout << "Thông tin bổ sung: ";
                std::string additionalInfo;
                std::getline(cin, additionalInfo);
                emp->setAdditionalInfo(additionalInfo);
                cout << "Ngày hết hạn hợp đồng (dd mm yyyy): ";
                int day, month, year;
                cin >> day >> month >> year;
                cin.ignore(); // Bỏ qua ký tự newline sau khi nhập số
                emp->setContractExpiry(day, month, year);
                EmployeeAdder adder;
                adder.add(manager, std::move(emp));
                break;
            }
            default:
                cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
                continue;
            }
            break;
        }
        case 2: {
            cout << "Nhập mã nhân viên cần xoá: ";
            std::string employeeId;
            std::getline(cin, employeeId);
            EmployeeRemover remover;
            if (remover.remove(manager, employeeId)) {
                cout << "Xoá nhân viên thành công.\n";
            }
            else {
                cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
            }
            break;
        }
        case 3: {
            cout << "Nhập mã nhân viên cần tìm: ";
            std::string employeeId;
            std::getline(cin, employeeId);
            EmployeeFinder finder;
            auto employee = finder.findById(manager, employeeId);
            if (employee == nullptr) {
                cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
            }
            else {
                EmployeePrinter::printEmployeeDetails(manager, employeeId);
            }
            break;
        }
        case 4: {
            cout << "Nhập mã nhân viên cần chỉnh sửa: ";
            std::string employeeId;
            std::getline(cin, employeeId);
            EmployeeFinder finder;
            auto employee = finder.findById(manager, employeeId);
            if (employee == nullptr) {
                cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
            }
            else {
                cout << "Sửa thông tin nhân viên:\n";
                cout << "1. Sửa tên\n";
                cout << "2. Sửa địa chỉ\n";
                cout << "3. Sửa số điện thoại\n";
                cout << "4. Sửa email\n";
                cout << "5. Sửa thông tin bổ sung\n";
                int editChoice;
                cin >> editChoice;
                cin.ignore(); // Bỏ qua ký tự newline sau khi nhập số
                EmployeeEditor editor(manager);

                switch (editChoice) {
                case 1: {
                    cout << "Nhập tên mới: ";
                    std::string newName; // Declare and initialize inside the block
                    std::getline(cin, newName);
                    if (editor.editNameById(employeeId, newName)) {
                        cout << "Cập nhật tên thành công.\n";
                    }
                    else {
                        cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
                    }
                    break;
                }
                case 2: {
                    cout << "Nhập địa chỉ mới: ";
                    std::string newAddress; // Declare and initialize inside the block
                    std::getline(cin, newAddress);
                    if (editor.editPhoneById(employeeId, newAddress)) {
                        cout << "Cập nhật địa chỉ thành công.\n";
                    }
                    else {
                        cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
                    }
                    break;
                }
                case 3: {
                    cout << "Nhập số điện thoại mới: ";
                    std::string newPhone; // Declare and initialize inside the block
                    std::getline(cin, newPhone);
                    if (editor.editPhoneById(employeeId, newPhone)) {
                        cout << "Cập nhật số điện thoại thành công.\n";
                    }
                    else {
                        cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
                    }
                    break;
                }
                case 4: {
                    cout << "Nhập email mới: ";
                    std::string newEmail; // Declare and initialize inside the block
                    std::getline(cin, newEmail);
                    if (editor.editEmailById(employeeId, newEmail)) {
                        cout << "Cập nhật email thành công.\n";
                    }
                    else {
                        cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
                    }
                    break;
                }
                case 5: {
                    cout << "Nhập thông tin bổ sung mới: ";
                    std::string newInfo; // Declare and initialize inside the block
                    std::getline(cin, newInfo);
                    if (editor.editAllById(employeeId, newInfo, employee->getPhone(), employee->getEmail())) {
                        cout << "Cập nhật thông tin bổ sung thành công.\n";
                    }
                    else {
                        cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
                    }
                    break;
                }
                default:
                    cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
                    break;
                }
            }
            break;
        }
        case 5: {
            EmployeePrinter::printAllEmployees(manager);
            cout << "Nhập mã nhân viên để xem chi tiết (hoặc 0 để quay lại): ";
            std::string employeeId;
            std::getline(cin, employeeId);
            if (employeeId == "0") {
                break; // Quay lại menu chính
            }
            EmployeePrinter::printEmployeeDetails(manager, employeeId);
            break;
        }
        case 6: {
            cout << "Nhập mã nhân viên để xem lương: ";
            std::string employeeId;
            std::getline(cin, employeeId);
            EmployeeFinder finder;
            auto employee = finder.findById(manager, employeeId);
            if (employee == nullptr) {
                cout << "Không tìm thấy nhân viên với mã: " << employeeId << "\n";
            }
            else {
                std::vector<Attendance> attendanceRecords = loadAttendanceFromFile("attendance.csv");
                cout << "Nhập mức lương theo giờ (VND): ";
                double hourlyRate;
                cin >> hourlyRate;
                cin.ignore(); // Bỏ qua ký tự newline sau khi nhập số
                PayrollCalculator calculator(hourlyRate);
                std::vector<PaySlip> paySlips = calculator.calculatePayroll(attendanceRecords);
                PayrollPrinter pr("vi-VN");
                pr.printPaySlip(paySlips, employeeId);

            }
            break;
        }
        default:
            cout << "Lựa chọn không hợp lệ. Vui lòng chọn lại.\n";
            break;
        }


        return 0;
    }
}
