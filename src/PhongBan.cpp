#include "PhongBan.h"

PhongBan::PhongBan() { soNV = 0; }

PhongBan::PhongBan(const string& maPB, const string& tenPB, const string& moTa) {
    this->maPB = maPB;
    this->tenPB = tenPB;
    this->moTa = moTa;
    soNV = 0;
}

string PhongBan::getMaPB() const { return maPB; }
string PhongBan::getTenPB() const { return tenPB; }
void PhongBan::setTenPB(const string& ten) { tenPB = ten; }
void PhongBan::setMoTa(const string& mt) { moTa = mt; }

void PhongBan::themNhanVien(NhanVien* nv) {
    if (nv == NULL) throw "Nhan vien khong hop le.";
    for (int i = 0; i < soNV; i++)
        if (dsNhanVien[i]->getMaNV() == nv->getMaNV()) throw "Nhan vien da co trong phong ban.";
    if (soNV >= MAX_NV) throw "Phong ban da day.";
    dsNhanVien[soNV++] = nv;
}

bool PhongBan::xoaNhanVien(const string& maNV) {
    for (int i = 0; i < soNV; i++) {
        if (dsNhanVien[i]->getMaNV() == maNV) {
            for (int j = i; j < soNV - 1; j++)
                dsNhanVien[j] = dsNhanVien[j + 1];   // chỉ dồn con trỏ, không delete
            soNV--;
            return true;
        }
    }
    return false;
}

int PhongBan::soLuongNhanVien() const { return soNV; }

void PhongBan::hienThiDanhSach() const {
    if (soNV == 0) {
        cout << "  (Phong chua co nhan vien)\n";
        return;
    }
    for (int i = 0; i < soNV; i++)
        cout << "  " << *dsNhanVien[i] << "\n";   // operator<< gọi vaiTro() ảo
}

void PhongBan::hienThiThongTin() const {
    cout << maPB << " - " << tenPB << " (" << soLuongNhanVien() << " nhan vien) - " << moTa << "\n";
}

void PhongBan::ghiFile(ostream& os) const {
    os << maPB << "|" << tenPB << "|" << moTa << "\n";
}
