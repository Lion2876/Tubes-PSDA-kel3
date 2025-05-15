#ifndef MAINWINDOW_H                // Cegah agar file tidak di-include lebih dari sekali
#define MAINWINDOW_H

#include <QMainWindow>              // Gunakan QMainWindow sebagai basis UI utama

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;                  // Deklarasi kelas UI untuk MainWindow
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow // Kelas MainWindow turunan dari QMainWindow
{
    Q_OBJECT                         // Makro Qt untuk mendukung signal dan slot

public:
    MainWindow(QWidget *parent = nullptr); // Konstruktor
    ~MainWindow();                         // Destruktor

private slots:
    void on_pushButtonAdmin_clicked(); // Slot untuk tombol Admin diklik
    void on_pushButtonUser_clicked();  // Slot untuk tombol User diklik

private:
    Ui::MainWindow *ui;               // Pointer ke objek UI
};

#endif // MAINWINDOW_H               // Penutup include guard
