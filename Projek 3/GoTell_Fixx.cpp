#include <iostream>   // Untuk cin, cout, getline
#include <iomanip>    // Untuk setw, setfill, fixed, setprecision
#include <ctime>      // Untuk mengambil tanggal sekarang
#include <sstream>    // Untuk membuat format tanggal dengan ostringstream
#include <cstdlib>    // Untuk system("cls"), system("chcp 65001 > nul"), exit(0)
#include <thread>     // Untuk animasi loading
#include <chrono>     // Untuk waktu delay animasi loading
#include <conio.h>    // Untuk getch(), tombol panah, dan pause tanpa Enter
#include <vector>     // [BARU] Pengganti array fixed-size, ukurannya bisa berubah-ubah

using namespace std;

const int SOFT_LIMIT_TAMU       = 500;
const int SOFT_LIMIT_TRANSAKSI  = 1000;

const double PAJAK           = 0.11;
const double SERVICE_CHARGE  = 0.05;

const string MERAH  = "\033[31m";
const string HIJAU  = "\033[32m";
const string KUNING = "\033[33m";
const string BIRU   = "\033[36m";
const string UNGU   = "\033[35m";
const string TEBAL  = "\033[1m";
const string RESET  = "\033[0m";


struct Kamar {
    string nomor;
    string tipe;
    string status;
    int    lantai;
    int    kapasitas;
    double harga;
};

struct Tamu {
    string nama;
    string noKTP;
    string telepon;
    int    totalMenginap;
    double totalBelanja;
};

struct Layanan {
    string id;
    string nama;
    double harga;
};

struct Transaksi {
    string id;
    string nomorKamar;
    string namaTamu;
    string ktpTamu;
    int    malam;
    double hargaKamar;
    double totalLayanan;
    double grandTotal;
    string status;
    string metodeBayar;
};

struct User {
    string username;
    string password;
    string nama;
    string role;
};

vector<Kamar>     daftarKamar;
vector<User>      daftarUser;
vector<Tamu>      daftarTamu;
vector<Layanan>   daftarLayanan;
vector<Transaksi> daftarTransaksi;

int idBerjalan = 1;

void cekEOF() {
    if (cin.eof()) {
        cout << MERAH << "\n  Input berakhir tak terduga. Program dihentikan.\n" << RESET;
        exit(0);
    }
}

string trimTeks(const string &s) {
    int awal = 0;
    int akhir = (int) s.length() - 1;

    while (awal <= akhir && (s[awal] == ' ' || s[awal] == '\t')) awal++;
    while (akhir >= awal && (s[akhir] == ' ' || s[akhir] == '\t')) akhir--;

    if (awal > akhir) return "";
    return s.substr(awal, akhir - awal + 1);
}

string bacaTeks(const string &label, bool wajib = true) {
    string s;
    while (true) {
        cout << "  " << label << ": ";
        getline(cin, s);
        cekEOF();

        s = trimTeks(s);


        if (!wajib || !s.empty()) return s;
        cout << MERAH << "  Input tidak boleh kosong!" << RESET << "\n";
    }
}

string bacaTeksPanjang(const string &label, int panjangMin, int panjangMax) {
    string s;
    string keterangan = (panjangMin == panjangMax)
        ? (to_string(panjangMin) + " digit")
        : (to_string(panjangMin) + "-" + to_string(panjangMax) + " digit");

    while (true) {
        cout << "  " << label << " (" << keterangan << "): ";
        getline(cin, s);
        cekEOF();

        s = trimTeks(s);


        if ((int) s.length() < panjangMin || (int) s.length() > panjangMax) {
            if (panjangMin == panjangMax) {
                cout << MERAH << "  Harus tepat " << panjangMin << " digit!" << RESET << "\n";
            } else {
                cout << MERAH << "  Panjang harus antara " << panjangMin
                     << " sampai " << panjangMax << " digit!" << RESET << "\n";
            }
            continue;
        }
        return s;
    }
}

bool semuaAngka(const string &s) {
    if (s.empty()) return false;
    for (int i = 0; i < (int) s.length(); i++) {
        if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }
    return true;
}

string bacaKTP(const string &label = "Nomor KTP") {
    string s;
    while (true) {
        s = bacaTeksPanjang(label, 16, 16);
        if (!semuaAngka(s)) {
            cout << MERAH << "  KTP harus berupa angka semua!" << RESET << "\n";
            continue;
        }
        return s;
    }
}

bool namaValid(const string &s) {
    if (s.empty()) return false;

    bool adaHuruf = false;
    for (int i = 0; i < (int) s.length(); i++) {
        char c = s[i];

        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
            adaHuruf = true;
        } else if (c == ' ') {
            // Spasi antar nama masih diperbolehkan.
        } else {
            return false;
        }
    }

    return adaHuruf;
}

string bacaNamaTamu(const string &label = "Nama lengkap tamu") {
    string s;
    while (true) {
        s = bacaTeks(label);
        if (!namaValid(s)) {
            cout << MERAH << "  Nama hanya boleh berisi huruf dan spasi!" << RESET << "\n";
            continue;
        }
        return s;
    }
}

bool formatHPValid(const string &s) {
    if (!semuaAngka(s)) return false;
    if ((int) s.length() < 9 || (int) s.length() > 13) return false;

    if (s.length() >= 2 && s.substr(0, 2) == "08") return true;
    if (s.length() >= 2 && s.substr(0, 2) == "62") return true;

    return false;
}

