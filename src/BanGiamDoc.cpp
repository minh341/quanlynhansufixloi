#include "BanGiamDoc.h"
#include "TienIch.h"
#include <iomanip>

BanGiamDoc::BanGiamDoc() {}

BanGiamDoc::BanGiamDoc(const NhanVien& nv, const string& capQuanLy) : NhanVien(nv) {
    this->capQuanLy = capQuanLy;
}

string BanGiamDoc::getCapQuanLy() const { return capQuanLy; }
void BanGiamDoc::setCapQuanLy(const string& cap) { capQuanLy = cap; }

void BanGiamDoc::xemThongTin() const {
    NhanVien::xemThongTin();
    cout << "Cap quan ly    : " << capQuanLy << "\n";
}

string BanGiamDoc::vaiTro() const { return "Ban giam doc"; }
int BanGiamDoc::loaiNhanVien() const { return LOAI_BGD; }

double BanGiamDoc::tinhPhuCapQuanLy() const {
    if (capQuanLy == "Giam doc") return 10000000;
    if (capQuanLy == "Truong phong") return 5000000;
    return 3000000;
}

void BanGiamDoc::ghiFile(ostream& os) const {
    os << "BGD|";
    ghiTruongCoBan(os);
    os << "|" << capQuanLy << "\n";
}

// [Chương 6] Các điều kiện không hợp lệ được báo bằng throw, nơi gọi dùng try / catch.
void BanGiamDoc::pheDuyetNghiPhep(DonNghiPhep& don, NhanVien& nguoiGui) {
    if (don.getMaNV() != nguoiGui.getMaNV()) throw "Don khong thuoc nhan vien nay.";
    if (nguoiGui.getMaNV() == getMaNV()) throw "Khong the tu duyet don cua chinh minh.";
    if (don.getTrangThai() != CHO_DUYET) throw "Don nay da duoc xu ly.";
    // Chỉ "Phep nam" mới trừ vào quỹ phép năm; nghỉ ốm / việc riêng được duyệt mà không trừ
    bool truPhepNam = (don.getLoaiPhep() == "Phep nam");
    if (truPhepNam && nguoiGui.soNgayPhepConLai() < don.getSoNgay()) throw "Khong du phep nam de duyet don nay.";
    don.pheDuyet();
    if (truPhepNam) nguoiGui.truPhep(don.getSoNgay());
}

void BanGiamDoc::tuChoiNghiPhep(DonNghiPhep& don) { don.tuChoi(); }

void BanGiamDoc::xemDonChoDuyet(const DonNghiPhep dsDon[], int soDon) const {
    int dem = 0;
    for (int i = 0; i < soDon; i++) {
        if (dsDon[i].getTrangThai() == CHO_DUYET) {
            dsDon[i].hienThi();
            dem++;
        }
    }
    if (dem == 0) cout << "  Khong co don nao dang cho duyet.\n";
}

void BanGiamDoc::xemBaoCaoLuong(const BangLuong dsBL[], int n) const {
    double tong = 0;
    int soNguoi = 0;
    cout << left << setw(10) << "Ma NV" << setw(12) << "Ngay cong" << "Thuc nhan\n";
    for (int i = 0; i < n; i++) {
        if (dsBL[i].getSoNgayCong() <= 0) continue;
        cout << left << setw(10) << dsBL[i].getMaNV() << setw(12) << dinhDangCong(dsBL[i].getSoNgayCong());
        inTien(cout, dsBL[i].getThucNhan());
        cout << "\n";
        tong += dsBL[i].getThucNhan();
        soNguoi++;
    }
    cout << "So nhan vien co cong : " << soNguoi << "\n"
         << "Tong quy luong       : ";
    inTien(cout, tong);
    cout << " VND\n";
}
