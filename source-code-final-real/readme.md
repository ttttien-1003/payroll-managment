# Đồ án Môn học: Hệ thống Quản lý Lương Nhân viên (Payroll Management System)

Đây là BÁO CÁO cho đồ án môn học Lập trình Hướng đối tượng (OOP). Dự án này xây dựng một hệ thống quản lý lương nhân viên bằng C++, áp dụng các nguyên tắc OOP và các mẫu thiết kế.

## 1. Thành viên nhóm

| Họ và Tên | MSSV | Vai trò | Link Git |
| :--- | :--- | :--- | :--- |
| **Nguyễn Việt Cường** | 23120116 | **Nhóm trưởng** | [(Link Git cá nhân)](https://github.com/nvcuong12) |
| Lê Hải Sơn | 23120162) | Thành viên | [(Link Git cá nhân)](https://github.com/haison65) |
| Trần Thị Thủy Tiên | 23120172 | Thành viên | [(Link Git cá nhân)](https://github.com/ttttien-1003) |

## 2. Phân công công việc

| Tên thành viên | Công việc đã thực hiện | Mức độ commit Git |
| :--- | :--- | :--- |
| Nguyễn Việt Cường | - Quản lý chung, phân công công việc, theo dõi tiến độ. <br> - Xây dựng module tính lương (`SalaryCalculator`). <br> - Xây dựng module quản lý chấm công (`AttendanceManager`). <br> - Xây dựng module giao diện người dùng. <br> - Quay video demo đồ án. | *(Mô tả: Đều đặn)* |
| Lê Hải Sơn | - Xây dựng các lớp nhân viên cụ thể (`FulltimeEmployee`, `Intern`, `ContractualEmployee`). <br> - Xây dựng module giao diện người dùng CLI (`App`) và định dạng hiển thị (`PayrollPrinter`, `NumberFormatter`). <br> - Xử lý đọc/ghi file CSV chấm công. <br> - Tích hợp các module. <br> - Vẽ class diagram và tạo tài liệu mô tả về các lớp, ý nghĩa các hàm. | *(Mô tả: Đều đặn)* |
| Trần Thị Thủy Tiên | - Thiết kế kiến trúc tổng thể (Lớp `IEmployee`, `IWelfare`). <br> - Xây dựng các lớp nhân viên cụ thể (`FulltimeEmployee`, `Intern`, `ContractualEmployee`). <br> - Xây dựng các lớp phúc lợi cụ thể (`SocialInsuranceWelfare`, `BonusWelfare`, `TransportationWelfare`). <br> - Xây dựng module quản lý phúc lợi (`WelfareManager`). <br> - Xử lý đọc/ghi file danh sách nhân viên. <br> - ... | *(Mô tả: Đều đặn)* |

## 3. Tỉ lệ đóng góp

| Tên thành viên | Tỉ lệ đóng góp |
| :--- | :--- |
| Nguyễn Việt Cường | 34% |
| Lê Hải Sơn | 33% |
| Trần Thị Thủy Tiên | 33% |
| **Tổng** | **100%** |

## 4. Tỉ lệ điểm

Nhóm đề xuất tỉ lệ chia điểm như sau: **Chia đều**.

## 5. Mô tả chi tiết theo Cách thức đánh giá

### 5.1. Teamwork (15%)

* **Phân công và theo dõi tiến độ:** Nhóm đã sử dụng Google Docs, GitHub để phân công nhiệm vụ và theo dõi tiến độ. Công việc được chia nhỏ và gán cho từng thành viên dựa trên thế mạnh và sự thống nhất của cả nhóm.
* **Biên bản họp nhóm:** [*(Link đến thư mục chứa biên bản họp nhóm)*](https://studenthcmusedu-my.sharepoint.com/:f:/g/personal/23120172_student_hcmus_edu_vn/EoEojEnJprtBjMGgZHddJycBAXOOQ0N74ooxMC5Q4w6MxQ?e=QwEb9p). Nhóm đã tổ chức họp trực tuyến qua Google Meet 3 lần để báo cáo tiến độ, giải quyết khó khăn và định hướng công việc tiếp theo. Ngoài ra, với những lần phân công công việc, nhóm cũng thường phân công trực tiếp qua Messenger.
* **Git của từng thành viên:**
    * **(Họ Tên 1):** (Link Git cá nhân 1)
    * **(Họ Tên 2):** (Link Git cá nhân 2)
    * **(Họ Tên 3):** (Link Git cá nhân 3)
    * Lịch sử commit trên GitHub *(Link đến repo chính)* thể hiện sự tham gia đều đặn của các thành viên trong suốt quá trình thực hiện đồ án. Mỗi commit đều có mô tả rõ ràng về thay đổi được thực hiện.

### 5.2. UI/UX (20%)

* **Cài đặt lại chức năng của mã nguồn mẫu theo hướng đối tượng (3%):**
    * Nhóm đã phân tích mã nguồn mẫu và tái cấu trúc hoàn toàn theo hướng đối tượng.
    * Lớp `IEmployee` được định nghĩa làm lớp cơ sở trừu tượng, và các loại nhân viên cụ thể (`FulltimeEmployee`, `Intern`, `ContractualEmployee`) kế thừa từ đó, thể hiện tính đa hình và kế thừa.
    * Logic tính lương và phúc lợi được tách ra khỏi các lớp nhân viên và quản lý bởi các lớp chuyên biệt (`SalaryCalculator`, `WelfareManager`), tuân thủ nguyên tắc S (Single Responsibility principle).
* **Các chức năng thêm và cải tiến (14%):**
    * **Quản lý nhiều loại nhân viên:** Hỗ trợ nhân viên chính thức, hợp đồng và thực tập sinh, mỗi loại có cách tính lương riêng.
    * **Quản lý chấm công:** Tải và xử lý dữ liệu chấm công từ file CSV (`attendance.csv`), phân biệt giờ làm bình thường, tăng ca và ngày lễ.
    * **Quản lý phúc lợi linh hoạt:** Xây dựng hệ thống phúc lợi (`IWelfare`) cho phép dễ dàng thêm/bớt các loại phúc lợi (BHXH, Thưởng, Trợ cấp đi lại).
    * **Tính lương tự động:** Tính lương chi tiết dựa trên giờ công và phúc lợi.
    * **In phiếu lương:** Hỗ trợ in phiếu lương cho từng nhân viên hoặc toàn bộ nhân viên ra file (`payroll_export.txt`), có định dạng số tiền dễ đọc.
    * **Lưu/Tải dữ liệu:** Chương trình có khả năng lưu và tải danh sách nhân viên từ file (`employee_list.txt`), giúp duy trì dữ liệu giữa các lần chạy.
    * **Giao diện dòng lệnh (CLI):** Cung cấp menu tương tác cho người dùng.
* **Giao diện bố trí hợp lí (3%):**
    * Giao diện CLI được thiết kế rõ ràng, có hướng dẫn cụ thể cho từng chức năng.
    * Thông tin hiển thị (danh sách nhân viên, chi tiết, phiếu lương) được định dạng cơ bản, dễ nhìn.
    * Sử dụng `NumberFormatter` và `CultureInfo` để định dạng số tiền theo chuẩn Việt Nam, giúp dễ đọc hơn.

### 5.3. Kiến trúc phần mềm + Design Pattern (20%)

* **Kiến trúc phần mềm:**
    * Nhóm đã áp dụng kiến trúc **Lớp (Layered Architecture)** ở mức cơ bản:
        * **Lớp Trình bày (Presentation):** Lớp `App` và `PayrollPrinter` xử lý tương tác người dùng và hiển thị dữ liệu.
        * **Lớp Nghiệp vụ (Business Logic):** Các lớp `EmployeeManager`, `SalaryCalculator`, `WelfareManager`, `AttendanceManager` chứa các quy tắc và logic chính của hệ thống.
        * **Lớp Dữ liệu (Data - Mức cơ bản):** Việc đọc/ghi file đóng vai trò lưu trữ dữ liệu.
    * Thiết kế hướng module, tách biệt các chức năng chính (Quản lý nhân viên, Chấm công, Phúc lợi, Tính lương).
* **Nguyên tắc OOP:**
    * **Tính đóng gói (Encapsulation):** Dữ liệu được che giấu trong các lớp, chỉ truy cập qua các phương thức công khai.
    * **Tính kế thừa (Inheritance):** Sử dụng `IEmployee` làm lớp cơ sở cho các loại nhân viên, `IWelfare` làm giao diện cho các loại phúc lợi.
    * **Tính đa hình (Polymorphism):** Sử dụng con trỏ/tham chiếu lớp cơ sở (`IEmployee*`, `IWelfare*`) để làm việc với các đối tượng cụ thể, gọi các phương thức ảo (`getEmployeeType`, `calculateSalary`, `calculateImpact`).
    * **Tính trừu tượng (Abstraction):** Lớp `IEmployee` và `IWelfare` là các lớp trừu tượng, định nghĩa giao diện chung.
* **Design Patterns:**
    * **Strategy Pattern:** Các lớp `IEmployee` khác nhau có cách `calculateSalary` khác nhau; các lớp `IWelfare` khác nhau có cách `calculateImpact` khác nhau. Điều này cho phép thay đổi hoặc thêm thuật toán tính lương/phúc lợi mà không ảnh hưởng đến client (ví dụ `EmployeeManager`).
    * **Factory Method (Mức cơ bản):** Hàm `handleAddEmployee` trong `App.cpp` hoạt động như một Simple Factory, tạo ra các đối tượng `IEmployee` cụ thể dựa trên lựa chọn của người dùng.

### 5.4. Đảm bảo chất lượng (20%)

* **Test:** *(Mô tả cách thức test, ví dụ: Test thủ công các chức năng, test đơn vị (nếu có)).* Nhóm đã thực hiện test thủ công các luồng chính: Thêm/Xóa/Sửa nhân viên, tải chấm công, tính lương và in phiếu lương cho từng loại nhân viên với các trường hợp dữ liệu khác nhau (ví dụ: có tăng ca, có ngày lễ, có BHXH, không có BHXH). Đã kiểm tra kết quả tính lương với file `payroll_export.txt`.
* **Coding Convention:**
    * Nhóm đã cố gắng tuân thủ coding convention (Google C++ Style Guide) về cách đặt tên biến, hàm, lớp. Tuy nhiên, do trong quá trình thực hiện đồ án, có một số hàm phát sinh không biết trước cũng như code do nhiều thành viên gửi về, cách đặt tên sẽ không quá đồng nhất. Với vấn đề này, tập thể thành viên của nhóm sẽ chịu trách nhiệm.
    * Sử dụng comment (đặc biệt là Doxygen-style trong file `.h`) để giải thích mục đích của các lớp và phương thức, giúp tăng khả năng đọc hiểu và bảo trì code.
    * Sử dụng `std::shared_ptr` và `std::unique_ptr` để quản lý bộ nhớ tự động, giảm nguy cơ rò rỉ bộ nhớ.
    * Sử dụng `#ifndef`/`#define`/`#endif` để tránh include lặp.

### 5.5. Tài liệu mô tả kiến trúc phần mềm và các module (10%)

* **Tài liệu:** Chính là file `README.md` này, cùng với các comment Doxygen trong mã nguồn.
* **Mô tả kiến trúc:** Đã được mô tả ở mục 5.3.
* **Mô tả các module:**
    * **`IEmployee` & Derivatives:** Định nghĩa các loại nhân viên và hành vi cơ bản.
    * **`IWelfare` & Derivatives:** Định nghĩa các loại phúc lợi, cách tính và điều kiện áp dụng.
    * **`EmployeeManager`:** Module trung tâm, điều phối việc quản lý nhân viên, phúc lợi và tính lương.
    * **`AttendanceManager`:** Quản lý dữ liệu chấm công.
    * **`WelfareManager`:** Quản lý và tính toán tổng hợp các phúc lợi.
    * **`SalaryCalculator`:** Tính toán chi tiết các thành phần lương.
    * **`PayrollPrinter` & `NumberFormatter`:** Định dạng hàng nghìn của tiền lương và xuất phiếu lương.
    * **`App`:** Giao diện người dùng và luồng chính.

### 5.6. Các chủ đề nâng cao (15%)

* **Lập trình Hướng đối tượng nâng cao:** Áp dụng sâu các nguyên tắc Kế thừa, Đa hình, Trừu tượng và các nguyên tắc SOLID.
* **Design Patterns:** Sử dụng Strategy Pattern và Simple Factory như đã mô tả ở mục 5.3.
* **Quản lý bộ nhớ thông minh:** Sử dụng `std::unique_ptr` và `std::shared_ptr` để quản lý vòng đời đối tượng.
* **Xử lý File I/O:** Đọc và ghi dữ liệu từ các file text (`.txt`) và CSV (`.csv`), sử dụng `fstream` và `sstream`.
* **Sử dụng STL:** Vận dụng hiệu quả các cấu trúc dữ liệu (`std::vector`, `std::map`) và thuật toán (`std::remove_if`) từ Standard Template Library.
* **Thiết kế Giao diện Phúc lợi Linh hoạt:** Kiến trúc `IWelfare` cho phép dễ dàng mở rộng hệ thống bằng cách thêm các loại phúc lợi mới mà không cần sửa đổi nhiều code hiện có, thể hiện nguyên tắc Open/Closed.

## 6. Video Demo

**(Dán link Youtube Unlisted vào đây)**

Link: [https://www.youtube.com/watch?v=your_video_id](https://www.youtube.com/watch?v=your_video_id)
