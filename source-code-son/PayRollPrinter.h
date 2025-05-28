#ifndef PAYROLL_PRINTER_H
#define PAYROLL_PRINTER_H

#include "PaySlip.h"
#include "NumberFormatter.h"
#include "CultureInfo.h"
#include <vector>
#include <string>

/**
 * @brief Lớp hỗ trợ in danh sách phiếu lương ra file định dạng bảng.
 */
class PayrollPrinter {
private:
    std::string locale;
    NumberFormatter formatter;

public:
    /**
     * @brief Khởi tạo với mã ngôn ngữ định dạng (ví dụ: "vi-VN").
     * @param locale Mã văn hóa (ngôn ngữ, quốc gia).
     */
    PayrollPrinter(const std::string& locale = "vi-VN");

    /**
    * @brief In lương của 1 nhân viên 
	* @param slip Phiếu lương của nhân viên.
    */
	void printPaySlip(const std::vector<PaySlip>& slips, std::string id) const;

    /**
     * @brief In danh sách phiếu lương ra file với định dạng bảng.
     *
     * @param slips Danh sách phiếu lương.
     * @param advances Bản đồ lương ứng trước theo mã nhân viên.
     * @param filename Tên file cần ghi (mặc định là "phieuluong.txt").
     */
    void printToFile(const std::vector<PaySlip>& slips,
        const std::unordered_map<std::string, double>& advances,
        const std::string& filename = "phieuluong.txt") const;
};

#endif // PAYROLL_PRINTER_H
