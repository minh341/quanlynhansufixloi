// ============================================================
//  HE THONG QUAN LY NHAN SU (HRMS) - Bai tap lon OOP (C++)
//  Dang nhap bang ma nhan vien; menu thay doi theo vai tro.
//
//  Cac ky thuat theo chuong:
//   [Chuong 2] lop, doi tuong, ham tao/huy, ham ban, thanh phan tinh, mang doi tuong, con tro
//   [Chuong 3] ke thua: NhanVien -> QuanLyNhanSu, BanGiamDoc
//   [Chuong 4] ham ao, da hinh (con tro lop co so), khuon hinh ham (ghiMang)
//   [Chuong 5] dong du lieu vao ra: cin/cout, iomanip, doc/ghi file (ifstream/ofstream)
//   [Chuong 6] xu ly ngoai le: throw / try / catch
// ============================================================
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cstdlib>

#include "TienIch.h"
#include "NhanVien.h"
#include "QuanLyNhanSu.h"
#include "BanGiamDoc.h"
#include "PhongBan.h"
#include "ChucDanh.h"
#include "ChamCong.h"
#include "BangLuong.h"
#include "DonNghiPhep.h"
using namespace std;

const string THU_MUC = "data/";

// ---------------- Du lieu chung (dung mang + bien dem) ----------------
struct DuLieu {
    NhanVien* dsNV[MAX_NV];     // mang con tro: so huu cac doi tuong NhanVien (delete trong ham huy)
    int soNV;
    PhongBan dsPB[MAX_PB];
    int soPB;
    ChucDanh dsCD[MAX_CD];
    int soCD;
    ChamCong dsCC[MAX_CC];
    int soCC;
    DonNghiPhep dsDon[MAX_DON];
    int soDon;

    DuLieu() {
        soNV = 0; soPB = 0; soCD = 0; soCC = 0; soDon = 0;
        for (int i = 0; i < MAX_NV; i++) dsNV[i] = NULL;
    }
    ~DuLieu() {
        for (int i = 0; i < soNV; i++) delete dsNV[i];
    }
};

// ---------------- Tien ich nhap / xuat ----------------
// [Chuong 6] Het du lieu nhap (Ctrl+D / Ctrl+Z) -> throw 0, main bat va luu du lieu truoc khi thoat
string nhapDong(const string& nhan) {
    cout << nhan;
    string s;
    if (!getline(cin, s)) throw 0;
    return lamSach(s);
}

int nhapSo(const string& nhan, int lo, int hi) {
    while (true) {
        string s = nhapDong(nhan);
        bool hopLe = !s.empty() && s.size() <= 9;
        for (int i = 0; i < (int)s.size(); i++)
            if (s[i] < '0' || s[i] > '9') hopLe = false;
        if (hopLe) {
            int v = atoi(s.c_str());
            if (v >= lo && v <= hi) return v;
        }
        cout << "  Gia tri khong hop le (" << lo << " - " << hi << "). Nhap lai.\n";
    }
}

string nhapNgay(const string& nhan) {
    while (true) {
        string s = nhapDong(nhan);
        if (hopLeNgay(s)) return s;
        cout << "  Ngay phai co dang dd/mm/yyyy.\n";
    }
}

string nhapGio(const string& nhan) {
    while (true) {
        string s = nhapDong(nhan);
        if (hopLeGio(s)) return s;
        cout << "  Gio phai co dang HH:MM.\n";
    }
}

void tieuDe(const string& s) { cout << "\n=== " << s << " ===\n"; }

// ---------------- Tim kiem ----------------
PhongBan* timPB(DuLieu& d, const string& ma) {
    for (int i = 0; i < d.soPB; i++)
        if (d.dsPB[i].getMaPB() == ma) return &d.dsPB[i];
    return NULL;
}

const ChucDanh* timCD(const DuLieu& d, const string& ma) {
    for (int i = 0; i < d.soCD; i++)
        if (d.dsCD[i].getMaCD() == ma) return &d.dsCD[i];
    return NULL;
}

NhanVien* timNV(DuLieu& d, const string& ma) {
    for (int i = 0; i < d.soNV; i++)
        if (d.dsNV[i]->getMaNV() == ma) return d.dsNV[i];
    return NULL;
}

// ---------------- [Chuong 5] Doc / ghi file ----------------
void boXuongDong(string& dong) {   // bo ky tu '\r' neu file tao tren Windows
    if (!dong.empty() && dong[dong.size() - 1] == '\r') dong.erase(dong.size() - 1);
}

