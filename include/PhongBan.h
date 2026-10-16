#ifndef PHONGBAN_H
#define PHONGBAN_H
#include <string>
#include "NhanVien.h"
using namespace std;

const int MAX_PB = 20;

// [Chương 2] Quan hệ TẬP HỢP (aggregation) với NhanVien: phòng ban giữ mảng con trỏ
// tới nhân viên nhưng KHÔNG sở hữu (hàm hủy / xóa phòng ban không delete nhân viên).
class PhongBan {
private:
    string maPB, tenPB, moTa;
    NhanVien* dsNhanVien[MAX_NV];
    int soNV;

public:
    PhongBan();
    PhongBan(const string& maPB, const string& tenPB, const string& moTa);

    string getMaPB() const;
    string getTenPB() const;
    void setTenPB(const string& ten);
    void setMoTa(const string& mt);

    void themNhanVien(NhanVien* nv);          // throw nếu null / trùng / đầy
    bool xoaNhanVien(const string& maNV);     // chỉ gỡ con trỏ, không delete
    int soLuongNhanVien() const;
    void hienThiDanhSach() const;             // [Chương 4] gọi hàm ảo vaiTro() qua con trỏ lớp cơ sở
    void hienThiThongTin() const;
    void ghiFile(ostream& os) const;
};

#endif
