#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include "Attendance.h"
#include "SalaryPayment.h"

std::vector<Attendance> loadAttendanceFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::vector<Attendance> attendanceRecords;

    if (!inFile) {
        std::cerr << "Không thể mở file để đọc: " << filename << "\n";
        return attendanceRecords;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        attendanceRecords.push_back(Attendance::fromCSV(line));
    }

    inFile.close();
    return attendanceRecords;
}

std::vector<SalaryPayment> loadSalaryPaymentsFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    std::vector<SalaryPayment> payments;

    if (!inFile) {
        std::cerr << "Không thể mở file để đọc: " << filename << "\n";
        return payments;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        payments.push_back(SalaryPayment::fromCSV(line));
    }

    inFile.close();
    return payments;
}

void saveSalaryPaymentsToFile(const std::string& filename, const std::vector<SalaryPayment>& payments) {
    std::ofstream outFile(filename, std::ios::app); // Mở file ở chế độ ghi thêm (append)

    if (!outFile) {
        std::cerr << "Không thể mở file để ghi: " << filename << "\n";
        return;
    }

    for (const auto& payment : payments) {
        outFile << payment.toCSV() << "\n";
    }

    outFile.close();
    std::cout << "Dữ liệu thanh toán lương đã được lưu vào file: " << filename << "\n";
}

void saveAttendanceToFile(const std::string& filename, const std::vector<Attendance>& attendanceRecords) {
    std::ofstream outFile(filename, std::ios::app); // Mở file ở chế độ ghi thêm (append)

    if (!outFile) {
        std::cerr << "Không thể mở file để ghi: " << filename << "\n";
        return;
    }

    for (const auto& record : attendanceRecords) {
        outFile << record.toCSV() << "\n";
    }

    outFile.close();
    std::cout << "Dữ liệu chấm công đã được lưu vào file: " << filename << "\n";
}
