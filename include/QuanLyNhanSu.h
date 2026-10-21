#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H
#include <vector>
#include "NhanVien.h"
#include "BangLuong.h"
#include "ChamCong.h"
#include "ChucDanh.h"
#include "DonNghiPhep.h"

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

    // ---- Quản lý hồ sơ nhân viên (thao tác trên vector dùng chung) ----
    void themNhanVien(vector<NhanVien*>& ds, NhanVien* nv);   // throw nếu trùng mã
    bool suaNhanVien(const vector<NhanVien*>& ds, const string& maNV);
    bool xoaNhanVien(vector<NhanVien*>& ds, const string& maNV);   // delete đối tượng; nơi gọi gỡ khỏi PhongBan trước
    NhanVien* timNhanVien(const vector<NhanVien*>& ds, const string& maNV) const;
    vector<NhanVien*> timTheoTen(const vector<NhanVien*>& ds, const string& tuKhoa) const;

    // ---- Chấm công và lương ----
    void ghiNhanChamCong(vector<ChamCong>& dsCC, const ChamCong& cc);   // ghi đè nếu trùng ngày
    BangLuong lapBangLuong(const NhanVien& nv, const ChucDanh& cd,
                           const vector<ChamCong>& dsCC, const vector<DonNghiPhep>& dsDon,
                           int thang, int nam) const;
};

#endif
