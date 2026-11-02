#ifndef TIENICH_H
#define TIENICH_H
#include <string>
#include <iostream>
using namespace std;

void inTien(ostream& os, double so);
string soThanhChuoi(long long n);
string dinhDangCong(double cong);
string chuThuong(string s);
string lamSach(string s);
int tach(const string& dong, char c, string f[], int toiDa);
int soNgayTrongThang(int thang, int nam);
bool hopLeNgay(const string& s);
bool hopLeGio(const string& s);
long long ngaySangSo(const string& s);
int soSanhNgay(const string& ngay1, const string& ngay2);

#endif