string bacaNoHP(const string &label = "Nomor HP") {
    string s;
    while (true) {
        s = bacaTeksPanjang(label, 9, 13);
        if (!formatHPValid(s)) {
            cout << MERAH << "  Nomor HP harus angka dan diawali 08 atau 62!" << RESET << "\n";
            continue;
        }
        return s;
    }
}

int bacaAngka(const string &label, int min = 0, int max = 999999) {
    string input;

    while (true) {
        cout << "  " << label << ": ";
        getline(cin, input);
        cekEOF();

        input = trimTeks(input);

        if (!semuaAngka(input)) {
            cout << MERAH << "  Input harus berupa angka semua!" << RESET << "\n";
            continue;
        }

        int x;
        try {
            x = stoi(input);
        } catch (...) {
            cout << MERAH << "  Angka terlalu besar atau tidak valid!" << RESET << "\n";
            continue;
        }

        if (x < min || x > max) {
            cout << MERAH << "  Masukkan angka antara " << min << " - " << max << RESET << "\n";
            continue;
        }

        return x;
    }
}

void clearScreen() {
    system("cls");
}

void tampilkanBanner();
void judul(const string &teks);

const int ARAH_ATAS  = 1;
const int ARAH_BAWAH = 2;
const int ARAH_ENTER = 3;
const int ARAH_LAIN  = 0;

int bacaTombolArah() {
    int tombol = getch();
    if (tombol == 224 || tombol == 0) {
        tombol = getch();
        if (tombol == 72) return ARAH_ATAS;
        if (tombol == 80) return ARAH_BAWAH;
        return ARAH_LAIN;
    }
    if (tombol == 13) return ARAH_ENTER;
    return ARAH_LAIN;
}

const int LEBAR_LAYAR = 64;

void kotakMenu(const string &teks, bool aktif, int lebarKotak) {
    int pjg   = (int) teks.length();
    int kiri  = (lebarKotak - pjg) / 2;
    if (kiri < 0) kiri = 0;
    int kanan = lebarKotak - pjg - kiri;
    if (kanan < 0) kanan = 0;

    string garisHorizontal = "";
    for (int i = 0; i < lebarKotak; i++) garisHorizontal += "═";

    int totalLebarKotak = lebarKotak + 2;
    int indent = (LEBAR_LAYAR - totalLebarKotak) / 2;
    if (indent < 0) indent = 0;
    string spasiTengah(indent, ' ');

    if (aktif) cout << BIRU << TEBAL;

    cout << spasiTengah << "╔" << garisHorizontal << "╗\n";
    cout << spasiTengah << "║" << string(kiri, ' ') << teks
         << string(kanan, ' ') << "║\n";
    cout << spasiTengah << "╚" << garisHorizontal << "╝\n";

    if (aktif) cout << RESET;
}

int hitungLebarKotak(string opsi[], int jumlahOpsi) {
    int lebar = 0;
    for (int i = 0; i < jumlahOpsi; i++) {
        if ((int) opsi[i].length() > lebar) lebar = (int) opsi[i].length();
    }
    return lebar + 6;
}

int pilihMenuKotak(const string &judulMenu, string opsi[], int jumlahOpsi) {
    int lebar = hitungLebarKotak(opsi, jumlahOpsi);

    int pilih = 0;
    while (true) {
        clearScreen();
        tampilkanBanner();
        judul(judulMenu);
        cout << "\n";
        for (int i = 0; i < jumlahOpsi; i++) {
            kotakMenu(opsi[i], i == pilih, lebar);
        }
        cout << KUNING << "\n  [ Tombol ATAS/BAWAH pilih menu, ENTER untuk konfirmasi ]" << RESET << "\n";

        int arah = bacaTombolArah();
        if (arah == ARAH_ATAS) {
            pilih--;
            if (pilih < 0) pilih = jumlahOpsi - 1;
        } else if (arah == ARAH_BAWAH) {
            pilih++;
            if (pilih >= jumlahOpsi) pilih = 0;
        } else if (arah == ARAH_ENTER) {
            return pilih;
        }
    }
}

void tungguTombol() {
    cout << KUNING << "\n  Tekan tombol apa saja untuk kembali ke menu..." << RESET;
    getch();
}

void animasiLoading(const string &pesan, int langkah = 15) {
    cout << "\n  " << pesan << " ";
    for (int i = 0; i < langkah; i++) {
        cout << HIJAU << "█" << RESET << flush;
        this_thread::sleep_for(chrono::milliseconds(25));
    }
    cout << " Selesai!\n";
}

string formatRupiah(double angka) {
    long long n = (long long) angka;
    string s = to_string(n);
    int pos = (int) s.length() - 3;
    while (pos > 0) {
        s.insert(pos, ".");
        pos -= 3;
    }
    return "Rp " + s;
}

string tanggalSekarang() {
    time_t t = time(0);
    tm *now = localtime(&t);
    ostringstream oss;
    oss << (now->tm_year + 1900) << "-"
        << setw(2) << setfill('0') << (now->tm_mon + 1) << "-"
        << setw(2) << setfill('0') << now->tm_mday;
    return oss.str();
}

string buatID(const string &prefix) {
    string id = prefix + "-" + to_string(100 + idBerjalan);
    idBerjalan++;
    return id;
}

void garis(int panjang = 64, char isi = '-') {
    cout << string(panjang, isi) << "\n";
}

void judul(const string &teks) {
    garis(LEBAR_LAYAR);
    cout << TEBAL << BIRU << "  " << teks << RESET << "\n";
    garis(LEBAR_LAYAR);
}