void docDuLieu(DuLieu& d) {
    string dong, f[20];
    int k;
    {   // chuc danh: maCD|tenCD|luongCoBan|phuCap
        ifstream in((THU_MUC + "chucdanh.txt").c_str());
        while (getline(in, dong)) {
            boXuongDong(dong);
            if (dong.empty()) continue;
            k = tach(dong, '|', f, 20);
            if (k < 4) continue;
            if (d.soCD >= MAX_CD) throw "Du lieu chuc danh vuot qua gioi han.";
            d.dsCD[d.soCD++] = ChucDanh(f[0], f[1], atof(f[2].c_str()), atof(f[3].c_str()));
        }
    }
    {   // phong ban: maPB|tenPB|moTa
        ifstream in((THU_MUC + "phongban.txt").c_str());
        while (getline(in, dong)) {
            boXuongDong(dong);
            if (dong.empty()) continue;
            k = tach(dong, '|', f, 20);
            if (k < 3) continue;
            if (d.soPB >= MAX_PB) throw "Du lieu phong ban vuot qua gioi han.";
            d.dsPB[d.soPB++] = PhongBan(f[0], f[1], f[2]);
        }
    }
    {   // nhan vien: loai|maNV|hoTen|ngaySinh|gioiTinh|cccd|diaChi|sdt|email|ngayVaoLam|trangThai|maPB|maCD|phepNam|phepDaDung[|truongRieng]
        ifstream in((THU_MUC + "nhanvien.txt").c_str());
        while (getline(in, dong)) {
            boXuongDong(dong);
            if (dong.empty()) continue;
            k = tach(dong, '|', f, 20);
            if (k < 15) continue;
            if (d.soNV >= MAX_NV) throw "Du lieu nhan vien vuot qua gioi han.";
            NhanVien base(f[1], f[2], f[3], f[4], f[5], f[6], f[7], f[8], f[9], f[11], f[12]);
            NhanVien* p;
            if (f[0] == "QL" && k >= 16) p = new QuanLyNhanSu(base, f[15]);
            else if (f[0] == "BGD" && k >= 16) p = new BanGiamDoc(base, f[15]);
            else p = new NhanVien(base);
            p->setTrangThai(f[10]);
            p->setSoNgayPhepNam(atoi(f[13].c_str()));
            p->setSoNgayPhepDaDung(atoi(f[14].c_str()));
            d.dsNV[d.soNV++] = p;
        }
    }
    for (int i = 0; i < d.soNV; i++) {   // dung lai quan he PhongBan -> NhanVien
        PhongBan* pb = timPB(d, d.dsNV[i]->getMaPB());
        if (pb != NULL) pb->themNhanVien(d.dsNV[i]);
    }
    {   // cham cong: maCC|maNV|ngay|gioVao|gioRa
        ifstream in((THU_MUC + "chamcong.txt").c_str());
        while (getline(in, dong)) {
            boXuongDong(dong);
            if (dong.empty()) continue;
            k = tach(dong, '|', f, 20);
            if (k < 5) continue;
            if (d.soCC >= MAX_CC) throw "Du lieu cham cong vuot qua gioi han.";
            ChamCong cc(f[0], f[1], f[2]);
            if (!f[3].empty() && !f[4].empty()) cc.ghiNhanCong(f[3], f[4]);
            d.dsCC[d.soCC++] = cc;
        }
    }
    {   // don nghi phep: maDon|maNV|loaiPhep|tuNgay|denNgay|soNgay|lyDo|trangThai
        ifstream in((THU_MUC + "donnghiphep.txt").c_str());
        while (getline(in, dong)) {
            boXuongDong(dong);
            if (dong.empty()) continue;
            k = tach(dong, '|', f, 20);
            if (k < 8) continue;
            if (d.soDon >= MAX_DON) throw "Du lieu don nghi phep vuot qua gioi han.";
            DonNghiPhep dn(f[0], f[1], f[2], f[3], f[4], atoi(f[5].c_str()), f[6]);
            dn.setTrangThai((TrangThaiDon)atoi(f[7].c_str()));
            d.dsDon[d.soDon++] = dn;
        }
    }
}

// [Chuong 4] Khuon hinh ham: ghi mang doi tuong bat ky co ham ghiFile(ostream&)
template <typename T>
void ghiMang(const string& tenFile, const T ds[], int n) {
    ofstream out((THU_MUC + tenFile).c_str());
    if (!out) throw "Khong ghi duoc vao thu muc data/. Hay chay chuong trinh tu thu muc HRMS.";
    for (int i = 0; i < n; i++) ds[i].ghiFile(out);
}

