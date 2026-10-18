#include "TienIch.h"
#include <cctype>
#include <cstdlib>

string soThanhChuoi(long long n) {
    if (n == 0) return "0";
    bool am = n < 0;
    if (am) n = -n;
    string s = "";
    while (n > 0) {
        s = char('0' + n % 10) + s;   // thêm chữ số vào đầu chuỗi
        n = n / 10;
    }
    if (am) s = "-" + s;
    return s;
}

void inTien(ostream& os, double so) {
    long long v;
    if (so < 0) v = -(long long)(-so + 0.5);   // làm tròn đến đồng
    else v = (long long)(so + 0.5);
    string s = soThanhChuoi(v < 0 ? -v : v);
    for (int i = (int)s.size() - 3; i > 0; i -= 3)
        s.insert(i, ",");                      // chèn dấu phẩy mỗi 3 chữ số
    if (v < 0) os << "-";
    os << s;
}

string dinhDangCong(double cong) {
    long long nguyen = (long long)cong;
    bool nuaCong = (cong - nguyen) >= 0.25;
    return soThanhChuoi(nguyen) + (nuaCong ? ".5" : "");
}

string chuThuong(string s) {
    for (int i = 0; i < (int)s.size(); i++)
        s[i] = (char)tolower((unsigned char)s[i]);
    return s;
}

string lamSach(string s) {
    for (int i = 0; i < (int)s.size(); i++)
        if (s[i] == '|') s[i] = '/';
    return s;
}

int tach(const string& dong, char c, string f[], int toiDa) {
    int dem = 0;
    size_t dau = 0;
    while (dem < toiDa) {
        size_t vt = dong.find(c, dau);
        if (vt == string::npos) {
            f[dem++] = dong.substr(dau);   // trường cuối cùng (có thể rỗng)
            break;
        }
        f[dem++] = dong.substr(dau, vt - dau);
        dau = vt + 1;
    }
    return dem;
}

int soNgayTrongThang(int thang, int nam) {
    switch (thang) {
        case 4: case 6: case 9: case 11:
            return 30;
        case 2: {
            bool nhuan = (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
            return nhuan ? 29 : 28;
        }
        default:
            return 31;
    }
}

bool hopLeNgay(const string& s) {
    if (s.size() != 10 || s[2] != '/' || s[5] != '/') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 2 || i == 5) continue;
        if (!isdigit((unsigned char)s[i])) return false;
    }
    int d = atoi(s.substr(0, 2).c_str());
    int m = atoi(s.substr(3, 2).c_str());
    int y = atoi(s.substr(6, 4).c_str());
    if (m < 1 || m > 12 || y < 1900 || y > 2100) return false;
    return d >= 1 && d <= soNgayTrongThang(m, y);   // loại 31/02, 31/04, 29/02 năm thường...
}

bool hopLeGio(const string& s) {
    if (s.size() != 5 || s[2] != ':') return false;
    for (int i = 0; i < 5; i++) {
        if (i == 2) continue;
        if (!isdigit((unsigned char)s[i])) return false;
    }
    int h = atoi(s.substr(0, 2).c_str());
    int m = atoi(s.substr(3, 2).c_str());
    return h >= 0 && h < 24 && m >= 0 && m < 60;
}
