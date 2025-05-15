#include "mainwindow.h"        // Mengimpor file header MainWindow yang berisi deklarasi kelas MainWindow
#include "./ui_mainwindow.h"   // Mengimpor file header UI hasil generate dari Qt Designer untuk MainWindow
#include "loginadmin.h"        // Mengimpor header untuk kelas loginadmin (login sebagai admin)
#include "loginuser.h"         // Mengimpor header untuk kelas loginuser (login sebagai user)

// Konstruktor untuk kelas MainWindow
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),     // Memanggil konstruktor induk QMainWindow
    ui(new Ui::MainWindow)  // Membuat objek UI untuk MainWindow
{
    ui->setupUi(this);         // Menyiapkan antarmuka pengguna dari file .ui
}

// Destruktor untuk MainWindow
MainWindow::~MainWindow()
{
    delete ui;                 // Menghapus objek UI untuk mencegah memory leak
}

// Fungsi yang dipanggil saat tombol "Admin" diklik
void MainWindow::on_pushButtonAdmin_clicked()
{
    this->hide();                     // Menyembunyikan halaman utama (MainWindow)
    loginadmin *Loginadmin = new loginadmin(this); // Membuat objek loginadmin sebagai anak dari MainWindow
    Loginadmin->show();              // Menampilkan jendela login untuk admin
}

// Fungsi yang dipanggil saat tombol "User" diklik
void MainWindow::on_pushButtonUser_clicked()
{
    this->hide();                    // Menyembunyikan halaman utama (MainWindow)
    loginuser *LoginUser = new loginuser(this);   // Membuat objek loginuser sebagai anak dari MainWindow
    LoginUser->show();              // Menampilkan jendela login untuk user
}


