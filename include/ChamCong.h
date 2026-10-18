#ifndef CHAMCONG_H
#define CHAMCONG_H
#include <string>
#include <iostream>
using namespace std;

// [Chương 2] Một bản ghi chấm công của 1 nhân viên trong 1 ngày.
// Giờ lưu dạng "HH:MM"; số phút đi muộn / về sớm / tăng ca tự tính từ ca chuẩn 08:00 - 17:00.
class ChamCong {
private:
    string maCC, maNV, ngay;      // ngày: "dd/mm/yyyy"
    string gioVao, gioRa;         // "HH:MM"
    double soGioTangCa;
    int diMuon, veSom;            // đơn vị: phút

    static int chuyenPhut(const string& hhmm);   // phương thức tĩnh: "08:30" -> 510

public:
    ChamCong();
    ChamCong(const string& maCC, const string& maNV, const string& ngay);

    string getMaNV() const;
    string getNgay() const;
    int getThang() const;
    int getNam() const;
    double getSoGioTangCa() const;
    int getDiMuon() const;
    int getVeSom() const;

    void ghiNhanCong(const string& gioVao, const string& gioRa);   // tự tính muộn / sớm / tăng ca
    double tinhGioLam() const;    // trừ 1 giờ nghỉ trưa nếu làm trên 5 giờ
    double tinhCong() const;      // 1 công (>= 7 giờ làm), 0.5 công (>= 3.5 giờ), còn lại 0

    void hienThi() const;
    void ghiFile(ostream& os) const;
};

#endif
