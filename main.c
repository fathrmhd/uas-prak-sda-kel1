#include "header.h"

struct Kampus *headKampus = NULL;
struct LogRiwayat *topStack = NULL;

struct NilaiSnbt nilaiTOTerakhir;
int nilaiTO = 0;

int main()
{
    int pilihan;
    char kampus[50], jurusan[50];

    printf("=========================================\n");
    printf("  SISTEM ANALISIS DISTRIBUSI NILAI SNBT  \n");
    printf("  Praktikum Struktur Data dan Algoritma  \n");
    printf("=========================================\n");

    inputData();

    do
    {
        printf("\n=========================================\n");
        printf("               MENU UTAMA                \n");
        printf("=========================================\n");
        printf("1. Input Nilai TO Peserta\n");
        printf("2. Prediksi Hasil UTBK\n");
        printf("3. Analisis Distribusi Nilai\n");
        printf("4. Lihat Riwayat Prediksi (Stack LIFO)\n");
        printf("5. Keluar dari Program\n");
        printf("-----------------------------------------\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
        case 1:
        {
            printf("\n--- INPUT NILAI TO ---\n");
            printf("Nilai PU  : ");
            scanf("%f", &nilaiTOTerakhir.pu);
            printf("Nilai PBM : ");
            scanf("%f", &nilaiTOTerakhir.pbm);
            printf("Nilai PPU : ");
            scanf("%f", &nilaiTOTerakhir.ppu);
            printf("Nilai PK  : ");
            scanf("%f", &nilaiTOTerakhir.pk);
            printf("Nilai LBI : ");
            scanf("%f", &nilaiTOTerakhir.lbi);
            printf("Nilai LBE : ");
            scanf("%f", &nilaiTOTerakhir.lbe);
            printf("Nilai PM  : ");
            scanf("%f", &nilaiTOTerakhir.pm);

            hitungRataRata(&nilaiTOTerakhir);
            nilaiTO = 1;
            printf("\n=> Nilai TO berhasil dicatat.\n");
            printf("=> Rata-rata Anda: %.2f\n", nilaiTOTerakhir.rataRata);
            break;
        }
        case 2:
        {
            int opsiPrediksi;
            printf("\n--- PREDIKSI HASIL UTBK ---\n");
            printf("1. Gunakan nilai TO yang sudah diinput sebelumnya\n");
            printf("2. Input nilai TO terbaru\n");
            printf("Pilih opsi: ");
            scanf("%d", &opsiPrediksi);

            float skorDigunakan = 0.0f;

            if (opsiPrediksi == 1)
            {
                if (!nilaiTO)
                {
                    printf("\n[!] Anda belum pernah menginput nilai TO. Silakan pilih opsi 2 atau menu 1 terlebih dahulu.\n");
                    break;
                }
                skorDigunakan = nilaiTOTerakhir.rataRata;
            }
            else if (opsiPrediksi == 2)
            {
                struct NilaiSnbt nilaiBaru;
                printf("\n--- INPUT NILAI TO ---\n");
                printf("Nilai PU  : ");
                scanf("%f", &nilaiBaru.pu);
                printf("Nilai PBM : ");
                scanf("%f", &nilaiBaru.pbm);
                printf("Nilai PPU : ");
                scanf("%f", &nilaiBaru.ppu);
                printf("Nilai PK  : ");
                scanf("%f", &nilaiBaru.pk);
                printf("Nilai LBI : ");
                scanf("%f", &nilaiBaru.lbi);
                printf("Nilai LBE : ");
                scanf("%f", &nilaiBaru.lbe);
                printf("Nilai PM  : ");
                scanf("%f", &nilaiBaru.pm);
                hitungRataRata(&nilaiBaru);
                nilaiTOTerakhir = nilaiBaru; // Update nilai terakhir
                nilaiTO = 1;
                skorDigunakan = nilaiTOTerakhir.rataRata;
                printf("=> Rata-rata Nilai TO Baru: %.2f\n", skorDigunakan);
            }
            else
            {
                printf("\nOpsi tidak valid.\n");
                break;
            }
            tampilDaftarKampus();
            printf("\nNama Kampus yang ingin dicek : ");
            scanf(" %49[^\n]", kampus);
            printf("Nama Jurusan yang ingin dicek: ");
            scanf(" %49[^\n]", jurusan);

            prediksiHasilUTBK(kampus, jurusan, skorDigunakan);
            break;
        }
        case 3:
        {
            printf("\n--- Analisis Distribusi Nilai ---\n");
            tampilDaftarKampus();
            printf("Nama Kampus  : ");
            scanf(" %49[^\n]", kampus);
            printf("Nama Jurusan : ");
            scanf(" %49[^\n]", jurusan);

            struct Kampus *k = cariKampus(kampus);
            if (k == NULL)
            {
                printf("\nKampus '%s' tidak ditemukan.\n", kampus);
                break;
            }
            struct Jurusan *j = cariJurusan(k, jurusan);
            if (j == NULL)
            {
                printf("\nJurusan '%s' tidak ditemukan.\n", jurusan);
                break;
            }

            hitungStatistikJurusan(j);

            printf("\n=========================================\n");
            printf("      DISTRIBUSI NILAI TAHUN LALU      \n");
            printf("=========================================\n");
            printf("Kampus        : %s\n", k->nama);
            printf("Jurusan       : %s\n", j->nama);
            printf("Daya Tampung  : %d\n", j->kuota);
            printf("-----------------------------------------\n");
            printf("Rata-rata (Mean): %.2f\n", j->info_statistik.rata_rata_jurusan);
            printf("Median          : %.2f\n", j->info_statistik.median);
            printf("Kuartil 1 (Q1)  : %.2f\n", j->info_statistik.q1);
            printf("Passing Grade   : %.2f\n", j->info_statistik.batas_lulus);
            printf("=========================================\n");
            analisisDistribusiNilai(j);
            break;
        }
        case 4:
            tampil(); // Tugas Person 6
            break;
        case 5:
            printf("\nTerima kasih telah menggunakan sistem prediksi SNBT!\n");
            break;
        default:
            printf("\nPilihan menu tidak valid!\n");
        }
    } while (pilihan != 5);

    freeMemori(); // Tugas Person 6
    return 0;
}
