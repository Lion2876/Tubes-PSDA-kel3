#ifndef BARANG_H             // Cegah header agar tidak di-include dua kali
#define BARANG_H

#include <QString>           // Gunakan QString dari Qt
#include <QMainWindow>       // Gunakan QMainWindow untuk window utama

struct Barang {              // Struktur data untuk menyimpan informasi barang
    QString nama;            // Nama barang
    QString kategori;        // Kategori barang
    int jumlah;              // Jumlah barang
    QString kondisi;         // Kondisi barang
};

namespace Ui {
class barang;               // Forward declaration UI class hasil dari Qt Designer
}

class barang : public QMainWindow   // Kelas barang, turunan dari QMainWindow
{
    Q_OBJECT                // Makro Qt untuk signal dan slot

public:
    explicit barang(QWidget *parent = nullptr); // Konstruktor
    ~barang();             // Destruktor

private:
    Ui::barang *ui;        // Pointer ke UI class
};

#endif // BARANG_H           // Penutup include guard
