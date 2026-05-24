//Person 1 (Febi)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCT NILAI 7 SUBTES
struct NilaiSnbt {
    float pu, pbm, ppu, pk, lbi, lbe, pm, rataRata;
};

// STRUCT PESERTA
struct Peserta {
    struct NilaiSnbt nilai;
};

// STRUCT STATISTIK
struct Statistik {
    float rata_rata_jurusan;
    float median;
    float q1;
    float batas_lulus;
};

// STRUCT JURUSAN (node linked list)
struct Jurusan {
    char nama[50];
    int kuota;
    struct Peserta data_kursi[100];
    int jumlahPeserta;
    struct Statistik info_statistik;
    struct Jurusan *next;
};

// STRUCT KAMPUS (node linked list)
struct Kampus {
    char nama[50];
    struct Jurusan *headerJurusan;
    struct Kampus *next;
};

// STRUCT LOG RIWAYAT (node stact)
struct LogRiwayat {
    char kampus_tujuan[50];
    char jurusan_tujuan[50];
    float skor_akhir;
    char status_kelulusan[20];
    struct LogRiwayat *next;
};

// VARIABEL GLOBAL
extern struct Kampus *headKampus;
extern struct LogRiwayat *topStack;

// VARIABEL untuk menyimpan log Nilai TO
extern struct NilaiSnbt nilaiTOTerakhir;
extern int nilaiTO;

void distribusiFrekuensi(struct Jurusan *j);
void analisisDistribusiNilai(struct Jurusan *j);

struct Kampus* cariAtauBuatKampus(const char *namaKampus);
struct Jurusan* cariAtauBuatJurusan(struct Kampus *kampusNode, const char *namaJurusan, int kuotaAwal);
void hitungRataRata(struct NilaiSnbt *nilai);
void insertPeserta(const char *namaKampus, const char *namaJurusan, int kuota, struct NilaiSnbt nilaiSubtes);

void merge(struct Peserta *arr, int kiri, int tengah, int kanan);
void mergeSort(struct Peserta *arr, int kiri, int kanan);
void hitungStatistikJurusan(struct Jurusan *j);

int binarySearch(struct Peserta *arr, int kiri, int kanan, float targetNilai);
struct Kampus* cariKampus(const char *namaKampus);
struct Jurusan* cariJurusan(struct Kampus *kampusNode, const char *namaJurusan);
void prediksiHasilUTBK(const char *namaKampus, const char *namaJurusan, float targetNilai);

void tampilDaftarKampus();
void pushRiwayat(const char *Kampus, const char *Jurusan, float skor, const char *status);
void tampil();
void inputData();
void freeMemori();
