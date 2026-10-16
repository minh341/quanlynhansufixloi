#ifndef CHUCDANH_H
#define CHUCDANH_H
#include <string>
#include <iostream>
using namespace std;

const int MAX_CD = 20;

// [Chương 2] Lớp ChucDanh: lương cơ bản và phụ cấp theo chức danh.
class ChucDanh {
private:
    string maCD, tenCD;
    double luongCoBan;       // lương cơ bản theo hợp đồng (tháng)
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
