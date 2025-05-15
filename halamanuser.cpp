#include "halamanuser.h"           // Mengimpor file header halamanuser.h
#include "ui_halamanuser.h"        // Mengimpor file UI halamanuser.h untuk pengaturan antarmuka pengguna
#include <QFile>                   // Mengimpor kelas QFile untuk bekerja dengan file
#include <QTextStream>            // Mengimpor kelas QTextStream untuk membaca dan menulis file teks
#include <QMessageBox>            // Mengimpor kelas QMessageBox untuk menampilkan pesan kesalahan atau informasi
#include <QTableWidgetItem>       // Mengimpor kelas QTableWidgetItem untuk menampilkan dan mengelola item dalam tabel
#include "mainwindow.h"           // Mengimpor file header mainwindow.h untuk navigasi atau kontrol antar halaman

halamanUser::halamanUser(QWidget *parent) :
    QMainWindow(parent),  // Konstruktor halamanUser yang memanggil konstruktor kelas induk QMainWindow
    ui(new Ui::halamanUser)  // Membuat objek UI untuk halamanUser
{
    ui->setupUi(this);  // Menyiapkan antarmuka pengguna sesuai dengan definisi di file .ui
    ui->tableWidget_2->setColumnCount(4);  // Menetapkan jumlah kolom tabel menjadi 4
    QStringList headers = {"Barang", "Kategori", "Jumlah", "Kondisi"};  // Menentukan header kolom
    ui->tableWidget_2->setHorizontalHeaderLabels(headers);  // Menetapkan header kolom ke tabel
    QFont headerFont;
    headerFont.setPointSize(14);
    ui->tableWidget_2->horizontalHeader()->setFont(headerFont);
    // Membesarkan font tulisan dalam tabel
    QFont font;
    font.setPointSize(14); // Ganti 14 sesuai keinginan
    ui->tableWidget_2->setFont(font);

    // Membesarkan tinggi baris
    ui->tableWidget_2->verticalHeader()->setDefaultSectionSize(30); // Atur tinggi baris

    // Membesarkan lebar kolom
    ui->tableWidget_2->horizontalHeader()->setDefaultSectionSize(170); // Atur lebar kolom
    loadDataFromFile("data_barang.csv");  // Memuat data barang dari file CSV
}

halamanUser::~halamanUser()  // Destruktor untuk halamanUser
{
    delete ui;  // Menghapus objek UI untuk mencegah kebocoran memori
}

void halamanUser::loadDataFromFile(const QString &filename) {  // Fungsi untuk memuat data dari file CSV
    QFile file(filename);  // Membuka file dengan nama yang diberikan
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {  // Memastikan file dapat dibuka untuk dibaca
        QTextStream in(&file);  // Membaca file menggunakan QTextStream
        while (!in.atEnd()) {  // Selama masih ada baris yang belum dibaca
            QString line = in.readLine();  // Membaca satu baris dari file
            QStringList fields = line.split(",");  // Memisahkan baris berdasarkan koma
            if (fields.size() == 4) {  // Memastikan ada 4 elemen dalam baris (nama, kategori, jumlah, kondisi)
                Barang barang;  // Membuat objek barang bar
                barang.nama = fields[0];  // Menetapkan nama barang dari elemen pertama
                barang.kategori = fields[1];  // Menetapkan kategori barang dari elemen kedua
                barang.jumlah = fields[2].toInt();  // Mengonversi jumlah menjadi integer
                barang.kondisi = fields[3];  // Menetapkan kondisi barang dari elemen keempat
                listBarang.append(barang);  // Menambahkan barang ke dalam listBarang
            }
        }
        file.close();  // Menutup file setelah selesai membaca
        loadTable(listBarang);  // Memuat data ke dalam tabel
    } else {  // Jika file tidak bisa dibuka
        QMessageBox::warning(this, "Error", "Gagal memuat data dari file. Error: " + file.errorString());  // Menampilkan pesan kesalahan dengan deskripsi error
    }
}

void halamanUser::loadTable(const QList<Barang> &data) {  // Fungsi untuk menampilkan data barang ke dalam tabel
    ui->tableWidget_2->setRowCount(0);  // Menghapus semua baris yang ada di tabel
    for (const auto &item : data) {  // Iterasi melalui setiap item dalam data
        int row = ui->tableWidget_2->rowCount();  // Mendapatkan jumlah baris yang ada saat ini
        ui->tableWidget_2->insertRow(row);  // Menambahkan baris baru di tabel
        ui->tableWidget_2->setItem(row, 0, new QTableWidgetItem(item.nama));  // Menambahkan nama barang di kolom pertama
        ui->tableWidget_2->setItem(row, 1, new QTableWidgetItem(item.kategori));  // Menambahkan kategori barang di kolom kedua
        ui->tableWidget_2->setItem(row, 2, new QTableWidgetItem(QString::number(item.jumlah)));  // Menambahkan jumlah barang di kolom ketiga
        ui->tableWidget_2->setItem(row, 3, new QTableWidgetItem(item.kondisi));  // Menambahkan kondisi barang di kolom keempat
    }
}

void halamanUser::on_btnSearch_2_clicked() {  // Fungsi yang dipanggil ketika tombol pencarian ditekan
    QString keyword = ui->lineEditSearch_2->text().trimmed();  // Mengambil kata kunci dari input pencarian dan menghapus spasi ekstra
    QList<Barang> hasilSearch;  // Mengubah dari QVector menjadi QList untuk menyimpan hasil pencarian

    for (const auto &barang : listBarang) {  // Iterasi melalui setiap barang dalam listBarang
        if (barang.nama.contains(keyword, Qt::CaseInsensitive) ||  // Memeriksa apakah nama barang mengandung kata kunci (tanpa memperhatikan kapitalisasi)
            barang.kategori.contains(keyword, Qt::CaseInsensitive) ||  // Memeriksa kategori barang
            barang.kondisi.contains(keyword, Qt::CaseInsensitive) ||  // Memeriksa kondisi barang
            QString::number(barang.jumlah).contains(keyword)) {  // Memeriksa jumlah barang
            hasilSearch.append(barang);  // Menambahkan barang yang sesuai ke dalam hasil pencarian
        }
    }

    loadTable(hasilSearch);  // Memuat hasil pencarian ke dalam tabel
}

void halamanUser::on_btnLogoutUser_clicked() {
    this->close();  // Menutup HalamanUser

    MainWindow *mainWindow = new MainWindow();  // Membuat instance baru MainWindow
    mainWindow->show();  // Menampilkan kembali MainWindow

}
