#ifndef CULTURE_INFO_H
#define CULTURE_INFO_H

#include <string>
#include <map>

/**
 * @struct CultureInfo
 * @brief Cấu trúc lưu trữ các thông tin định dạng theo văn hóa.
 *
 * Chứa các quy tắc về cách hiển thị số, tiền tệ, ngày tháng, v.v.
 * cho một quốc gia hoặc khu vực cụ thể.
 */
struct CultureInfo {
    char thousandSeparator; // Dấu phân cách hàng nghìn (ví dụ: '.' hoặc ',')
    // Có thể mở rộng thêm:
    // char decimalSeparator;
    // std::string currencySymbol;

    /**
     * @brief Lấy thông tin văn hóa cho Việt Nam.
     * @return CultureInfo cho 'vi-VN'.
     */
    static CultureInfo vi() {
        return CultureInfo{ '.' }; // Ví dụ: 100.000
    }

    /**
     * @brief Lấy thông tin văn hóa cho Mỹ (English - US).
     * @return CultureInfo cho 'en-US'.
     */
    static CultureInfo en() {
        return CultureInfo{ ',' }; // Ví dụ: 100,000
    }

    /**
     * @brief Lấy CultureInfo dựa trên chuỗi định danh (locale string).
     * @param locale Chuỗi định danh, ví dụ "vi-VN" hoặc "en-US".
     * @return Đối tượng CultureInfo tương ứng.
     */
    static CultureInfo get(const std::string& locale) {
        static const std::map<std::string, CultureInfo> dicts = {
            {"vi-VN", CultureInfo::vi()},
            {"en-US", CultureInfo::en()}
        };

        auto it = dicts.find(locale);
        if (it != dicts.end()) {
            return it->second;
        }

        return CultureInfo::en(); // Mặc định là 'en-US' nếu không tìm thấy
    }
};

#endif // CULTURE_INFO_H