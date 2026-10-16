#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H
#include "NhanVien.h"
#include "BangLuong.h"
#include "ChamCong.h"
#include "ChucDanh.h"

// [Chương 3] KẾ THỪA public từ NhanVien: bổ sung thuộc tính chuyenMon và quyền quản trị
//            hồ sơ nhân viên, chấm công, lương.
// [Chương 4] Định nghĩa lại (ghi đè) các hàm ảo của lớp cơ sở.
class QuanLyNhanSu : public NhanVien {
private:
    string chuyenMon;

public:
    QuanLyNhanSu();
    QuanLyNhanSu(const NhanVien& nv, const string& chuyenMon);   // gọi hàm tạo lớp cơ sở

    string getChuyenMon() const;
    void setChuyenMon(const string& cm);

    // ---- Hàm ảo định nghĩa lại ----
    virtual void xemThongTin() const;
    virtual string vaiTro() const;
    virtual int loaiNhanVien() const;
    virtual double tinhPhuCapQuanLy() const;
    virtual void ghiFile(ostream& os) const;

    // ---- Quản lý hồ sơ nhân viên (thao tác trên mảng dùng chung) ----
    void themNhanVien(NhanVien* ds[], int& n, NhanVien* nv);   // throw nếu trùng mã / mảng đầy
    bool suaNhanVien(NhanVien* const ds[], int n, const string& maNV);
    bool xoaNhanVien(NhanVien* ds[], int& n, const string& maNV);   // delete đối tượng; nơi gọi gỡ khỏi PhongBan trước
    NhanVien* timNhanVien(NhanVien* const ds[], int n, const string& maNV) const;
    int timTheoTen(NhanVien* const ds[], int n, const string& tuKhoa, NhanVien* kq[]) const;   // trả về số kết quả

    // ---- Chấm công và lương ----
    void ghiNhanChamCong(ChamCong dsCC[], int& soCC, const ChamCong& cc);   // ghi đè nếu trùng ngày; throw nếu đầy
    BangLuong lapBangLuong(const NhanVien& nv, const ChucDanh& cd,
                           const ChamCong dsCC[], int soCC, int thang, int nam) const;
};

#endif
