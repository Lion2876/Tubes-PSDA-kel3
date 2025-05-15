#include "halamanadmin.h"           // Mengimpor header halaman admin
#include "ui_halamanadmin.h"        // Mengimpor file UI yang dihasilkan oleh Qt Designer
#include <QMessageBox>              // Mengimpor QMessageBox untuk menampilkan pesan kesalahan atau informasi
#include <QInputDialog>             // Mengimpor QInputDialog untuk menampilkan input dialog
#include <QFormLayout>              // Mengimpor QFormLayout untuk layout form
#include <QLineEdit>                // Mengimpor QLineEdit untuk input teks
#include <QSpinBox>                 // Mengimpor QSpinBox untuk input angka
#include <QDialogButtonBox>         // Mengimpor QDialogButtonBox untuk tombol dialog
#include <QFile>                    // Mengimpor QFile untuk operasi file (membaca dan menulis file)
#include <QTextStream>              // Mengimpor QTextStream untuk mempermudah membaca dan menulis teks ke file
#include <QFileDialog>              // Mengimpor QFileDialog untuk memilih file dari dialog file system
#include "mainwindow.h"             // Mengimpor MainWindow untuk fungsi pindah halaman

// Konstruktor HalamanAdmin
HalamanAdmin::HalamanAdmin(QWidget *parent)
    : QMainWindow(parent)           // Memanggil konstruktor QMainWindow dengan parent widget
    , ui(new Ui::HalamanAdmin)      // Menginisialisasi objek UI HalamanAdmin
{
    ui->setupUi(this);                                                  // Menghubungkan file UI dengan objek ini
    ui->tableWidget->setColumnCount(4);                                 // Mengatur jumlah kolom pada tabel menjadi 4
    QStringList headers = {"Barang", "Kategori", "Jumlah", "Kondisi"};   // Mendefinisikan header tabel yang akan digunakan
    ui->tableWidget->setHorizontalHeaderLabels(headers);               // Menetapkan header pada tabel
    QFont headerFont;
    headerFont.setPointSize(14);
    ui->tableWidget->horizontalHeader()->setFont(headerFont);

    // Reset stylesheet agar tidak override font
    ui->tableWidget->horizontalHeader()->setStyleSheet("");

    // Tambahkan jika masih tidak bereaksi
    ui->tableWidget->horizontalHeader()->setMinimumHeight(30);


    // Membesarkan font tulisan dalam tabel
    QFont font;
    font.setPointSize(14); // Ganti 14 sesuai keinginan
    ui->tableWidget->setFont(font);

    // Membesarkan tinggi baris
    ui->tableWidget->verticalHeader()->setDefaultSectionSize(30); // Atur tinggi baris

    // Membesarkan lebar kolom
    ui->tableWidget->horizontalHeader()->setDefaultSectionSize(170); // Atur lebar kolom


    loadDataFromFile("data_barang.csv");  // Memuat data awal dari file CSV ke dalam aplikasi
}

// Destruktor HalamanAdmin
HalamanAdmin::~HalamanAdmin() {
    delete ui;  // Menghapus objek UI untuk mencegah memory leak
}

// Muat data barang dari file CSV
void HalamanAdmin::loadDataFromFile(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(",");
            if (fields.size() == 4) {
                Barang barang;
                barang.nama = fields[0];
                barang.kategori = fields[1];
                barang.jumlah = fields[2].toInt();
                barang.kondisi = fields[3];
                listBarang.append(barang);
            }
        }
        file.close();
        loadTable(listBarang);  // Tampilkan data ke tabel
    } else {
        QMessageBox::warning(this, "Error", "Gagal memuat data dari file.");
    }
}

// Simpan data barang ke file
void HalamanAdmin::simpanDataKeFile(const QString &filename) {
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const Barang &barang : listBarang) {
            out << barang.nama << "," << barang.kategori << ","
                << barang.jumlah << "," << barang.kondisi << "\n";
        }
        file.close();
    } else {
        QMessageBox::warning(this, "Error", "Gagal menyimpan data ke file.");
    }
}

// Tampilkan data ke tabel
void HalamanAdmin::loadTable(const QList<Barang>& data) {
    ui->tableWidget->setRowCount(0);  // Reset isi tabel
    for (const auto& item : data) {
        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(item.nama));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(item.kategori));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(item.jumlah)));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(item.kondisi));
    }
}

