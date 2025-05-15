#ifndef HALAMANADMIN_H
#define HALAMANADMIN_H

#include "ui_halamanuser.h"  // Mengimpor file UI yang dihasilkan oleh Qt Designer (pastikan namanya sesuai)
#include <QMainWindow>       // Mengimpor kelas QMainWindow sebagai dasar untuk jendela utama
#include <QList>             // Mengimpor kelas QList untuk menyimpan daftar objek
#include <QString>           // Mengimpor kelas QString untuk menangani string
#include "barang.h"          // Mengimpor file header Barang untuk mendefinisikan objek Barang

QT_BEGIN_NAMESPACE
namespace Ui { class HalamanAdmin; }  // Deklarasi kelas Ui::HalamanAdmin di dalam namespace Ui
QT_END_NAMESPACE

class HalamanAdmin : public QMainWindow  // Kelas HalamanAdmin turunan dari QMainWindow
{
    Q_OBJECT  // Makro untuk mendeklarasikan kelas yang menggunakan sinyal dan slot di Qt

public:
    explicit HalamanAdmin(QWidget *parent = nullptr); // Konstruktor, menerima parameter parent (widget induk)
    ~HalamanAdmin();                                  // Destruktor untuk membersihkan memori

private slots:
    void on_btnCreate_clicked();   // Slot untuk menangani klik tombol "Create" (untuk membuat barang baru)
    void on_btnUpdate_clicked();   // Slot untuk menangani klik tombol "Update" (untuk mengupdate data barang)
    void on_btnDelete_clicked();   // Slot untuk menangani klik tombol "Delete" (untuk menghapus barang)
    void on_btnSearch_clicked();   // Slot untuk menangani klik tombol "Search" (untuk mencari barang)
    void on_btnLogout_clicked();   // Slot untuk menangani klik tombol "Logout" (untuk keluar dari admin)

private:
    Ui::HalamanAdmin *ui;          // Pointer ke objek UI yang dihasilkan oleh Qt Designer

    QList<Barang> listBarang;      // Daftar barang yang disimpan dalam objek QList

    void loadTable(const QList<Barang>& data);              // Fungsi untuk memuat data barang ke dalam tabel UI
    bool tampilDialogTambahBarang(Barang &barangBaru);      // Fungsi untuk menampilkan dialog untuk menambah barang
    bool tampilDialogEditBarang(Barang &barang);            // Fungsi untuk menampilkan dialog untuk mengedit barang
    void loadDataFromFile(const QString &filename);         // Fungsi untuk memuat data dari file
    void simpanDataKeFile(const QString &filename);         // Fungsi untuk menyimpan data ke file
};

#endif // HALAMANADMIN_H
