// CultureInfo.h
#ifndef CULTURE_INFO_H
#define CULTURE_INFO_H

#include <string>

/**
 * @brief Cấu hình định dạng theo ngôn ngữ/văn hóa.
 */
struct CultureInfo {
    char thousandSeparator;

    static CultureInfo vi() {
        return CultureInfo{ '.' }; // Dùng dấu chấm làm phân cách hàng nghìn
    }

    static CultureInfo get(const std::string& locale) {
        if (locale == "vi" || locale == "vi-VN") {
            return vi();
        }
        return CultureInfo{ ',' }; // Mặc định (US)
    }
};

#endif