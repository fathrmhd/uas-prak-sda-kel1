#include "header.h"

//awal bagian person5 (melanie)
void tampilData() {

    struct Kampus *k = headKampus;

    while (k != NULL) {

        printf("\n=====================================\n");
        printf("KAMPUS : %s\n", k->nama);
        printf("=====================================\n");

        struct Jurusan *j = k->headerJurusan;

        while (j != NULL) {

            printf("\nJurusan : %s\n", j->nama);
            printf("Kuota   : %d\n", j->kuota);

            printf("--------------------------------------------------\n");
            printf("%-3s %-20s %-10s\n", "No", "Nama", "Rata-rata");
            printf("--------------------------------------------------\n");

            for (int i = 0; i < j->jumlahPeserta; i++) {

                printf("%-3d %-20s %-10.2f\n",
                    i + 1,
                    j->data_kursi[i].nama,
                    j->data_kursi[i].nilai.rataRata);
            }

            j = j->next;
        }

        k = k->next;
    }
}

void distribusiFrekuensi(struct Jurusan *j) {
    int freq[11] = {0};

    for (int i = 0; i < j->jumlahPeserta; i++) {

        int index = j->data_kursi[i].nilai.rataRata / 100;

        if (index > 10) {
            index = 10;
        }

        freq[index]++;
    }

    printf("\nDistribusi Frekuensi Nilai\n");
    printf("----------------------------------\n");

    for (int i = 0; i <= 10; i++) {

        int batasBawah = i * 100;
        int batasAtas = batasBawah + 99;

        printf("%3d - %3d : %d\n",
            batasBawah,
            batasAtas,
            freq[i]);
    }
}

void analisisDistribusiNilai(struct Jurusan *j) {
    int freq[11] = {0};

    for (int i = 0; i < j->jumlahPeserta; i++) {

        int index = j->data_kursi[i].nilai.rataRata / 100;

        if (index > 10) {
            index = 10;
        }

        freq[index]++;
    }

    printf("\nHistogram Distribusi Nilai\n");
    printf("====================================\n");

    for (int i = 0; i <= 10; i++) {

        int batasBawah = i * 100;
        int batasAtas = batasBawah + 99;

        printf("%3d - %3d : ",
            batasBawah,
            batasAtas);

        for (int jml = 0; jml < freq[i]; jml++) {
            printf("*");
        }

        printf(" (%d)\n", freq[i]);
    }
}
//akhir bagian person5 (melanie)

//awal bagian person2 (rafid)
void hitungRataRata(struct NilaiSnbt *nilai) {
    if (nilai == NULL);
        return;
        float total = nilai->pu + nilai->pbm + nilai->ppu + nilai->pk + nilai->lbi + nilai->lbe + nilai->pm;
        nilai->rataRata = total / 7.0f;
}

struct Kampus* cariAtauBuatKampus(const char *namaKampus) {
    struct Kampus *curr = headKampus;

    while (curr != NULL) {
        if (strcmp(curr->nama, namaKampus) == 0) {
            return curr; 
        }
        curr = curr->next;
    }

    struct Kampus *newKampus = (struct Kampus*)malloc(sizeof(struct Kampus));
    strcpy(newKampus->nama, namaKampus);
    newKampus->headerJurusan = NULL;

    newKampus->next = headKampus;
    headKampus = newKampus;
    
    return newKampus;
}

struct Jurusan* cariAtauBuatJurusan(struct Kampus *kampusNode, const char *namaJurusan, int kuotaAwal) {
    if (kampusNode == NULL) return NULL;
    
    struct Jurusan *curr = kampusNode->headerJurusan;

    while (curr != NULL) {
        if (strcmp(curr->nama, namaJurusan) == 0) {
            return curr; 
        }
        curr = curr->next;
    }

    struct Jurusan *newJurusan = (struct Jurusan*)malloc(sizeof(struct Jurusan));
    strcpy(newJurusan->nama, namaJurusan);
    newJurusan->kuota = kuotaAwal;
    newJurusan->jumlahPeserta = 0;
    newJurusan->info_statistik.rata_rata_jurusan = 0.0f;
    newJurusan->info_statistik.median = 0.0f;
    newJurusan->info_statistik.q1 = 0.0f;
    newJurusan->info_statistik.batas_lulus = 0.0f;

    newJurusan->next = kampusNode->headerJurusan;
    kampusNode->headerJurusan = newJurusan;
    
    return newJurusan;
}

void insertPeserta(const char *namaKampus, const char *namaJurusan, int kuota, const char *namaPeserta, struct NilaiSnbt nilaiSubtes) {
    struct Kampus *kampus = cariAtauBuatKampus(namaKampus);
    struct Jurusan *jurusan = cariAtauBuatJurusan(kampus, namaJurusan, kuota);
    
    hitungRataRata(&nilaiSubtes);
    
    if (jurusan->jumlahPeserta < 100) {
        int index = jurusan->jumlahPeserta;
        strcpy(jurusan->data_kursi[index].nama, namaPeserta);
        jurusan->data_kursi[index].nilai = nilaiSubtes;
        jurusan->jumlahPeserta++;
    } else {
        printf("Gagal menginput! Jurusan %s di %s sudah penuh.\n", jurusan->nama, kampus->nama);
    }
}
//akhir bagian person2 (rafid)