double hitungTotalAkhir(double hargaKamar, double totalLayanan) {
    double subtotal = hargaKamar + totalLayanan;
    double pajak     = subtotal * PAJAK;
    double service   = subtotal * SERVICE_CHARGE;
    return subtotal + pajak + service;
}

Kamar* cariKamar(const string &nomor) {
    for (auto &k : daftarKamar) {
        if (k.nomor == nomor) return &k;
    }
    return nullptr;
}

User* cariUser(const string &username) {
    for (auto &u : daftarUser) {
        if (u.username == username) return &u;
    }
    return nullptr;
}

Tamu* cariTamuByKTP(const string &ktp) {
    for (auto &t : daftarTamu) {
        if (t.noKTP == ktp) return &t;
    }
    return nullptr;
}

Layanan* cariLayanan(const string &id) {
    for (auto &l : daftarLayanan) {
        if (l.id == id) return &l;
    }
    return nullptr;
}

Transaksi* cariTransaksiAktif(const string &nomorKamar) {
    for (auto &t : daftarTransaksi) {
        if (t.nomorKamar == nomorKamar && t.status == "Aktif") return &t;
    }
    return nullptr;
}

Tamu* ambilOrTambahTamu(const string &nama, const string &ktp, const string &telp) {
    Tamu *t = cariTamuByKTP(ktp);
    if (t != nullptr) return t;

    Tamu baru;
    baru.nama          = nama;
    baru.noKTP         = ktp;
    baru.telepon       = telp;
    baru.totalMenginap = 0;
    baru.totalBelanja  = 0;
    daftarTamu.push_back(baru);
    return &daftarTamu.back();
}

void tambahKamar(string nomor, string tipe, int lantai, int kap, double harga) {
    if (cariKamar(nomor) != nullptr) {
        cout << MERAH << "  Nomor kamar " << nomor << " sudah ada, dilewati.\n" << RESET;
        return;
    }
    daftarKamar.push_back({nomor, tipe, "Kosong", lantai, kap, harga});
}

void inisialisasiKamarDefault() {
    tambahKamar("101", "Standard", 1, 2, 450000);
    tambahKamar("102", "Standard", 1, 2, 450000);
    tambahKamar("103", "Standard", 1, 2, 450000);
    tambahKamar("104", "Standard", 1, 3, 550000);
    tambahKamar("105", "Standard", 1, 2, 450000);
    tambahKamar("201", "Deluxe",   2, 2, 750000);
    tambahKamar("202", "Deluxe",   2, 2, 750000);
    tambahKamar("203", "Deluxe",   2, 3, 950000);
    tambahKamar("204", "Deluxe",   2, 2, 850000);
    tambahKamar("301", "Suite",    3, 4, 1500000);
    tambahKamar("302", "Suite",    3, 4, 1500000);
    tambahKamar("303", "Suite",    3, 2, 1800000);
    tambahKamar("401", "Presidential", 4, 6, 5000000);
    tambahKamar("402", "Presidential", 4, 4, 4500000);
}

void tambahUser(string user, string pass, string nama, string role) {
    daftarUser.push_back({user, pass, nama, role});
}

void inisialisasiUser() {
    tambahUser("manager", "manager123", "Iqbal ganteng", "Manager");
    tambahUser("resep1",  "resep123",   "Adji",          "Resepsionis");
    tambahUser("resep2",  "resep456",   "zhyla",         "Resepsionis");
    tambahUser("hk1",     "hk123",      "Nurra",         "Housekeeping");
    tambahUser("hk2",     "hk456",      "Wira",          "Housekeeping");
}

void tambahLayanan(string id, string nama, double harga) {
    daftarLayanan.push_back({id, nama, harga});
}

void inisialisasiLayanan() {
    tambahLayanan("FB-01", "Sarapan Pagi (Buffet)",  85000);
    tambahLayanan("FB-02", "Room Service 24 Jam",    50000);
    tambahLayanan("FB-03", "Makan Malam Romantis",  350000);
    tambahLayanan("SP-01", "Pijat Tradisional",     250000);
    tambahLayanan("SP-02", "Spa Pasangan",          750000);
    tambahLayanan("LN-01", "Laundry Express",        50000);
    tambahLayanan("TR-01", "Antar Jemput Bandara",  200000);
    tambahLayanan("TR-02", "City Tour Setengah Hari",350000);
    tambahLayanan("EN-01", "Karaoke 1 Jam",         150000);
    tambahLayanan("BS-01", "Sewa Meeting Room",     500000);
}

void inisialisasiDataAwal() {
    daftarKamar.clear();
    daftarUser.clear();
    daftarTamu.clear();
    daftarLayanan.clear();
    daftarTransaksi.clear();
    idBerjalan = 1;

    inisialisasiKamarDefault();
    inisialisasiUser();
    inisialisasiLayanan();
}
string warnaStatusKamar(const string &status) {
    if (status == "Kosong")      return HIJAU;
    if (status == "Terisi")      return MERAH;
    if (status == "Dipesan")     return KUNING;
    if (status == "Dibersihkan") return BIRU;
    return UNGU;
}

void tampilkanSemuaKamar() {
    clearScreen();
    judul("                 DAFTAR SEMUA KAMAR");
    cout << left << setw(6) << "No" << setw(14) << "Tipe" << setw(10) << "Lantai"
         << setw(16) << "Harga/Malam" << "Status" << "\n";
    garis(LEBAR_LAYAR);
    for (auto &k : daftarKamar) {
        cout << left << setw(6) << k.nomor << setw(14) << k.tipe
             << setw(10) << k.lantai << setw(16) << formatRupiah(k.harga)
             << warnaStatusKamar(k.status) << k.status << RESET << "\n";
    }
}

