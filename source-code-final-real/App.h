#ifndef APP_H
#define APP_H

#include "EmployeeManager.h"

/**
 * @class App
 * @brief Lớp ứng dụng chính, điều khiển toàn bộ luồng chạy của chương trình.
 *
 * Lớp này khởi tạo các đối tượng quản lý cần thiết và xử lý
 * tương tác của người dùng thông qua một giao diện dòng lệnh (CLI).
 */
class App {
private:
    EmployeeManager _empManager; // Đối tượng quản lý nhân viên

    // --- Các phương thức private để xử lý từng chức năng ---
    /**
     * @brief Hiển thị menu chính cho người dùng.
     */
    void showMenu() const;

    /**
     * @brief Khởi tạo dữ liệu mẫu (thêm một vài nhân viên).
     */
    void seedData();

    /**
     * @brief Xử lý logic thêm nhân viên mới.
     */
    void handleAddEmployee();

    /**
     * @brief Xử lý logic xóa nhân viên.
     */
    void handleDeleteEmployee();

    /**
     * @brief Xử lý logic hiển thị chi tiết một nhân viên.
     */
    void handleShowEmployeeDetails();

public:
    /**
     * @brief Constructor của lớp App.
     * Khởi tạo EmployeeManager và dữ liệu mẫu.
     */
    App();

    /**
     * @brief Phương thức chính để chạy ứng dụng.
     * Chứa vòng lặp chính của chương trình.
     */
    void run();
    /**
     * @brief Phương thức chính để lưu danh sách nhân viên hiện tại vào file.
     */
    void saveData();
};

#endif // APP_H