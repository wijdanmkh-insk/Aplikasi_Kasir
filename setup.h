#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
//#include "admin.h"
//#include "cashier.h"
//#include "logisticians.h"

void setup(){
    system("cls");
    struct users input;
    struct users check;

    printf("Selamat datang di menu setup aplikasi kasir\n");
    printf("Tahapan yang akan dilewati :\n1. Membuat direktori dan file pengguna\n2. Setup akun admin\n");

    FILE *data_admin;
    data_admin = fopen("data_admin.dat", "wb");

    printf("Setup akun admin\n");
    printf("Masukkan nickname : "); gets(input.nickname);
    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);
    fwrite(&input, sizeof(input), 1, data_admin);

    printf("Setup aplikasi berhasil! Silahkan login");
    
    fclose(data_admin);
}

void pilih_role(){
    system("cls");
    printf("Selamat datang! Anda akan masuk sebagai :\n");
    printf("1. Cashier\n2. Logistician\n3. Manager\n4. Admin\nSilahkan pilih : "); int pilih; scanf("%d", &pilih); getchar();

    switch(pilih){
        case 1 :
        login_cashier(limit);
        break;
        case 2 :
        login_logistician(limit);
        break;
        case 3 : 
        login_admin(limit);
        break;
        case 4 :
        login_admin(limit);
        break;
        default : 
        printf("Pilihan salah!");
        pilih_role();
        break;
    }
}