void tampilkanKamarTersedia() {
    judul("              KAMAR YANG TERSEDIA (KOSONG)");
    cout << "  " << left << setw(6) << "No" << setw(14) << "Tipe" << setw(12) << "Kapasitas"
         << "Harga/Malam" << "\n";
    cout << "  "; garis(LEBAR_LAYAR - 2);
    for (auto &k : daftarKamar) {
        if (k.status == "Kosong") {
            string kapasitasStr = to_string(k.kapasitas) + " org";
            cout << "  " << left << setw(6) << k.nomor << setw(14) << k.tipe
                 << setw(12) << kapasitasStr << formatRupiah(k.harga) << "\n";
        }
    }
    cout << "\n";
}

void tampilkanLayanan() {
    judul("DAFTAR LAYANAN HOTEL");
    cout << "  " << left << setw(8) << "ID" << setw(30) << "Nama Layanan" << "Harga" << "\n";
    cout << "  "; garis(LEBAR_LAYAR - 2);
    for (auto &l : daftarLayanan) {
        cout << "  " << left << setw(8) << l.id << setw(30) << l.nama << formatRupiah(l.harga) << "\n";
    }
    cout << "\n";
}

void cetakStruk(const Transaksi &t) {
    garis(LEBAR_LAYAR, '=');
    string judulStruk = "STRUK GOTELL HOTEL";
    int indentJudul = (LEBAR_LAYAR - (int) judulStruk.length()) / 2;
    cout << TEBAL << string(indentJudul, ' ') << judulStruk << RESET << "\n";
    garis(LEBAR_LAYAR, '=');
    cout << "  No. Transaksi : " << t.id << "\n";
    cout << "  Nama Tamu     : " << t.namaTamu << "\n";
    cout << "  Kamar         : " << t.nomorKamar << "\n";
    cout << "  Lama Menginap : " << t.malam << " malam\n";
    garis(LEBAR_LAYAR);
    cout << left << setw(28) << "  Biaya Kamar" << formatRupiah(t.hargaKamar) << "\n";
    cout << left << setw(28) << "  Total Layanan Tambahan" << formatRupiah(t.totalLayanan) << "\n";
    double subtotal = t.hargaKamar + t.totalLayanan;
    cout << left << setw(28) << "  Subtotal" << formatRupiah(subtotal) << "\n";
    cout << left << setw(28) << "  Pajak (11%)" << formatRupiah(subtotal * PAJAK) << "\n";
    cout << left << setw(28) << "  Service Charge (5%)" << formatRupiah(subtotal * SERVICE_CHARGE) << "\n";
    garis(LEBAR_LAYAR, '=');
    cout << KUNING << TEBAL << left << setw(28) << "  TOTAL BAYAR" << formatRupiah(t.grandTotal) << RESET << "\n";
    garis(LEBAR_LAYAR, '=');
}

void tampilkanLogoQRIS() {
    cout << BIRU << TEBAL;
    cout << R"(
        ██████╗ ██████╗ ██╗███████╗
       ██╔═══██╗██╔══██╗██║██╔════╝
       ██║   ██║██████╔╝██║███████╗
       ██║▄▄ ██║██╔══██╗██║╚════██║
       ╚██████╔╝██║  ██║██║███████║
        ╚══▀▀═╝ ╚═╝  ╚═╝╚═╝╚══════╝
)";
    cout << RESET;
}

void tampilkanDataQRIS(const Transaksi &t) {
    garis(LEBAR_LAYAR, '=');

    string judulQRIS = "SCAN QRIS PEMBAYARAN GOTELL";
    int indentJudul = (LEBAR_LAYAR - (int) judulQRIS.length()) / 2;
    if (indentJudul < 0) indentJudul = 0;

    cout << TEBAL << string(indentJudul, ' ') << judulQRIS << RESET << "\n";
    garis(LEBAR_LAYAR, '=');

    cout << "  Merchant      : GoTell Hotel\n";
    cout << "  No. Transaksi : " << t.id << "\n";
    cout << "  Nama Tamu     : " << t.namaTamu << "\n";
    cout << "  Nominal       : " << KUNING << formatRupiah(t.grandTotal) << RESET << "\n";

    garis(LEBAR_LAYAR);
    cout << "\n";
}

void tampilkanQRISSimbol() {
    cout << TEBAL;
    cout << "        ╔══════════════════════════════════╗\n";
    cout << "        ║  ██  ██  ██████  ██       ████   ║\n";
    cout << "        ║  ██      ██  ██      ██   ██     ║\n";
    cout << "        ║  ██████  ██  ██  ██████   ████   ║\n";
    cout << "        ║      ██          ██  ██      ██  ║\n";
    cout << "        ║  ████    ██████      ██████      ║\n";
    cout << "        ║  ██  ██      ██  ████    ██  ██  ║\n";
    cout << "        ║  ██  ██████      ██  ██████  ██  ║\n";
    cout << "        ║      ██      ████        ██      ║\n";
    cout << "        ║  ██████  ██  ██  ██████  ██████  ║\n";
    cout << "        ║  ██      ██      ██      ██      ║\n";
    cout << "        ║  ████  ██████  ██████      ████  ║\n";
    cout << "        ╚══════════════════════════════════╝\n";
    cout << RESET;
}

