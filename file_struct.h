#include <stdio.h>
//#include "setup.h"

//DEFINISIKAN VARIABEL GLOBAL DISINI
int limit  = 3;

//DEFINISIKAN VARIABEL FILE DISINI
char nama_file[3][50] = {"data_cashier.dat", "data_logistician.dat", "data_manager.dat"};
char nama_file_temp[3][50] = {"data_cashier1.dat", "data_logistician1.dat", "data_manager1.dat"};

//DEFINISIKAN ROLE PENGGUNA APLIKASI DISINI
char roles[3][25] = {"cashier", "logistician", "manager"};

//DEFINISIKAN STRUCT DISINI
struct users{
    char nickname[300];
    char username[300];
    char password[300];
};

struct barang{
    char nama[300];
    char tipe[300];
    int harga;
    int stok;
    int kode;
};

struct dataBarang{
    char nama[50];
    char tipeBarang[50];
    int harga;
    int stok; 
    int kode;
}dataBarang;
