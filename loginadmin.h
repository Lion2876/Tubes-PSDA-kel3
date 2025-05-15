#ifndef LOGINADMIN_H
#define LOGINADMIN_H

#include <QMainWindow>  // Mengimpor kelas QMainWindow sebagai dasar untuk jendela utama

namespace Ui {
class loginadmin;  // Deklarasi kelas Ui::loginadmin di dalam namespace Ui
}

class loginadmin : public QMainWindow  // Kelas loginadmin turunan dari QMainWindow
{
    Q_OBJECT  // Makro untuk mendeklarasikan kelas yang menggunakan sinyal dan slot di Qt

public:
    explicit loginadmin(QWidget *parent = nullptr);  // Konstruktor, menerima parameter parent (widget induk)
    ~loginadmin();  // Destruktor untuk membersihkan memori

private slots:
    void on_pushButton_clicked();  // Slot untuk menangani klik tombol login (pushButton)

private:
    Ui::loginadmin *ui;  // Pointer ke objek UI yang dihasilkan oleh Qt Designer
};

#endif // LOGINADMIN_H
