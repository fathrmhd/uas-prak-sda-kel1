#include "header.h"

//awal bagian person2 (rafid)
void hitungRataRata(struct NilaiSnbt *nilai) {
    if (nilai == NULL){
        return;
    }
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
    if (newKampus == NULL) {
        printf("[ERROR] Gagal alokasi memori untuk Kampus.\n");
        return NULL;
    }
    strcpy(newKampus->nama, namaKampus);
    newKampus->headerJurusan = NULL;
    newKampus->next = headKampus;
    headKampus = newKampus;
    return newKampus;
}

struct Jurusan* cariAtauBuatJurusan(struct Kampus *kampusNode, const char *namaJurusan, int kuotaAwal) {
    if (kampusNode == NULL){
        return NULL;
    }
    
    struct Jurusan *curr = kampusNode->headerJurusan;

    while (curr != NULL) {
        if (strcmp(curr->nama, namaJurusan) == 0) {
            return curr; 
        }
        curr = curr->next;
    }

    struct Jurusan *newJurusan = (struct Jurusan*)malloc(sizeof(struct Jurusan));
    if (newJurusan == NULL) {
        printf("[ERROR] Gagal alokasi memori untuk Jurusan.\n");
        return NULL;
    }
    strcpy(newJurusan->nama, namaJurusan);
    newJurusan->kuota = kuotaAwal;
    newJurusan->jumlahPeserta = 0;
    memset(&newJurusan->info_statistik, 0, sizeof(struct Statistik));
    newJurusan->next = kampusNode->headerJurusan;
    kampusNode->headerJurusan = newJurusan;
    return newJurusan;
}

void insertPeserta(const char *namaKampus, const char *namaJurusan, int kuota, struct NilaiSnbt nilaiSubtes) {
    struct Kampus *kampus = cariAtauBuatKampus(namaKampus);
    struct Jurusan *jurusan = cariAtauBuatJurusan(kampus, namaJurusan, kuota);
    hitungRataRata(&nilaiSubtes);

    if (jurusan->jumlahPeserta < 100) {
        int index = jurusan->jumlahPeserta;
        jurusan->data_kursi[index].nilai = nilaiSubtes;
        jurusan->jumlahPeserta++;
    } else {
        printf("Gagal menginput! Jurusan %s di %s penuh.\n", jurusan->nama, kampus->nama);
    }
}
//akhir bagian person2 (rafid)

