# Sistem Analisis Distribusi Nilai SNBT

## Deskripsi Project

Sistem ini merupakan program berbasis bahasa C yang digunakan untuk melakukan analisis distribusi nilai SNBT serta prediksi peluang kelulusan pada suatu kampus dan jurusan tertentu.

Program dibuat sebagai tugas Praktikum Struktur Data dan Algoritma dengan menerapkan beberapa konsep penting seperti Linked List, Stack, Merge Sort, Binary Search, Statistik Dasar, dan File Handling. Data peserta dibaca dari file `dataNilai.csv`, kemudian sistem dapat melakukan analisis statistik dan prediksi berdasarkan nilai Try Out (TO) pengguna.

**Disusun Oleh Kelompok 1:**
* Muhammad Fathir (250810701100001)
* Zahra Febi Maharani (250810701100006)
* Rafid Khaulika (250810701100016)
* Dhawy Azzhafran (250810701100043)
* Mellani Sofie (250810701100069)
* Mustaqim (250810701100095)

---

## Fitur Utama

* **Input Nilai TO Peserta:** Pengguna dapat memasukkan nilai 7 subtes SNBT (PU, PBM, PPU, PK, LBI, LBE, PM). Sistem akan menghitung rata-rata secara otomatis.
* **Prediksi Hasil UTBK:** Program akan membandingkan nilai rata-rata TO pengguna dengan data peserta pada jurusan tertentu untuk memprediksi kemungkinan Lulus atau Tidak Lulus. Prediksi ini menggunakan *passing grade* yang dihitung berdasarkan kuota jurusan.
* **Analisis Distribusi Nilai:** Menampilkan data statistik yang terdiri dari Mean, Median, Kuartil 1 (Q1), Passing Grade, serta Histogram distribusi nilai.
* **Riwayat Prediksi (Stack):** Setiap hasil prediksi yang dilakukan pengguna akan disimpan menggunakan struktur data stack dengan prinsip LIFO (*Last In, First Out*).

---

## Struktur Data yang Digunakan

* **Linked List:** Digunakan untuk membuat dan mengelola Daftar Kampus serta Daftar Jurusan.
* **Stack:** Digunakan untuk menyimpan riwayat prediksi pengguna.
* **Array:** Digunakan untuk menyimpan data peserta pada masing-masing jurusan.

---

## Algoritma yang Digunakan

* **Merge Sort:** Digunakan untuk mengurutkan data peserta pada setiap jurusan berdasarkan rata-rata nilai secara *descending* (dari nilai tertinggi ke terendah) sebagai syarat mutlak sebelum melakukan pencarian.
* **Binary Search:** Digunakan dalam fitur prediksi kelulusan untuk melacak posisi nilai Try Out (TO) pengguna di dalam pangkalan data yang sudah terurut. Algoritma ini membandingkan nilai TO dengan elemen tengah data, lalu mempersempit ruang pencarian menjadi setengahnya secara berulang. Hal ini membuat proses pencarian posisi nilai dan pengecekan *passing grade* menjadi sangat cepat dan efisien.
