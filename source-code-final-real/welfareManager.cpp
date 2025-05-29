#include "WelfareManager.h"
#include "IEmployee.h"
#include <stdexcept>
#include <cmath> // Để dùng std::abs

/**
 * @brief Thêm một phúc lợi mới vào danh sách quản lý.
 */
void WelfareManager::addWelfare(std::unique_ptr<IWelfare> welfare) {
    if (welfare) {
        _welfareList.push_back(std::move(welfare));
    }
    else {
        throw std::invalid_argument("Khong the them mot phuc loi null.");
    }
}

/**
 * @brief Tính toán và phân loại tất cả các phúc lợi cho một nhân viên.
 */
void WelfareManager::calculateAllWelfareForEmployee(const IEmployee& employee, const AttendanceManager& attendanceManager, double& outBonuses, double& outAllowances, double& outDeductions) const {
    // Reset các giá trị đầu ra
    outBonuses = 0.0;
    outAllowances = 0.0;
    outDeductions = 0.0;

    // Lặp qua từng phúc lợi trong danh sách
    for (const auto& welfare : _welfareList) {
        // Kiểm tra xem nhân viên có đủ điều kiện nhận phúc lợi này không
        if (welfare && welfare->isEligible(employee, attendanceManager))
        {
            // Nếu đủ điều kiện, tính toán tác động của nó
            double impact = welfare->calculateImpact(employee);

            // Phân loại tác động dựa trên WelfareType
            // Tác động dương là thưởng hoặc phụ cấp
            if (impact > 0) {
                // Giả định rằng loại phúc lợi Bonus là thưởng, còn lại là phụ cấp
                if (welfare->getDetails().type == WelfareType::Bonus) {
                    outBonuses += impact;
                }
                else {
                    outAllowances += impact;
                }
            }
            // Tác động âm là các khoản khấu trừ (như bảo hiểm)
            else if (impact < 0) {
                outDeductions += std::abs(impact); // Lưu khấu trừ dưới dạng số dương
            }
        }
    }
}