void luuDuLieu(const DuLieu& d) {
    ofstream out((THU_MUC + "nhanvien.txt").c_str());
    if (!out) throw "Khong ghi duoc vao thu muc data/. Hay chay chuong trinh tu thu muc HRMS.";
    for (int i = 0; i < d.soNV; i++) d.dsNV[i]->ghiFile(out);   // ham ao -> ghi dung loai
    out.close();
    ghiMang("phongban.txt", d.dsPB, d.soPB);
    ghiMang("chucdanh.txt", d.dsCD, d.soCD);
    ghiMang("chamcong.txt", d.dsCC, d.soCC);
    ghiMang("donnghiphep.txt", d.dsDon, d.soDon);
    cout << "[Da luu du lieu vao thu muc data/]\n";
}

void taoDuLieuMau(DuLieu& d) {
    d.dsCD[0] = ChucDanh("CD01", "Nhan vien", 8000000, 500000);
    d.dsCD[1] = ChucDanh("CD02", "Chuyen vien", 12000000, 1000000);
    d.dsCD[2] = ChucDanh("CD03", "Truong phong", 20000000, 3000000);
    d.dsCD[3] = ChucDanh("CD04", "Giam doc", 40000000, 5000000);
    d.soCD = 4;
    d.dsPB[0] = PhongBan("PB01", "Phong Nhan su", "Tuyen dung, ho so, luong");
    d.dsPB[1] = PhongBan("PB02", "Phong Ke toan", "Tai chinh, ke toan");
    d.dsPB[2] = PhongBan("PB03", "Phong Kinh doanh", "Ban hang, cham soc khach hang");
    d.dsPB[3] = PhongBan("PB04", "Ban Giam doc", "Dieu hanh cong ty");
    d.soPB = 4;

    NhanVien a("NV001", "Nguyen Van An", "12/03/1992", "Nam", "001092000111", "Ha Noi",
               "0901000001", "an@congty.vn", "01/02/2020", "PB01", "CD02");
    NhanVien b("NV002", "Tran Thi Binh", "25/07/1985", "Nu", "001085000222", "Ha Noi",
               "0901000002", "binh@congty.vn", "01/01/2018", "PB04", "CD04");
    NhanVien c("NV003", "Le Van Cuong", "05/11/1998", "Nam", "001098000333", "Hai Phong",
               "0901000003", "cuong@congty.vn", "15/06/2023", "PB02", "CD01");
    NhanVien e("NV004", "Pham Thi Dung", "30/01/1999", "Nu", "001099000444", "Nam Dinh",
               "0901000004", "dung@congty.vn", "10/09/2023", "PB03", "CD01");
    NhanVien g("NV005", "Hoang Van Em", "18/09/1988", "Nam", "001088000555", "Ha Noi",
               "0901000005", "em@congty.vn", "01/03/2019", "PB03", "CD03");
    d.dsNV[0] = new QuanLyNhanSu(a, "Tuyen dung");
    d.dsNV[1] = new BanGiamDoc(b, "Giam doc");
    d.dsNV[2] = new NhanVien(c);
    d.dsNV[3] = new NhanVien(e);
    d.dsNV[4] = new BanGiamDoc(g, "Truong phong");
    d.soNV = 5;
    for (int i = 0; i < d.soNV; i++) {
        PhongBan* pb = timPB(d, d.dsNV[i]->getMaPB());
        if (pb != NULL) pb->themNhanVien(d.dsNV[i]);
    }
    // Cham cong mau thang 09/2026 (22 ngay) cho moi nhan vien
    for (int i = 0; i < d.soNV; i++) {
        for (int ngay = 1; ngay <= 22; ngay++) {
            string ngayStr = soThanhChuoi(ngay / 10) + soThanhChuoi(ngay % 10) + "/09/2026";
            string ma = d.dsNV[i]->getMaNV();
            ChamCong cc("CC" + ma + "_" + ngayStr, ma, ngayStr);
            cc.ghiNhanCong(ngay % 5 == 0 ? "08:15" : "08:00", ngay % 4 == 0 ? "19:00" : "17:00");
            d.dsCC[d.soCC++] = cc;
        }
    }
    d.dsDon[0] = DonNghiPhep("DN1", "NV003", "Phep nam", "20/10/2026", "21/10/2026", 2, "Ve que");
    d.soDon = 1;
}

