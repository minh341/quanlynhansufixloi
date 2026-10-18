# HRMS - Hệ thống Quản lý Nhân sự (Bài tập lớn OOP, C++)

Chương trình console quản lý nhân sự: hồ sơ nhân viên, phòng ban, chấm công, tính lương, nghỉ phép.
Đăng nhập bằng mã nhân viên, menu thay đổi theo vai trò.

## Cấu trúc thư mục

```
HRMS/
├── main.cpp            # hàm main, menu, đọc/ghi file
├── include/            # khai báo lớp (.h) + TienIch.h (hàm tiện ích)
├── src/                # cài đặt (.cpp)
├── data/               # dữ liệu lưu dạng văn bản, các trường ngăn bằng '|'
└── README.md
```

8 lớp: `NhanVien`, `QuanLyNhanSu`, `BanGiamDoc`, `PhongBan`, `ChucDanh`, `ChamCong`, `BangLuong`, `DonNghiPhep`.
`TienIch` chỉ chứa hàm tiện ích (không phải lớp).

## Biên dịch và chạy

Chạy từ thư mục `HRMS` (để chương trình tìm thấy thư mục `data/`):

```
g++ -Iinclude main.cpp src/*.cpp -o hrms
./hrms          (Windows: hrms)
```

Với Code::Blocks: tạo project rỗng, thêm `main.cpp` và các file trong `src/`, vào *Project > Build options > Search directories* thêm thư mục `include`, đặt *Working directory* là thư mục `HRMS`.

Mã đăng nhập mẫu:

| Mã | Vai trò |
|---|---|
| NV001 | Quản lý nhân sự |
| NV002, NV005 | Ban giám đốc |
| NV003, NV004 | Nhân viên |

Nhấn Enter ở màn hình đăng nhập để thoát. Dữ liệu được lưu vào `data/` khi thoát. Muốn quay lại dữ liệu mẫu thì xóa các file `.txt` trong `data/` rồi chạy lại.

## Kỹ thuật dùng, đối chiếu theo chương môn học

| Chương | Kỹ thuật | Nơi dùng |
|---|---|---|
| 2 - Lớp và đối tượng | Đóng gói (dữ liệu private, getter/setter) | tất cả các lớp |
| | Hàm tạo mặc định, hàm tạo có đối, hàm tạo sao chép, hàm hủy | `NhanVien.cpp` |
| | Thành phần tĩnh, phương thức tĩnh | `NhanVien::soDoiTuong`, `NhanVien::demNhanVien()`; `ChamCong::chuyenPhut()` |
| | Hàm bạn, nạp chồng toán tử `<<` | `operator<<` của `NhanVien` |
| | Con trỏ `this`, con trỏ đối tượng, `new` / `delete` | `main.cpp`, `QuanLyNhanSu::xoaNhanVien` |
| | Quan hệ tập hợp (aggregation) | `PhongBan` giữ `vector<NhanVien*>` |
| 3 - Kế thừa | Kế thừa `public`, danh sách khởi tạo gọi hàm tạo lớp cơ sở | `QuanLyNhanSu`, `BanGiamDoc` |
| | Gọi hàm lớp cơ sở bằng `NhanVien::xemThongTin()` | `QuanLyNhanSu.cpp`, `BanGiamDoc.cpp` |
| | Dữ liệu private + giao diện protected (`ghiTruongCoBan`) | `NhanVien.h` |
| 4 - Đa hình | Hàm ảo, liên kết động qua con trỏ lớp cơ sở | `xemThongTin`, `vaiTro`, `loaiNhanVien`, `tinhPhuCapQuanLy`, `ghiFile` |
| | Hàm hủy ảo | `NhanVien::~NhanVien` |
| | Khuôn hình hàm | `ghiMang<T>` trong `main.cpp` |
| 5 - Dòng dữ liệu vào ra | `cin`, `cout`, `getline`, `iomanip` (`setw`, `setprecision`) | `main.cpp`, các hàm `hienThi` |
| | Đọc/ghi file: `ifstream`, `ofstream` | `docDuLieu`, `luuDuLieu` |
| 6 - Xử lý ngoại lệ | `throw`, `try`, `catch` | `BanGiamDoc::pheDuyetNghiPhep`, `DonNghiPhep::pheDuyet`, `QuanLyNhanSu::themNhanVien`, `phienLamViec` |

## Lưu trữ danh sách

Các danh sách (nhân viên, phòng ban, chức danh, chấm công, đơn nghỉ phép) dùng `std::vector` của thư viện chuẩn nên không bị giới hạn số lượng. Danh sách nhân viên là `vector<NhanVien*>` (con trỏ lớp cơ sở) để chứa được cả nhân viên thường, quản lý nhân sự và ban giám đốc; đối tượng được `delete` trong hàm hủy của `DuLieu`.

## Quy tắc nghiệp vụ

- **Công theo giờ làm:** giờ làm = giờ ra - giờ vào, trừ 1 giờ nghỉ trưa nếu làm trên 5 giờ. Từ 7 giờ trở lên tính 1 công, từ 3,5 giờ tính 0,5 công, dưới đó không tính công (`ChamCong::tinhCong`).
- **Tăng ca:** tính từ `max(giờ vào, 17:00)` đến giờ ra, hệ số 1,5.
- **Lương:** lương cơ bản = lương hợp đồng x số công / 26; lương thực nhận không bao giờ âm.
- **Bảo hiểm (BHXH, BHYT, BHTN):** chỉ trích khi tháng đó có từ 14 công trở lên. Lưu ý đây là một "ngưỡng": làm 13,5 công không bị trừ bảo hiểm nên thực nhận có thể cao hơn làm 14 công. Nhóm đối chiếu quy định hiện hành trước khi nộp.
- **Nghỉ phép:** chỉ đơn loại "Phep nam" mới bị kiểm tra và trừ vào quỹ phép năm; "Nghi om" và "Viec rieng" được duyệt mà không trừ phép. Không được tự duyệt đơn của chính mình.
- **Xóa nhân viên:** xóa luôn chấm công và đơn nghỉ phép của người đó; không cho xóa nhân viên thuộc Ban giám đốc. Mã đơn mới luôn lớn hơn mã lớn nhất đang có nên không bị trùng.
- **Ngày nhập:** phải đúng dạng dd/mm/yyyy và là ngày có thật (có xét năm nhuận).

## Điều chỉnh các hằng số tính lương

Trong `src/BangLuong.cpp`: số ngày công chuẩn, ngưỡng 14 công trích bảo hiểm, mức giảm trừ bản thân, tỷ lệ BHXH/BHYT/BHTN, hệ số tăng ca. Ngưỡng giờ làm tính công nằm trong `src/ChamCong.cpp`. Biểu thuế TNCN trong hàm `tinhThueTNCN` là mô hình đơn giản hóa, nhóm cần đối chiếu với quy định hiện hành trước khi nộp.
