<div align="center">

```
       ██████╗  ██████╗ ████████╗███████╗██╗     ██╗
      ██╔════╝ ██╔═══██╗╚══██╔══╝██╔════╝██║     ██║
      ██║  ███╗██║   ██║   ██║   █████╗  ██║     ██║
      ██║   ██║██║   ██║   ██║   ██╔══╝  ██║     ██║
           ╚██████╔╝╚██████╔╝   ██║   ███████╗███████╗███████╗
            ╚═════╝  ╚═════╝    ╚═╝   ╚══════╝╚══════╝╚══════╝
```

### 🏨 Smart Hotel Management System

<br/>

[![C++](https://img.shields.io/badge/Language-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)](https://isocpp.org/)
[![Console App](https://img.shields.io/badge/Type-Console%20App-F97316?style=for-the-badge&logo=windowsterminal&logoColor=white)]()
[![Role Based](https://img.shields.io/badge/Login-Role%20Based-0EA5E9?style=for-the-badge&logo=shield&logoColor=white)]()
[![Windows](https://img.shields.io/badge/Platform-Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)]()
[![Status](https://img.shields.io/badge/Status-Development-22C55E?style=for-the-badge)]()

<br/>

> Aplikasi manajemen hotel berbasis **console/CLI** yang dibuat menggunakan **C++** murni.  
> Mensimulasikan operasional hotel nyata dengan tiga role: **Manager**, **Resepsionis**, dan **Housekeeping**.

</div>

---

## 📌 Daftar Isi

| # | Bagian |
|---|--------|
| 1 | [Tentang Proyek](#-tentang-proyek) |
| 2 | [Fitur Utama](#-fitur-utama) |
| 3 | [Tampilan Program](#️-tampilan-program) |
| 4 | [Konsep C++ yang Digunakan](#-konsep-c-yang-digunakan) |
| 5 | [Struktur Data yang Di-set di Program](#-struktur-data-yang-di-set-di-program) |
| 6 | [Alur Program](#-alur-program) |
| 7 | [Cara Menjalankan](#-cara-menjalankan) |
| 8 | [Library yang Digunakan](#-library-yang-digunakan) |
| 9 | [Rumus Perhitungan](#-rumus-perhitungan) |
| 10 | [Catatan Batasan Program](#️-catatan-batasan-program) |
| 11 | [Pembagian Tugas Tim](#-pembagian-tugas-tim-7-anggota) |
| 12 | [Lisensi](#-lisensi) |

---

## 📖 Tentang Proyek

GoTell dibuat sebagai studi kasus penerapan konsep dasar pemrograman C++ dalam bentuk aplikasi sederhana yang menyerupai sistem hotel. Program ini berfokus pada pengelolaan kamar, tamu, layanan, transaksi, pembayaran, laporan, dan status kamar.

Tampilan program dibuat lebih interaktif dengan beberapa elemen berikut:

- 🎨 Banner ASCII art **GoTell**
- 🌈 Warna teks menggunakan ANSI escape code
- 📦 Menu berbentuk kotak interaktif
- ⌨️ Navigasi menggunakan tombol **panah atas**, **panah bawah**, dan **Enter**
- ⏳ Animasi loading sederhana
- 🧾 Struk transaksi berbasis teks
- 💳 Simulasi tampilan QRIS menggunakan karakter/simbol
- 🚪 Banner penutup saat program selesai

> **📝 Catatan:** Versi kode ini **tidak memakai file `.txt` atau database**. Semua data disimpan di memori selama program berjalan. Jika program ditutup lalu dijalankan ulang, data akan kembali ke data default dari kode.

---

## ✨ Fitur Utama

<details>
<summary><b>👔 Manager</b></summary>
<br/>

| No | Fitur | Keterangan |
|:--:|-------|------------|
| 1 | Dashboard Utama | Menampilkan total pendapatan, transaksi selesai, tingkat okupansi, dan status kamar |
| 2 | Lihat Semua Kamar | Menampilkan seluruh kamar beserta tipe, lantai, harga, dan status |
| 3 | Lihat Transaksi Aktif | Menampilkan transaksi yang masih berstatus aktif |
| 4 | Laporan Pendapatan | Menampilkan total pendapatan kamar, layanan, dan grand total |
| 5 | Statistik Okupansi | Menampilkan okupansi per tipe kamar dan total booking |
| 6 | Logout | Keluar dari akun manager dan kembali ke menu awal |

</details>

<details>
<summary><b>🧾 Resepsionis</b></summary>
<br/>

| No | Fitur | Keterangan |
|:--:|-------|------------|
| 1 | Check-in Tamu | Memilih kamar kosong, input data tamu, membuat transaksi aktif |
| 2 | Tambah Layanan ke Tamu | Menambahkan layanan tambahan ke transaksi aktif |
| 3 | Check-out Tamu | Menampilkan struk, memilih pembayaran Tunai/QRIS, menyelesaikan transaksi |
| 4 | Lihat Semua Kamar | Melihat status semua kamar |
| 5 | Lihat Transaksi Aktif | Melihat transaksi yang sedang berjalan |
| 6 | Logout | Keluar dari akun resepsionis dan kembali ke menu awal |

</details>

<details>
<summary><b>🧹 Housekeeping</b></summary>
<br/>

| No | Fitur | Keterangan |
|:--:|-------|------------|
| 1 | Lihat Semua Status Kamar | Menampilkan seluruh kamar dan statusnya |
| 2 | Selesaikan Pembersihan Kamar | Mengubah kamar dari `Dibersihkan` menjadi `Kosong` |
| 3 | Set Kamar ke Maintenance | Mengubah kamar menjadi `Maintenance` jika tidak sedang terisi |
| 4 | Selesaikan Maintenance | Mengubah kamar dari `Maintenance` menjadi `Dibersihkan` |
| 5 | Logout | Keluar dari akun housekeeping dan kembali ke menu awal |

</details>

<details>
<summary><b>🔐 Validasi Input</b></summary>
<br/>

Program sudah menambahkan validasi agar input tidak mudah menyebabkan error:

- Nama tamu hanya boleh huruf dan spasi
- Nomor KTP wajib **16 digit angka**
- Nomor HP wajib angka, panjang **9–13 digit**, dan diawali `08` atau `62`
- Input angka tidak menerima teks seperti `1a`, `abc`, atau nilai kosong — parsing dilakukan manual karakter per karakter
- Nomor kamar harus benar-benar ada dan berstatus `Kosong` saat check-in
- Login dibatasi maksimal **3 kali percobaan**

</details>

---

## 🖼️ Tampilan Program

Bagian ini dapat diisi dengan screenshot asli hasil running program. Karena kode ini berbasis console, screenshot sebaiknya diambil langsung dari terminal/Command Prompt.

<details>
<summary><b>📂 Struktur folder aset yang disarankan</b></summary>
<br/>

```text
assets/
│
├── gotell-banner.svg
├── screenshot-menu-awal.png
├── screenshot-login.png
├── screenshot-dashboard-manager.png
├── screenshot-menu-resepsionis.png
├── screenshot-checkin.png
├── screenshot-struk-qris.png
├── screenshot-menu-housekeeping.png
└── screenshot-penutup.png
```

</details>

### 🔐 Menu Awal & Login

<div align="center">
  <img src="assets/screenshot-menu-awal.png" alt="Menu Awal GoTell" width="80%"/>
  <br/><br/>
  <img src="assets/screenshot-login.png" alt="Login GoTell" width="80%"/>
</div>

### 👔 Dashboard Manager

<div align="center">
  <img src="assets/screenshot-dashboard-manager.png" alt="Dashboard Manager GoTell" width="80%"/>
</div>

### 🧾 Menu Resepsionis & Check-in

<div align="center">
  <img src="assets/screenshot-menu-resepsionis.png" alt="Menu Resepsionis GoTell" width="80%"/>
  <br/><br/>
  <img src="assets/screenshot-checkin.png" alt="Check-in GoTell" width="80%"/>
</div>

### 💳 Struk & Simulasi QRIS

<div align="center">
  <img src="assets/screenshot-struk-qris.png" alt="Struk dan QRIS GoTell" width="80%"/>
</div>

### 🧹 Menu Housekeeping

<div align="center">
  <img src="assets/screenshot-menu-housekeeping.png" alt="Menu Housekeeping GoTell" width="80%"/>
</div>

---

## 🧠 Konsep C++ yang Digunakan

| Konsep | Penerapan dalam Program |
|--------|--------------------------|
| `struct` | Membuat model data `Kamar`, `Tamu`, `Layanan`, `Transaksi`, dan `User` |
| **Array statis + counter** | Menyimpan data utama seperti `daftarKamar[MAX_KAMAR]`, `daftarUser[MAX_USER]`, dll. dengan variabel counter `jumlahKamar`, `jumlahUser`, dll. |
| Fungsi | Hampir seluruh proses dipisahkan menjadi fungsi agar kode lebih rapi dan modular |
| Pointer | Fungsi pencarian seperti `cariKamar()` dan `cariTransaksiAktif()` mengembalikan alamat data agar data asli bisa langsung diubah |
| Looping | Digunakan untuk menampilkan data, mencari data, validasi input, dan menjalankan menu |
| Percabangan | Mengatur pilihan menu, role user, validasi status kamar, dan metode pembayaran |
| String processing | Digunakan untuk validasi nama, KTP, nomor HP, format rupiah, dan format tanggal |
| ANSI escape code | Digunakan untuk memberi warna pada output console |
| **Parsing angka manual** | Konversi string ke integer dilakukan karakter per karakter tanpa `stoi()` untuk keamanan input |

---

## 🗂 Struktur Data yang Di-set di Program

Semua data awal dibuat langsung dari kode melalui fungsi `inisialisasiDataAwal()`. Fungsi ini akan membersihkan data lama lalu mengisi kembali data default kamar, user, dan layanan.

### 🛏️ Daftar Kamar Default

> Total kamar default: **14 kamar**

| Nomor | Tipe | Lantai | Kapasitas | Harga/Malam |
|:-----:|------|:------:|:---------:|------------:|
| 101 | Standard | 1 | 2 orang | Rp 450.000 |
| 102 | Standard | 1 | 2 orang | Rp 450.000 |
| 103 | Standard | 1 | 2 orang | Rp 450.000 |
| 104 | Standard | 1 | 3 orang | Rp 550.000 |
| 105 | Standard | 1 | 2 orang | Rp 450.000 |
| 201 | Deluxe | 2 | 2 orang | Rp 750.000 |
| 202 | Deluxe | 2 | 2 orang | Rp 750.000 |
| 203 | Deluxe | 2 | 3 orang | Rp 950.000 |
| 204 | Deluxe | 2 | 2 orang | Rp 850.000 |
| 301 | Suite | 3 | 4 orang | Rp 1.500.000 |
| 302 | Suite | 3 | 4 orang | Rp 1.500.000 |
| 303 | Suite | 3 | 2 orang | Rp 1.800.000 |
| 401 | Presidential | 4 | 6 orang | Rp 5.000.000 |
| 402 | Presidential | 4 | 4 orang | Rp 4.500.000 |

### 👤 Daftar Akun Default

> Total akun default: **5 user**

| Username | Password | Nama | Role |
|----------|----------|------|------|
| `manager` | `manager123` | Iqbal ganteng | 👔 Manager |
| `resep1` | `resep123` | Adji | 🧾 Resepsionis |
| `resep2` | `resep456` | zhyla | 🧾 Resepsionis |
| `hk1` | `hk123` | Nurra | 🧹 Housekeeping |
| `hk2` | `hk456` | Wira | 🧹 Housekeeping |

### 🛎️ Daftar Layanan Default

> Total layanan default: **10 layanan**

| ID | Nama Layanan | Harga |
|:--:|--------------|------:|
| `FB-01` | Sarapan Pagi (Buffet) | Rp 85.000 |
| `FB-02` | Room Service 24 Jam | Rp 50.000 |
| `FB-03` | Makan Malam Romantis | Rp 350.000 |
| `SP-01` | Pijat Tradisional | Rp 250.000 |
| `SP-02` | Spa Pasangan | Rp 750.000 |
| `LN-01` | Laundry Express | Rp 50.000 |
| `TR-01` | Antar Jemput Bandara | Rp 200.000 |
| `TR-02` | City Tour Setengah Hari | Rp 350.000 |
| `EN-01` | Karaoke 1 Jam | Rp 150.000 |
| `BS-01` | Sewa Meeting Room | Rp 500.000 |

### 🚪 Status Kamar

| Status | Warna | Arti |
|--------|:-----:|------|
| `Kosong` | 🟢 | Kamar tersedia dan bisa dipilih saat check-in |
| `Terisi` | 🔴 | Kamar sedang ditempati tamu |
| `Dipesan` | 🟡 | Status disiapkan di program, belum ada fitur reservasi pada versi ini |
| `Dibersihkan` | 🔵 | Kamar sudah check-out dan menunggu dibersihkan housekeeping |
| `Maintenance` | 🟣 | Kamar sedang dalam perbaikan |

---

## 🔄 Alur Program

```text
Mulai
  │
  ▼
Set encoding console ke UTF-8
  │
  ▼
Inisialisasi data awal dari kode
  │
  ▼
Tampilkan menu awal
  │
  ├── Login
  │     │
  │     ▼
  │   Input username dan password
  │     │
  │     ├── Gagal 3 kali → kembali ke menu awal
  │     │
  │     └── Berhasil
  │           │
  │           ▼
  │        Cek role user
  │           │
  │           ├── Manager       → Menu Manager
  │           ├── Resepsionis   → Menu Resepsionis
  │           └── Housekeeping  → Menu Housekeeping
  │
  │        Setelah logout
  │           │
  │           ▼
  │        Kembali ke menu awal
  │
  └── Keluar
        │
        ▼
     Tampilkan banner penutup
        │
        ▼
      Selesai
```

<details>
<summary><b>📋 Alur Check-in</b></summary>
<br/>

```text
Check-in
  │
  ├── Cek batas transaksi (maks. 1000)
  ├── Tampilkan kamar kosong
  ├── Input nomor kamar
  ├── Validasi kamar harus ada dan statusnya Kosong
  ├── Input nama tamu
  ├── Input KTP 16 digit
  ├── Input nomor HP
  ├── Input lama menginap
  ├── Tambah data tamu jika belum pernah ada
  ├── Buat transaksi aktif di array daftarTransaksi
  ├── Ubah status kamar menjadi Terisi
  └── Tampilkan pesan check-in berhasil
```

</details>

<details>
<summary><b>📋 Alur Check-out</b></summary>
<br/>

```text
Check-out
  │
  ├── Input nomor kamar
  ├── Cari transaksi aktif
  ├── Tampilkan struk
  ├── Pilih metode bayar
  │     ├── Tunai
  │     └── QRIS → tampilkan simulasi QRIS
  ├── Ubah transaksi menjadi Selesai
  ├── Ubah kamar menjadi Dibersihkan
  ├── Tambahkan total belanja tamu
  └── Tampilkan struk akhir
```

</details>

<details>
<summary><b>📋 Alur Housekeeping</b></summary>
<br/>

```text
Kamar selesai check-out
  │
  ▼
Status kamar menjadi Dibersihkan
  │
  ▼
Housekeeping memilih "Selesaikan Pembersihan Kamar"
  │
  ▼
Status kamar berubah menjadi Kosong
```

</details>

---

## 🚀 Cara Menjalankan

> ⚠️ Program ini paling aman dijalankan di **Windows**, karena memakai `<conio.h>` untuk tombol panah, `system("cls")` untuk clear screen, dan `system("chcp 65001")` untuk UTF-8.

### 1. Compile dengan MinGW/g++

```bash
# Jika nama file masih default:
g++ -std=c++17 "Pasted code(72).cpp" -o GoTell.exe

# Jika file sudah diubah namanya:
g++ -std=c++17 GoTell.cpp -o GoTell.exe
```

### 2. Jalankan program

```bash
GoTell.exe
```

> Untuk Linux/Mac, program perlu disesuaikan terlebih dahulu karena `<conio.h>` dan `system("cls")` bersifat khusus Windows.

---

## 📚 Library yang Digunakan

| Library | Fungsi dalam Program | Status |
|---------|----------------------|:------:|
| `<iostream>` | Input dan output utama seperti `cin`, `cout`, dan `getline` | ✅ Wajib |
| `<iomanip>` | Merapikan tabel dan angka dengan `setw`, `setfill`, `fixed`, `setprecision` | ✅ Wajib |
| `<string>` | Menggunakan tipe data `string` dan `to_string` | ✅ Wajib |
| `<ctime>` | Mengambil tanggal sekarang untuk dashboard manager | 🔵 Dipakai |
| `<sstream>` | Membuat format tanggal dengan `ostringstream` | 🔵 Dipakai |
| `<cstdlib>` | Menjalankan `system("cls")` dan `system("chcp 65001 > nul")` | 🔵 Dipakai |
| `<thread>` | Membuat animasi loading | 🔵 Dipakai |
| `<chrono>` | Mengatur jeda waktu animasi loading | 🔵 Dipakai |
| `<conio.h>` | Mengambil input tombol tanpa Enter memakai `getch()` | ⚠️ Windows only |

---

## 🧮 Rumus Perhitungan

### 💰 Total Pembayaran

```text
biaya kamar  = harga kamar per malam × lama menginap
subtotal     = biaya kamar + total layanan
pajak        = subtotal × 11%
service      = subtotal × 5%
grand total  = subtotal + pajak + service
```

Dalam kode, pajak disimpan pada konstanta:

```cpp
const double PAJAK          = 0.11;
const double SERVICE_CHARGE = 0.05;
```

### 📊 Okupansi Kamar

```text
okupansi = (jumlah kamar berstatus Terisi / total kamar) × 100%
```

Contoh:

```text
Total kamar  = 14
Kamar terisi = 3

okupansi = 3 / 14 × 100% = 21.4%
```

### 📈 Progress Bar Okupansi

Progress bar dibuat dengan lebar **30 karakter**:

```text
jumlah blok = persen × lebar bar / 100  (dibulatkan ke terdekat)
```

```cpp
int isi = (int)((persen * lebarBar / 100.0) + 0.5);
```

> Jika okupansi > 0% tetapi hasil blok masih 0, program tetap menampilkan minimal **1 blok** agar terlihat ada isi.

---

## ⚠️ Catatan Batasan Program

Versi kode ini sengaja dibuat tanpa file `.txt`, sehingga beberapa hal berikut perlu diperhatikan:

| # | Batasan |
|:-:|---------|
| 1 | Data hanya tersimpan selama program masih berjalan |
| 2 | Jika program ditutup, semua data kembali ke default |
| 3 | Kapasitas maksimum: **100 kamar**, **50 user**, **500 tamu**, **50 layanan**, **1.000 transaksi** |
| 4 | Program belum memiliki fitur penyimpanan permanen |
| 5 | Program belum memiliki fitur reservasi kamar |
| 6 | Program belum memiliki fitur pembatalan reservasi |
| 7 | Program belum memiliki fitur upgrade/pindah kamar |
| 8 | Program belum memiliki fitur cetak ulang struk |
| 9 | Status `Dipesan` sudah dikenali di tampilan, tetapi belum ada menu yang mengubah kamar ke status ini |
| 10 | QRIS yang ditampilkan hanya simulasi simbol, bukan QRIS asli yang bisa discan |

---

## 👥 Pembagian Tugas Tim (7 Anggota)

> Jumlah akun login di program adalah **5 akun**, sedangkan pembagian tugas dibuat untuk **7 anggota tim**.

| # | Anggota | Modul | Tanggung Jawab Utama |
|:-:|---------|-------|----------------------|
| 1 | **Iqbal** | Core System & Data Model | Struct, array global, konstanta, alur utama, inisialisasi data |
| 2 | **Zhyla** | Input Validation & Utility | Validasi nama/KTP/HP/angka, format rupiah, format tanggal, ID transaksi |
| 3 | **Adji** | UI Console & Navigasi | Banner, menu kotak, tombol panah, animasi loading, tampilan penutup |
| 4 | **Nurra** | Data Master & Pencarian | Data default kamar/user/layanan, fungsi pencarian pointer |
| 5 | **Wira** | Resepsionis & Transaksi | Check-in, check-out, layanan, struk, QRIS, menu resepsionis |
| 6 | **Sultan** | Housekeeping & Status Kamar | Status kamar, pembersihan, maintenance, menu housekeeping |
| 7 | **Isam** | Manager, Dashboard & Statistik | Dashboard, laporan pendapatan, statistik okupansi, login, menu manager |

---

<details>
<summary><b>📂 Detail Fungsi per Anggota (klik untuk expand)</b></summary>

<br/>

### 🟦 Iqbal — Core System & Data Model
> Pondasi utama program: struct, array statis, konstanta global, dan inisialisasi awal.

**Konstanta & Data Global:**
```cpp
const int SOFT_LIMIT_TAMU      = 500;
const int SOFT_LIMIT_TRANSAKSI = 1000;
const int MAX_KAMAR            = 100;
const int MAX_USER             = 50;
const int MAX_TAMU             = 500;
const int MAX_LAYANAN          = 50;
const int MAX_TRANSAKSI        = 1000;
const double PAJAK             = 0.11;
const double SERVICE_CHARGE    = 0.05;

Kamar     daftarKamar[MAX_KAMAR];
User      daftarUser[MAX_USER];
Tamu      daftarTamu[MAX_TAMU];
Layanan   daftarLayanan[MAX_LAYANAN];
Transaksi daftarTransaksi[MAX_TRANSAKSI];

int jumlahKamar, jumlahUser, jumlahTamu, jumlahLayanan, jumlahTransaksi;
```

**Struct:** `Kamar`, `Tamu`, `Layanan`, `Transaksi`, `User`

**Fungsi:** `inisialisasiDataAwal()`, `menuAwal()`, `main()`

---

### 🟩 Zhyla — Input Validation & Utility

| Fungsi | Keterangan |
|--------|------------|
| `bacaTeks(label, wajib)` | Membaca input teks dengan validasi wajib isi |
| `bacaTeksPanjang(label, min, max)` | Membaca teks dengan batas panjang karakter |
| `semuaAngka(s)` | Mengecek apakah string hanya berisi angka |
| `bacaKTP(label)` | Membaca dan memvalidasi KTP 16 digit |
| `namaValid(s)` | Mengecek apakah nama hanya huruf dan spasi |
| `bacaNamaTamu(label)` | Membaca nama tamu dengan validasi |
| `formatHPValid(s)` | Mengecek format nomor HP (diawali `08`/`62`, 9–13 digit) |
| `bacaNoHP(label)` | Membaca nomor HP dengan validasi |
| `bacaAngka(label, min, max)` | Membaca angka integer dengan parsing manual |
| `formatRupiah(angka)` | Mengubah angka menjadi format `Rp xxx.xxx` |
| `tanggalSekarang()` | Mengembalikan tanggal hari ini sebagai string |
| `buatID(prefix)` | Membuat ID transaksi unik dengan prefix tertentu |

---

### 🟨 Adji — UI Console & Navigasi Interaktif

| Fungsi | Keterangan |
|--------|------------|
| `clearScreen()` | Membersihkan layar console |
| `tampilkanBanner()` | Menampilkan banner ASCII art GoTell |
| `judul(teks)` | Menampilkan judul seksi dengan border |
| `garis(panjang, isi)` | Menampilkan garis pemisah |
| `bacaTombolArah()` | Membaca input tombol panah dan Enter |
| `kotakMenu(teks, aktif, lebarKotak)` | Menggambar satu item menu berbentuk kotak |
| `hitungLebarKotak(opsi[], jumlahOpsi)` | Menghitung lebar kotak menu otomatis |
| `pilihMenuKotak(judulMenu, opsi[], jumlahOpsi)` | Menjalankan menu interaktif dengan tombol panah |
| `tungguTombol()` | Menunggu pengguna menekan sembarang tombol |
| `animasiLoading(pesan, langkah)` | Menampilkan animasi loading dengan teks |
| `tampilkanPenutup()` | Menampilkan banner penutup saat program selesai |

---

### 🟪 Nurra — Data Master & Pencarian Pointer

| Fungsi | Keterangan |
|--------|------------|
| `tambahKamar(...)` | Menambahkan satu data kamar ke array |
| `inisialisasiKamarDefault()` | Mengisi 14 kamar default ke array |
| `tambahUser(...)` | Menambahkan satu akun user ke array |
| `inisialisasiUser()` | Mengisi 5 akun default ke array |
| `tambahLayanan(...)` | Menambahkan satu layanan ke array |
| `inisialisasiLayanan()` | Mengisi 10 layanan default ke array |
| `cariKamar(nomor)` | Mencari kamar berdasarkan nomor, return pointer |
| `cariUser(username)` | Mencari user berdasarkan username, return pointer |
| `cariTamuByKTP(ktp)` | Mencari tamu berdasarkan KTP, return pointer |
| `cariLayanan(id)` | Mencari layanan berdasarkan ID, return pointer |
| `cariTransaksiAktif(nomorKamar)` | Mencari transaksi aktif berdasarkan nomor kamar, return pointer |
| `ambilOrTambahTamu(nama, ktp, telp)` | Mengambil data tamu yang sudah ada atau menambahkan baru ke array |

---

### 🟥 Wira — Resepsionis & Transaksi

| Fungsi | Keterangan |
|--------|------------|
| `hitungTotalAkhir(hargaKamar, totalLayanan)` | Menghitung grand total dengan pajak dan service charge |
| `bacaKamarKosong()` | Membaca input nomor kamar yang berstatus `Kosong` |
| `prosesCheckIn()` | Menjalankan alur check-in lengkap |
| `prosesTambahLayanan()` | Menambahkan layanan ke transaksi aktif |
| `pilihMetodeBayar(t)` | Menampilkan pilihan metode pembayaran |
| `prosesCheckOut()` | Menjalankan alur check-out lengkap |
| `tampilkanKamarTersedia()` | Menampilkan daftar kamar berstatus `Kosong` |
| `tampilkanLayanan()` | Menampilkan daftar layanan yang tersedia |
| `tampilkanTransaksiAktif()` | Menampilkan semua transaksi berstatus aktif |
| `cetakStruk(t)` | Mencetak struk transaksi ke console |
| `tampilkanLogoQRIS()` | Menampilkan logo teks QRIS |
| `tampilkanDataQRIS(t)` | Menampilkan detail pembayaran pada tampilan QRIS |
| `tampilkanQRISSimbol()` | Menampilkan simulasi kode QR menggunakan simbol |
| `tampilkanHeaderQRIS(t)` | Menampilkan header nota QRIS |
| `menuResepsionis(user)` | Menjalankan menu utama Resepsionis |

---

### 🟦 Sultan — Housekeeping & Status Kamar

| Fungsi | Keterangan |
|--------|------------|
| `warnaStatusKamar(status)` | Mengembalikan kode warna ANSI sesuai status kamar |
| `tampilkanSemuaKamar()` | Menampilkan seluruh kamar beserta statusnya |
| `prosesBersihkanKamar()` | Mengubah kamar dari `Dibersihkan` menjadi `Kosong` |
| `prosesSetMaintenance()` | Mengubah kamar menjadi `Maintenance` |
| `prosesSelesaiMaintenance()` | Mengubah kamar dari `Maintenance` menjadi `Dibersihkan` |
| `menuHousekeeping(user)` | Menjalankan menu utama Housekeeping |

---

### 🟫 Isam — Manager, Dashboard & Statistik

| Fungsi | Keterangan |
|--------|------------|
| `tampilkanBarOkupansi(persen, lebarBar)` | Menggambar progress bar okupansi kamar |
| `hitungKamarStatus(status)` | Menghitung jumlah kamar berdasarkan status tertentu |
| `hitungTransaksiSelesai()` | Menghitung jumlah transaksi berstatus selesai |
| `hitungPendapatanSelesai()` | Menghitung total pendapatan dari transaksi selesai |
| `tampilkanDashboard()` | Menampilkan dashboard ringkasan operasional hotel |
| `tampilkanLaporanPendapatan()` | Menampilkan laporan rincian pendapatan |
| `tampilkanOkupansi()` | Menampilkan statistik okupansi per tipe kamar |
| `menuManager(user)` | Menjalankan menu utama Manager |
| `login()` | Menangani proses autentikasi user (maks. 3 percobaan) |

</details>

> 💡 **Saran kerja tim:** setiap anggota dapat membuat branch sesuai modulnya, misalnya `feature/resepsionis`, `feature/housekeeping`, `feature/manager`, lalu digabungkan ke branch utama setelah direview.

---

## 📄 Lisensi

Proyek ini dibuat untuk keperluan tugas dan pembelajaran. Bebas digunakan serta dimodifikasi untuk kebutuhan edukasi.

---

<div align="center">

**GoTell : Smart Hotel Management System**

Made with ❤️ using C++

</div>