// ---------------- Chuc nang chung (moi vai tro) ----------------
void xemBangLuongCuaToi(DuLieu& d, NhanVien* user) {
    tieuDe("BANG LUONG CUA TOI");
    int thang = nhapSo("Thang (1-12): ", 1, 12);
    int nam = nhapSo("Nam: ", 2000, 2100);
    const ChucDanh* cd = timCD(d, user->getMaCD());
    if (cd == NULL) { cout << "Chua co chuc danh hop le.\n"; return; }
    BangLuong bl("BL" + user->getMaNV(), user->getMaNV(), thang, nam);
    bl.tinhLuong(*user, *cd, d.dsCC, d.soCC);
    if (bl.getSoNgayCong() <= 0) cout << "Chua co du lieu cham cong thang nay.\n";
    else bl.inPhieuLuong();
}

void guiDonNghiPhep(DuLieu& d, NhanVien* user) {
    tieuDe("GUI DON NGHI PHEP");
    if (d.soDon >= MAX_DON) throw "Danh sach don nghi phep da day.";
    cout << "Phep con lai: " << user->soNgayPhepConLai() << " ngay\n";
    int loai = nhapSo("Loai phep (1=Phep nam, 2=Nghi om, 3=Viec rieng): ", 1, 3);
    string ten[4] = {"", "Phep nam", "Nghi om", "Viec rieng"};
    string tu = nhapNgay("Tu ngay (dd/mm/yyyy): ");
    string den = nhapNgay("Den ngay (dd/mm/yyyy): ");
    int soNgay = nhapSo("So ngay nghi (1-30): ", 1, 30);
    string lyDo = nhapDong("Ly do: ");
    int lonNhat = 0;   // mã đơn mới = số lớn nhất đang có + 1 (không trùng kể cả khi đã xóa bớt đơn)
    for (int i = 0; i < d.soDon; i++) {
        string maCu = d.dsDon[i].getMaDon();
        if (maCu.size() > 2) {
            int so = atoi(maCu.c_str() + 2);
            if (so > lonNhat) lonNhat = so;
        }
    }
    DonNghiPhep dn("DN" + soThanhChuoi(lonNhat + 1), user->getMaNV(), ten[loai], tu, den, soNgay, lyDo);
    dn.guiDon();
    d.dsDon[d.soDon++] = dn;
    cout << "Da gui don " << dn.getMaDon() << ", dang cho Ban giam doc duyet.\n";
}

void xemDonCuaToi(const DuLieu& d, NhanVien* user) {
    tieuDe("DON NGHI PHEP CUA TOI");
    int dem = 0;
    for (int i = 0; i < d.soDon; i++)
        if (d.dsDon[i].getMaNV() == user->getMaNV()) { d.dsDon[i].hienThi(); dem++; }
    if (dem == 0) cout << "  Ban chua gui don nao.\n";
}

// ---------------- Chuc nang Quan ly nhan su ----------------
void inDanhSachNV(const DuLieu& d) {
    cout << left << setw(8) << "Ma" << setw(24) << "Ho ten" << setw(18) << "Vai tro"
         << setw(8) << "PB" << setw(8) << "CD" << "Trang thai\n";
    for (int i = 0; i < d.soNV; i++)
        cout << *d.dsNV[i] << "\n";   // operator<< goi vaiTro() ao
}

// Khi xóa nhân viên: xóa luôn chấm công và đơn nghỉ phép của người đó (tránh dữ liệu mồ côi)
int xoaChamCongCuaNV(DuLieu& d, const string& ma) {
    int giu = 0, daXoa = 0;
    for (int i = 0; i < d.soCC; i++) {
        if (d.dsCC[i].getMaNV() == ma) daXoa++;
        else d.dsCC[giu++] = d.dsCC[i];   // dồn các bản ghi còn lại
    }
    d.soCC = giu;
    return daXoa;
}

int xoaDonCuaNV(DuLieu& d, const string& ma) {
    int giu = 0, daXoa = 0;
    for (int i = 0; i < d.soDon; i++) {
        if (d.dsDon[i].getMaNV() == ma) daXoa++;
        else d.dsDon[giu++] = d.dsDon[i];
    }
    d.soDon = giu;
    return daXoa;
}

