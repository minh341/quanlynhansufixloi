#include "ChamCong.h"
#include <cstdlib>
#include <iomanip>

const int GIO_VAO_CHUAN = 8 * 60;    // 08:00 (tính bằng phút từ 0h)
const int GIO_RA_CHUAN = 17 * 60;    // 17:00
const double GIO_LAM_DU_CONG = 7;        // làm từ 7 giờ (đã trừ nghỉ trưa) tính 1 công
const double GIO_LAM_NUA_CONG = 3.5;     // làm từ 3.5 giờ tính 0.5 công

ChamCong::ChamCong() {
    soGioTangCa = 0;
    diMuon = 0;
    veSom = 0;
}

ChamCong::ChamCong(const string& maCC, const string& maNV, const string& ngay) {
    this->maCC = maCC;
    this->maNV = maNV;
    this->ngay = ngay;
    soGioTangCa = 0;
    diMuon = 0;
    veSom = 0;
}

// "HH:MM" -> số phút kể từ 0h (giờ đã được kiểm tra đúng dạng trước khi gọi)
int ChamCong::chuyenPhut(const string& hhmm) {
    int h = (hhmm[0] - '0') * 10 + (hhmm[1] - '0');
    int m = (hhmm[3] - '0') * 10 + (hhmm[4] - '0');
    return h * 60 + m;
}

string ChamCong::getMaNV() const { return maNV; }
string ChamCong::getNgay() const { return ngay; }
int ChamCong::getThang() const { return ngay.size() >= 5 ? atoi(ngay.substr(3, 2).c_str()) : 0; }
int ChamCong::getNam() const { return ngay.size() >= 10 ? atoi(ngay.substr(6, 4).c_str()) : 0; }
double ChamCong::getSoGioTangCa() const { return soGioTangCa; }
int ChamCong::getDiMuon() const { return diMuon; }
int ChamCong::getVeSom() const { return veSom; }

void ChamCong::ghiNhanCong(const string& gv, const string& gr) {
    gioVao = gv;
    gioRa = gr;
    int vao = chuyenPhut(gv);
    int ra = chuyenPhut(gr);
    // Đi muộn chỉ tính cho ca làm việc trong giờ hành chính (vào trước giờ ra chuẩn 17:00)
    diMuon = (vao > GIO_VAO_CHUAN && vao < GIO_RA_CHUAN) ? vao - GIO_VAO_CHUAN : 0;
    veSom = (ra < GIO_RA_CHUAN && ra > GIO_VAO_CHUAN) ? GIO_RA_CHUAN - ra : 0;
    // Tăng ca tính từ max(giờ vào, 17:00): đến lúc 18:00 thì chỉ tính từ 18:00
    int batDauTangCa = vao > GIO_RA_CHUAN ? vao : GIO_RA_CHUAN;
    soGioTangCa = ra > batDauTangCa ? (ra - batDauTangCa) / 60.0 : 0.0;
}

double ChamCong::tinhGioLam() const {
    if (gioVao.empty() || gioRa.empty()) return 0;
    int vao = chuyenPhut(gioVao);
    int ra = chuyenPhut(gioRa);
    if (ra <= vao) return 0;

    int tongPhut = ra - vao;
    // Khoảng nghỉ trưa chuẩn: 12:00 (720 phút) đến 13:00 (780 phút)
    int batDauNghi = 12 * 60;
    int ketThucNghi = 13 * 60;
    int giaoDau = vao > batDauNghi ? vao : batDauNghi;
    int giaoCuoi = ra < ketThucNghi ? ra : ketThucNghi;
    if (giaoCuoi > giaoDau) {
        tongPhut -= (giaoCuoi - giaoDau); // Chỉ trừ đúng khoảng thời gian trùng với giờ nghỉ trưa
    }
    return tongPhut > 0 ? (tongPhut / 60.0) : 0;
}

double ChamCong::tinhCong() const {
    double h = tinhGioLam();
    if (h >= GIO_LAM_DU_CONG) return 1;
    if (h >= GIO_LAM_NUA_CONG) return 0.5;
    return 0;
}

void ChamCong::hienThi() const {
    cout << left << setw(12) << ngay << setw(8) << gioVao << setw(8) << gioRa
         << setw(10) << fixed << setprecision(1) << tinhGioLam()
         << setw(10) << diMuon << setw(10) << veSom << setw(12) << soGioTangCa << tinhCong() << "\n";
}

void ChamCong::ghiFile(ostream& os) const {
    os << maCC << "|" << maNV << "|" << ngay << "|" << gioVao << "|" << gioRa << "\n";
}
