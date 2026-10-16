#include "NhanVien.h"
#include <iomanip>

int NhanVien::soDoiTuong = 0;   // định nghĩa thành phần tĩnh bên ngoài lớp

NhanVien::NhanVien() {
    trangThai = "Dang lam";
    soNgayPhepNam = 12;
    soNgayPhepDaDung = 0;
    soDoiTuong++;
}

NhanVien::NhanVien(const string& maNV, const string& hoTen, const string& ngaySinh,
                   const string& gioiTinh, const string& cccd, const string& diaChi,
                   const string& soDienThoai, const string& email, const string& ngayVaoLam,
                   const string& maPB, const string& maCD) {
    this->maNV = maNV;
    this->hoTen = hoTen;
    this->ngaySinh = ngaySinh;
    this->gioiTinh = gioiTinh;
    this->cccd = cccd;
    this->diaChi = diaChi;
    this->soDienThoai = soDienThoai;
    this->email = email;
    this->ngayVaoLam = ngayVaoLam;
    this->maPB = maPB;
    this->maCD = maCD;
    trangThai = "Dang lam";
    soNgayPhepNam = 12;
    soNgayPhepDaDung = 0;
    soDoiTuong++;
}

NhanVien::NhanVien(const NhanVien& nv) {
    maNV = nv.maNV;
    hoTen = nv.hoTen;
    ngaySinh = nv.ngaySinh;
    gioiTinh = nv.gioiTinh;
    cccd = nv.cccd;
    diaChi = nv.diaChi;
    soDienThoai = nv.soDienThoai;
    email = nv.email;
    ngayVaoLam = nv.ngayVaoLam;
    trangThai = nv.trangThai;
    maPB = nv.maPB;
    maCD = nv.maCD;
    soNgayPhepNam = nv.soNgayPhepNam;
    soNgayPhepDaDung = nv.soNgayPhepDaDung;
    soDoiTuong++;
}

NhanVien::~NhanVien() { soDoiTuong--; }

int NhanVien::demNhanVien() { return soDoiTuong; }

// ---- Getter ----
string NhanVien::getMaNV() const { return maNV; }
string NhanVien::getHoTen() const { return hoTen; }
string NhanVien::getMaPB() const { return maPB; }
string NhanVien::getMaCD() const { return maCD; }
string NhanVien::getTrangThai() const { return trangThai; }
int NhanVien::getSoNgayPhepNam() const { return soNgayPhepNam; }
int NhanVien::soNgayPhepConLai() const { return soNgayPhepNam - soNgayPhepDaDung; }

// ---- Setter ----
void NhanVien::setHoTen(const string& ten) { hoTen = ten; }
void NhanVien::setDiaChi(const string& dc) { diaChi = dc; }
void NhanVien::setSoDienThoai(const string& sdt) { soDienThoai = sdt; }
void NhanVien::setEmail(const string& mail) { email = mail; }
void NhanVien::setMaPB(const string& ma) { maPB = ma; }
void NhanVien::setMaCD(const string& ma) { maCD = ma; }
void NhanVien::setTrangThai(const string& tt) { trangThai = tt; }
void NhanVien::setSoNgayPhepNam(int n) { soNgayPhepNam = n; }
void NhanVien::setSoNgayPhepDaDung(int n) { soNgayPhepDaDung = n; }

// ---- Nghiệp vụ ----
bool NhanVien::truPhep(int soNgay) {
    if (soNgay <= 0 || soNgay > soNgayPhepConLai()) return false;
    soNgayPhepDaDung += soNgay;
    return true;
}

// ---- Các hàm ảo ----
void NhanVien::xemThongTin() const {
    cout << "----------- HO SO NHAN VIEN -----------\n"
         << "Ma NV          : " << maNV << "\n"
         << "Ho ten         : " << hoTen << "\n"
         << "Vai tro        : " << vaiTro() << "\n"
         << "Ngay sinh      : " << ngaySinh << "\n"
         << "Gioi tinh      : " << gioiTinh << "\n"
         << "CCCD           : " << cccd << "\n"
         << "Dia chi        : " << diaChi << "\n"
         << "So dien thoai  : " << soDienThoai << "\n"
         << "Email          : " << email << "\n"
         << "Ngay vao lam   : " << ngayVaoLam << "\n"
         << "Trang thai     : " << trangThai << "\n"
         << "Phong ban      : " << maPB << "\n"
         << "Chuc danh      : " << maCD << "\n"
         << "Phep con lai   : " << soNgayPhepConLai() << "/" << soNgayPhepNam << " ngay\n";
}

string NhanVien::vaiTro() const { return "Nhan vien"; }
int NhanVien::loaiNhanVien() const { return LOAI_THUONG; }
double NhanVien::tinhPhuCapQuanLy() const { return 0; }

void NhanVien::ghiTruongCoBan(ostream& os) const {
    os << maNV << "|" << hoTen << "|" << ngaySinh << "|" << gioiTinh << "|" << cccd << "|"
       << diaChi << "|" << soDienThoai << "|" << email << "|" << ngayVaoLam << "|" << trangThai << "|"
       << maPB << "|" << maCD << "|" << soNgayPhepNam << "|" << soNgayPhepDaDung;
}

void NhanVien::ghiFile(ostream& os) const {
    os << "NV|";
    ghiTruongCoBan(os);
    os << "\n";
}

ostream& operator<<(ostream& os, const NhanVien& nv) {
    os << left << setw(8) << nv.maNV << setw(24) << nv.hoTen << setw(18) << nv.vaiTro()
       << setw(8) << nv.maPB << setw(8) << nv.maCD << nv.trangThai;
    return os;
}