void themNhanVien(DuLieu& d, QuanLyNhanSu* ql) {
    tieuDe("THEM NHAN VIEN");
    if (d.soNV >= MAX_NV) throw "Danh sach nhan vien da day.";
    string ma = nhapDong("Ma NV: ");
    if (ma.empty()) return;
    if (timNV(d, ma) != NULL) { cout << "Ma nhan vien da ton tai.\n"; return; }
    string ten = nhapDong("Ho ten: ");
    string ns = nhapNgay("Ngay sinh (dd/mm/yyyy): ");
    string gt = nhapDong("Gioi tinh: ");
    string cccd = nhapDong("CCCD: ");
    string dc = nhapDong("Dia chi: ");
    string sdt = nhapDong("So dien thoai: ");
    string mail = nhapDong("Email: ");
    string nvl = nhapNgay("Ngay vao lam (dd/mm/yyyy): ");
    string maPB = nhapDong("Ma phong ban: ");
    PhongBan* pb = timPB(d, maPB);
    if (pb == NULL) { cout << "Phong ban khong ton tai.\n"; return; }
    string maCD = nhapDong("Ma chuc danh: ");
    if (timCD(d, maCD) == NULL) { cout << "Chuc danh khong ton tai.\n"; return; }
    int loai = nhapSo("Loai (1=Nhan vien, 2=Quan ly nhan su, 3=Ban giam doc): ", 1, 3);

    NhanVien base(ma, ten, ns, gt, cccd, dc, sdt, mail, nvl, maPB, maCD);
    NhanVien* p;
    if (loai == 2) p = new QuanLyNhanSu(base, nhapDong("Chuyen mon: "));
    else if (loai == 3) p = new BanGiamDoc(base, nhapDong("Cap quan ly (Giam doc/Truong phong/...): "));
    else p = new NhanVien(base);
    ql->themNhanVien(d.dsNV, d.soNV, p);
    pb->themNhanVien(p);
    cout << "Da them nhan vien " << ma << ".\n";
}

void menuQuanLyNhanVien(DuLieu& d, QuanLyNhanSu* ql, NhanVien* user) {
    while (true) {
        tieuDe("QUAN LY NHAN VIEN");
        cout << "1. Danh sach nhan vien\n2. Them nhan vien\n3. Sua thong tin\n"
                "4. Xoa nhan vien\n5. Tim theo ten\n6. Xem ho so chi tiet\n0. Quay lai\n";
        int c = nhapSo("Chon: ", 0, 6);
        if (c == 0) return;
        try {
            switch (c) {
            case 1:
                inDanhSachNV(d);
                break;
            case 2:
                themNhanVien(d, ql);
                break;
            case 3: {
                string ma = nhapDong("Ma NV can sua: ");
                if (!ql->suaNhanVien(d.dsNV, d.soNV, ma)) cout << "Khong tim thay.\n";
                else cout << "Da cap nhat.\n";
                break;
            }
            case 4: {
                string ma = nhapDong("Ma NV can xoa: ");
                if (ma == user->getMaNV()) { cout << "Khong the tu xoa tai khoan dang dang nhap.\n"; break; }
                NhanVien* canXoa = timNV(d, ma);
                if (canXoa == NULL) { cout << "Khong tim thay.\n"; break; }
                if (canXoa->loaiNhanVien() == LOAI_BGD) {   // ham ao
                    cout << "Khong the xoa nhan vien thuoc Ban giam doc.\n";
                    break;
                }
                for (int i = 0; i < d.soPB; i++) d.dsPB[i].xoaNhanVien(ma);   // go con tro truoc khi delete
                ql->xoaNhanVien(d.dsNV, d.soNV, ma);
                cout << "Da xoa nhan vien " << ma << ".\n";
                int soCC = xoaChamCongCuaNV(d, ma);
                int soDon = xoaDonCuaNV(d, ma);
                if (soCC > 0 || soDon > 0)
                    cout << "Da xoa kem " << soCC << " ban ghi cham cong va " << soDon << " don nghi phep.\n";
                break;
            }
            case 5: {
                NhanVien* kq[MAX_NV];
                int soKQ = ql->timTheoTen(d.dsNV, d.soNV, nhapDong("Tu khoa: "), kq);
                if (soKQ == 0) cout << "Khong tim thay.\n";
                for (int i = 0; i < soKQ; i++) cout << *kq[i] << "\n";
                break;
            }
            case 6: {
                NhanVien* p = timNV(d, nhapDong("Ma NV: "));
                if (p != NULL) p->xemThongTin();   // DA HINH: moi lop in thong tin rieng
                else cout << "Khong tim thay.\n";
                break;
            }
            }
        } catch (const char* loi) {
            cout << "  " << loi << "\n";
        }
    }
}

