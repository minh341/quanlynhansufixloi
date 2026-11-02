#ifndef NHANVIEN_H
#define NHANVIEN_H
#include <string>
#include <iostream>
using namespace std;

const int LOAI_THUONG = 0;
const int LOAI_QLNS = 1;
const int LOAI_BGD = 2;

class NhanVien {
private:
    string maNV, hoTen, ngaySinh, gioiTinh, cccd;
    string diaChi, soDienThoai, email, ngayVaoLam, trangThai;
    string maPB;
    string maCD;
    int soNgayPhepNam;
    int soNgayPhepDaDung;
    static int soDoiTuong;

protected:
    void ghiTruongCoBan(ostream& os) const;

public:
    NhanVien();
    NhanVien(const string& maNV, const string& hoTen, const string& ngaySinh,
             const string& gioiTinh, const string& cccd, const string& diaChi,
             const string& soDienThoai, const string& email, const string& ngayVaoLam,
             const string& maPB, const string& maCD);
    NhanVien(const NhanVien& nv);
    virtual ~NhanVien();

    static int demNhanVien();

    string getMaNV() const;
    string getHoTen() const;
    string getCCCD() const;
    string getMaPB() const;
    string getMaCD() const;
    string getTrangThai() const;
    int getSoNgayPhepNam() const;
    int soNgayPhepConLai() const;

    void setHoTen(const string& ten);
    void setDiaChi(const string& dc);
    void setSoDienThoai(const string& sdt);
    void setEmail(const string& mail);
    void setMaPB(const string& ma);
    void setMaCD(const string& ma);
    void setTrangThai(const string& tt);
    void setSoNgayPhepNam(int n);
    void setSoNgayPhepDaDung(int n);

    bool truPhep(int soNgay);

    virtual void xemThongTin() const;
    virtual string vaiTro() const;
    virtual int loaiNhanVien() const;
    virtual double tinhPhuCapQuanLy() const;
    virtual void ghiFile(ostream& os) const;

    friend ostream& operator<<(ostream& os, const NhanVien& nv);
};

#endif
