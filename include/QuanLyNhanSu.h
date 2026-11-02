#ifndef QUANLYNHANSU_H
#define QUANLYNHANSU_H
#include <vector>
#include "NhanVien.h"
#include "BangLuong.h"
#include "ChamCong.h"
#include "ChucDanh.h"
#include "DonNghiPhep.h"

class QuanLyNhanSu : public NhanVien {
private:
    string chuyenMon;

public:
    QuanLyNhanSu();
    QuanLyNhanSu(const NhanVien& nv, const string& chuyenMon);

    string getChuyenMon() const;
    void setChuyenMon(const string& cm);

    virtual void xemThongTin() const;
    virtual string vaiTro() const;
    virtual int loaiNhanVien() const;
    virtual double tinhPhuCapQuanLy() const;
    virtual void ghiFile(ostream& os) const;

    void themNhanVien(vector<NhanVien*>& ds, NhanVien* nv);
    bool suaNhanVien(const vector<NhanVien*>& ds, const string& maNV);
    bool xoaNhanVien(vector<NhanVien*>& ds, const string& maNV);
    NhanVien* timNhanVien(const vector<NhanVien*>& ds, const string& maNV) const;
    vector<NhanVien*> timTheoTen(const vector<NhanVien*>& ds, const string& tuKhoa) const;

    void ghiNhanChamCong(vector<ChamCong>& dsCC, const ChamCong& cc);
    BangLuong lapBangLuong(const NhanVien& nv, const ChucDanh& cd,
                           const vector<ChamCong>& dsCC, const vector<DonNghiPhep>& dsDon,
                           int thang, int nam) const;
};

#endif
