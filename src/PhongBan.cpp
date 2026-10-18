#include "PhongBan.h"

PhongBan::PhongBan() {}

PhongBan::PhongBan(const string& maPB, const string& tenPB, const string& moTa) {
    this->maPB = maPB;
    this->tenPB = tenPB;
    this->moTa = moTa;
}

string PhongBan::getMaPB() const { return maPB; }
string PhongBan::getTenPB() const { return tenPB; }
void PhongBan::setTenPB(const string& ten) { tenPB = ten; }
void PhongBan::setMoTa(const string& mt) { moTa = mt; }

void PhongBan::themNhanVien(NhanVien* nv) {
    if (nv == NULL) throw "Nhan vien khong hop le.";
    for (int i = 0; i < (int)dsNhanVien.size(); i++)
        if (dsNhanVien[i]->getMaNV() == nv->getMaNV()) throw "Nhan vien da co trong phong ban.";
    dsNhanVien.push_back(nv);
}

bool PhongBan::xoaNhanVien(const string& maNV) {
    for (int i = 0; i < (int)dsNhanVien.size(); i++) {
        if (dsNhanVien[i]->getMaNV() == maNV) {
            dsNhanVien.erase(dsNhanVien.begin() + i);   // chỉ gỡ con trỏ, không delete
            return true;
        }
    }
    return false;
}

int PhongBan::soLuongNhanVien() const { return (int)dsNhanVien.size(); }

void PhongBan::hienThiDanhSach() const {
    if (dsNhanVien.empty()) {
        cout << "  (Phong chua co nhan vien)\n";
        return;
    }
    for (int i = 0; i < (int)dsNhanVien.size(); i++)
        cout << "  " << *dsNhanVien[i] << "\n";   // operator<< gọi vaiTro() ảo
}

void PhongBan::hienThiThongTin() const {
    cout << maPB << " - " << tenPB << " (" << soLuongNhanVien() << " nhan vien) - " << moTa << "\n";
}

void PhongBan::ghiFile(ostream& os) const {
    os << maPB << "|" << tenPB << "|" << moTa << "\n";
}
