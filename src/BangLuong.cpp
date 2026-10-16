#include "BangLuong.h"
#include "TienIch.h"

const int NGAY_CONG_CHUAN = 26;             // số ngày công chuẩn của 1 tháng
const double GIAM_TRU_BAN_THAN = 11000000;  // giảm trừ gia cảnh bản thân (chỉnh theo quy định hiện hành)
const double TL_BHXH = 0.08;                // tỷ lệ bảo hiểm tính trên lương hợp đồng
const double TL_BHYT = 0.015;
const double TL_BHTN = 0.01;
const double HE_SO_TANG_CA = 1.5;
const double NGAY_CONG_TOI_THIEU_BH = 14;   // dưới mức này thì không trích bảo hiểm tháng đó

BangLuong::BangLuong() {
    thang = 0; nam = 0; soNgayCong = 0;
    luongCoBan = 0; phuCap = 0; tienTangCa = 0;
    bhxh = 0; bhyt = 0; bhtn = 0; thueTNCN = 0; thucNhan = 0;
}

BangLuong::BangLuong(const string& maBL, const string& maNV, int thang, int nam) {
    this->maBL = maBL;
    this->maNV = maNV;
    this->thang = thang;
    this->nam = nam;
    soNgayCong = 0;
    luongCoBan = 0; phuCap = 0; tienTangCa = 0;
    bhxh = 0; bhyt = 0; bhtn = 0; thueTNCN = 0; thucNhan = 0;
}

string BangLuong::getMaNV() const { return maNV; }
int BangLuong::getThang() const { return thang; }
int BangLuong::getNam() const { return nam; }
double BangLuong::getSoNgayCong() const { return soNgayCong; }
double BangLuong::getThucNhan() const { return thucNhan; }

// Thuế lũy tiến từng phần (7 bậc: 5%, 10%, 15%, 20%, 25%, 30%, 35%)
double BangLuong::tinhThueTNCN(double t) const {
    if (t <= 0) return 0;
    double moc[6] = {5000000, 10000000, 18000000, 32000000, 52000000, 80000000};
    double suat[7] = {0.05, 0.10, 0.15, 0.20, 0.25, 0.30, 0.35};
    double thue = 0, truoc = 0;
    for (int i = 0; i < 6; i++) {
        if (t <= moc[i]) return thue + (t - truoc) * suat[i];
        thue = thue + (moc[i] - truoc) * suat[i];
        truoc = moc[i];
    }
    return thue + (t - truoc) * suat[6];
}

void BangLuong::tinhLuong(const NhanVien& nv, const ChucDanh& cd, const ChamCong dsCC[], int soCC) {
    double luongHD = cd.getLuongCoBan();
    double gioTangCa = 0;
    soNgayCong = 0;
    for (int i = 0; i < soCC; i++) {
        if (dsCC[i].getMaNV() == nv.getMaNV() && dsCC[i].getThang() == thang && dsCC[i].getNam() == nam) {
            soNgayCong = soNgayCong + dsCC[i].tinhCong();   // công tính theo giờ làm
            gioTangCa = gioTangCa + dsCC[i].getSoGioTangCa();
        }
    }
    if (soNgayCong > NGAY_CONG_CHUAN) soNgayCong = NGAY_CONG_CHUAN;
    if (soNgayCong <= 0) {   // không có công -> không có lương
        luongCoBan = 0; phuCap = 0; tienTangCa = 0;
        bhxh = 0; bhyt = 0; bhtn = 0; thueTNCN = 0; thucNhan = 0;
        return;
    }

    luongCoBan = luongHD * soNgayCong / NGAY_CONG_CHUAN;
    phuCap = cd.getPhuCap() + nv.tinhPhuCapQuanLy();   // ĐA HÌNH: hàm ảo, tùy loại nhân viên
    tienTangCa = gioTangCa * (luongHD / NGAY_CONG_CHUAN / 8.0) * HE_SO_TANG_CA;
    if (soNgayCong >= NGAY_CONG_TOI_THIEU_BH) {
        bhxh = luongHD * TL_BHXH;
        bhyt = luongHD * TL_BHYT;
        bhtn = luongHD * TL_BHTN;
    } else {
        bhxh = 0; bhyt = 0; bhtn = 0;   // làm quá ít công: không trích bảo hiểm
    }

    double chiuThue = luongCoBan + phuCap + tienTangCa - (bhxh + bhyt + bhtn) - GIAM_TRU_BAN_THAN;
    thueTNCN = tinhThueTNCN(chiuThue);
    thucNhan = luongCoBan + phuCap + tienTangCa - (bhxh + bhyt + bhtn) - thueTNCN;
    if (thucNhan < 0) thucNhan = 0;   // lương thực nhận không bao giờ âm
}

void BangLuong::inPhieuLuong() const {
    cout << "============ PHIEU LUONG " << thang << "/" << nam << " ============\n"
         << "Ma nhan vien    : " << maNV << "\n"
         << "So ngay cong    : " << dinhDangCong(soNgayCong) << "/" << NGAY_CONG_CHUAN << "\n";
    cout << "Luong co ban    : "; inTien(cout, luongCoBan); cout << "\n";
    cout << "Phu cap         : "; inTien(cout, phuCap); cout << "\n";
    cout << "Tien tang ca    : "; inTien(cout, tienTangCa); cout << "\n";
    cout << "BHXH (8%)       : " << (bhxh > 0 ? "-" : ""); inTien(cout, bhxh); cout << "\n";
    cout << "BHYT (1.5%)     : " << (bhyt > 0 ? "-" : ""); inTien(cout, bhyt); cout << "\n";
    cout << "BHTN (1%)       : " << (bhtn > 0 ? "-" : ""); inTien(cout, bhtn); cout << "\n";
    cout << "Thue TNCN       : " << (thueTNCN > 0 ? "-" : ""); inTien(cout, thueTNCN); cout << "\n";
    cout << "---------------------------------------\n";
    cout << "THUC NHAN       : "; inTien(cout, thucNhan); cout << " VND\n";
}
