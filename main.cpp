#include "mainwindow.h"  // Menyertakan file header MainWindow untuk deklarasi kelas MainWindow

#include <QApplication>  // Menyertakan kelas QApplication yang diperlukan untuk aplikasi berbasis Qt
#include <QLocale>  // Menyertakan kelas QLocale untuk menentukan pengaturan lokal sistem
#include <QTranslator>  // Menyertakan kelas QTranslator untuk melakukan terjemahan teks dalam aplikasi

int main(int argc, char *argv[])  // Fungsi utama aplikasi
{
    QApplication a(argc, argv);  // Membuat objek QApplication yang diperlukan untuk aplikasi Qt
    MainWindow w;  // Membuat objek MainWindow untuk antarmuka pengguna utama
    w.show();  // Menampilkan jendela utama aplikasi

    return a.exec();  // Memulai eksekusi event loop aplikasi dan menunggu untuk input pengguna
}
