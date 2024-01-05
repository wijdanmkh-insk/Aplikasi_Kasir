#include <stdio.h>
//#include "setup.h"

//DEFINISIKAN VARIABEL GLOBAL DISINI
int limit  = 3;

//DEFINISIKAN VARIABEL FILE DISINI
char nama_file[4][50] = {"data_cashier.dat", "data_logistician.dat", "data_manager.dat", "data_admin.dat"};
char nama_file_temp[4][50] = {"data_cashier1.dat", "data_logistician1.dat", "data_manager1.dat", "data_admin1.dat"};
//char cek_presensi[3][50] = {"presensi_cashier.dat", "presensi_logistician.dat", "presensi_manager.dat"};

//DEFINISIKAN ROLE PENGGUNA APLIKASI DISINI
char roles[4][25] = {"cashier", "logistician", "manager", "admin"};

//DEFINISIKAN STRUCT DISINI
struct tanggal{
    int hari;
    int bulan;
    int tahun;
};

struct waktu{
    int jam;
    int menit;
    int detik;
};

struct users{
    char nickname[300];
    char username[300];
    char password[300];
    struct tanggal presensi;
    struct waktu login;
    struct waktu logout;
};

struct barang{
    struct tanggal tanggal_masuk;
    struct waktu waktu_masuk;
    char nama[300];
    char tipe[300];
    int harga;
    int stok;
    int kode;
}barang;

/*
struct dataBarang{
    char nama[50];
    char tipeBarang[50];
    int harga;
    int stok; 
    int kode;
}dataBarang;
*/

/*
void catat_presensi(char nickname[300]){
    time_t waktu_beli;
    waktu_beli = time(NULL);
    struct tm tm = *localtime(&waktu_beli);

    struct users check;
    struct users search;

    FILE *cek_presensi = fopen("presensi.dat", "ab+");
    while(fread(&check, sizeof(check), 1, cek_presensi) != 0){
        if(search.presensi.)
    }
}
*/

