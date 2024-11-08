// FINAL PROJECT STRUKTUR DATA : PROGRAM SEWA KAMERA
// KELOMPOK 6 KELAS C
// ANGGOTA KELOMPOK : 
// 1. CHRISTIAN VALENTINO (2308561081)
// 2. ANAK AGUNG GEDE ANGGA PUTRA WIBAWA (2308561099)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct lensa
{
    char jenisLensa[20];
    struct lensa *next;
    struct lensa *prev;
} lensa;

typedef struct kamera
{
    char jenisKamera[20];
    int unitTersedia;
    float hargaSewa;
    lensa *jenisLensaHead;
    struct kamera *next;
    struct kamera *prev;
} kamera;

typedef struct data
{
    char nama[50];
    char jenisKamera[30];
    char jenisLensa[20];
    char tanggalPenyewaan[11];
    int lamaSewa;
    int biaya; 
    char tanggalPengembalian[11];
    char jaminan[20];
    struct data *next;
    struct data *prev;
} data;

kamera *headKamera = NULL;
data *headData = NULL;
lensa *headLensa = NULL;

void tambahNodeData(const char *nama, const char *jenisKamera, const char *jenisLensa, const char *tanggalPenyewaan, int lamaSewa, int biaya, const char *tanggalPengembalian, const char *jaminan)
{
    data *newData = (data *)malloc(sizeof(data));
    strcpy(newData->nama, nama);
    strcpy(newData->jenisKamera, jenisKamera);
    strcpy(newData->jenisLensa, jenisLensa);
    strcpy(newData->tanggalPenyewaan, tanggalPenyewaan);
    newData->lamaSewa = lamaSewa;
    newData->biaya = biaya;
    strcpy(newData->tanggalPengembalian, tanggalPengembalian);
    strcpy(newData->jaminan, jaminan);
    newData->next = NULL;
    newData->prev = NULL;
    data *temp = headData;
    if (temp == NULL)
    {
        headData = newData;
    } else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newData;
        newData->prev = temp;
    }
}

void tambahNodeKamera(const char *jenisKamera, int jumlah, float hargaSewa)
{
    kamera *newKamera = (kamera *)malloc(sizeof(kamera));
    strcpy(newKamera->jenisKamera, jenisKamera);
    newKamera->unitTersedia = jumlah;
    newKamera->hargaSewa = hargaSewa;
    newKamera->jenisLensaHead = headLensa;
    newKamera->next = NULL;
    newKamera->prev = NULL;
    kamera *temp = headKamera;
    if (temp == NULL)
    {
        headKamera = newKamera;
    } else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newKamera;
        newKamera->prev = temp;
    }
}

void tambahNodeLensa(const char *jenisLensa)
{
    lensa *newLensa = (lensa *)malloc(sizeof(lensa));
    strcpy(newLensa->jenisLensa, jenisLensa);
    newLensa->next = NULL;
    newLensa->prev = NULL;
    lensa *temp = headLensa;
    if (temp == NULL)
    {
        headLensa = newLensa;
    } else
    {
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newLensa;
        newLensa->prev = temp;
    }
}

void tambahJenisKamera()
{
    char jenisKamera[20];
    int jumlah;
    float hargaSewa;

    printf("Masukkan Produk Kamera Baru : ");
    getchar();
    fgets(jenisKamera, sizeof(jenisKamera), stdin);
    strtok(jenisKamera, "\n");
    printf("Masukkan Jumlah Unit : ");
    scanf("%d", &jumlah);
    printf("Masukkan Harga Sewa Per Hari : ");
    scanf("%f", &hargaSewa);

    tambahNodeKamera(jenisKamera, jumlah, hargaSewa);
}

void tambahJenisLensa()
{
    char jenisLensa[20];

    printf("Masukkan Jenis Lensa Baru : ");
    getchar();
    fgets(jenisLensa, sizeof(jenisLensa), stdin);
    strtok(jenisLensa, "\n");

    tambahNodeLensa(jenisLensa);
}

void kameraAwal()
{
    tambahNodeKamera("Sony A7 III", 5, 375.0);
    tambahNodeKamera("Sony A6600", 8, 250.0);
    tambahNodeKamera("Sony A6400", 15, 200.0);
    tambahNodeKamera("Canon EOS RP", 4,  375.0);
    tambahNodeKamera("Canon EOS R6", 5, 425.0);
    tambahNodeKamera("Canon EOS M50", 10, 225.0);
    tambahNodeKamera("Canon EOS M3", 3, 200.0);
    tambahNodeKamera("Fujifilm X-T30 II", 8, 275.0);
    tambahNodeKamera("Fujifilm X-T3", 5, 300.0);
    tambahNodeKamera("Fujifilm X-S10", 2, 350.0);
}

