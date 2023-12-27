#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//#include "file_struct.h"

//DEFINISIKAN FUNGSI DISINI
void tambahBarang();
void lihatBarang();
void updateHarga();
void update_stok();
void menu_logistician();
void login_logistician();
void keluar();

void tambahBarang(char nickname[], char username[]){
    system("cls");
    int jumlahTambah;
    printf("Input Jumlah barang yang ingin Ditambahkan: ");
    scanf("%d",&jumlahTambah);getchar();
    FILE*file;
    file=fopen("data_barang.dat","ab");
    for(int i=0;i<jumlahTambah;i++){
        printf("Data Barang Ke-%d\n",i+1);
        printf("Nama Barang  : ");gets(dataBarang.nama);
        printf("Tipe Barang  : ");gets(dataBarang.tipeBarang);
        printf("Kode barang  : "); scanf("%d", &dataBarang.kode); 
        printf("Harga Barang : Rp. ");scanf("%d",&dataBarang.harga);
        printf("Stok Barang  : \n");scanf("%d",&dataBarang.stok);getchar();
        fwrite(&dataBarang,sizeof(dataBarang),1,file);
    }
    fclose(file);
    printf("Data Barang Berhasil Ditambahkan");

    printf("Ke menu utama...\n");
    system("pause");
    menu_logistician(nickname, username);
}
void lihatBarang(char nickname[], char username[]){
    system("cls");
    FILE*file;
    file=fopen("data_barang.dat","rb");
    while(fread(&dataBarang,sizeof(dataBarang),1,file)==1){
        printf("Nama Barang : %s\n",dataBarang.nama);
        printf("Tipe Barang : %s\n",dataBarang.tipeBarang);
        printf("Harga Barang: Rp.%d\n",dataBarang.harga);
        printf("Stok Barang : %d\n\n",dataBarang.stok);
    }
    fclose(file);

    printf("Ke menu utama...\n");
    system("pause");
    menu_logistician(nickname, username);
}
void updateHarga(char nickname[], char username[]){
    system("cls");
    char namaUpdate[50];
    int ketemu=0;
    printf("Nama Barang yang ingin diUpdate: ");gets(namaUpdate);
    FILE*file;
    FILE*file2;
    file=fopen("data_barang.dat","rb");
    file2=fopen("data_barang2.dat","wb");
    while(fread(&dataBarang,sizeof(dataBarang),1,file)){
        if(strcmp(dataBarang.nama,namaUpdate)==0){
            printf("Update Harga: Rp.");scanf("%d",&dataBarang.harga);
            ketemu=1;
        }
        fwrite(&dataBarang,sizeof(dataBarang),1,file2);
    }
    if(ketemu==1){
        printf("harga %s Brehasil di Update\n",namaUpdate);
    }else{
        printf("Barang Tidak Ditemukan\n");
    }
    fclose(file);
    fclose(file2);
    remove("data_barang.dat");
    rename("data_barang2.dat","data_barang.dat");
    
    printf("Ke menu utama...");
    system("pause");
    menu_logistician(nickname, username);
}

void updateStok(char nickname[], char username[]){
    system("cls");
    char namaUpdate[50];
    int ketemu=0;
    printf("Nama Barang yang ingin diUpdate: ");gets(namaUpdate);
    FILE*file;
    FILE*file2;
    FILE *rekap_stok;

    file  = fopen("data_barang.dat","rb");
    file2 = fopen("data_barang2.dat","wb");
    rekap_stok = fopen("update_stok.dat", "ab");
    while(fread(&dataBarang,sizeof(dataBarang),1,file)){
        if(strcmp(dataBarang.nama,namaUpdate)==0){
            printf("Update Stok: ");scanf("%d",&dataBarang.stok);
            ketemu=1;
        }
        fwrite(&dataBarang,sizeof(dataBarang),1,file2);
        fwrite(&dataBarang, sizeof(dataBarang), 1, rekap_stok);
    }
    if(ketemu==1){
        printf("harga %s Berhasil di Update\n",namaUpdate);
    }else{
        printf("Barang Tidak Ditemukan\n");
    }
    fclose(file);
    fclose(file2);
    fclose(rekap_stok);

    remove("data_barang.dat");
    rename("data_barang2.dat","data_barang.dat");
    
    printf("Ke menu utama...");
    system("pause");
    menu_logistician(nickname, username);
}

void login_logistician(int limit){
    FILE *data_logistician;
    data_logistician = fopen("data_logistician.dat", "rb");

    struct users input;
    struct users check;
    struct users copy;

    int akun_ada;

    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);

    akun_ada = 0;
    while(fread(&check, sizeof(check), 1, data_logistician) == 1){
        if(strcmp(input.username, check.username) == 0 && strcmp(input.password, check.password) == 0){
            strcpy(copy.nickname, input.nickname);
            strcpy(copy.password, input.password);
            akun_ada = 1;
            break;
        }
    }
    fclose(data_logistician);

    if(akun_ada){
        menu_logistician(copy.nickname, copy.username);
    }else{
        if(limit > 1){
            printf("Username atau password salah! Kesempatan login tersisa %d lagi\n", limit-1);
            login_logistician(limit-1);
        }else{
                printf("Maaf, kesempatan login sudah habis\n");
                system("pause");
                pilih_role();
        }
    }

}

void menu_logistician(char nickname[], char username[]){
    system("cls");
    int n;
    printf("MENU LOGISTICIAN\n");
    printf("Selamat datang, %s! Berikut adalah menu yang tersedia untuk mulai bekerja\n");
    printf("\n 1.Lihat Barang\n");
    printf("2. Tambah Barang\n");
    printf("3. Update Harga Barang\n");
    printf("4. Update Stok Barang\n");
    printf("5. Keluar dari akun\n");
    printf("6. Keluar dari aplikasi");
    printf("Pilih Menu: ");scanf("%d",&n);getchar();
    switch(n){
        case 1:
        lihatBarang(nickname, username);
        break;
        case 2:
        tambahBarang(nickname, username);
        break;
        case 3:
        updateHarga(nickname, username);
        break;
        case 4:
        updateStok(nickname, username);
        break;
        case 5 :
        //login_logistician(limit);
        pilih_role();
        break;
        case 6 :
        exit(0);
        break;
        default :
        printf("Pilihan salah!");
        menu_logistician(nickname, username);
    }
}

void keluar(char nickname[], char username[]){
    printf("Apakah anda ingin keluar akun? (Y/N) : "); char ans; scanf("%c", &ans);
    if(ans == 'y' && ans == 'Y'){
        login_logistician(limit);
    }else{
        menu_logistician(nickname, username);
    }
}

/*
void catat_presensi(FILE *data_presensi, struct users user){
    fseek(data_presensi, 0, SEEK_SET);
}
*/