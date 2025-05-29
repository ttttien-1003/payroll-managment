#ifndef WELFARE_MANAGER_H
#define WELFARE_MANAGER_H

#include "IWelfare.h" // Phải include lớp cơ sở IWelfare
#include <vector>
#include <memory> // Để dùng std::unique_ptr

// Khai báo chuyển tiếp để tránh include vòng lặp
class IEmployee;

/**
 * @class WelfareManager
 * @brief Lớp quản lý danh sách các phúc lợi và tính toán tác động của chúng.
 *
 * Lớp này giữ một danh sách tất cả các loại phúc lợi có trong hệ thống
 * (như bảo hiểm, thưởng, phụ cấp) và cung cấp phương thức để tính tổng
 * tác động của chúng lên lương của một nhân viên cụ thể.
 */
class WelfareManager {
private:
    // Sử dụng con trỏ thông minh để tự động quản lý bộ nhớ của các đối tượng phúc lợi
    std::vector<std::unique_ptr<IWelfare>> _welfareList;

public:
    /**
     * @brief Constructor mặc định.
     */
    WelfareManager() = default;

    /**
     * @brief Thêm một phúc lợi mới vào hệ thống.
     * @param welfare Con trỏ unique_ptr đến đối tượng phúc lợi.
     */
    void addWelfare(std::unique_ptr<IWelfare> welfare);

    /**
     * @brief Tính toán tổng các khoản thưởng, phụ cấp, và khấu trừ cho một nhân viên.
     *
     * Phương thức này lặp qua tất cả các phúc lợi, kiểm tra xem nhân viên có đủ
     * điều kiện không, sau đó tính toán và phân loại tác động vào các biến tham chiếu.
     *
     * @param employee Nhân viên cần tính phúc lợi.
     * @param outBonuses Tham chiếu đến biến để lưu tổng tiền thưởng.
     * @param outAllowances Tham chiếu đến biến để lưu tổng tiền phụ cấp.
     * @param outDeductions Tham chiếu đến biến để lưu tổng tiền khấu trừ.
     */
    void calculateAllWelfareForEmployee(const IEmployee& employee, const AttendanceManager& attendanceManager, double& outBonuses, double& outAllowances, double& outDeductions) const;
};

#endif // WELFARE_MANAGER_H