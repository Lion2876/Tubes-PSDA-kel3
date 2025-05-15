#include "loginadmin.h"              // Mengimpor file header untuk kelas loginadmin
#include "ui_loginadmin.h"           // Mengimpor file UI loginadmin untuk tampilan antarmuka pengguna
#include "HalamanAdmin.h"           // Mengimpor file header HalamanAdmin untuk menampilkan halaman admin setelah login berhasil
#include <QString>                   // Mengimpor kelas QString untuk menangani string Qt
#include <QMessageBox>              // Mengimpor kelas QMessageBox untuk menampilkan pesan dialog

// Konstruktor loginadmin
loginadmin::loginadmin(QWidget *parent)
    : QMainWindow(parent),          // Memanggil konstruktor QMainWindow
    ui(new Ui::loginadmin)       // Menginisialisasi objek UI
{
    ui->setupUi(this);              // Mengatur tampilan UI
}

// Destruktor loginadmin
loginadmin::~loginadmin()
{
    delete ui;                      // Menghapus alokasi memori dari UI
}

// Data login (sementara)
QString usernames[] = {"anjel", "admin2"};    // Daftar username yang diperbolehkan
QString passwords[] = {"admin53", "adminpass"};  // Daftar password sesuai username
int dataSize = 2;                              // Ukuran array data login

// Fungsi yang dipanggil saat tombol login ditekan
void loginadmin::on_pushButton_clicked()
{
    QString inputUsername = ui->loginadminusername->text();    // Mengambil input username dari UI
    QString inputPassword = ui->loginadminpassword->text();    // Mengambil input password dari UI

    bool loginSuccess = false;                                 // Variabel untuk menandai keberhasilan login

    // Melakukan pemeriksaan username dan password
    for (int i = 0; i < dataSize; i++) {
        if (inputUsername == usernames[i] && inputPassword == passwords[i]) {
            loginSuccess = true;   // Login berhasil jika username dan password cocok
            break;                 // Keluar dari loop
        }
    }

    if (loginSuccess) {
        this->hide();                         // Menyembunyikan halaman login
        HalamanAdmin *halamanadmin = new HalamanAdmin();  // Membuat instance halaman admin
        halamanadmin->show();                // Menampilkan halaman admin
    } else {
        QMessageBox::warning(this, "Login Gagal", "Username atau Password salah!");  // Menampilkan peringatan jika login gagal
    }
}