void menuPhongBan(DuLieu& d) {
    while (true) {
        tieuDe("QUAN LY PHONG BAN");
        cout << "1. Danh sach phong ban\n2. Xem nhan vien trong phong\n"
                "3. Chuyen nhan vien sang phong khac\n4. Them phong ban\n0. Quay lai\n";
        int c = nhapSo("Chon: ", 0, 4);
        if (c == 0) return;
        try {
            switch (c) {
            case 1:
                for (int i = 0; i < d.soPB; i++) d.dsPB[i].hienThiThongTin();
                break;
            case 2: {
                PhongBan* pb = timPB(d, nhapDong("Ma phong ban: "));
                if (pb != NULL) { pb->hienThiThongTin(); pb->hienThiDanhSach(); }
                else cout << "Khong tim thay.\n";
                break;
            }
            case 3: {
                NhanVien* nv = timNV(d, nhapDong("Ma NV: "));
                if (nv == NULL) { cout << "Khong tim thay nhan vien.\n"; break; }
                PhongBan* moi = timPB(d, nhapDong("Ma phong ban moi: "));
                if (moi == NULL) { cout << "Khong tim thay phong ban.\n"; break; }
                PhongBan* cu = timPB(d, nv->getMaPB());
                moi->themNhanVien(nv);   // throw neu da co trong phong / day
                if (cu != NULL) cu->xoaNhanVien(nv->getMaNV());
                nv->setMaPB(moi->getMaPB());
                cout << "Da chuyen " << nv->getHoTen() << " sang " << moi->getTenPB() << ".\n";
                break;
            }
            case 4: {
                string ma = nhapDong("Ma phong ban: ");
                if (ma.empty() || timPB(d, ma) != NULL) { cout << "Ma rong hoac da ton tai.\n"; break; }
                if (d.soPB >= MAX_PB) throw "Danh sach phong ban da day.";
                string ten = nhapDong("Ten phong ban: ");
                string mt = nhapDong("Mo ta: ");
                d.dsPB[d.soPB++] = PhongBan(ma, ten, mt);
                cout << "Da them phong ban.\n";
                break;
            }
            }
        } catch (const char* loi) {
            cout << "  " << loi << "\n";
        }
    }
}

void menuChamCong(DuLieu& d, QuanLyNhanSu* ql) {
    while (true) {
        tieuDe("CHAM CONG");
        cout << "1. Ghi nhan cong\n2. Xem cham cong cua mot nhan vien\n0. Quay lai\n";
        int c = nhapSo("Chon: ", 0, 2);
        if (c == 0) return;
        try {
            NhanVien* nv = timNV(d, nhapDong("Ma NV: "));
            if (nv == NULL) { cout << "Khong tim thay nhan vien.\n"; continue; }
            if (c == 1) {
                string ngay = nhapNgay("Ngay (dd/mm/yyyy): ");
                string vao = nhapGio("Gio vao (HH:MM): ");
                string ra = nhapGio("Gio ra (HH:MM): ");
                if (ra <= vao) { cout << "Gio ra phai sau gio vao.\n"; continue; }
                ChamCong cc("CC" + nv->getMaNV() + "_" + ngay, nv->getMaNV(), ngay);
                cc.ghiNhanCong(vao, ra);
                ql->ghiNhanChamCong(d.dsCC, d.soCC, cc);
                cout << "Da ghi nhan: di muon " << cc.getDiMuon() << " phut, ve som " << cc.getVeSom()
                     << " phut, tang ca " << fixed << setprecision(1) << cc.getSoGioTangCa()
                     << " gio, cong ghi nhan: " << cc.tinhCong() << ".\n";
            } else {
                int thang = nhapSo("Thang: ", 1, 12);
                int nam = nhapSo("Nam: ", 2000, 2100);
                cout << left << setw(12) << "Ngay" << setw(8) << "Vao" << setw(8) << "Ra"
                     << setw(10) << "Gio lam" << setw(10) << "Muon(p)" << setw(10) << "Som(p)"
                     << setw(12) << "Tang ca(h)" << "Cong\n";
                int dem = 0;
                for (int i = 0; i < d.soCC; i++)
                    if (d.dsCC[i].getMaNV() == nv->getMaNV() && d.dsCC[i].getThang() == thang &&
                        d.dsCC[i].getNam() == nam) {
                        d.dsCC[i].hienThi();
                        dem++;
                    }
                if (dem == 0) cout << "  Khong co du lieu.\n";
            }
        } catch (const char* loi) {
            cout << "  " << loi << "\n";
        }
    }
}

