#include "NumberFormatter.h"
#include <sstream>
#include <iomanip>
#include <cmath> // Để dùng std::abs
#include <algorithm> // Để dùng std::reverse

/**
 * @brief Định dạng một số kiểu int.
 */
std::string NumberFormatter::format(int number, const CultureInfo& culture) const {
    return format(static_cast<double>(number), culture);
}

/**
 * @brief Định dạng một số kiểu double.
 */
std::string NumberFormatter::format(double number, const CultureInfo& culture) const {
    // Chuyển số thành chuỗi với độ chính xác 0 chữ số thập phân
    std::stringstream ss;
    ss << std::fixed << std::setprecision(0) << std::abs(number);
    std::string numStr = ss.str();

    // Chèn dấu phân cách hàng nghìn
    int insertPosition = numStr.length() - 3;
    while (insertPosition > 0) {
        numStr.insert(insertPosition, 1, culture.thousandSeparator);
        insertPosition -= 3;
    }

    // Thêm dấu âm nếu số là số âm
    if (number < 0) {
        numStr.insert(0, "-");
    }

    return numStr;
}