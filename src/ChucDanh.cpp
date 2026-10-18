#include "ChucDanh.h"
#include "TienIch.h"

ChucDanh::ChucDanh() {
    luongCoBan = 0;
    phuCapChucDanh = 0;
}

ChucDanh::ChucDanh(const string& maCD, const string& tenCD, double luongCoBan, double phuCapChucDanh) {
    this->maCD = maCD;
    this->tenCD = tenCD;
    this->luongCoBan = luongCoBan;
    this->phuCapChucDanh = phuCapChucDanh;
}

string ChucDanh::getMaCD() const { return maCD; }
string ChucDanh::getTenCD() const { return tenCD; }
double ChucDanh::getLuongCoBan() const { return luongCoBan; }
double ChucDanh::getPhuCap() const { return phuCapChucDanh; }
void ChucDanh::setTenCD(const string& ten) { tenCD = ten; }
void ChucDanh::setLuongCoBan(double luong) { luongCoBan = luong; }
void ChucDanh::setPhuCap(double pc) { phuCapChucDanh = pc; }

void ChucDanh::hienThi() const {
    cout << maCD << " - " << tenCD << " | Luong co ban: ";
    inTien(cout, luongCoBan);
    cout << " | Phu cap: ";
    inTien(cout, phuCapChucDanh);
    cout << "\n";
}

void ChucDanh::ghiFile(ostream& os) const {
    os << maCD << "|" << tenCD << "|" << (long long)(luongCoBan + 0.5) << "|"
       << (long long)(phuCapChucDanh + 0.5) << "\n";
}
