#include "QuanLyNhanSu.h"
#include "TienIch.h"

QuanLyNhanSu::QuanLyNhanSu() {}

// Danh sách khởi tạo gọi hàm tạo sao chép của lớp cơ sở
QuanLyNhanSu::QuanLyNhanSu(const NhanVien& nv, const string& chuyenMon) : NhanVien(nv) {
    this->chuyenMon = chuyenMon;
}

string QuanLyNhanSu::getChuyenMon() const { return chuyenMon; }
void QuanLyNhanSu::setChuyenMon(const string& cm) { chuyenMon = cm; }

void QuanLyNhanSu::xemThongTin() const {
    NhanVien::xemThongTin();   // gọi hàm của lớp cơ sở bằng toán tử ::
    cout << "Chuyen mon     : " << chuyenMon << "\n";
}

string QuanLyNhanSu::vaiTro() const { return "Quan ly nhan su"; }
int QuanLyNhanSu::loaiNhanVien() const { return LOAI_QLNS; }
double QuanLyNhanSu::tinhPhuCapQuanLy() const { return 2000000; }

void QuanLyNhanSu::ghiFile(ostream& os) const {
    os << "QL|";
    ghiTruongCoBan(os);   // dùng giao diện protected của lớp cơ sở
    os << "|" << chuyenMon << "\n";
}

NhanVien* QuanLyNhanSu::timNhanVien(NhanVien* const ds[], int n, const string& maNV) const {
    for (int i = 0; i < n; i++)
        if (ds[i]->getMaNV() == maNV) return ds[i];
    return NULL;
}

int QuanLyNhanSu::timTheoTen(NhanVien* const ds[], int n, const string& tuKhoa, NhanVien* kq[]) const {
    int dem = 0;
    string k = chuThuong(tuKhoa);
    for (int i = 0; i < n; i++)
        if (chuThuong(ds[i]->getHoTen()).find(k) != string::npos)
            kq[dem++] = ds[i];
    return dem;
}

void QuanLyNhanSu::themNhanVien(NhanVien* ds[], int& n, NhanVien* nv) {
    if (nv == NULL) throw "Nhan vien khong hop le.";
    if (timNhanVien(ds, n, nv->getMaNV()) != NULL) throw "Ma nhan vien da ton tai.";
    if (n >= MAX_NV) throw "Danh sach nhan vien da day.";
    ds[n++] = nv;
}

bool QuanLyNhanSu::suaNhanVien(NhanVien* const ds[], int n, const string& maNV) {
    NhanVien* nv = timNhanVien(ds, n, maNV);
    if (nv == NULL) return false;
    string s;
    cout << "(De trong de giu nguyen)\n";
    cout << "Ho ten moi: ";        getline(cin, s); if (!s.empty()) nv->setHoTen(lamSach(s));
    cout << "Dia chi moi: ";       getline(cin, s); if (!s.empty()) nv->setDiaChi(lamSach(s));
    cout << "So dien thoai moi: "; getline(cin, s); if (!s.empty()) nv->setSoDienThoai(lamSach(s));
    cout << "Email moi: ";         getline(cin, s); if (!s.empty()) nv->setEmail(lamSach(s));
    return true;
}

// Lưu ý: hàm này giải phóng đối tượng (delete); nơi gọi phải gỡ nhân viên khỏi PhongBan trước.
bool QuanLyNhanSu::xoaNhanVien(NhanVien* ds[], int& n, const string& maNV) {
    for (int i = 0; i < n; i++) {
        if (ds[i]->getMaNV() == maNV) {
            delete ds[i];                 // hàm hủy ảo -> hủy đúng loại đối tượng
            for (int j = i; j < n - 1; j++)
                ds[j] = ds[j + 1];        // dồn mảng
            n--;
            return true;
        }
    }
    return false;
}

void QuanLyNhanSu::ghiNhanChamCong(ChamCong dsCC[], int& soCC, const ChamCong& cc) {
    for (int i = 0; i < soCC; i++) {
        if (dsCC[i].getMaNV() == cc.getMaNV() && dsCC[i].getNgay() == cc.getNgay()) {
            dsCC[i] = cc;   // đã có bản ghi cùng ngày -> ghi đè
            return;
        }
    }
    if (soCC >= MAX_CC) throw "Danh sach cham cong da day.";
    dsCC[soCC++] = cc;
}

BangLuong QuanLyNhanSu::lapBangLuong(const NhanVien& nv, const ChucDanh& cd,
                                     const ChamCong dsCC[], int soCC, int thang, int nam) const {
    BangLuong bl("BL" + nv.getMaNV() + "_" + soThanhChuoi(thang) + "_" + soThanhChuoi(nam),
                 nv.getMaNV(), thang, nam);
    bl.tinhLuong(nv, cd, dsCC, soCC);
    return bl;
}