void lapBangLuongTatCa(DuLieu& d, QuanLyNhanSu* ql) {
    tieuDe("LAP BANG LUONG");
    int thang = nhapSo("Thang (1-12): ", 1, 12);
    int nam = nhapSo("Nam: ", 2000, 2100);
    cout << left << setw(8) << "Ma" << setw(24) << "Ho ten" << setw(12) << "Ngay cong" << "Thuc nhan\n";
    BangLuong ds[MAX_NV];
    int soBL = 0;
    for (int i = 0; i < d.soNV; i++) {
        const ChucDanh* cd = timCD(d, d.dsNV[i]->getMaCD());
        if (cd == NULL) continue;
        BangLuong bl = ql->lapBangLuong(*d.dsNV[i], *cd, d.dsCC, d.soCC, thang, nam);
        cout << left << setw(8) << d.dsNV[i]->getMaNV() << setw(24) << d.dsNV[i]->getHoTen()
             << setw(12) << dinhDangCong(bl.getSoNgayCong());
        inTien(cout, bl.getThucNhan());
        cout << "\n";
        ds[soBL++] = bl;
    }
    string ma = nhapDong("Nhap ma NV de xem phieu luong chi tiet (Enter de bo qua): ");
    for (int i = 0; i < soBL; i++)
        if (ds[i].getMaNV() == ma) { ds[i].inPhieuLuong(); return; }
}

void thongKe(const DuLieu& d) {
    tieuDe("THONG KE");
    cout << "Tong so nhan vien: " << NhanVien::demNhanVien() << "\n";   // phuong thuc tinh
    int ql = 0, bgd = 0, nv = 0;
    for (int i = 0; i < d.soNV; i++) {
        int loai = d.dsNV[i]->loaiNhanVien();   // ham ao
        if (loai == LOAI_QLNS) ql++;
        else if (loai == LOAI_BGD) bgd++;
        else nv++;
    }
    cout << "  Nhan vien: " << nv << " | Quan ly nhan su: " << ql << " | Ban giam doc: " << bgd << "\n";
    cout << "So nhan vien theo phong ban:\n";
    for (int i = 0; i < d.soPB; i++)
        cout << "  " << d.dsPB[i].getTenPB() << ": " << d.dsPB[i].soLuongNhanVien() << "\n";
    int cho = 0;
    for (int i = 0; i < d.soDon; i++)
        if (d.dsDon[i].getTrangThai() == CHO_DUYET) cho++;
    cout << "Don nghi phep dang cho duyet: " << cho << "\n";
}

// ---------------- Chuc nang Ban giam doc ----------------
void duyetDon(DuLieu& d, BanGiamDoc* bgd) {
    tieuDe("DUYET DON NGHI PHEP");
    bgd->xemDonChoDuyet(d.dsDon, d.soDon);
    string ma = nhapDong("Nhap ma don can xu ly (Enter de bo qua): ");
    if (ma.empty()) return;
    for (int i = 0; i < d.soDon; i++) {
        if (d.dsDon[i].getMaDon() != ma) continue;
        NhanVien* nguoiGui = timNV(d, d.dsDon[i].getMaNV());
        if (nguoiGui == NULL) { cout << "Khong tim thay nguoi gui.\n"; return; }
        int c = nhapSo("1 = Phe duyet, 2 = Tu choi: ", 1, 2);
        if (c == 1) {
            bgd->pheDuyetNghiPhep(d.dsDon[i], *nguoiGui);   // co the throw
            if (d.dsDon[i].getLoaiPhep() == "Phep nam") cout << "Da duyet. ";
            else cout << "Da duyet (khong tru phep nam). ";
            cout << nguoiGui->getHoTen() << " con " << nguoiGui->soNgayPhepConLai() << " ngay phep.\n";
        } else {
            bgd->tuChoiNghiPhep(d.dsDon[i]);                // co the throw
            cout << "Da tu choi don.\n";
        }
        return;
    }
    cout << "Khong tim thay don.\n";
}

