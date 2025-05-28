/**
 * @file IWelfare.h
 * @brief Định nghĩa các giao diện và cấu trúc dữ liệu liên quan đến phúc lợi nhân viên.
 *
 * File này chứa định nghĩa cho các loại phúc lợi khác nhau mà nhân viên có thể được hưởng.
 * Các phúc lợi này có thể có tác động trực tiếp hoặc gián tiếp đến việc tính toán lương.
 * Thiết kế hướng đến tính mở rộng (Open/Closed Principle) và dễ dàng tích hợp với
 * hệ thống tính lương (Dependency Inversion Principle).
 */

#ifndef _IWELFARE_H_
#define _IWELFARE_H_

#include <string>
#include <vector>
#include <memory> // Dùng cho con trỏ thông minh (smart pointers)
#include <stdexcept> // Dùng cho xử lý ngoại lệ

 // Khai báo chuyển tiếp (Forward declaration) để tránh include vòng lặp
 // Cần thiết vì IWelfare có thể cần thông tin từ IEmployee để tính toán phúc lợi
class IEmployee;

/**
 * @brief Liệt kê các loại phúc lợi cơ bản.
 *
 * Enum này giúp phân loại các loại phúc lợi một cách rõ ràng. Có thể mở rộng
 * thêm các loại phúc lợi mới khi cần thiết.
 */
enum class WelfareType
{
    SocialInsurance,    ///< Bảo hiểm xã hội.
    HealthInsurance,    ///< Bảo hiểm y tế.
    Transportation,     ///< Phụ cấp đi lại.
    Bonus,              ///< Thưởng (lương tháng 13, doanh thu,...)
    Allowance          ///< Phụ cấp khác (thai sản, bệnh tật,...)
};

/**
 * @brief Cấu trúc chứa thông tin chi tiết về một phúc lợi.
 *
 * Cấu trúc này lưu trữ các thông tin mô tả chung về một loại phúc lợi,
 * độc lập với việc tính toán tác động đến lương của nó.
 */
struct WelfareDetails
{
    WelfareType type;       ///< Loại phúc lợi.
    std::string name;       ///< Tên của phúc lợi.
    std::string description;///< Mô tả chi tiết về phúc lợi.
};

/**
 * @brief Lớp trừu tượng cơ sở cho tất cả các loại phúc lợi. (Giao diện - Interface)
 *
 * Lớp này định nghĩa hợp đồng (contract) mà mọi phúc lợi cụ thể phải tuân theo.
 * Nó tuân thủ nguyên tắc Liskov Substitution Principle (LSP) và Interface Segregation Principle (ISP - ở mức cơ bản).
 * Đồng thời hỗ trợ Dependency Inversion Principle (DIP) bằng cách cho phép hệ thống
 * tính lương phụ thuộc vào giao diện này thay vì các cài đặt cụ thể.
 */
class IWelfare
{
public:
    /**
     * @brief Destructor ảo mặc định.
     *
     * Đảm bảo giải phóng bộ nhớ đúng khi làm việc với các đối tượng phúc lợi cụ thể
     * thông qua con trỏ lớp cơ sở IWelfare.
     */
    virtual ~IWelfare() = default;

    /**
     * @brief Lấy thông tin chi tiết về phúc lợi.
     *
     * @return Tham chiếu hằng đến đối tượng WelfareDetails chứa thông tin mô tả phúc lợi.
     */
    virtual const WelfareDetails& getDetails() const = 0;

    /**
     * @brief Tính toán tác động của phúc lợi này đến lương của nhân viên.
     *
     * Phương thức này là trọng tâm của việc tích hợp phúc lợi vào hệ thống tính lương.
     * Nó nhận đối tượng nhân viên làm tham số để có thể tính toán dựa trên thông tin
     * cụ thể của từng nhân viên (ví dụ: mức lương cơ bản, loại hợp đồng, v.v.).
     *
     * Đây là một điểm áp dụng nguyên tắc Single Responsibility (phúc lợi biết cách tính toán tác động của nó)
     * và Open/Closed Principle (có thể thêm loại phúc lợi mới với logic tính toán riêng
     * mà không sửa đổi lớp tính lương chính).
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee mà phúc lợi này áp dụng.
     * @return Giá trị số biểu thị tác động của phúc lợi lên lương.
     * Giá trị dương là khoản cộng thêm, giá trị âm là khoản trừ đi.
     */
    virtual double calculateImpact(const IEmployee& employee) const = 0;

    /**
     * @brief Kiểm tra xem nhân viên có đủ điều kiện nhận phúc lợi này hay không.
     *
     * Phương thức này cho phép định nghĩa các quy tắc đủ điều kiện phức tạp
     * dựa trên thông tin của nhân viên.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee cần kiểm tra.
     * @return true nếu nhân viên đủ điều kiện, false ngược lại.
     */
    virtual bool isEligible(const IEmployee& employee) const = 0;
};

/**
 * @brief Lớp quản lý danh sách các phúc lợi.
 *
 * Lớp này có thể đóng vai trò là một Repository hoặc Service để lưu trữ và
 * truy xuất các đối tượng IWelfare.
 * Đây là nơi Dependency Injection có thể được áp dụng, nơi một instance của
 * lớp này (hoặc một giao diện tương tự) được inject vào các lớp cần truy cập
 * danh sách phúc lợi.
 */
class WelfareManager
{
private:
    // Sử dụng smart pointers để quản lý bộ nhớ của các đối tượng phúc lợi
    std::vector<std::unique_ptr<IWelfare>> welfareList;

public:
    /**
     * @brief Constructor mặc định.
     */
    WelfareManager() = default;

    /**
     * @brief Thêm một phúc lợi mới vào danh sách.
     *
     * Sử dụng unique_ptr để đảm bảo quyền sở hữu duy nhất và quản lý bộ nhớ tự động.
     *
     * @param welfare Con trỏ unique_ptr đến đối tượng IWelfare cần thêm.
     */
    void addWelfare(std::unique_ptr<IWelfare> welfare);

    /**
     * @brief Lấy danh sách tất cả các phúc lợi hiện có.
     *
     * Trả về tham chiếu hằng đến vector các unique_ptr.
     *
     * @return Tham chiếu hằng đến vector các unique_ptr IWelfare.
     */
    const std::vector<std::unique_ptr<IWelfare>>& getAllWelfares() const;

    /**
     * @brief Tính tổng tác động của tất cả các phúc lợi đủ điều kiện đối với một nhân viên.
     *
     * Phương thức này lặp qua danh sách tất cả các phúc lợi, kiểm tra xem nhân viên
     * có đủ điều kiện nhận phúc lợi đó không bằng cách gọi phương thức isEligible().
     * Nếu đủ điều kiện, nó sẽ gọi phương thức calculateImpact() của phúc lợi đó
     * để lấy giá trị tác động và cộng dồn vào tổng.
     *
     * @param employee Tham chiếu hằng đến đối tượng IEmployee cần tính toán.
     * @return Tổng giá trị tác động của các phúc lợi đủ điều kiện lên lương của nhân viên.
     * Giá trị dương là tổng tiền cộng thêm, giá trị âm là tổng tiền trừ đi.
     */
    double calculateTotalWelfareImpactForEmployee(const IEmployee& employee) const;
};

#endif // _IWELFARE_H_
