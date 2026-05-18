#ifndef HEADER_H
#define HEADER_H 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// STRUCT NILAI 7 SUBTES
struct NilaiSnbt {
    float pu;
    float pbm;
    float ppu;
    float pk;
    float lbi;
    float lbe;
    float pm;
    float rataRata;
};

// STRUCT PESERTA
struct Peserta {
    char nama[50];
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

#endif