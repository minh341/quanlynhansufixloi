#ifndef DONNGHIPHEP_H
#define DONNGHIPHEP_H
#include <string>
#include <iostream>
using namespace std;

enum TrangThaiDon { CHO_DUYET, DA_DUYET, TU_CHOI };

class DonNghiPhep {
private:
    string maDon, maNV, loaiPhep;
    string tuNgay, denNgay, lyDo;
    int soNgay;
    TrangThaiDon trangThai;

public:
    DonNghiPhep();
    DonNghiPhep(const string& maDon, const string& maNV, const string& loaiPhep,
                const string& tuNgay, const string& denNgay, int soNgay, const string& lyDo);

    string getMaDon() const;
    string getMaNV() const;
    string getLoaiPhep() const;
    string getTuNgay() const;
    string getDenNgay() const;
    int getSoNgay() const;
    TrangThaiDon getTrangThai() const;
    void setTrangThai(TrangThaiDon tt);
    string trangThaiString() const;

    void guiDon();
    void pheDuyet();
    void tuChoi();

    void hienThi() const;
    void ghiFile(ostream& os) const;
};

#endif
