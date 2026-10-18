#ifndef DONNGHIPHEP_H
#define DONNGHIPHEP_H
#include <string>
#include <iostream>
using namespace std;

enum TrangThaiDon { CHO_DUYET, DA_DUYET, TU_CHOI };

// [Chương 2] Đơn xin nghỉ phép: nhân viên gửi -> Ban Giám đốc duyệt / từ chối.
// [Chương 6] pheDuyet() và tuChoi() ném ngoại lệ (throw) nếu đơn đã được xử lý.
class DonNghiPhep {
private:
    string maDon, maNV, loaiPhep;
    string tuNgay, denNgay, lyDo;   // "dd/mm/yyyy"
    int soNgay;
    TrangThaiDon trangThai;

public:
    DonNghiPhep();
    DonNghiPhep(const string& maDon, const string& maNV, const string& loaiPhep,
                const string& tuNgay, const string& denNgay, int soNgay, const string& lyDo);

    string getMaDon() const;
    string getMaNV() const;
    string getLoaiPhep() const;   // "Phep nam", "Nghi om", "Viec rieng"
    int getSoNgay() const;
    TrangThaiDon getTrangThai() const;
    void setTrangThai(TrangThaiDon tt);
    string trangThaiString() const;

    void guiDon();       // đặt trạng thái = chờ duyệt
    void pheDuyet();     // throw nếu đơn không ở trạng thái chờ duyệt
    void tuChoi();       // throw nếu đơn không ở trạng thái chờ duyệt

    void hienThi() const;
    void ghiFile(ostream& os) const;
};

#endif