void tampilkanHeaderQRIS(const Transaksi &t) {
    tampilkanLogoQRIS();
    tampilkanDataQRIS(t);
    tampilkanQRISSimbol();

    cout << "\n";
    garis(LEBAR_LAYAR);
    cout << HIJAU;
    cout << "  Arahkan kamera aplikasi e-wallet/mobile banking ke QRIS di atas.\n";
    cout << RESET;
    cout << KUNING;
    cout << "  Setelah pembayaran berhasil, tekan tombol apa saja untuk konfirmasi...";
    cout << RESET;
}

void tampilkanTransaksiAktif() {
    clearScreen();
    judul("TRANSAKSI YANG SEDANG AKTIF");
    bool ada = false;
    for (auto &t : daftarTransaksi) {
        if (t.status == "Aktif") {
            cout << "  " << t.id << " | Kamar " << t.nomorKamar << " | " << t.namaTamu
                 << " | " << t.malam << " malam | " << formatRupiah(t.grandTotal) << "\n";
            ada = true;
        }
    }
    if (!ada) cout << "  Tidak ada transaksi aktif saat ini.\n";
}

Kamar* bacaKamarKosong() {
    while (true) {
        string nomorKamar = bacaTeks("Nomor kamar yang dipilih");
        Kamar *kamar = cariKamar(nomorKamar);

        if (kamar == nullptr) {
            cout << MERAH << "  Kamar tidak ditemukan!" << RESET << "\n";
            continue;
        }

        if (kamar->status != "Kosong") {
            cout << MERAH << "  Kamar tidak tersedia! Status saat ini: "
                 << kamar->status << RESET << "\n";
            continue;
        }

        return kamar;
    }
}

void prosesCheckIn() {
    clearScreen();
    judul("                     CHECK-IN TAMU");

    if ((int) daftarTransaksi.size() >= SOFT_LIMIT_TRANSAKSI) {
        cout << MERAH << "  Kapasitas transaksi sudah mencapai batas wajar ("
             << SOFT_LIMIT_TRANSAKSI << "). Tidak bisa check-in dulu." << RESET << "\n";
        return;
    }
    tampilkanKamarTersedia();

    Kamar *kamar = bacaKamarKosong();

    string nama  = bacaNamaTamu();
    string ktp   = bacaKTP();
    string telp  = bacaNoHP();
    int    malam = bacaAngka("Lama menginap (malam)", 1, 365);

    if (cariTamuByKTP(ktp) == nullptr && (int) daftarTamu.size() >= SOFT_LIMIT_TAMU) {
        cout << MERAH << "  Data tamu sudah mencapai batas wajar ("
             << SOFT_LIMIT_TAMU << "). Tidak bisa menambah tamu baru." << RESET << "\n";
        return;
    }

    Tamu *tamu = ambilOrTambahTamu(nama, ktp, telp);

    Transaksi t;
    t.id            = buatID("TRX");
    t.nomorKamar    = kamar->nomor;
    t.namaTamu      = tamu->nama;
    t.ktpTamu       = tamu->noKTP;
    t.malam         = malam;
    t.hargaKamar    = kamar->harga * malam;
    t.totalLayanan  = 0;
    t.grandTotal    = hitungTotalAkhir(t.hargaKamar, t.totalLayanan);
    t.status        = "Aktif";
    t.metodeBayar   = "-";
    daftarTransaksi.push_back(t);

    kamar->status = "Terisi";
    tamu->totalMenginap++;

    animasiLoading("Memproses check-in...");
    cout << HIJAU << "\n  Check-in berhasil! ID Transaksi: " << t.id << RESET << "\n";
    cout << "  Estimasi total saat ini: " << formatRupiah(t.grandTotal) << "\n";
}

void prosesTambahLayanan() {
    clearScreen();
    judul("TAMBAH LAYANAN UNTUK TAMU");
    string nomorKamar = bacaTeks("Nomor kamar tamu");
    cout << "\n";

    Transaksi *t = cariTransaksiAktif(nomorKamar);
    if (t == nullptr) {
        cout << MERAH << "  Tidak ada transaksi aktif di kamar ini." << RESET << "\n";
        return;
    }

    tampilkanLayanan();
    string idLayanan = bacaTeks("ID Layanan");
    Layanan *layanan = cariLayanan(idLayanan);
    if (layanan == nullptr) {
        cout << MERAH << "  Layanan tidak ditemukan." << RESET << "\n";
        return;
    }

    int qty = bacaAngka("Jumlah", 1, 50);
    double subtotal = layanan->harga * qty;

    t->totalLayanan += subtotal;
    t->grandTotal = hitungTotalAkhir(t->hargaKamar, t->totalLayanan);

    cout << HIJAU << "  " << layanan->nama << " x" << qty
         << " ditambahkan (" << formatRupiah(subtotal) << ")" << RESET << "\n";
}

string pilihMetodeBayar(const Transaksi &t) {
    string opsiBayar[] = { "Tunai", "QRIS" };
    int jumlahOpsiBayar = 2;
    int lebarBayar = hitungLebarKotak(opsiBayar, jumlahOpsiBayar);
    int pilihBayar = 0;

    while (true) {
        clearScreen();
        cetakStruk(t);
        cout << "\n";
        for (int i = 0; i < jumlahOpsiBayar; i++) {
            kotakMenu(opsiBayar[i], i == pilihBayar, lebarBayar);
        }
        cout << KUNING << "\n  [ Pilih metode pembayaran: ATAS/BAWAH lalu ENTER ]" << RESET << "\n";

        int arah = bacaTombolArah();
        if (arah == ARAH_ATAS) {
            pilihBayar--;
            if (pilihBayar < 0) pilihBayar = jumlahOpsiBayar - 1;
        } else if (arah == ARAH_BAWAH) {
            pilihBayar++;
            if (pilihBayar >= jumlahOpsiBayar) pilihBayar = 0;
        } else if (arah == ARAH_ENTER) {
            return opsiBayar[pilihBayar];
        }
    }
}

