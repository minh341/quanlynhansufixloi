#ifndef PHONGBAN_H
#define PHONGBAN_H
#include <string>
#include <vector>
#include "NhanVien.h"
using namespace std;

class PhongBan {
private:
    string maPB, tenPB, moTa;
    vector<NhanVien*> dsNhanVien;

public:
    PhongBan();
    PhongBan(const string& maPB, const string& tenPB, const string& moTa);

    string getMaPB() const;
    string getTenPB() const;
    void setTenPB(const string& ten);
    void setMoTa(const string& mt);

    void themNhanVien(NhanVien* nv);
    bool xoaNhanVien(const string& maNV);
    int soLuongNhanVien() const;
    void hienThiDanhSach() const;
    void hienThiThongTin() const;
    void ghiFile(ostream& os) const;
};

#endif
