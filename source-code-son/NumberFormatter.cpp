#include "NumberFormatter.h"
#include <sstream>
#include <iomanip>

std::string NumberFormatter::format(int number, const CultureInfo& culture) const {
    return format(static_cast<double>(number), culture);
}

std::string NumberFormatter::format(double number, const CultureInfo& culture) const {
    std::ostringstream oss;
    oss.imbue(std::locale("C"));
    oss << std::fixed << std::setprecision(0) << number;
    std::string numStr = oss.str();

    int n = numStr.length();
    int dotPos = numStr.find('.') != std::string::npos ? numStr.find('.') : n;
    std::string result;
    int count = 0;

    for (int i = dotPos - 1; i >= 0; --i) {
        result.insert(0, 1, numStr[i]);
        count++;
        if (count % 3 == 0 && i != 0) {
            result.insert(0, 1, culture.thousandSeparator);
        }
    }

    if (dotPos != n) {
        result += numStr.substr(dotPos);
    }

    return result;
}