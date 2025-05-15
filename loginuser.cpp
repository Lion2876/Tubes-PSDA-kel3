#include "loginuser.h"             // Mengimpor file header untuk kelas loginuser
#include "ui_loginuser.h"          // Mengimpor file UI loginuser untuk antarmuka pengguna
#include "halamanuser.h"           // Mengimpor file header halamanUser untuk halaman setelah login berhasil
#include <QString>                 // Mengimpor kelas QString untuk menangani string
#include <QMessageBox>            // Mengimpor kelas QMessageBox untuk menampilkan dialog pesan

// Konstruktor loginuser
loginuser::loginuser(QWidget *parent)
    : QMainWindow(parent),         // Menginisialisasi sebagai QMainWindow
    ui(new Ui::loginuser)       // Membuat objek UI untuk loginuser
{
    ui->setupUi(this);             // Menyiapkan UI dari file .ui
}

// Destruktor loginuser
loginuser::~loginuser()
{
    delete ui;                     // Menghapus memori UI
}

// Data login pengguna
QString userNames[] = {"widya", "gusti", "rifqi"};       // Daftar username yang valid
QString userPasswords[] = {"pass59", "pass81", "pass51"}; // Daftar password yang sesuai dengan username
int userDataSize = 3;                                     // Jumlah data user

// Fungsi yang dipanggil saat tombol login ditekan
void loginuser::on_pushButton_clicked()
{
    QString inputUser = ui->loginuserusername->text();    // Mengambil input username dari pengguna
    QString inputPass = ui->loginuserpassword->text();    // Mengambil input password dari pengguna

    bool loginBerhasil = false;                           // Status login berhasil atau tidak

    // Mengecek input dengan data login yang tersedia
    for (int i = 0; i < userDataSize; i++) {
        if (inputUser == userNames[i] && inputPass == userPasswords[i]) {
            loginBerhasil = true;                         // Menandai login berhasil
            break;                                         // Keluar dari loop saat cocok
        }
    }

    if (loginBerhasil) {
        this->close();                                    // Menutup jendela login saat login berhasil
        halamanUser *halamanuser = new halamanUser();     // Membuat objek halamanUser tanpa parent
        halamanuser->show();                              // Menampilkan halamanUser
    } else {
        QMessageBox::warning(this, "Login Gagal", "Username atau Password salah!"); // Pesan kesalahan login
    }
}
