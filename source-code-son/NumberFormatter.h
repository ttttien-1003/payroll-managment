// NumberFormatter.h
#ifndef NUMBER_FORMATTER_H
#define NUMBER_FORMATTER_H

#include <string>
#include "CultureInfo.h"

class NumberFormatter {
public:
    /**
     * @brief Định dạng số nguyên có chấm phân tách theo hàng nghìn.
     * @param number Số cần định dạng.
     * @param culture Cấu hình văn hóa.
     * @return Chuỗi định dạng.
     */
    std::string format(int number, const CultureInfo& culture) const;

    /**
     * @brief Định dạng số thực có chấm phân tách theo hàng nghìn.
     * @param number Số cần định dạng.
     * @param culture Cấu hình văn hóa.
     * @return Chuỗi định dạng.
     */
    std::string format(double number, const CultureInfo& culture) const;
};

#endif