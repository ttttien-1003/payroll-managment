#ifndef UTILS_H
#define UTILS_H

#include <windows.h> // Cho SetConsoleCursorPosition, GetStdHandle, v.v.
#include <iostream>  // Cho std::cout (dù bạn sẽ dùng nó với gotoXY)
#include <string>
#include <vector>    // Nếu cần cho việc vẽ phức tạp hơn sau này
#include <iomanip>

// Ở đầu file App.cpp (hoặc AppConstants.h rồi include vào App.cpp)
const int DEFAULT_WINDOW_WIDTH_CHARS = 100; // Chiều rộng cửa sổ console mong muốn (số ký tự)
const int DEFAULT_WINDOW_HEIGHT_CHARS = 30; // Chiều cao cửa sổ console mong muốn (số dòng)

// Kích thước khung chung (nhỏ hơn cửa sổ một chút)
const int FRAME_MARGIN_X = 2; // Khoảng cách từ lề cửa sổ đến khung theo chiều X
const int FRAME_MARGIN_Y = 1; // Khoảng cách từ lề cửa sổ đến khung theo chiều Y

// Offset cho nội dung bên trong khung
const int FRAME_TITLE_Y_OFFSET = 2;       // Dòng cho tiêu đề, tính từ lề trên của KHUNG
const int FRAME_SEPARATOR_Y_OFFSET = 3;   // Dòng cho dấu gạch ngang, tính từ lề trên của KHUNG
const int FRAME_CONTENT_START_Y_OFFSET = 5; // Dòng bắt đầu nội dung chính, tính từ lề trên của KHUNG
const int FRAME_CONTENT_START_X_OFFSET = 4; // Khoảng cách từ lề trái của KHUNG đến nội dung

const int AVG_CHAR_WIDTH_PIXELS = 8;
const int AVG_CHAR_HEIGHT_PIXELS = 16;
const int FRAME_FOOTER_Y_OFFSET = 1;

// const int FRAME_MARGIN_X = 1;
// const int FRAME_MARGIN_Y = 1;
// const int FRAME_TITLE_Y_OFFSET = 1;
// const int FRAME_SEPARATOR_Y_OFFSET = 2;
// const int FRAME_CONTENT_START_Y_OFFSET = 4;
// const int FRAME_CONTENT_START_X_OFFSET = 3;

// Hàm đặt vị trí con trỏ
void gotoXY(int X, int Y);

// Hàm vẽ khung viền (có thể đơn giản hóa từ Payroll.cpp)
void drawBorder(int x1, int y1, int x2, int y2, bool withDelay = false);

// Hàm xóa màn hình
void clearScreen();

// Hàm tạo độ trễ đơn giản
void cDelay(int milliseconds);

/**
 * @brief Lấy kích thước hiện tại của cửa sổ console (phần nhìn thấy được).
 * @param outWidth Tham chiếu đến biến để lưu trữ chiều rộng của cửa sổ.
 * @param outHeight Tham chiếu đến biến để lưu trữ chiều cao của cửa sổ.
 */
void getConsoleWindowSize(int& outWidth, int& outHeight);

/**
 * @brief In một chuỗi văn bản ra giữa theo chiều ngang tại dòng yPos.
 * @param text Chuỗi văn bản cần in.
 * @param yPos Tọa độ dòng Y để in.
 * @param windowWidth Chiều rộng của cửa sổ console (dùng để tính toán căn giữa).
 */
void printCenteredText(const std::string& text, int yPos, int windowWidth);

// (Tùy chọn) Đặt kích thước cửa sổ - có thể ít quan trọng hơn lúc này
// void setWindowSize(int width, int height);

// --- TIỆN ÍCH XỬ LÝ NGÀY THÁNG ---

/**
 * @brief Phân tích chuỗi ngày tháng từ định dạng "M/D/YYYY" hoặc "MM/DD/YYYY".
 * * Hàm này sẽ cố gắng đọc tháng, ngày, năm từ chuỗi đầu vào.
 * * @param dateStr Chuỗi ngày tháng cần phân tích.
 * @param year Biến tham chiếu để lưu trữ năm sau khi phân tích.
 * @param month Biến tham chiếu để lưu trữ tháng sau khi phân tích.
 * @param day Biến tham chiếu để lưu trữ ngày sau khi phân tích.
 * @return true nếu phân tích thành công và ngày tháng hợp lệ (ở mức cơ bản), false nếu ngược lại.
 * * @note Hàm này hiện chỉ kiểm tra định dạng cơ bản, chưa kiểm tra tính hợp lệ sâu của ngày tháng (ví dụ: tháng 2 có 30 ngày).
 */
bool parseWorkDate(const std::string& dateStr, int& year, int& month, int& day);

/**
 * @brief Chuyển đổi ngày, tháng, năm thành chuỗi định dạng "YYYY-MM-DD".
 * * @param year Năm.
 * @param month Tháng.
 * @param day Ngày.
 * @return Chuỗi ngày tháng đã định dạng, hoặc chuỗi rỗng nếu đầu vào không hợp lệ.
 */
std::string formatDateToYYYYMMDD(int year, int month, int day);

#endif // CONSOLE_UTILS_H