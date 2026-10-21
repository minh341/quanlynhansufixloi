#include "DonNghiPhep.h"

DonNghiPhep::DonNghiPhep() {
    soNgay = 0;
    trangThai = CHO_DUYET;
}

DonNghiPhep::DonNghiPhep(const string& maDon, const string& maNV, const string& loaiPhep,
                         const string& tuNgay, const string& denNgay, int soNgay, const string& lyDo) {
    this->maDon = maDon;
    this->maNV = maNV;
    this->loaiPhep = loaiPhep;
    this->tuNgay = tuNgay;
    this->denNgay = denNgay;
    this->soNgay = soNgay;
    this->lyDo = lyDo;
    trangThai = CHO_DUYET;
}

string DonNghiPhep::getMaDon() const { return maDon; }
string DonNghiPhep::getMaNV() const { return maNV; }
string DonNghiPhep::getLoaiPhep() const { return loaiPhep; }
string DonNghiPhep::getTuNgay() const { return tuNgay; }
string DonNghiPhep::getDenNgay() const { return denNgay; }
int DonNghiPhep::getSoNgay() const { return soNgay; }
TrangThaiDon DonNghiPhep::getTrangThai() const { return trangThai; }
void DonNghiPhep::setTrangThai(TrangThaiDon tt) { trangThai = tt; }

string DonNghiPhep::trangThaiString() const {
    switch (trangThai) {
        case CHO_DUYET: return "Cho duyet";
        case DA_DUYET: return "Da duyet";
        default: return "Tu choi";
    }
}

void DonNghiPhep::guiDon() { trangThai = CHO_DUYET; }

void DonNghiPhep::pheDuyet() {
    if (trangThai != CHO_DUYET) throw "Don nay da duoc xu ly.";
    trangThai = DA_DUYET;
}

void DonNghiPhep::tuChoi() {
    if (trangThai != CHO_DUYET) throw "Don nay da duoc xu ly.";
    trangThai = TU_CHOI;
}

void DonNghiPhep::hienThi() const {
    cout << "  [" << maDon << "] NV " << maNV << " | " << loaiPhep << " | " << tuNgay << " -> "
         << denNgay << " (" << soNgay << " ngay) | Ly do: " << lyDo
         << " | " << trangThaiString() << "\n";
}

void DonNghiPhep::ghiFile(ostream& os) const {
    os << maDon << "|" << maNV << "|" << loaiPhep << "|" << tuNgay << "|" << denNgay << "|"
       << soNgay << "|" << lyDo << "|" << (int)trangThai << "\n";
}
