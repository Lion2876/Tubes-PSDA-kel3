#ifndef LOGINUSER_H
#define LOGINUSER_H

#include <QMainWindow>  // Mengimpor kelas QMainWindow sebagai dasar untuk jendela utama (mengganti QDialog ke QMainWindow)

namespace Ui {
class loginuser;  // Deklarasi kelas Ui::loginuser di dalam namespace Ui
}

class loginuser : public QMainWindow  // Kelas loginuser turunan dari QMainWindow
{
    Q_OBJECT  // Makro untuk mendeklarasikan kelas yang menggunakan sinyal dan slot di Qt

public:
    explicit loginuser(QWidget *parent = nullptr);  // Konstruktor, menerima parameter parent (widget induk)
    ~loginuser();  // Destruktor untuk membersihkan memori

private slots:
    void on_pushButton_clicked();  // Slot untuk menangani klik tombol login (pushButton)

private:
    Ui::loginuser *ui;  // Pointer ke objek UI yang dihasilkan oleh Qt Designer
};

#endif // LOGINUSER_H
