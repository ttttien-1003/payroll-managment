#include "SalaryPayment.h"
#include <sstream>

// Constructor
SalaryPayment::SalaryPayment(const std::string& employeeId, const std::string& paymentDate, double amount, double advance, const std::string& notes)
    : employeeId(employeeId), paymentDate(paymentDate), amount(amount), advance(advance), notes(notes) {
}

// Getters
const std::string& SalaryPayment::getEmployeeId() const { return employeeId; }
const std::string& SalaryPayment::getPaymentDate() const { return paymentDate; }
double SalaryPayment::getAmount() const { return amount; }
double SalaryPayment::getAdvance() const { return advance; }
const std::string& SalaryPayment::getNotes() const { return notes; }

// Setters
void SalaryPayment::setAmount(double amount) { this->amount = amount; }
void SalaryPayment::setAdvance(double advance) { this->advance = advance; }
void SalaryPayment::setNotes(const std::string& notes) { this->notes = notes; }

// Chuyển đổi đối tượng thành chuỗi CSV
std::string SalaryPayment::toCSV() const {
    std::ostringstream oss;
    oss << employeeId << "," << paymentDate << "," << amount << "," << advance << "," << notes;
    return oss.str();
}

// Tạo đối tượng từ chuỗi CSV
SalaryPayment SalaryPayment::fromCSV(const std::string& csvLine) {
    std::istringstream ss(csvLine);
    std::string employeeId, paymentDate, amountStr, advanceStr, notes;

    std::getline(ss, employeeId, ',');
    std::getline(ss, paymentDate, ',');
    std::getline(ss, amountStr, ',');
    std::getline(ss, advanceStr, ',');
    std::getline(ss, notes, ',');

    return SalaryPayment(employeeId, paymentDate, std::stod(amountStr), std::stod(advanceStr), notes);
}