#ifndef BANGIAMDOC_H
#define BANGIAMDOC_H
#include "NhanVien.h"
#include "DonNghiPhep.h"
#include "BangLuong.h"

// [Chương 3] KẾ THỪA public từ NhanVien: bổ sung capQuanLy, quyền phê duyệt nghỉ phép, xem báo cáo.
// [Chương 4] Định nghĩa lại các hàm ảo của lớp cơ sở.
// [Chương 6] pheDuyetNghiPhep() ném ngoại lệ (throw) khi không hợp lệ.
class BanGiamDoc : public NhanVien {
private:
    string capQuanLy;   // ví dụ: "Giam doc", "Truong phong"

public:
    BanGiamDoc();
    BanGiamDoc(const NhanVien& nv, const string& capQuanLy);

    string getCapQuanLy() const;
    void setCapQuanLy(const string& cap);

    // ---- Hàm ảo định nghĩa lại ----
    virtual void xemThongTin() const;
    virtual string vaiTro() const;
    virtual int loaiNhanVien() const;
    virtual double tinhPhuCapQuanLy() const;
    virtual void ghiFile(ostream& os) const;

    // ---- Nghiệp vụ ----
    void pheDuyetNghiPhep(DonNghiPhep& don, NhanVien& nguoiGui);   // đổi trạng thái đơn + trừ phép; throw nếu không hợp lệ
    void tuChoiNghiPhep(DonNghiPhep& don);
    void xemDonChoDuyet(const DonNghiPhep dsDon[], int soDon) const;
    void xemBaoCaoLuong(const BangLuong dsBL[], int n) const;      // tổng quỹ lương
};

#endif
