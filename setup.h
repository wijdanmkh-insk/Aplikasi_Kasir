#include <stdio.h>
#include <sys/types.h>
#include <stdbool.h>
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
    char confirm[300];

    bool match;
    bool not_blank;

    printf("================================ SETUP AKUN ================================\n");
    printf("Selamat datang di menu setup aplikasi kasir\n");
    printf("Tahapan yang akan dilewati : Setup akun admin\n");
    printf("\nWARNING :\nPASTIKAN ANDA MENCATAT USERNAME DAN PASSWORD KARENA SETELAH ANDA TERDAFTAR,\nDATA YANG SUDAH TERSIMPAN TIDAK DAPAT DIUBAH LAGI\n");

    FILE *data_admin;
    data_admin = fopen("data_admin.dat", "wb");

    match = false;
    not_blank = false;
    printf("Masukkan nickname            : "); gets(input.nickname);
    printf("Masukkan username            : "); gets(input.username);

    do{ 
        printf("Masukkan password            : "); gets(input.password);
        printf("Masukkan konfirmasi password : "); gets(confirm);
        if(strcmp(input.password, confirm)!= 0){
            match = true;
            system("cls");
            printf("Password dan konfirmasinya tidak cocok!\n");
            printf("Masukkan nickname            : %s\n", input.nickname); 
            printf("Masukkan username            : %s\n", input.username); 
        }else{
            if(fwrite(&input, sizeof(input), 1, data_admin) != 0){
                match = false;
                printf("Setup aplikasi berhasil! Tekan apapun untuk melanjutkan...");
            }
        }
    }while(match);
    
    getchar();
    fclose(data_admin);
}

void pilih_role(){
    system("cls");
    printf("================================ MENU LOGIN ================================\n");
    printf("Selamat datang! Anda akan masuk sebagai :\n");
    printf("1. Cashier\n2. Logistician\n3. Manager\n4. Admin\n5. KELUAR\nSilahkan pilih : "); int pilih; scanf("%d", &pilih); getchar();

    switch(pilih){
        case 1 :
        login_cashier(limit);
        break;
        case 2 :
        login_logistician(limit);
        break;
        case 3 : 
        login_manager(limit);
        break;
        case 4 :
        login_admin(limit);
        break;
        case 5 :
        exit(0);
        default : 
        printf("Pilihan salah!");
        pilih_role();
        break;
    }
}
