#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Pesanan {
    int id;
    string nama;
    string menu;
    string status;
};

vector<Pesanan> antrian;
int idCounter = 1;

// CREATE
void tambahPesanan() {
    Pesanan p;
    cout << "\n=== PEMBUATAN PESANAN ===\n";
    p.id = idCounter++;

    cout << "Masukkan Nama Customer : ";
    cin >> p.nama;
    cout << "Masukkan Nama Menu     : ";
    cin >> p.menu;

    cout << "\nValidasi Pesanan... [BERHASIL]\n";
    cout << "Pembayaran... [LUNAS]\n";

    p.status = "Mengantri";
    antrian.push_back(p);

    cout << "Pesanan masuk ke antrian.\n";
}

// READ
void tampilkanSemua() {
    cout << "\n=== TAMPILAN SEMUA PESANAN ===\n";
    if (antrian.empty()) {
        cout << "Antrian kosong.\n";
        return;
    }

    for (auto p : antrian) {
        cout << "ID: " << p.id
             << " | Nama: " << p.nama
             << " | Menu: " << p.menu
             << " | Status: " << p.status << endl;
    }
}

// SEARCH
void cariPesanan() {
    int id;
    cout << "\nMasukkan ID Pesanan: ";
    cin >> id;

    for (auto p : antrian) {
        if (p.id == id) {
            cout << "\n=== HASIL PENCARIAN ===\n";
            cout << "ID     : " << p.id << endl;
            cout << "Nama   : " << p.nama << endl;
            cout << "Menu   : " << p.menu << endl;
            cout << "Status : " << p.status << endl;
            return;
        }
    }
    cout << "Pesanan tidak ditemukan.\n";
}

// UPDATE
void perbaikiPesanan() {
    int id;
    cout << "\nMasukkan ID Pesanan yang diperbaiki: ";
    cin >> id;

    for (auto &p : antrian) {
        if (p.id == id) {
            cout << "Masukkan Menu Baru: ";
            cin >> p.menu;
            cout << "Pesanan berhasil diperbaiki.\n";
            return;
        }
    }
    cout << "Pesanan tidak ditemukan.\n";
}

// DELETE
void batalkanPesanan() {
    int id;
    cout << "\nMasukkan ID Pesanan yang dibatalkan: ";
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

// SORT
void sortirPesanan() {
    sort(antrian.begin(), antrian.end(), [](Pesanan a, Pesanan b) {
        return a.status < b.status;
    });
    cout << "Pesanan berhasil disortir berdasarkan status.\n";
}

// SUB MENU LIHAT ANTRIAN
void menuAntrian() {
    int pilih;
    do {
        cout << "\n=== MENU ANTRIAN PESANAN ===\n";
        cout << "1. Tampilkan Semua Pesanan\n";
        cout << "2. Cari Pesanan Berdasarkan ID\n";
        cout << "3. Perbaiki Pesanan\n";
        cout << "4. Batalkan Pesanan\n";
        cout << "5. Sortir Pesanan\n";
        cout << "0. Kembali\n";
        cout << "Pilih Menu: ";
        cin >> pilih;

        switch (pilih) {
            case 1: tampilkanSemua(); break;
            case 2: cariPesanan(); break;
            case 3: perbaikiPesanan(); break;
            case 4: batalkanPesanan(); break;
            case 5: sortirPesanan(); tampilkanSemua(); break;
            case 0: break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilih != 0);
}

int main() {
    int menu;
    do {
        cout << "\n=== MENU UTAMA ===\n";
        cout << "1. Tambahkan Pesanan\n";
        cout << "2. Lihat Antrian Pesanan\n";
        cout << "0. Selesai\n";
        cout << "Pilih Menu: ";
        cin >> menu;

        switch (menu) {
            case 1: tambahPesanan(); break;
            case 2: menuAntrian(); break;
            case 0: cout << "\nProgram selesai.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (menu != 0);

    return 0;
}