void lensaAwal()
{
    tambahNodeLensa("Fix");
    tambahNodeLensa("Zoom");
    tambahNodeLensa("Macro");
    tambahNodeLensa("Telephoto");
    tambahNodeLensa("Wide Angle");
    tambahNodeLensa("Standard");
}

void tampilkanJenisKamera()
{
    kamera *temp = headKamera;
    int index = 1;
    printf("=============== Kamera Yang Tersedia ==============\n");
    printf("\n| %-3s | %-20s | %-5s | %-10s |\n",
        "No", "Jenis Kamera", "Unit", "Harga Sewa");
    while (temp != NULL)
    {
        printf("| %-3d | %-20s | %-5d | %-10.3f |\n",
            index++, temp->jenisKamera, temp->unitTersedia, temp->hargaSewa);
        temp = temp->next;
    }
}

void tampilkanJenisLensa(lensa *headLensa)
{
    lensa *temp = headLensa;
    int index = 1;
    printf("\n=== Jenis Lensa yang Tersedia ===\n");
    while (temp != NULL)
    {
        printf("%d. %s\n", index++, temp->jenisLensa);
        temp = temp->next;
    }
}

void hitungTanggal(const char *tanggalPenyewaan, int lamaSewa, char *tanggalPengembalian)
{
    const int hariTiapBulan[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    int tanggal;
    int bulan;
    int tahun;

    sscanf(tanggalPenyewaan, "%d/%d/%d", &tanggal, &bulan, &tahun);
    tanggal += lamaSewa;

    while (tanggal > hariTiapBulan[bulan - 1])
    {
        tanggal -= hariTiapBulan[bulan - 1];
        bulan++;
        if (bulan > 12)
        {
            bulan = 1;
            tahun++;
        }
    }
    sprintf(tanggalPengembalian, "%02d/%02d/%04d", tanggal, bulan, tahun);
}

void sewaKamera()
{
    tampilkanJenisKamera();
    int pilihan;
    printf("\nPilih Jenis Kamera Yang Ingin Disewa (Input Nomor): ");
    scanf("%d", &pilihan);

    kamera *temp = headKamera;
    int indexKamera = 1;
    while (temp != NULL && indexKamera < pilihan)
    {
        temp = temp->next;
        indexKamera++;
    }

    if (temp != NULL && temp->unitTersedia > 0)
    {
        printf("Jenis Kamera Yang Dipilih : %s\n", temp->jenisKamera);

        tampilkanJenisLensa(temp->jenisLensaHead);

        int pilihLensa;
        printf("\nMasukkan Nomor Jenis Lensa Yang Ingin Disewa \n");
        printf("Input 0 Untuk Batal Sewa \n");
        printf("Pilih : ");
        scanf("%d", &pilihLensa);

        if (pilihLensa == 0)
        {
            printf("Penyewaan Dibatalkan.\n");
            return;
        }

        int indexLensa = 1;
        lensa *lensaTemp = temp->jenisLensaHead;
        while (lensaTemp != NULL && indexLensa < pilihLensa)
        {
            lensaTemp = lensaTemp->next;
            indexLensa++;
        }

        if (lensaTemp != NULL)
        {
            printf("Jenis Lensa Yang Dipilih : %s\n", lensaTemp->jenisLensa);
            char namaPenyewa[50];
            char tanggalPenyewaan[11];
            char tanggalPengembalian[11];
            int lamaSewa;
            char jaminan[20];
            int jumlahBayar;
            int kurang;
            int nominal;

            getchar();
            printf("Masukkan Nama Penyewa : ");
            fgets(namaPenyewa, sizeof(namaPenyewa), stdin);
            strtok(namaPenyewa, "\n");
            printf("Masukkan Tanggal Penyewaan (dd/mm/yyyy): ");
            scanf("%s", tanggalPenyewaan);
            printf("Masukkan Lama Sewa (Hari): ");
            scanf("%d", &lamaSewa);
            hitungTanggal(tanggalPenyewaan, lamaSewa, tanggalPengembalian);
            jumlahBayar = temp->hargaSewa * lamaSewa * 1000;
            printf("Total Harga Sewa: Rp %d\n", jumlahBayar);
            printf("Jumlah Bayar : Rp ");
            scanf("%d", &nominal);
            if (nominal < jumlahBayar)
            {
                printf("\nUang Anda Kurang : Rp %d\n", jumlahBayar - nominal);
                return;
            }
            printf("\nKembalian : Rp %d\n", nominal - jumlahBayar);
            getchar();
            printf("Masukkan Jaminan Penyewaan: ");
            scanf("%s", jaminan);

            tambahNodeData(namaPenyewa, temp->jenisKamera, lensaTemp->jenisLensa, tanggalPenyewaan, lamaSewa, jumlahBayar, tanggalPengembalian, jaminan);

            temp->unitTersedia--;

            printf("Penyewaan Berhasil!\n");
        } else
        {
            printf("Lensa Tidak Tersedia.\n");
        }
    } else
    {
        printf("Kamera Tidak Tersedia.\n");
    }
}

void tampilkanData()
{
    data *temp = headData;
    int index = 1;
    printf("\n=============================================================== Data Penyewaan ===============================================================\n");
    printf("| %-3s | %-20s | %-20s | %-15s | %-10s | %-5s | %-10s | %-15s | %-15s |\n",
        "No", "Nama", "Jenis Kamera", "Jenis Lensa", "Tgl Sewa", "Hari", "Tgl Kembali", "Jaminan", "Biaya Sewa");
    while (temp != NULL)
    {
        printf("| %-3d | %-20s | %-20s | %-15s | %-10s | %-5d | %-11s | %-15s | %-15d |\n",
            index++, temp->nama, temp->jenisKamera, temp->jenisLensa, temp->tanggalPenyewaan, temp->lamaSewa, temp->tanggalPengembalian, temp->jaminan, temp->biaya);
        temp = temp->next;
    }
}

void hapusData()
{
    tampilkanData();

    int pilihan;
    printf("Pilih Nomor Data Yang Ingin Dihapus!\n");
    printf("Ketik 0 Untuk Batalkan\n");
    printf("Pilih : ");
    scanf("%d", &pilihan);
    if (pilihan == 0)
    {
        printf("Penghapusan Data Dibatalkan.\n");
        return;
    }
    data *temp = headData;
    for (int i = 1; temp != NULL && i < pilihan; i++)
    {
        temp = temp->next;
    }
    if (temp != NULL)
    {
        char jenisKamera[20];
        char jenisLensa[20];
        strcpy(jenisKamera, temp->jenisKamera);
        strcpy(jenisLensa, temp->jenisLensa);

        if (temp->prev != NULL)
        {
            temp->prev->next = temp->next;
        } else
        {
            headData = temp->next;
        }
        if (temp->next != NULL)
        {
            temp->next->prev = temp->prev;
        }
        free(temp);
        printf("Data Berhasil Dihapus.\n");

        kamera *tempKamera = headKamera;
        while (tempKamera != NULL)
        {
            if (strcmp(tempKamera->jenisKamera, jenisKamera) == 0)
            {
                lensa *tempLensa = tempKamera->jenisLensaHead;
                while (tempLensa != NULL)
                {
                    if (strcmp(tempLensa->jenisLensa, jenisLensa) == 0)
                    {
                        tempKamera->unitTersedia++;
                        break;
                    }
                    tempLensa = tempLensa->next;
                }
                break;
            }
            tempKamera = tempKamera->next;
        }
    } else
    {
        printf("Data Tidak Ada.\n");
    }
}

int main()
{
    lensaAwal();
    kameraAwal();
    char konfirmasi;
    int pilihan;
    int pilih2;
    int pilih5;
    do
    {
        printf("\n======== Sistem Penyewaan Kamera ========\n");
        printf("1. Sewa Kamera\n");
        printf("2. Tampilkan Produk Yang Tersedia\n");
        printf("3. Tampilkan Data Penyewaan\n");
        printf("4. Hapus Data Penyewaan\n");
        printf("5. Tambah Produk Baru\n");
        printf("6. Keluar\n");
        printf("Pilih Menu: ");
        scanf("%d", &pilihan);

        switch (pilihan)
        {
            case 1:
                sewaKamera();
                break;
            case 2:
                printf("1. Kamera\n");
                printf("2. Lensa\n");
                printf("Pilih : ");
                scanf("%d", &pilih2);
                if (pilih2 == 1)
                {
                    tampilkanJenisKamera();
                } else if (pilih2 == 2)
                {
                    tampilkanJenisLensa(headLensa);
                }
                break;
            case 3:
                tampilkanData();
                break;
            case 4:
                hapusData();
                break;
            case 5:
                printf("1. Kamera\n");
                printf("2. Lensa\n");
                printf("Pilih : ");
                scanf("%d", &pilih5);
                if (pilih5 == 1)
                {
                    tambahJenisKamera();
                } else if (pilih5 == 2)
                {
                    tambahJenisLensa();
                }
                break;
            case 6:
                printf("\nApakah anda yakin akan keluar? (Y/T) : ");
                scanf(" %c", &konfirmasi);
                if (konfirmasi == 'Y') {
                    printf("Terima kasih!\n");
                }
                break;
            default:
                printf("Pilihan Tidak Ada. Silakan Coba Lagi!\n");
        }
    } while (konfirmasi != 'Y');

    return 0;
}
