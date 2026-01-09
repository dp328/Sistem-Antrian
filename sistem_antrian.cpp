#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ===== FUNCTION PROTOTYPE =====
void tampilkanMenu();
void tambahPesanan();
void tampilkanSemua();
void cariPesanan();
void batalkanPesanan();
void sortirMenuByHarga();
void menuAntrian();

struct Pesanan {
    int id;
    string nama;
    vector<string> menu;
    string status;
    string jenis;   // Makan di Tempat / Bawa Pulang
};

vector<Pesanan> antrian;
int idCounter = 1;

// ========== DATA BASE MENU =============
struct MenuItem {
    int id;
    string nama;
    string kategori; // Makanan / Minuman
    int harga;
};

vector<MenuItem> databaseMenu = {
    {1, "Nasi Goreng", "Makanan", 20000},
    {2, "Mie Ayam", "Makanan", 18000},
    {3, "Ayam Geprek", "Makanan", 22000},
    {4, "Sate Ayam", "Makanan", 25000},
    {5, "Bakso", "Makanan", 20000},
    {6, "Es Teh", "Minuman", 5000},
    {7, "Es Jeruk", "Minuman", 7000},
    {8, "Kopi Hitam", "Minuman", 8000},
    {9, "Teh Hangat", "Minuman", 5000},
    {10, "Jus Alpukat", "Minuman", 12000}
};

// ============= output daftar menu ===========
void tampilkanMenu() {
    cout << "\n=== DAFTAR MENU ===\n";
    cout << "ID | Nama Menu      | Kategori | Harga\n";
    cout << "-------------------------------------\n";
    for (auto m : databaseMenu) {
        cout << m.id << "  | "
             << m.nama << " | "
             << m.kategori << " | Rp"
             << m.harga << endl;
    }
}



// ================= CREATE PESANAN =================
void tambahPesanan() {
    Pesanan p;
    int jenis;

    cout << "\n=== PEMBUATAN PESANAN ===\n";
    p.id = idCounter++;

    cout << "Masukkan Nama Customer : ";
    cin >> p.nama;

    // ================= LOOP INPUT & VALIDASI =================
    bool selesai = false;

    while (!selesai) {

        p.menu.clear();   // Hapus menu lama jika perbaikan

        int jumlahMenu;
        cout << "\nMasukkan jumlah menu yang dipesan (1 - 2): ";
        cin >> jumlahMenu;

        tampilkanMenu();

        bool inputValid = true;

        for (int i = 0; i < jumlahMenu; i++) {
            int idMenu;
            bool ditemukan = false;

            cout << "Pilih ID Menu ke-" << (i + 1) << " : ";
            cin >> idMenu;

            for (auto m : databaseMenu) {
                if (m.id == idMenu) {
                    p.menu.push_back(m.nama);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan) {
                cout << "ID Menu tidak valid.\n";
                inputValid = false;
                break;
            }
        }

        if (!inputValid) continue;

        cout << "\nJenis Pesanan:\n";
        cout << "1. Makan di Tempat\n";
        cout << "2. Bawa Pulang\n";
        cout << "Pilih: ";
        cin >> jenis;

        p.jenis = (jenis == 1) ? "Makan di Tempat" : "Bawa Pulang";

        // ================= VALIDASI =================
        char konfirmasi;
        cout << "\nValidasi Pesanan (y/n)? ";
        cin >> konfirmasi;

        if (konfirmasi == 'y' || konfirmasi == 'Y') {
            selesai = true;   // keluar loop, lanjut proses
        } else {
            int pilihan;
            cout << "\n1. Perbaiki Menu\n";
            cout << "2. Batalkan Pesanan\n";
            cout << "Pilih: ";
            cin >> pilihan;

            if (pilihan == 2) {
                cout << "Pesanan dibatalkan.\n";
                return;
            }
            // jika pilih 1 → loop ulang otomatis
        }
    }

    // ================= MASUK ANTRIAN =================
    p.status = "Sedang Diproses";
    antrian.push_back(p);
    cout << "Pesanan masuk antrian (" << p.jenis << ").\n";

    // ================= PEMBAYARAN =================
    char bayar;
    cout << "\nPesanan siap. Lanjut ke pembayaran (y/n)? ";
    cin >> bayar;

    if (bayar != 'y' && bayar != 'Y') {
        cout << "Pembayaran ditunda.\n";
        return;
    }

    cout << "Pembayaran... [LUNAS]\n";

    // ================= UPDATE STATUS =================
    for (auto &ps : antrian) {
        if (ps.id == p.id) {
            ps.status = "Selesai";
            break;
        }
    }

    cout << "Status pesanan: SELESAI\n";
}

// ======== READ (URUT BERDASARKAN ID) ===========
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
         << " | Menu: ";

    for (int i = 0; i < p.menu.size(); i++) {
        cout << p.menu[i];
        if (i < p.menu.size() - 1) cout << ", ";
    }

    cout << " | Jenis: " << p.jenis
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
            cout << "Menu   : ";
            for (int i = 0; i < p.menu.size(); i++) {
            cout << p.menu[i];
             if (i < p.menu.size() - 1) cout << ", ";
            }
            cout << endl;
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
void sortirMenuByHarga() {
    int minHarga, maxHarga;

    cout << "\n=== SORTIR MENU BERDASARKAN HARGA ===\n";
    cout << "Masukkan harga minimum : Rp";
    cin >> minHarga;
    cout << "Masukkan harga maksimum : Rp";
    cin >> maxHarga;

    vector<MenuItem> hasil;

    for (auto m : databaseMenu) {
        if (m.harga >= minHarga && m.harga <= maxHarga) {
            hasil.push_back(m);
        }
    }

    if (hasil.empty()) {
        cout << "Tidak ada menu pada rentang harga tersebut.\n";
        return;
    }

    sort(hasil.begin(), hasil.end(), [](MenuItem a, MenuItem b) {
        return a.harga < b.harga;
    });

    cout << "\n=== HASIL SORTIR MENU ===\n";
    cout << "ID | Nama Menu | Kategori | Harga\n";
    cout << "---------------------------------\n";

    for (auto m : hasil) {
        cout << m.id << " | "
             << m.nama << " | "
             << m.kategori << " | Rp"
             << m.harga << endl;
    }
}

// ================= SUB MENU =================
void menuAntrian() {
    int pilih;
    do {
        cout << "\n=== MENU ANTRIAN ===\n";
        cout << "1. Tampilkan Semua Pesanan\n";
        cout << "2. Cari Pesanan\n";
        cout << "0. Kembali\n";
        cout << "Pilih: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tampilkanSemua(); break; 
            case 2: cariPesanan(); break;    
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}

// ================= MAIN =================
int main() {
    int menu;
    do {
        // ===== TAMPILKAN DATABASE MENU DI AWAL =====
        tampilkanMenu();

        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambah Pesanan\n";
        cout << "2. Lihat Antrian\n";
        cout << "3. Sortir Menu Berdasarkan Harga\n";
        cout << "0. Keluar\n";

        cout << "Pilih Menu: ";
        cin >> menu;

        switch (menu) {
            case 1: tambahPesanan(); break;
            case 2: menuAntrian(); break;
            case 3: sortirMenuByHarga(); break;
            case 0: cout << "Program selesai.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (menu != 0);

    return 0;
}