void prosesCheckOut() {
    clearScreen();
    judul("CHECK-OUT TAMU");
    string nomorKamar = bacaTeks("Nomor kamar");

    Transaksi *t = cariTransaksiAktif(nomorKamar);
    if (t == nullptr) {
        cout << MERAH << "  Tidak ada transaksi aktif di kamar ini." << RESET << "\n";
        return;
    }

    string metode = pilihMetodeBayar(*t);

    if (metode == "QRIS") {
        clearScreen();
        tampilkanHeaderQRIS(*t);
        getch();
    }

    t->metodeBayar = metode;
    t->status      = "Selesai";

    cariKamar(nomorKamar)->status = "Dibersihkan";
    cariTamuByKTP(t->ktpTamu)->totalBelanja += t->grandTotal;

    clearScreen();
    cetakStruk(*t);
    animasiLoading("Memproses pembayaran...");
    cout << HIJAU << "\n  Check-out berhasil! Total dibayar: "
         << formatRupiah(t->grandTotal) << " (" << metode << ")" << RESET << "\n";
}

void menuResepsionis(User *user) {
    string opsi[] = {
        "Check-in Tamu",
        "Tambah Layanan ke Tamu",
        "Check-out Tamu",
        "Lihat Semua Kamar",
        "Lihat Transaksi Aktif",
        "Logout"
    };
    int jumlahOpsi = 6;
    int pilihan;

    do {
        pilihan = pilihMenuKotak("                  MENU RESEPSIONIS - " + user->nama, opsi, jumlahOpsi);

        switch (pilihan) {
            case 0: prosesCheckIn();           tungguTombol(); break;
            case 1: prosesTambahLayanan();     tungguTombol(); break;
            case 2: prosesCheckOut();          tungguTombol(); break;
            case 3: tampilkanSemuaKamar();     tungguTombol(); break;
            case 4: tampilkanTransaksiAktif(); tungguTombol(); break;
        }
    } while (pilihan != jumlahOpsi - 1);
}

void prosesBersihkanKamar() {
    clearScreen();
    judul("SELESAIKAN PEMBERSIHAN KAMAR");
    cout << "  Kamar yang perlu dibersihkan:\n";
    for (auto &k : daftarKamar) {
        if (k.status == "Dibersihkan") cout << "  - " << k.nomor << "\n";
    }
    string nomor = bacaTeks("Nomor kamar yang sudah selesai dibersihkan");
    Kamar *kamar = cariKamar(nomor);
    if (kamar == nullptr || kamar->status != "Dibersihkan") {
        cout << MERAH << "  Kamar tidak dalam status Dibersihkan." << RESET << "\n";
        return;
    }
    kamar->status = "Kosong";
    cout << HIJAU << "  Kamar " << nomor << " sekarang siap digunakan!" << RESET << "\n";
}

void prosesSetMaintenance() {
    clearScreen();
    judul("SET KAMAR KE MAINTENANCE");
    string nomor = bacaTeks("Nomor kamar yang rusak");
    Kamar *kamar = cariKamar(nomor);
    if (kamar == nullptr) {
        cout << MERAH << "  Kamar tidak ditemukan." << RESET << "\n";
        return;
    }
    if (kamar->status == "Terisi") {
        cout << MERAH << "  Kamar sedang ditempati tamu, tidak bisa di-maintenance." << RESET << "\n";
        return;
    }
    kamar->status = "Maintenance";
    cout << KUNING << "  Kamar " << nomor << " sekarang dalam status Maintenance." << RESET << "\n";
}

void prosesSelesaiMaintenance() {
    clearScreen();
    judul("SELESAIKAN MAINTENANCE");
    string nomor = bacaTeks("Nomor kamar yang sudah selesai diperbaiki");
    Kamar *kamar = cariKamar(nomor);
    if (kamar == nullptr || kamar->status != "Maintenance") {
        cout << MERAH << "  Kamar tidak dalam status Maintenance." << RESET << "\n";
        return;
    }
    kamar->status = "Dibersihkan";
    cout << HIJAU << "  Kamar " << nomor << " selesai diperbaiki, menunggu dibersihkan." << RESET << "\n";
}

void menuHousekeeping(User *user) {
    string opsi[] = {
        "Lihat Semua Status Kamar",
        "Selesaikan Pembersihan Kamar",
        "Set Kamar ke Maintenance",
        "Selesaikan Maintenance",
        "Logout"
    };
    int jumlahOpsi = 5;
    int pilihan;

    do {
        pilihan = pilihMenuKotak("                  MENU HOUSEKEEPING - " + user->nama, opsi, jumlahOpsi);

        switch (pilihan) {
            case 0: tampilkanSemuaKamar();      tungguTombol(); break;
            case 1: prosesBersihkanKamar();     tungguTombol(); break;
            case 2: prosesSetMaintenance();     tungguTombol(); break;
            case 3: prosesSelesaiMaintenance(); tungguTombol(); break;
        }
    } while (pilihan != jumlahOpsi - 1);
}

