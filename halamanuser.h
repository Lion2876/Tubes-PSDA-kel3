#ifndef HALAMANUSER_H
#define HALAMANUSER_H

#include <QMainWindow>          // Mengimpor kelas QMainWindow sebagai dasar untuk jendela utama
#include "ui_halamanuser.h"     // Mengimpor file UI yang dihasilkan oleh Qt Designer (pastikan nama file sesuai)
#include <QList>                // Mengimpor kelas QList untuk menyimpan daftar objek
#include <QString>              // Mengimpor kelas QString untuk menangani string
#include "barang.h"             // Mengimpor file header Barang untuk mendefinisikan objek Barang

class halamanUser : public QMainWindow {  // Kelas halamanUser turunan dari QMainWindow
    Q_OBJECT  // Makro untuk mendeklarasikan kelas yang menggunakan sinyal dan slot di Qt

public:
    explicit halamanUser(QWidget *parent = nullptr);  // Konstruktor, menerima parameter parent (widget induk)
    ~halamanUser();  // Destruktor untuk membersihkan memori

private slots:
    void on_btnSearch_2_clicked();  // Slot untuk menangani klik tombol "Search" pada halaman user
    void on_btnLogoutUser_clicked();  // Slot untuk menangani klik tombol "Logout" pada halaman user

private:
    Ui::halamanUser *ui;  // Pointer ke objek UI yang dihasilkan oleh Qt Designer
    QList<Barang> listBarang;  // Daftar barang yang disimpan dalam objek QList

    void loadDataFromFile(const QString &filename);  // Fungsi untuk memuat data barang dari file
    void loadTable(const QList<Barang>& data);  // Fungsi untuk memuat data barang ke dalam tabel UI
};

#endif // HALAMANUSER_H
