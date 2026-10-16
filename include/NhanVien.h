#ifndef NHANVIEN_H
#define NHANVIEN_H
#include <string>
#include <iostream>
using namespace std;

const int MAX_NV = 100;   // số nhân viên tối đa (dùng mảng + biến đếm)

// Mã loại nhân viên, trả về bởi hàm ảo loaiNhanVien()
const int LOAI_THUONG = 0;
const int LOAI_QLNS = 1;
const int LOAI_BGD = 2;

// [Chương 2] Lớp NhanVien: ĐÓNG GÓI (dữ liệu private + getter/setter),
//            hàm tạo, hàm tạo sao chép, hàm hủy, thành phần tĩnh, hàm bạn.
// [Chương 3] Là LỚP CƠ SỞ của QuanLyNhanSu và BanGiamDoc.
// [Chương 4] Có các HÀM ẢO để lớp dẫn xuất định nghĩa lại (đa hình).
class NhanVien {
private:
    string maNV, hoTen, ngaySinh, gioiTinh, cccd;
    string diaChi, soDienThoai, email, ngayVaoLam, trangThai;
    string maPB;   // mã phòng ban đang thuộc về
    string maCD;   // mã chức danh đang giữ
    int soNgayPhepNam;    // quỹ phép năm
    int soNgayPhepDaDung;
    static int soDoiTuong;   // thành phần tĩnh: đếm số đối tượng NhanVien đang tồn tại

protected:
    // Giao diện protected cho lớp dẫn xuất (không cho truy cập trực tiếp dữ liệu private)
    void ghiTruongCoBan(ostream& os) const;

public:
    NhanVien();
    NhanVien(const string& maNV, const string& hoTen, const string& ngaySinh,
             const string& gioiTinh, const string& cccd, const string& diaChi,
             const string& soDienThoai, const string& email, const string& ngayVaoLam,
             const string& maPB, const string& maCD);
    NhanVien(const NhanVien& nv);   // hàm tạo sao chép
    virtual ~NhanVien();            // hàm hủy ảo: xóa đúng đối tượng lớp dẫn xuất qua con trỏ lớp cơ sở

    static int demNhanVien();       // phương thức tĩnh: trả về số đối tượng đang tồn tại

    // ---- Getter ----
    string getMaNV() const;
    string getHoTen() const;
    string getMaPB() const;
    string getMaCD() const;
    string getTrangThai() const;
    int getSoNgayPhepNam() const;
    int soNgayPhepConLai() const;

    // ---- Setter ----
    void setHoTen(const string& ten);
    void setDiaChi(const string& dc);
    void setSoDienThoai(const string& sdt);
    void setEmail(const string& mail);
    void setMaPB(const string& ma);
    void setMaCD(const string& ma);
    void setTrangThai(const string& tt);
    void setSoNgayPhepNam(int n);
    void setSoNgayPhepDaDung(int n);

    // ---- Nghiệp vụ ----
    bool truPhep(int soNgay);   // trừ quỹ phép; false nếu không đủ

    // ---- Các hàm ảo (đa hình động) ----
    virtual void xemThongTin() const;
    virtual string vaiTro() const;
    virtual int loaiNhanVien() const;
    virtual double tinhPhuCapQuanLy() const;   // phụ cấp theo vai trò, mặc định 0
    virtual void ghiFile(ostream& os) const;   // ghi 1 dòng dữ liệu ra file

    friend ostream& operator<<(ostream& os, const NhanVien& nv);   // hàm bạn
};

#endif
