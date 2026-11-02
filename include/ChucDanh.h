#ifndef CHUCDANH_H
#define CHUCDANH_H
#include <string>
#include <iostream>
using namespace std;

class ChucDanh {
private:
    string maCD, tenCD;
    double luongCoBan;
    double phuCapChucDanh;

public:
    ChucDanh();
    ChucDanh(const string& maCD, const string& tenCD, double luongCoBan, double phuCapChucDanh);

    string getMaCD() const;
    string getTenCD() const;
    double getLuongCoBan() const;
    double getPhuCap() const;
    void setTenCD(const string& ten);
    void setLuongCoBan(double luong);
    void setPhuCap(double pc);

    void hienThi() const;
    void ghiFile(ostream& os) const;
};

#endif
