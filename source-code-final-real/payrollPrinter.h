#ifndef PAYROLL_PRINTER_H
#define PAYROLL_PRINTER_H

#include "GlobalDefinitions.h"
#include "NumberFormatter.h"
#include "IEmployee.h"
#include <vector>
#include <string>
#include <memory>

/**
 * @class PayrollPrinter
 * @brief Lớp chuyên dụng để in thông tin nhân viên và phiếu lương.
 * Sử dụng NumberFormatter để định dạng số liệu tài chính.
 */
class PayrollPrinter {
private:
    NumberFormatter _formatter; // Đối tượng định dạng số
    CultureInfo _culture;       // Thông tin văn hóa (ví dụ: vi-VN)

public:
    /**
     * @brief Constructor.
     * @param locale Chuỗi định danh văn hóa, ví dụ "vi-VN" hoặc "en-US".
     */
    PayrollPrinter(const std::string& locale = "vi-VN");

    /**
     * @brief In thông tin chi tiết của một nhân viên.
     * @param emp Con trỏ đến đối tượng nhân viên.
     */
    void printEmployeeDetails(const std::shared_ptr<IEmployee>& emp) const;

    /**
     * @brief In phiếu lương chi tiết của một nhân viên ra console.
     * @param emp Con trỏ đến đối tượng nhân viên.
     * @param details Chi tiết lương đã được tính toán.
     */
    void printPaySlip(const std::shared_ptr<IEmployee>& emp, const SalaryDetails& details) const;

    /**
     * @brief In phiếu lương của tất cả nhân viên ra file.
     * @param payrollData Vector chứa cặp (nhân viên, chi tiết lương).
     * @param filename Tên file để xuất dữ liệu.
     */
    void printToFile(const std::vector<std::pair<std::shared_ptr<IEmployee>, SalaryDetails>>& payrollData, const std::string& filename) const;
};

#endif // PAYROLL_PRINTER_H