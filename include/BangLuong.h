#ifndef BANGLUONG_H
#define BANGLUONG_H
#include <string>
#include <vector>
#include "NhanVien.h"
#include "ChucDanh.h"
#include "ChamCong.h"
#include "DonNghiPhep.h"
using namespace std;

class BangLuong {
private:
    string maBL, maNV;
    int thang, nam;
    double soNgayCong;
    double luongCoBan, phuCap, tienTangCa;
    double bhxh, bhyt, bhtn, thueTNCN, thucNhan;

    double tinhThueTNCN(double thuNhapChiuThue) const;

public:
    BangLuong();
    BangLuong(const string& maBL, const string& maNV, int thang, int nam);

    string getMaNV() const;
    int getThang() const;
    int getNam() const;
    double getSoNgayCong() const;
    double getThucNhan() const;

    void tinhLuong(const NhanVien& nv, const ChucDanh& cd, const vector<ChamCong>& dsCC,
                   const vector<DonNghiPhep>& dsDon = vector<DonNghiPhep>());
    void inPhieuLuong() const;
};

#endif
