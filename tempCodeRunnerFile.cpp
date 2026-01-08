#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pesanan {
    int id;
    string nama;
    string menu;
    string status;
    string jenis;   // Makan di Tempat / Bawa Pulang
};

vector<Pesanan> antrian;
int idCounter = 1;

// ================= CREATE PESANAN =================
void tambahPesanan() {
    Pesanan p;
    char konfirmasi;
    int pilihan, jenis;

    cout << "\n=== PEMBUATAN PESANAN ===\n";
    p.id = idCounter++;

    cout << "Masukkan Nama Customer : ";
    cin >> p.nama;
    cout << "Masukkan Nama Menu     : ";
    cin >> p.menu;

    cout << "\nJenis Pesanan:\n";
    cout << "1. Makan di Tempat\n";
    cout << "2. Bawa Pulang\n";
    cout << "Pilih: ";
    cin >> jenis;

    if (jenis == 1)
        p.jenis = "Makan di Tempat";
    else
        p.jenis = "Bawa Pulang";

ulang_validasi:
    // ===== VALIDASI =====
    cout << "\nValidasi Pesanan (y/n)? ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "\nValidasi ditolak.\n";
        cout << "1. Perbaiki Pesanan\n";
        cout << "2. Batalkan Pesanan\n";
        cout << "Pilih: ";
        cin >> pilihan;

        if (pilihan == 1) {
            cout << "Masukkan Menu Baru: ";
            cin >> p.menu;
            goto ulang_validasi;
        } else {
            cout << "Pesanan dibatalkan.\n";
            return;
        }
    }

    cout << "Validasi... [BERHASIL]\n";

    // ===== MASUK ANTRIAN =====
    p.status = "Sedang Diproses";
    antrian.push_back(p);
    cout << "Pesanan masuk antrian (" << p.jenis << ").\n";

    // ===== PEMBAYARAN =====
    cout << "\nPesanan siap. Lanjut ke pembayaran (y/n)? ";
    cin >> konfirmasi;

    if (konfirmasi != 'y' && konfirmasi != 'Y') {
        cout << "Pembayaran ditunda.\n";
        return;
    }

    cout << "Pembayaran... [LUNAS]\n";

    // ===== UPDATE STATUS =====
    for (auto &ps : antrian) {
        if (ps.id == p.id) {
            ps.status = "Selesai";
            break;
        }
    }

    cout << "Status pesanan: SELESAI\n";
}

// ================= READ (URUT BERDASARKAN ID) =================
void tampilkanSemua() {
    cout << "\n=== DAFTAR PESANAN (URUT ID) ===\n";
    if (antrian.empty()) {
        cout << "Antrian kosong.\n";
        return;
    }

    // Salin data agar urutan asli tidak berubah
    vector<Pesanan> temp = antrian;

    // Sort berdasarkan ID
    sort(temp.begin(), temp.end(), [](Pesanan a, Pesanan b) {
        return a.id < b.id;
    });

    for (auto p : temp) {
       cout << "ID: " << p.id
             << " | Nama: " << p.nama
             << " | Menu: " << p.menu
             << " | Jenis: " << p.jenis
             << " | Status: " << p.status << endl;
        cout << "---------------------------\n";
    }
}

// ================= SEARCH =================
void cariPesanan() {
    int id;
    cout << "\nMasukkan ID Pesanan: ";
    cin >> id;

    for (auto p : antrian) {
        if (p.id == id) {
            cout << "\nID     : " << p.id << endl;
            cout << "Nama   : " << p.nama << endl;
            cout << "Menu   : " << p.menu << endl;
            cout << "Status : " << p.status << endl;
            return;
        }
    }
    cout << "Pesanan tidak ditemukan.\n";
}

// ================= DELETE =================
void batalkanPesanan() {
    int id;
    cout << "\nMasukkan ID Pesanan: ";
    cin >> id;

    for (int i = 0; i < antrian.size(); i++) {
        if (antrian[i].id == id) {
            antrian.erase(antrian.begin() + i);
            cout << "Pesanan berhasil dibatalkan.\n";
            return;
        }
    }
    cout << "Pesanan tidak ditemukan.\n";
}

// ================= SORT =================
void sortirPesanan() {
    if (antrian.empty()) {
        cout << "Antrian kosong.\n";
        return;
    }

    // Salin data agar urutan asli tidak terganggu tampilan default
    vector<Pesanan> temp = antrian;

    // Sort berdasarkan jenis pesanan
    sort(temp.begin(), temp.end(), [](Pesanan a, Pesanan b) {
        return a.jenis < b.jenis;
    });

    cout << "\n=== HASIL SORT PESANAN (BERDASARKAN JENIS) ===\n";
    for (auto p : temp) {
        cout << "ID: " << p.id
             << " | Nama: " << p.nama
             << " | Menu: " << p.menu
             << " | Jenis: " << p.jenis
             << " | Status: " << p.status << endl;
        cout << "---------------------------\n";
    }
}

// ================= SUB MENU =================
void menuAntrian() {
    int pilih;
    do {
        cout << "\n=== MENU ANTRIAN ===\n";
        cout << "1. Tampilkan Semua Pesanan\n";
        cout << "2. Cari Pesanan\n";
        cout << "3. Sortir Pesanan\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tampilkanSemua(); break;
            case 2: cariPesanan(); break;
            case 3: sortirPesanan(); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}

// ================= MAIN =================
int main() {
    int menu;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Antrian\n";
        cout << "Pilih Menu: ";
        cin >> menu;

        switch (menu) {
            case 1: tambahPesanan(); break;
            case 2: menuAntrian(); break;
            case 0: cout << "Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (menu != 0);

    return 0;
}
