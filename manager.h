#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//DEFINISIKAN VARIABEL GLOBAL DISINI
int limit  = 3;

//DEFINISIKAN STRUCT DISINI
struct users{
    char nickname[300];
    char username[300];
    char password[300];
};

struct Presensi {
    char username[50];
    char nama[50];
    char tanggal[20];
};

//DEFINISIKAN FUNGSI MANAGER
void login_manager();
void menu_manager();
void rekap_presensi();
void rekap_penjualan();
int cekAbsensiHariIni(FILE *file, struct Presensi *presensi);
void catatPresensi(FILE *file, struct Presensi *presensi);
void lihatPresensi(FILE *file);
void waktu();
FILE *presensi;

//VOID UTAMA
void main(){
    system("cls");
    waktu();
    login_manager(limit);
}

//DEFINISIKAN FUNGSI SPESIFIK DARI ADMIN DISINI
void waktu(){
    struct Presensi presensi;
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    snprintf(presensi.tanggal, sizeof(presensi.tanggal), "%02d/%02d/%04d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour, tm.tm_min, tm.tm_sec);
}

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

void menu_manager(){
    system("cls");
    int pilih;
    printf("Menu tersedia manager :\n1. Rekap Presensi\n2. Rekap penjualan\n3. Keluar");

    do{
        printf("\nSilahkan pilih : ");
        scanf("%d", &pilih); getchar();

        switch(pilih){
            case 1 :
            lihatPresensi(presensi);
            break;
            case 2 :
            rekap_penjualan();
            break;
            case 3:
            exit(0);
            break;
            default : 
            printf("Pilihan salah!");
        }
    }while(pilih <= 0 || pilih > 2);
}

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

void rekap_penjualan(){
    system("cls");
    FILE *rekap_penjualan;
    rekap_penjualan = fopen("RekapPenjualan.dat", "rb"); 
    
    if (rekap_penjualan == NULL) {
        printf("TIDAK ADA PENJUALAN.\n");
        system("pause");
        menu_manager();
        return;
    }
}
