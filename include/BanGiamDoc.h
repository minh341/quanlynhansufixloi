#ifndef BANGIAMDOC_H
#define BANGIAMDOC_H
#include <vector>
#include "NhanVien.h"
#include "DonNghiPhep.h"
#include "BangLuong.h"

class BanGiamDoc : public NhanVien {
private:
    string capQuanLy;

public:
    BanGiamDoc();
    BanGiamDoc(const NhanVien& nv, const string& capQuanLy);

    string getCapQuanLy() const;
    void setCapQuanLy(const string& cap);

    virtual void xemThongTin() const;
    virtual string vaiTro() const;
    virtual int loaiNhanVien() const;
    virtual double tinhPhuCapQuanLy() const;
    virtual void ghiFile(ostream& os) const;

    void pheDuyetNghiPhep(DonNghiPhep& don, NhanVien& nguoiGui);
    void tuChoiNghiPhep(DonNghiPhep& don);
    void xemDonChoDuyet(const vector<DonNghiPhep>& dsDon) const;
    void xemBaoCaoLuong(const vector<BangLuong>& dsBL) const;
};

#endif