void baoCaoLuong(DuLieu& d, BanGiamDoc* bgd) {
    tieuDe("BAO CAO QUY LUONG");
    int thang = nhapSo("Thang (1-12): ", 1, 12);
    int nam = nhapSo("Nam: ", 2000, 2100);
    BangLuong ds[MAX_NV];
    int soBL = 0;
    for (int i = 0; i < d.soNV; i++) {
        const ChucDanh* cd = timCD(d, d.dsNV[i]->getMaCD());
        if (cd == NULL) continue;
        BangLuong bl("BL" + d.dsNV[i]->getMaNV(), d.dsNV[i]->getMaNV(), thang, nam);
        bl.tinhLuong(*d.dsNV[i], *cd, d.dsCC, d.soCC);
        ds[soBL++] = bl;
    }
    bgd->xemBaoCaoLuong(ds, soBL);
}

// ---------------- Phien lam viec sau khi dang nhap ----------------
void phienLamViec(DuLieu& d, NhanVien* user) {
    // [Chuong 4] Nhan biet lop that su qua ham ao loaiNhanVien(), roi ep kieu con tro lop co so ve lop dan xuat
    QuanLyNhanSu* ql = NULL;
    BanGiamDoc* bgd = NULL;
    if (user->loaiNhanVien() == LOAI_QLNS) ql = (QuanLyNhanSu*)user;
    else if (user->loaiNhanVien() == LOAI_BGD) bgd = (BanGiamDoc*)user;

    while (true) {
        tieuDe("HRMS - " + user->getHoTen() + " (" + user->vaiTro() + ")");
        cout << "1. Xem thong tin ca nhan\n2. Xem bang luong cua toi\n"
                "3. Gui don nghi phep\n4. Xem don nghi phep cua toi\n";
        int toiDa = 4;
        if (ql != NULL) {
            cout << "5. Quan ly nhan vien\n6. Quan ly phong ban\n7. Cham cong\n"
                    "8. Lap bang luong\n9. Thong ke\n";
            toiDa = 9;
        } else if (bgd != NULL) {
            cout << "5. Duyet don nghi phep\n6. Bao cao quy luong\n7. Danh sach nhan vien\n";
            toiDa = 7;
        }
        cout << "0. Dang xuat\n";
        int c = nhapSo("Chon: ", 0, toiDa);
        if (c == 0) return;
        try {   // [Chuong 6] bat ngoai le do cac ham nghiep vu nem ra
            switch (c) {
            case 1: user->xemThongTin(); break;
            case 2: xemBangLuongCuaToi(d, user); break;
            case 3: guiDonNghiPhep(d, user); break;
            case 4: xemDonCuaToi(d, user); break;
            default:
                if (ql != NULL) {
                    switch (c) {
                    case 5: menuQuanLyNhanVien(d, ql, user); break;
                    case 6: menuPhongBan(d); break;
                    case 7: menuChamCong(d, ql); break;
                    case 8: lapBangLuongTatCa(d, ql); break;
                    case 9: thongKe(d); break;
                    }
                } else if (bgd != NULL) {
                    switch (c) {
                    case 5: duyetDon(d, bgd); break;
                    case 6: baoCaoLuong(d, bgd); break;
                    case 7: tieuDe("DANH SACH NHAN VIEN"); inDanhSachNV(d); break;
                    }
                }
            }
        } catch (const char* loi) {
            cout << "  " << loi << "\n";
        }
    }
}

int main() {
    DuLieu* d = new DuLieu;   // cap phat dong vi cac mang kha lon
    try {
        docDuLieu(*d);
    } catch (const char* loi) {
        cout << "[Canh bao] " << loi << "\n";
    }
    if (d->soNV == 0) {
        cout << "Chua co du lieu, nap du lieu mau...\n";
        d->soCD = 0; d->soPB = 0; d->soCC = 0; d->soDon = 0;
        taoDuLieuMau(*d);
    }
    cout << "=========================================\n"
            "   HE THONG QUAN LY NHAN SU (HRMS)\n"
            "=========================================\n";
    try {
        while (true) {
            cout << "\nMa nhan vien mau: NV001 (Quan ly nhan su), NV002/NV005 (Ban giam doc), NV003/NV004 (Nhan vien)\n";
            string ma = nhapDong("Dang nhap - nhap ma nhan vien (Enter de thoat): ");
            if (ma.empty()) break;
            NhanVien* user = timNV(*d, ma);
            if (user == NULL) { cout << "Khong tim thay ma nhan vien.\n"; continue; }
            phienLamViec(*d, user);
        }
    } catch (int) {
        cout << "\n[Het du lieu nhap]\n";
    }
    try {
        luuDuLieu(*d);
    } catch (const char* loi) {
        cout << "[Canh bao] " << loi << "\n";
    }
    cout << "Tam biet!\n";
    delete d;
    return 0;
}
