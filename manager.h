#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

struct Presensi {
    char username[50];
    char nama[50];
    char tanggal[20];
};

//DEFINISIKAN FUNGSI MANAGER
void login_manager();
void menu_manager();
void rekap_penjualan();

void waktu();
FILE *presensi;

/*
//VOID UTAMA
void main(){
    system("cls");
    waktu();
    login_manager(limit);
}
*/

/*
//DEFINISIKAN FUNGSI SPESIFIK DARI ADMIN DISINI
void waktu(){
    struct Presensi presensi;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(presensi.tanggal, sizeof(presensi.tanggal), "%02d/%02d/%04d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour, tm.tm_min, tm.tm_sec);
}
*/

void login_manager(int limit){

    printf("================================ LOGIN MANAGER ================================\n");
    struct users check;
    struct users input;

    int ada;

    FILE *data_manager; 
    data_manager = fopen("data_manager.dat", "rb");

    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);

    ada = 0;
    while(fread(&check, sizeof(check), 1, data_manager) != 0){
        if(strcmp(check.username, input.username) == 0 && strcmp(input.password, check.password) == 0){
            strcpy(input.nickname, check.nickname);
            ada = 1;
            break;
        }else{
            ada = 0;
        }
    }

    fclose(data_manager);

    if(ada){
        menu_manager(input.nickname);
    }else{
       if(limit > 1){
            system("cls");
            printf("Password atau username salah!\nKesempatan login tersisa %d lagi\n", limit-1);
            login_manager(limit-1);
       }else{
            printf("Maaf, kesempatan login habis\nTekan apapun untuk kembali ke menu utama\n");
            getchar();
            pilih_role();
       }
    }
}

/*
void login_manager(int limit){
    struct users input;
    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);

    if(strcmp(input.username, "manager") == 0 && strcmp(input.password, "manager") == 0){
        menu_manager();
    }else{
        if(limit > 0){
            printf("Username atau password salah! Kesempatan login tersisa %d lagi\n", limit-1);
            login_manager(limit-1);
        }else{
            printf("Kesempatan login habis!\n");
        }
    }
}
*/

void menu_manager(char nickname[]){
    system("cls");
    printf("================================ MENU MANAGER ================================\n");
    int pilih;
    printf("Selamat datang, %s!\n", nickname);
    printf("Menu tersedia manager :\n1. Rekap penjualan\n2. Keluar dari akun\n3. Keluar\n");

    do{
        printf("\nSilahkan pilih : ");
        scanf("%d", &pilih); getchar();

        switch(pilih){
            case 1 :
            rekap_penjualan(nickname);
            break;
            case 2 :
            pilih_role();
            break;
            case 3:
            exit(0);
            break;
            default : 
            printf("Pilihan salah!");
        }
    }while(pilih <= 0 || pilih > 2);
}

/*
int cekAbsensiHariIni(FILE *file, struct Presensi *presensi) {
    fseek(file, 0, SEEK_SET);
    struct Presensi temp;

    // Iterate through the file and check for duplicate entries for the same username and date
    while (fread(&temp, sizeof(struct Presensi), 1, file) == 1) {
        if (strcmp(temp.username, presensi->username) == 0 &&
            strncmp(temp.tanggal, presensi->tanggal, 10) == 0) {
            // Admin sudah absen hari ini
            return 1;
        }
    }

    // Admin belum absen hari ini
    return 0;
}

void catatPresensi(FILE *file, struct Presensi *presensi) {
    fseek(file, 0, SEEK_END);
    fwrite(presensi, sizeof(struct Presensi), 1, file);
}

void lihatPresensi(FILE *file) {
    fseek(file, 0, SEEK_SET);

    struct Presensi presensi;

    while (fread(&presensi, sizeof(struct Presensi), 1, file) == 1) {
        printf("\nDaftar Presensi:\n");
        printf("Nama: %s\n", presensi.username);
        printf("Tanggal: %s\n", presensi.tanggal);
        printf("----------------------------\n");
        system("pause");
        menu_manager();
    }
    printf("tidak ada presensi hari ini!\n");
    system("pause");
    menu_manager();
}
*/

void rekap_penjualan(char nickname[]){
    printf("================================ REKAP PENJUALAN ================================\n");
    system("cls");
    FILE *rekap_penjualan;
    rekap_penjualan = fopen("laporan_penjualan.dat", "rb"); 
    int a  = 0;
    if (rekap_penjualan == NULL) {
        printf("TIDAK ADA PENJUALAN.\n");
        getchar();
        menu_manager(nickname);
        return;
    }else{
        while(fread(&barang, sizeof(barang), 1, rekap_penjualan) == 1){
            //printf("Barang ke : %d\n", a+=1);
            printf("Tanggal pembelian : %02d - %02d - %02d\n", barang.tanggal_masuk.hari, barang.tanggal_masuk.bulan, barang.tanggal_masuk.tahun);
            printf("Waktu pembelian   : %02d : %02d : %d\n", barang.waktu_masuk.jam, barang.waktu_masuk.menit, barang.waktu_masuk.detik);
            printf("Nama              : %s\n", barang.nama);
            printf("Jumlah pembelian  : %d\n", barang.stok);
            printf("Harga barang      : %d\n", barang.harga);
            printf("\n");
        }
        fclose(rekap_penjualan);
    }
    printf("Tekan apapun untuk kembali ke menu utama...\n");
    getchar();
    menu_manager(nickname);
}