bool HalamanAdmin::tampilDialogTambahBarang(Barang &barangBaru) {                 // Fungsi untuk menampilkan dialog input barang baru
    QDialog dialog(this);                                                         // Membuat dialog baru dengan induk HalamanAdmin
    dialog.setWindowTitle("Input Data Barang");                                   // Menetapkan judul dialog

    QFormLayout form(&dialog);                                                    // Membuat layout form di dalam dialog

    QLineEdit *editNama = new QLineEdit(&dialog);                                 // Input untuk nama barang
    QLineEdit *editKategori = new QLineEdit(&dialog);                             // Input untuk kategori barang
    QSpinBox *spinJumlah = new QSpinBox(&dialog);                                 // Input angka untuk jumlah barang
    spinJumlah->setRange(1, 1000);                                                // Mengatur rentang jumlah dari 1 sampai 1000
    QLineEdit *editKondisi = new QLineEdit(&dialog);                              // Input untuk kondisi barang

    form.addRow("Nama Barang:", editNama);                                        // Tambahkan input nama ke form layout
    form.addRow("Kategori:", editKategori);                                       // Tambahkan input kategori ke form layout
    form.addRow("Jumlah:", spinJumlah);                                           // Tambahkan input jumlah ke form layout
    form.addRow("Kondisi:", editKondisi);                                         // Tambahkan input kondisi ke form layout

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,   // Membuat tombol OK dan Cancel
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);                                                      // Menambahkan tombol ke layout

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);  // Menghubungkan tombol OK ke fungsi accept dialog
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);  // Menghubungkan tombol Cancel ke fungsi reject dialog

    if (dialog.exec() == QDialog::Accepted) {                                     // Jika pengguna menekan OK
        // Validasi input
        if (editNama->text().isEmpty() || editKategori->text().isEmpty() ||       // Periksa apakah ada input yang kosong
            editKondisi->text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Semua field harus diisi."); // Tampilkan peringatan jika input kosong
            return false;                                                         // Gagal karena input tidak lengkap
        }

        barangBaru.nama = editNama->text();                                       // Set nama barang
        barangBaru.kategori = editKategori->text();                               // Set kategori barang
        barangBaru.jumlah = spinJumlah->value();                                  // Set jumlah barang
        barangBaru.kondisi = editKondisi->text();                                 // Set kondisi barang
        return true;                                                              // Berhasil menambahkan barang
    }
    return false;                                                                 // Dialog dibatalkan oleh pengguna
}

void HalamanAdmin::on_btnCreate_clicked() {
    Barang barangBaru;  // Buat objek barang baru
    if (tampilDialogTambahBarang(barangBaru)) {  // Jika dialog berhasil, tambah barang baru
        listBarang.append(barangBaru);  // Tambahkan barang baru ke listBarang
        loadTable(listBarang);  // Update tabel
        simpanDataKeFile("data_barang.csv");  // Simpan data ke file
    }
}

void HalamanAdmin::on_btnUpdate_clicked() {
    int row = ui->tableWidget->currentRow();  // Ambil baris yang dipilih
    if (row < 0 || row >= listBarang.size()) return;  // Jika baris tidak valid, return

    Barang barangLama = listBarang[row];  // Ambil data barang yang lama
    Barang barangBaru = barangLama;  // Salin data barang lama

    if (tampilDialogEditBarang(barangBaru)) {  // Jika dialog edit barang berhasil
        listBarang[row] = barangBaru;  // Update barang di listBarang
        loadTable(listBarang);  // Update tabel
        simpanDataKeFile("data_barang.csv");  // Simpan data ke file
    }
}