void tampilkanBarOkupansi(double persen, int lebarBar) {
    int isi = (int)((persen * lebarBar / 100.0) + 0.5);

    if (persen > 0 && isi == 0) isi = 1;
    if (isi > lebarBar) isi = lebarBar;

    cout << MERAH;
    for (int i = 0; i < isi; i++) cout << "█";
    cout << RESET;

    cout << "\033[90m";
    for (int i = isi; i < lebarBar; i++) cout << "░";
    cout << RESET;
}

int hitungKamarStatus(const string &status) {
    int jumlah = 0;
    for (auto &k : daftarKamar) {
        if (k.status == status) jumlah++;
    }
    return jumlah;
}

int hitungTransaksiSelesai() {
    int jumlah = 0;
    for (auto &t : daftarTransaksi) {
        if (t.status == "Selesai") jumlah++;
    }
    return jumlah;
}

double hitungPendapatanSelesai() {
    double total = 0;
    for (auto &t : daftarTransaksi) {
        if (t.status == "Selesai") total += t.grandTotal;
    }
    return total;
}

void tampilkanDashboard() {
    clearScreen();
    judul("DASHBOARD MANAGER - " + tanggalSekarang());

    double totalPendapatan = hitungPendapatanSelesai();
    int transaksiSelesai = hitungTransaksiSelesai();

    int kosong       = hitungKamarStatus("Kosong");
    int terisi       = hitungKamarStatus("Terisi");
    int dipesan      = hitungKamarStatus("Dipesan");
    int dibersihkan  = hitungKamarStatus("Dibersihkan");
    int maintenance  = hitungKamarStatus("Maintenance");

    double okupansi = (!daftarKamar.empty()) ? (terisi * 100.0 / daftarKamar.size()) : 0;

    cout << "  Total Pendapatan      : " << HIJAU << formatRupiah(totalPendapatan) << RESET << "\n";
    cout << "  Transaksi Selesai     : " << transaksiSelesai << "\n";
    cout << "  Tingkat Okupansi      : ";
    tampilkanBarOkupansi(okupansi, 30);
    cout << " " << fixed << setprecision(1) << okupansi << "%\n\n";

    cout << "  Status Kamar:\n";
    cout << "  " << HIJAU << "Kosong: " << kosong << RESET << "   ";
    cout << MERAH << "Terisi: " << terisi << RESET << "   ";
    cout << KUNING << "Dipesan: " << dipesan << RESET << "   ";
    cout << BIRU << "Dibersihkan: " << dibersihkan << RESET << "   ";
    cout << UNGU << "Maintenance: " << maintenance << RESET << "\n";
}

void tampilkanLaporanPendapatan() {
    clearScreen();
    judul("LAPORAN PENDAPATAN DETAIL");

    double totalKamar = 0, totalLayanan = 0, totalGrand = 0;
    int    jumlah = 0;
    for (auto &t : daftarTransaksi) {
        if (t.status == "Selesai") {
            totalKamar   += t.hargaKamar;
            totalLayanan += t.totalLayanan;
            totalGrand   += t.grandTotal;
            jumlah++;
        }
    }

    cout << left << setw(28) << "  Jumlah Transaksi Selesai" << jumlah << "\n";
    cout << left << setw(28) << "  Pendapatan Kamar" << formatRupiah(totalKamar) << "\n";
    cout << left << setw(28) << "  Pendapatan Layanan" << formatRupiah(totalLayanan) << "\n";
    garis(LEBAR_LAYAR);
    cout << TEBAL << KUNING << left << setw(28) << "  TOTAL PENDAPATAN" << formatRupiah(totalGrand) << RESET << "\n";
}

void tampilkanOkupansi() {
    clearScreen();
    judul("STATISTIK OKUPANSI PER TIPE KAMAR");

    string tipeUnik[4] = {"Standard", "Deluxe", "Suite", "Presidential"};

    cout << "\n  " << TEBAL << BIRU << "Okupansi Saat Ini (kamar yang sedang Terisi)" << RESET << "\n";
    for (int j = 0; j < 4; j++) {
        int total = 0, terisi = 0;
        for (auto &k : daftarKamar) {
            if (k.tipe == tipeUnik[j]) {
                total++;
                if (k.status == "Terisi") terisi++;
            }
        }
        if (total == 0) continue;
        double persen = terisi * 100.0 / total;

        cout << "  " << left << setw(16) << tipeUnik[j];
        tampilkanBarOkupansi(persen, 30);
        cout << " " << terisi << "/" << total << " ("
             << fixed << setprecision(1) << persen << "%)\n";
    }

    cout << "\n  " << TEBAL << BIRU << "Total Booking Sepanjang Waktu (semua transaksi)" << RESET << "\n";
    for (int j = 0; j < 4; j++) {
        int totalKamarTipe = 0;
        for (auto &k : daftarKamar) {
            if (k.tipe == tipeUnik[j]) totalKamarTipe++;
        }
        if (totalKamarTipe == 0) continue;

        int totalBooking = 0;
        for (auto &t : daftarTransaksi) {
            Kamar *k = cariKamar(t.nomorKamar);
            if (k != nullptr && k->tipe == tipeUnik[j]) totalBooking++;
        }
        cout << "  " << left << setw(16) << tipeUnik[j] << totalBooking << " kali dibooking\n";
    }
}

