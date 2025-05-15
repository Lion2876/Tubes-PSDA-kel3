#include "barang.h"           // header untuk class barang
#include "ui_barang.h"        // header UI hasil generate dari Qt Designer

barang::barang(QWidget *parent)
    : QMainWindow(parent)    // Inisialisasi konstruktor QMainWindow dengan parent
    , ui(new Ui::barang)     // Buat objek dari kelas barang baru untuk UI
{
    ui->setupUi(this);       // Setup antarmuka pengguna
}

barang::~barang()
{
    delete ui;               // Hapus instance UI untuk mencegah memory leak
}