bool HalamanAdmin::tampilDialogEditBarang(Barang &barang) {                       // Fungsi untuk menampilkan dialog edit data barang
    QDialog dialog(this);                                                         // Membuat dialog baru dengan induk HalamanAdmin
    dialog.setWindowTitle("Edit Data Barang");                                    // Menetapkan judul dialog

    QFormLayout form(&dialog);                                                    // Membuat form layout untuk dialog

    QLineEdit *editNama = new QLineEdit(barang.nama, &dialog);                    // Input nama barang, diisi dengan nilai awal
    QLineEdit *editKategori = new QLineEdit(barang.kategori, &dialog);            // Input kategori, diisi dengan nilai awal
    QSpinBox *spinJumlah = new QSpinBox(&dialog);                                 // Input jumlah (angka)
    spinJumlah->setRange(1, 1000);                                                // Rentang jumlah: 1 sampai 1000
    spinJumlah->setValue(barang.jumlah);                                          // Nilai awal jumlah diambil dari data barang
    QLineEdit *editKondisi = new QLineEdit(barang.kondisi, &dialog);              // Input kondisi, diisi dengan nilai awal

    form.addRow("Nama Barang:", editNama);                                        // Tambahkan input nama ke form
    form.addRow("Kategori:", editKategori);                                       // Tambahkan input kategori ke form
    form.addRow("Jumlah:", spinJumlah);                                           // Tambahkan input jumlah ke form
    form.addRow("Kondisi:", editKondisi);                                         // Tambahkan input kondisi ke form

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,   // Tambahkan tombol OK dan Cancel
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);                                                      // Tambahkan tombol ke form layout

    connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);  // Hubungkan tombol OK ke fungsi accept
    connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);  // Hubungkan tombol Cancel ke fungsi reject

    if (dialog.exec() == QDialog::Accepted) {                                     // Jika pengguna klik OK
        if (editNama->text().isEmpty() || editKategori->text().isEmpty() ||       // Validasi: pastikan semua field diisi
            editKondisi->text().isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Semua field harus diisi."); // Tampilkan peringatan jika ada yang kosong
            return false;                                                         // Gagal karena input tidak lengkap
        }

        barang.nama = editNama->text();                                           // Set data nama barang
        barang.kategori = editKategori->text();                                   // Set data kategori barang
        barang.jumlah = spinJumlah->value();                                      // Set data jumlah barang
        barang.kondisi = editKondisi->text();                                     // Set data kondisi barang
        return true;                                                              // Return sukses edit
    }

    return false;                                                                 // Return batal edit
}

void HalamanAdmin::on_btnDelete_clicked() {                                       // Fungsi saat tombol hapus ditekan
    int row = ui->tableWidget->currentRow();                                      // Ambil baris yang sedang dipilih
    if (row < 0 || row >= listBarang.size()) return;                              // Jika baris tidak valid, keluar

    QMessageBox::StandardButton reply;                                            // Tampilkan konfirmasi
    reply = QMessageBox::question(this, "Hapus Data", "Anda yakin ingin menghapus data ini?",
                                  QMessageBox::Yes | QMessageBox::Cancel);

    if (reply == QMessageBox::Yes) {                                              // Jika pengguna setuju
        listBarang.removeAt(row);                                                 // Hapus data dari list
        loadTable(listBarang);                                                    // Refresh tampilan tabel
        simpanDataKeFile("data_barang.csv");                                      // Simpan perubahan ke file
    }
}

void HalamanAdmin::on_btnSearch_clicked() {                                       // Fungsi saat tombol cari ditekan
    QString keyword = ui->lineEditSearch->text().trimmed();                       // Ambil teks pencarian, hilangkan spasi
    QList<Barang> hasilSearch;                                                    // Buat list hasil pencarian

    for (const auto &barang : listBarang) {                                       // Iterasi setiap barang dalam list
        if (barang.nama.contains(keyword, Qt::CaseInsensitive) ||                 // Cocokkan dengan nama (tidak case sensitive)
            barang.kategori.contains(keyword, Qt::CaseInsensitive) ||             // Cocokkan dengan kategori
            barang.kondisi.contains(keyword, Qt::CaseInsensitive) ||              // Cocokkan dengan kondisi
            QString::number(barang.jumlah).contains(keyword)) {                   // Cocokkan dengan jumlah (konversi ke string)
            hasilSearch.append(barang);                                           // Tambahkan ke hasil pencarian
        }
    }

    loadTable(hasilSearch);                                                       // Tampilkan hasil pencarian di tabel
}

void HalamanAdmin::on_btnLogout_clicked() {
    this->close();  // Menutup HalamanAdmin

    MainWindow *mainWindow = new MainWindow();  // Membuat instance baru MainWindow
    mainWindow->show();  // Menampilkan kembali MainWindow
}
