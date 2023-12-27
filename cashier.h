#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//DEKLARASIKAN FUNGSI DISINI
void menu_utama();
void login_cashier();
void header();
void layar_kasir();

struct barang store[100];

void menu_utama();
void login_cashier();
void header();

void login_cashier(int limit){
    struct users check;
    struct users input;

    int ada;

    FILE *data_cashier; 
    data_cashier = fopen("data_cashier.dat", "rb");

    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);

    ada = 0;
    while(fread(&check, sizeof(check), 1, data_cashier) == 1){
        if(strcmp(check.username, input.username) == 0 && strcmp(input.password, check.password) == 0){
            strcpy(input.nickname, check.nickname);
            ada = 1;
            break;
        }else{
            ada = 0;
        }
    }

    fclose(data_cashier);

    if(ada){
        layar_kasir(check.nickname);
    }else{
       if(limit > 0){
            printf("Password atau username salah!\nKesempatan login tersisa %d lagi\n", limit-1);
            login_cashier(limit-1);
       }else{
            printf("Maaf, kesempatan login habis\n");
            system("pause");
            pilih_role();
       }
    }
}

void header(char nickname[300]){
    printf("====================================================================================\n");
    printf("\t\tCOUNTER HARGA BARANG\t\t\n");
    printf("====================================================================================\n");
    printf("Selamat datang, %s\nSilahkan bekerja ya!\n", nickname);
}

void layar_kasir(char nickname[300]){
    header(nickname);
    struct barang check;
    struct barang input;
    struct barang kembalikan;

    int lanjut;
    int hitung = 0;

    FILE *data_barang;
    FILE *data_barang_temp;
    FILE *laporan_penjualan;

    data_barang = fopen("data_barang.dat", "rb");
    data_barang_temp = fopen("data_barang2.dat", "wb");

    lanjut = 0;

    do{
        printf("Masukkan kode barang                     : "); scanf("%d", &input.kode);
        printf("Masukkan banyak barang yang ingin dibeli : "); scanf("%d", &input.stok);
        while(fread(&check, sizeof(check), 1, data_barang) == 1){
            if(check.kode == input.kode){
                store[hitung] = check;
                hitung++;
            }
        }
        printf("1. Tambah Barang\n2. Kurangi barang\n3. Konfirmasi pembelian\nSilahkan pilih : ");
        int pilih; scanf("%d", &pilih);

        if(pilih == 1){
            lanjut = 1;
        }else if(pilih == 2){
            char kembalikan[300];
            printf("Masukkan nama barang yang ingin dikembalikan : "); gets(kembalikan);
            for(int a = 0; a <= hitung; a++){
                if(strcmp(store[a].nama, kembalikan) == 0){
                    strcpy(store[a].nama, "");
                    strcpy(store[a].tipe, "");
                    store[a].harga = 0;
                    store[a].stok = 0;
                    store[a].kode = 0;
                }
            }

            lanjut = 1;
        }else if(pilih == 3){
            lanjut = 0;
        }
    }while(lanjut == 1);

    //TULIS LAPORAN PENJUALAN DISINI
    laporan_penjualan = fopen("laporan_penjualan.dat", "ab");
    printf("===================================================================\n");
    printf("=====================  Ringkasan Pembelian  =======================\n");
    printf("===================================================================\n");

    printf("Nama barang\t| qtc |\tHarga\t\n");
    for(int a = 0; a <= hitung; a++){
        printf("%s\t\t| %d   |\t%d\t\n", store[a].nama, store[a].stok, store[a].harga);
        fwrite(&store, sizeof(store), 1, laporan_penjualan);
    }

    long long int total= 0;
    for(int a = 0; a < hitung; a++){
        total = total + store[a].harga * store[a].stok;
    }
    printf("Total : %lld\n\n", total);
    printf("Terima kasih atas kunjungan anda!\n");
    fclose(laporan_penjualan);

    system("pause");

    printf("Menu :\n1. Bersihkan layar dan lanjut\n2. Keluar dari akun\n3. Keluar dari aplikasi\nSilahkan pilih : ");
    int ans; scanf("%d", &ans);

    if(ans == 1) system("cls");
    else if(ans == 2) menu_utama();
    else if(ans == 3) exit(0);

}

void menu_utama(){
    printf("Anda akan masuk sebagai cashier\n");
    system("pause");
    login_cashier(limit);
}