#ifndef TIENICH_H
#define TIENICH_H
#include <string>
#include <iostream>
using namespace std;

// ===== Hàm tiện ích dùng chung (không thuộc lớp nào) =====
void inTien(ostream& os, double so);        // in số tiền có dấu phẩy: 12345678 -> 12,345,678
string soThanhChuoi(long long n);           // 25 -> "25"
string dinhDangCong(double cong);           // 22 -> "22", 21.5 -> "21.5" (số công là bội của 0.5)
string chuThuong(string s);                 // đổi sang chữ thường (để tìm kiếm không phân biệt hoa/thường)
string lamSach(string s);                   // đổi ký tự '|' thành '/' (vì '|' là ký tự phân cách trong file)
int tach(const string& dong, char c, string f[], int toiDa);  // tách 1 dòng theo ký tự c, trả về số trường
int soNgayTrongThang(int thang, int nam);   // có xét năm nhuận
bool hopLeNgay(const string& s);            // đúng dạng dd/mm/yyyy và là ngày có thật trong lịch
bool hopLeGio(const string& s);             // đúng dạng HH:MM

#endif
