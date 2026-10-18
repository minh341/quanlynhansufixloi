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

NhanVien* QuanLyNhanSu::timNhanVien(const vector<NhanVien*>& ds, const string& maNV) const {
    for (int i = 0; i < (int)ds.size(); i++)
        if (ds[i]->getMaNV() == maNV) return ds[i];
    return NULL;
}

vector<NhanVien*> QuanLyNhanSu::timTheoTen(const vector<NhanVien*>& ds, const string& tuKhoa) const {
    vector<NhanVien*> kq;
    string k = chuThuong(tuKhoa);
    for (int i = 0; i < (int)ds.size(); i++)
        if (chuThuong(ds[i]->getHoTen()).find(k) != string::npos)
            kq.push_back(ds[i]);
    return kq;
}

void QuanLyNhanSu::themNhanVien(vector<NhanVien*>& ds, NhanVien* nv) {
    if (nv == NULL) throw "Nhan vien khong hop le.";
    if (timNhanVien(ds, nv->getMaNV()) != NULL) throw "Ma nhan vien da ton tai.";
    ds.push_back(nv);
}

bool QuanLyNhanSu::suaNhanVien(const vector<NhanVien*>& ds, const string& maNV) {
    NhanVien* nv = timNhanVien(ds, maNV);
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
bool QuanLyNhanSu::xoaNhanVien(vector<NhanVien*>& ds, const string& maNV) {
    for (int i = 0; i < (int)ds.size(); i++) {
        if (ds[i]->getMaNV() == maNV) {
            delete ds[i];                     // hàm hủy ảo -> hủy đúng loại đối tượng
            ds.erase(ds.begin() + i);         // gỡ con trỏ khỏi vector
            return true;
        }
    }
    return false;
}

void QuanLyNhanSu::ghiNhanChamCong(vector<ChamCong>& dsCC, const ChamCong& cc) {
    for (int i = 0; i < (int)dsCC.size(); i++) {
        if (dsCC[i].getMaNV() == cc.getMaNV() && dsCC[i].getNgay() == cc.getNgay()) {
            dsCC[i] = cc;   // đã có bản ghi cùng ngày -> ghi đè
            return;
        }
    }
    dsCC.push_back(cc);
}

BangLuong QuanLyNhanSu::lapBangLuong(const NhanVien& nv, const ChucDanh& cd,
                                     const vector<ChamCong>& dsCC, int thang, int nam) const {
    BangLuong bl("BL" + nv.getMaNV() + "_" + soThanhChuoi(thang) + "_" + soThanhChuoi(nam),
                 nv.getMaNV(), thang, nam);
    bl.tinhLuong(nv, cd, dsCC);
    return bl;
}
