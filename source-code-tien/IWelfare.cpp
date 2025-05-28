#include "IWelfare.h"

void WelfareManager::addWelfare(std::unique_ptr<IWelfare> welfare)
{
    if (welfare)
    {
        welfareList.push_back(std::move(welfare));
    }
    else
    {
        // Xử lý lỗi, ví dụ: ghi log hoặc ném ngoại lệ
        throw std::invalid_argument("Không thể thêm đối tượng phúc lợi null.");
    }
}

const std::vector<std::unique_ptr<IWelfare>>& WelfareManager::getAllWelfares() const
{
    return welfareList;
}

double WelfareManager::calculateTotalWelfareImpactForEmployee(const IEmployee& employee) const
{
    double totalImpact = 0.0;
    // Lặp qua từng phúc lợi trong danh sách
    for (const auto& welfare : welfareList)
    {
        // Kiểm tra xem con trỏ phúc lợi có hợp lệ không
        if (welfare)
        {
            // Kiểm tra xem nhân viên có đủ điều kiện nhận phúc lợi hiện tại không
            if (welfare->isEligible(employee))
            {
                // Nếu đủ điều kiện, tính toán tác động của phúc lợi này và cộng vào tổng
                totalImpact += welfare->calculateImpact(employee);
            }
        }
    }
    return totalImpact;
}