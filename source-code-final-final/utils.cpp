#include "utils.h"
#include <cstdio> // Cho printf nếu bạn thích dùng nó cho một số ký tự ASCII
#include <iomanip> // Cho std::setw, std::setfill
#include <sstream> // Cho std::stringstream, std::ostringstream

void gotoXY(int X, int Y) {
    COORD coordinates;
    coordinates.X = X;
    coordinates.Y = Y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinates);
}

void cDelay(int milliseconds) {
    Sleep(milliseconds); // Hàm Sleep của Windows
}

void clearScreen() {
    system("cls");
}

void drawBorder(int x1, int y1, int x2, int y2, bool withDelay) {
    // Góc trên-trái, trên-phải, dưới-trái, dưới-phải
    // Đường ngang, đường dọc
    char topLeft = 201, topRight = 187, botLeft = 200, botRight = 188;
    char hLine = 205, vLine = 186;

    gotoXY(x1, y1); std::cout << topLeft;
    gotoXY(x2, y1); std::cout << topRight;
    gotoXY(x1, y2); std::cout << botLeft;
    gotoXY(x2, y2); std::cout << botRight;

    for (int i = x1 + 1; i < x2; ++i) {
        if (withDelay) cDelay(5);
        gotoXY(i, y1); std::cout << hLine;
        gotoXY(i, y2); std::cout << hLine;
    }
    for (int i = y1 + 1; i < y2; ++i) {
        if (withDelay) cDelay(5);
        gotoXY(x1, i); std::cout << vLine;
        gotoXY(x2, i); std::cout << vLine;
    }
}

void getConsoleWindowSize(int& outWidth, int& outHeight) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
        // Kích thước của vùng cửa sổ có thể thấy được
        outWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        outHeight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    } else {
        // Giá trị mặc định nếu không lấy được thông tin
        outWidth = 80; 
        outHeight = 25;
    }
}

void printCenteredText(const std::string& text, int yPos, int windowWidth) {
    if (text.empty()) return;
    int textLength = text.length();
    int xPos = (windowWidth - textLength) / 2;
    if (xPos < 0) { // Nếu text dài hơn chiều rộng cửa sổ
        xPos = 0; 
    }
    gotoXY(xPos, yPos);
    std::cout << text;
}

bool parseWorkDate(const std::string& dateStr, int& year, int& month, int& day) {
    year = 0; month = 0; day = 0; // Khởi tạo giá trị mặc định
    if (dateStr.empty()) {
        return false;
    }

    std::stringstream ss(dateStr);
    char delimiter1 = 0, delimiter2 = 0;

    // Thử đọc tháng, ngày, năm với các delimiter có thể là '/' hoặc '-'
    ss >> month;
    if (ss.fail() || month < 1 || month > 12) return false;
    
    if (ss.peek() == '/' || ss.peek() == '-') {
        ss >> delimiter1;
    } else {
        return false; // Không có delimiter sau tháng
    }

    ss >> day;
    if (ss.fail() || day < 1 || day > 31) return false;

    if (ss.peek() == '/' || ss.peek() == '-') {
        ss >> delimiter2;
    } else {
        return false; // Không có delimiter sau ngày
    }
    
    // Delimiter phải giống nhau
    if (delimiter1 != delimiter2) return false; 

    ss >> year;
    if (ss.fail() || year < 1900 || year > 2100) { // Giới hạn năm hợp lý
         year = 0; month = 0; day = 0; // Reset nếu năm không hợp lệ
        return false;
    }
    
    // Kiểm tra cơ bản tính hợp lệ của ngày trong tháng (chưa tính năm nhuận phức tạp)
    if (month == 2 && day > 29) return false;
    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

    return true; 
}

std::string formatDateToYYYYMMDD(int year, int month, int day) {
    if (year == 0 || month == 0 || day == 0) { // Nếu ngày tháng không hợp lệ (ví dụ từ parse lỗi)
        return ""; // Hoặc "N/A" tùy bạn muốn
    }
    std::ostringstream oss;
    oss << year << "-"
        << std::setw(2) << std::setfill('0') << month << "-"
        << std::setw(2) << std::setfill('0') << day;
    return oss.str();
}