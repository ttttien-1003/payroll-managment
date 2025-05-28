#ifndef NUMBERFORMATTER_H
#define NUMBERFORMATTER_H

#include "CultureInfo.h"
#include <string>

/**
 * @class NumberFormatter
 * @brief Lớp chịu trách nhiệm định dạng số thành chuỗi theo CultureInfo.
 */
class NumberFormatter {
public:
    /**
     * @brief Định dạng một số kiểu double thành chuỗi.
     * @param number Số cần định dạng.
     * @param culture Thông tin văn hóa để sử dụng cho việc định dạng.
     * @return Chuỗi đã được định dạng.
     */
    std::string format(double number, const CultureInfo& culture) const;

    /**
     * @brief Định dạng một số kiểu integer thành chuỗi (gọi lại hàm format double).
     * @param number Số cần định dạng.
     * @param culture Thông tin văn hóa để sử dụng.
     * @return Chuỗi đã được định dạng.
     */
    std::string format(int number, const CultureInfo& culture) const;
};

#endif // NUMBER_FORMATTER_H