void menuManager(User *user) {
    string opsi[] = {
        "Dashboard Utama",
        "Lihat Semua Kamar",
        "Lihat Transaksi Aktif",
        "Laporan Pendapatan",
        "Statistik Okupansi",
        "Logout"
    };
    int jumlahOpsi = 6;
    int pilihan;

    do {
        pilihan = pilihMenuKotak("                MENU MANAGER - " + user->nama, opsi, jumlahOpsi);

        switch (pilihan) {
            case 0: tampilkanDashboard();         tungguTombol(); break;
            case 1: tampilkanSemuaKamar();         tungguTombol(); break;
            case 2: tampilkanTransaksiAktif();     tungguTombol(); break;
            case 3: tampilkanLaporanPendapatan();  tungguTombol(); break;
            case 4: tampilkanOkupansi();           tungguTombol(); break;
        }
    } while (pilihan != jumlahOpsi - 1);
}

User* login() {
    int percobaan = 0;
    while (percobaan < 3) {
        tampilkanBanner();
        judul("               LOGIN - GOTELL HOTEL SYSTEM");
        string username = bacaTeks("Username");
        string password = bacaTeks("Password");

        animasiLoading("Memeriksa data login...");

        User *user = cariUser(username);
        if (user != nullptr && user->password == password) {
            return user;
        }
        percobaan++;
        cout << MERAH << "\n  Username atau password salah! (Sisa percobaan: "
             << (3 - percobaan) << ")" << RESET << "\n";
        if (percobaan < 3) tungguTombol();
    }
    return nullptr;
}

void ketik(const string &teks, int delayMs = 50) {
    for (char c : teks) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delayMs));
    }
}

void tampilkanBanner() {
    clearScreen();
    cout << BIRU << TEBAL;
    cout << R"(
       ██████╗  ██████╗ ████████╗███████╗██╗     ██╗
      ██╔════╝ ██╔═══██╗╚══██╔══╝██╔════╝██║     ██║
      ██║  ███╗██║   ██║   ██║   █████╗  ██║     ██║
      ██║   ██║██║   ██║   ██║   ██╔══╝  ██║     ██║
      ╚██████╔╝╚██████╔╝   ██║   ███████╗███████╗███████╗
       ╚═════╝  ╚═════╝    ╚═╝   ╚══════╝╚══════╝╚══════╝
)";
    cout << RESET;
    cout << KUNING << TEBAL;
    cout << "   S m a r t   H o t e l   M a n a g e m e n t   S y s t e m\n";
    cout << RESET;
    garis(64, '=');
}

void tampilkanPenutup() {
    clearScreen();

    cout << BIRU << TEBAL;
    cout << R"(
   ██████╗  ██████╗  ██████╗ ██████╗     ██████╗ ██╗   ██╗███████╗
  ██╔════╝ ██╔═══██╗██╔═══██╗██╔══██╗    ██╔══██╗╚██╗ ██╔╝██╔════╝
  ██║  ███╗██║   ██║██║   ██║██║  ██║    ██████╔╝ ╚████╔╝ █████╗
  ██║   ██║██║   ██║██║   ██║██║  ██║    ██╔══██╗  ╚██╔╝  ██╔══╝
  ╚██████╔╝╚██████╔╝╚██████╔╝██████╔╝    ██████╔╝   ██║   ███████╗
   ╚═════╝  ╚═════╝  ╚═════╝ ╚═════╝     ╚═════╝    ╚═╝   ╚══════╝
)";
    cout << RESET;

    cout << KUNING << TEBAL;
    cout << "        S e s s i o n   C l o s e d   -   G o T e l l   H o t e l\n";
    cout << RESET;

    garis(LEBAR_LAYAR, '=');

    cout << "\n";

    cout << BIRU << TEBAL;
    ketik("          Terima kasih telah menggunakan GoTell Hotel.\n", 50);
    this_thread::sleep_for(chrono::milliseconds(300));
    ketik("                 Semoga harimu menyenangkan. . .\n", 50);
    this_thread::sleep_for(chrono::milliseconds(300));
    cout << RESET;

    cout << "\n";

    garis(LEBAR_LAYAR, '=');
}

int menuAwal() {
    string opsi[] = { "Login", "Keluar" };
    int jumlahOpsi = 2;
    return pilihMenuKotak("                SELAMAT DATANG DI GOTELL HOTEL", opsi, jumlahOpsi);
}

int main() {
    system("chcp 65001 > nul");

    inisialisasiDataAwal();

    bool lanjutProgram = true;
    while (lanjutProgram) {
        int pilihanAwal = menuAwal();
        if (pilihanAwal == 1) {
            lanjutProgram = false;
            break;
        }

        User *user = login();
        if (user == nullptr) {
            cout << MERAH << "\n  Gagal login 3 kali. Kembali ke menu awal.\n" << RESET;
            tungguTombol();
            continue;
        }

        clearScreen();
        tampilkanBanner();
        cout << HIJAU << "\n  Selamat datang, " << user->nama
             << " (" << user->role << ")" << RESET << "\n";
        tungguTombol();

        if (user->role == "Manager") {
            menuManager(user);
        } else if (user->role == "Resepsionis") {
            menuResepsionis(user);
        } else if (user->role == "Housekeeping") {
            menuHousekeeping(user);
        }

        clearScreen();
        tampilkanBanner();
        cout << KUNING << "\n  Logout dari akun " << user->username
             << " (" << user->role << ")" << RESET << "\n";
        animasiLoading("Mengakhiri sesi akun...");
        tungguTombol();
    }
    tampilkanPenutup();
    return 0;
}