#ifndef CHAMCONG_H
#define CHAMCONG_H
#include <string>
#include <iostream>
using namespace std;

class ChamCong {
private:
    string maCC, maNV, ngay;
    string gioVao, gioRa;
    double soGioTangCa;
    int diMuon, veSom;

    static int chuyenPhut(const string& hhmm);

public:
    ChamCong();
    ChamCong(const string& maCC, const string& maNV, const string& ngay);

    string getMaNV() const;
    string getNgay() const;
    int getThang() const;
    int getNam() const;
    double getSoGioTangCa() const;
    int getDiMuon() const;
    int getVeSom() const;

    void ghiNhanCong(const string& gioVao, const string& gioRa);
    double tinhGioLam() const;
    double tinhCong() const;

    void hienThi() const;
    void ghiFile(ostream& os) const;
};

#endif