// awal bagian person3 (Dhawy)
void merge(struct Peserta arr[], int kiri, int tengah, int kanan) {
    int n1 = tengah - kiri + 1;
    int n2 = kanan - tengah;

    struct Peserta *L = (struct Peserta*)malloc(n1 * sizeof(struct Peserta));
    struct Peserta *R = (struct Peserta*)malloc(n2 * sizeof(struct Peserta));
    if (L == NULL || R == NULL) {
        printf("[ERROR] Alokasi memori merge gagal.\n");
        free(L); free(R);
        return;
    }

    for (int i = 0; i < n1; i++) {
        L[i] = arr[kiri + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[tengah + 1 + j];
    }

    int i = 0, j = 0, k = kiri;
    while (i < n1 && j < n2) {
        if (L[i].nilai.rataRata >= R[j].nilai.rataRata) {
           arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }

    free(L);
    free(R);
}

void mergeSort(struct Peserta arr[], int kiri, int kanan) {
    if (kiri < kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        mergeSort(arr, kiri, tengah);
        mergeSort(arr, tengah + 1, kanan);
        merge(arr, kiri, tengah, kanan);
    }
}

void hitungStatistikJurusan(struct Jurusan *j) {
    if (j->jumlahPeserta == 0) {
        printf("Belum ada peserta.\n");
        return;
    }

    mergeSort(j->data_kursi, 0, j->jumlahPeserta - 1);
    
    float total = 0;
    int n = j->jumlahPeserta;
    for (int i = 0; i < n; i++) {
        total += j->data_kursi[i].nilai.rataRata;
    }
    j->info_statistik.rata_rata_jurusan = total / n;

    if (n % 2 == 0) {
        j->info_statistik.median = (j->data_kursi[n / 2 - 1].nilai.rataRata + j->data_kursi[n / 2].nilai.rataRata) / 2;
    } else {
        j->info_statistik.median = j->data_kursi[n / 2].nilai.rataRata;
    }

    int indexQ1 = (3 * n) / 4;
    j->info_statistik.q1 = j->data_kursi[indexQ1].nilai.rataRata;

    int passingGrade;
    if(n < j->kuota){
        passingGrade = n - 1;
    } else {
        passingGrade = j->kuota - 1;
    }

    j->info_statistik.batas_lulus = j->data_kursi[passingGrade].nilai.rataRata;
}
//akhir bagian person3 (Dhawy)

//awal bagian person4 (Mustaqim)
int binarySearch(struct Peserta arr[], int kiri, int kanan, float targetNilai) {
    if (kanan >= kiri) {
        int tengah = kiri + (kanan - kiri) / 2;
        float selisih = arr[tengah].nilai.rataRata - targetNilai;
        if (selisih < 0) selisih = -selisih;
        if (selisih < 0.01) {
            return tengah; // Ketemu
        }

        if (arr[tengah].nilai.rataRata > targetNilai) {
            return binarySearch(arr, kiri, tengah - 1, targetNilai);
        }
        return binarySearch(arr, tengah + 1, kanan, targetNilai);
    }
    return -1; // Tidak ketemu
}

struct Kampus* cariKampus(const char *namaKampus) {
    struct Kampus *k = headKampus;
    while (k != NULL) {
        if (strcmp(k->nama, namaKampus) == 0) {
            return k; // Kampus ditemukan
        }
        k = k->next;
    }
    return NULL; // Kampus tidak ditemukan
}

struct Jurusan* cariJurusan(struct Kampus *kampusNode, const char *namaJurusan) {
    if (kampusNode == NULL) return NULL;
    
    struct Jurusan *j = kampusNode->headerJurusan;
    while (j != NULL) {
        if (strcmp(j->nama, namaJurusan) == 0) {
            return j; // Jurusan ditemukan
        }
        j = j->next;
    }
    return NULL; // Jurusan tidak ditemukan
}

void prediksiHasilUTBK(const char *namaKampus, const char *namaJurusan, float targetNilai) {
    struct Kampus *k = cariKampus(namaKampus);
    if (k == NULL) {
        printf("Kampus %s tidak ditemukan dalam sistem.\n", namaKampus);
        return;
    }

    struct Jurusan *j = cariJurusan(k, namaJurusan);

    if (j == NULL) {
        printf("Jurusan %s tidak ditemukan di kampus %s.\n", namaJurusan, namaKampus);
        return;
    }

    hitungStatistikJurusan(j);

    int estimasiRank = 1;
    for (int i = 0; i < j->jumlahPeserta; i++) {
        if (j->data_kursi[i].nilai.rataRata > targetNilai) {
            estimasiRank++;
        }
    }
 
    int posisiPersisData = binarySearch(j->data_kursi, 0, j->jumlahPeserta - 1, targetNilai);

    printf("\n=========================================\n");
    printf("         HASIL PREDIKSI KELULUSAN        \n");
    printf("=========================================\n");
    printf("Kampus Tujuan : %s\n", k->nama);
    printf("Jurusan Tujuan: %s\n", j->nama);
    printf("Nilai Kamu    : %.2f\n", targetNilai);
    printf("Batas Lulus   : %.2f\n", j->info_statistik.batas_lulus);

    if (j->jumlahPeserta > 0) {
        printf("Estimasi Rank : %d dari %d peserta\n", estimasiRank, j->jumlahPeserta);
        if (posisiPersisData != -1) {
            printf("(Nilai ini cocok persis dengan data historis di posisi index %d)\n", posisiPersisData);
        }
    }

    char status[20];
    if (j->jumlahPeserta == 0) {
        strcpy(status, "Data Belum Ada");
        printf("\nStatus: BELUM BISA DIPREDIKSI (Data pendaftar masih kosong atau belum dihitung)\n");
    } else if (targetNilai >= j->info_statistik.batas_lulus) {
        strcpy(status, "Lulus");
        printf("\nStatus: PREDIKSI LULUS AMAN!\n");
        printf("Nilaimu berada di atas batas aman jurusan ini.\n");
    } else {
        strcpy(status, "Tidak Lulus");
        printf("\nStatus: PREDIKSI RAWAN / TIDAK LULUS\n");
        printf("Nilaimu masih di bawah batas lulus. Terus semangat belajar!\n");
    }
    printf("=========================================\n");

    pushRiwayat(namaKampus, namaJurusan, targetNilai, status);
}

// akhir bagian person4 (Mustaqim)

// awal bagian person5 (Mellanie)
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
        printf("%3d - %3d : %d\n", batasBawah, batasAtas, freq[i]);
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
    printf("=========================================\n");

    for (int i = 0; i <= 10; i++) {
        int batasBawah = i * 100;
        int batasAtas = batasBawah + 99;

        // Tampilkan hanya jika ada data agar terminal lebih bersih
        if (freq[i] > 0 || (i >= 4 && i <= 8)) { 
            printf("%3d - %3d : ", batasBawah, batasAtas);
            for (int jml = 0; jml < freq[i]; jml++) {
                printf("*");
            }
            printf(" (%d)\n", freq[i]);
        }
    }
}

//Person 6 (Fathir)
void pushRiwayat(const char *Kampus, const char *Jurusan, float skor, const char *status){
    struct LogRiwayat *new = (struct LogRiwayat*)malloc(sizeof(struct LogRiwayat));
    strcpy(new->kampus_tujuan, Kampus);
    strcpy(new->jurusan_tujuan, Jurusan);
    new->skor_akhir = skor;
    strcpy(new->status_kelulusan, status);
    new->next = topStack;
    topStack = new;
}

void tampil(){
    if(topStack == NULL){
        printf("Belum pernah melakukan prediksi kelulusan\n");
        return;
    }
    printf("\n==== HISTORY PREDIKSI ====\n");
    struct LogRiwayat *curent = topStack;
    int no = 1;
    while(curent != NULL){
        printf("%d. %s - %s | Skor: %.2f | Status: %s\n", no++, curent->kampus_tujuan, curent->jurusan_tujuan, curent->skor_akhir, curent->status_kelulusan);
        curent = curent->next;
    }
    
}

void tampilDaftarKampus() {
    if (headKampus == NULL) {
        printf("\n[!] Database kampus saat ini kosong.\n");
        return;
    }
    
    printf("\n=========================================\n");
    printf("         DAFTAR KAMPUS & JURUSAN          ");
    printf("\n=========================================\n");
    
    struct Kampus *k = headKampus;
    int noKampus = 1;
    
    while (k != NULL) {
        printf("%d. %s\n", noKampus++, k->nama);
        
        struct Jurusan *j = k->headerJurusan;
        while (j != NULL) {
            // Menampilkan nama jurusan, kuota penerimaan, dan ketersediaan data
            printf("   -> %s (Kuota: %d)\n", j->nama, j->kuota);
            j = j->next;
        }
        k = k->next;
    }
    printf("=========================================\n");
}

void freeMemori(){
    while (topStack != NULL) {
        struct LogRiwayat *tmp = topStack;
        topStack = topStack->next;
        free(tmp);
    }
    // Hapus Linked List Kampus & Jurusan
    while (headKampus != NULL) {
        struct Kampus *kTmp = headKampus;
        headKampus = headKampus->next;
        while (kTmp->headerJurusan != NULL) {
            struct Jurusan *jTmp = kTmp->headerJurusan;
            kTmp->headerJurusan = kTmp->headerJurusan->next;
            free(jTmp);
        }
        free(kTmp);
    }
}

void inputData() {
    FILE *file = fopen("dataNilai.csv", "r");
    if (file == NULL) {
        printf("[!] File dataNilai.csv tidak ditemukan!\n");
        return;
    }

    char buffer[1024];
    int baris = 0;

    while (fgets(buffer, sizeof(buffer), file)) {
        baris++;
        
        if (baris == 1) continue; 

        char kampus[50], jurusan[50];
        int kuota;
        struct NilaiSnbt n;

        // Parsing data yang dipisah dengan koma (10 elemen data)
        int parsed = sscanf(buffer, "%49[^,],%49[^,],%d,%f,%f,%f,%f,%f,%f,%f",
                            kampus, jurusan, &kuota,
                            &n.pu, &n.pbm, &n.ppu, &n.pk, &n.lbi, &n.lbe, &n.pm);

        if (parsed == 10) {
            insertPeserta(kampus, jurusan, kuota, n);
        }
    }

    fclose(file);
}
