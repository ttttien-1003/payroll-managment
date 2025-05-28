/**
 * @file ConcreteWelfareExample.h
 * @brief Ví dụ về một lớp phúc lợi cụ thể kế thừa từ IWelfare.
 *
 * Lớp này minh họa cách định nghĩa các phương thức thuần ảo
 * từ lớp cơ sở IWelfare cho một loại phúc lợi cụ thể.
 */

#ifndef _CONCRETE_WELFARE_EXAMPLE_H_
#define _CONCRETE_WELFARE_EXAMPLE_H_

#include "IWelfare.h" // Bao gồm định nghĩa của IWelfare
#include "IEmployee.h" // Bao gồm định nghĩa của IEmployee (cần thiết cho calculateImpact và isEligible)
#include <iostream> // Chỉ dùng cho mục đích minh họa in ra console

 /**
  * @brief Lớp ví dụ về một phúc lợi cụ thể
  *
  * Lớp này kế thừa từ IWelfare và cung cấp cài đặt cụ thể
  * cho các phương thức ảo.
  */
class ConcreteWelfareExample : public IWelfare
{
private:
    WelfareDetails details; // Thông tin chi tiết của phúc lợi này
    double allowanceAmount; // Số tiền phụ cấp cụ thể

public:
    /**
     * @brief Constructor cho ConcreteWelfareExample.
     *
     * @param amount Số tiền phụ cấp.
     */
    ConcreteWelfareExample(double amount) : allowanceAmount(amount)
    {
        // Khởi tạo thông tin chi tiết cho phúc lợi này
        details.type = WelfareType::Transportation;
        details.name = "Phu cap di lai hang thang";
        details.description = "Phu cap co dinh hang thang cho viec di lai.";
    }

    /**
     * @brief Định nghĩa phương thức getDetails() từ IWelfare.
     *
     * Trả về thông tin chi tiết cụ thể của phúc lợi Phụ cấp đi lại.
     *
     * @return Tham chiếu hằng đến đối tượng WelfareDetails.
     */
    const WelfareDetails& getDetails() const override
    {
        return details;
    }

    /**
     * @brief Định nghĩa phương thức calculateImpact() từ IWelfare.
     *
     * Tính toán tác động của phụ cấp đi lại đến lương.
     * Trong ví dụ này, tác động là số tiền phụ cấp cố định.
     * Logic phức tạp hơn có thể dựa vào thông tin nhân viên (employee).
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return Giá trị tác động lên lương (số tiền phụ cấp).
     */
    double calculateImpact(const IEmployee& employee) const override
    {
        // Logic tính toán tác động. Ví dụ đơn giản là trả về số tiền cố định.
        // Có thể phức tạp hơn, ví dụ: dựa trên chức vụ của employee.
        std::cout << "Calculating transportation allowance for " << employee.getName() << std::endl;
        return allowanceAmount;
    }

    /**
     * @brief Định nghĩa phương thức isEligible() từ IWelfare.
     *
     * Kiểm tra xem nhân viên có đủ điều kiện nhận phụ cấp đi lại hay không.
     * Trong ví dụ này, giả sử tất cả nhân viên đều đủ điều kiện.
     * Logic phức tạp hơn có thể dựa vào thông tin nhân viên (employee).
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee.
     * @return true nếu nhân viên đủ điều kiện, false ngược lại.
     */
    bool isEligible(const IEmployee& employee) const override
    {
        // Logic kiểm tra đủ điều kiện. Ví dụ đơn giản là luôn trả về true.
        // Có thể phức tạp hơn, ví dụ: dựa trên loại hợp đồng của employee.
        std::cout << "Checking eligibility for transportation allowance for " << employee.getName() << std::endl;
        return true; // Giả sử tất cả nhân viên đều đủ điều kiện
    }

    // Destructor mặc định là đủ vì không có tài nguyên cần giải phóng đặc biệt
    ~ConcreteWelfareExample() override = default;
};

#endif // _CONCRETE_WELFARE_EXAMPLE_H_

// --- File .cpp tương ứng (ConcreteWelfareExample.cpp) ---
/*
#include "ConcreteWelfareExample.h"

// Không cần định nghĩa lại các phương thức ở đây vì chúng đã được định nghĩa inline
// trong file header cho ví dụ đơn giản này.
// Đối với các cài đặt phức tạp hơn, bạn nên định nghĩa chúng trong file .cpp.

// Ví dụ về cách định nghĩa calculateImpact trong file .cpp (nếu không inline):
// double ConcreteWelfareExample::calculateImpact(const IEmployee& employee) const
// {
//     // Logic tính toán ở đây
//     return allowanceAmount;
// }
*/
