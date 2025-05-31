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
void WelfareManager::calculateAllWelfareForEmployee(const IEmployee& employee, const AttendanceManager& attendanceManager, int targetMonth, int targetYear, double& outBonuses, double& outAllowances, double& outDeductions) const {
    outBonuses = 0.0; //
    outAllowances = 0.0; //
    outDeductions = 0.0; //

    for (const auto& welfare : _welfareList) { //
        // Truyền targetMonth, targetYear vào isEligible
        if (welfare && welfare->isEligible(employee, attendanceManager, targetMonth, targetYear)) { //
            double impact = welfare->calculateImpact(employee); //
            if (impact > 0) { //
                if (welfare->getDetails().type == WelfareType::Bonus) { //
                    outBonuses += impact; //
                } else {
                    outAllowances += impact; //
                }
            } else if (impact < 0) { //
                outDeductions += std::abs(impact); //
            }
        }
    }
}