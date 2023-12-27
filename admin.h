#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file_struct.h"
//#include "setup.h"

//DEFINISIKAN FUNGSI ADMIN DISINI
void login_admin();
void menu_admin();
void ganti_password();
void hapus_akun();
void registrasi_akun();

//DEFINISIKAN FUNGSI SPESIFIK DARI ADMIN DISINI
void login_admin(int limit){

    struct users input;
    struct users check;
    
    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);

    FILE *data_admin;
    data_admin = fopen("data_admin.dat", "rb");

    while(fread(&check, sizeof(check), 1, data_admin) == 1){
        if(strcmp(input.username, check.username) == 0 && strcmp(input.password, check.password) == 0){
        menu_admin();
        }else{
            if(limit > 0){
                printf("Username atau password salah! Kesempatan login tersisa %d lagi\n", limit-1);
                login_admin(limit-1);
            }else{
                printf("Kesempatan login habis!\n");
                system("pause");
                pilih_role();
            }
        }
    }
}

void menu_admin(){
    system("cls");
    int pilih; 
    printf("Menu tersedia admin :\n1. Ganti password user\n2. Hapus akun user\n3. Registrasi akun\n4. Keluar dari akun\n5. Keluar aplikasi");

    do{
        printf("\nSilahkan pilih : ");
        scanf("%d", &pilih); getchar();

        switch(pilih){
            case 1 :
            ganti_password();
            break;
            case 2 :
            hapus_akun();
            break;
            case 3 : 
            registrasi_akun();
            break;
            case 4 :
            pilih_role();
            break;
            case 5 :
            exit(0);
            default : 
            printf("Pilihan salah!");
        }
    }while(pilih <= 0 || pilih > 3);
}

void ganti_password(){
    system("cls");

    char confirm[300];
    char file_temp_r[300];
    char file_temp_w[300];

    int role;
    int data_ada;
    int konfirmasi;

    FILE *data_user;
    FILE *data_user_temp;
    struct users check;
    struct users input;

    printf("Pilihan role yang tersedia :\n1. Cashier\n2. Logistician\n3. Manager\n");

    do{
        printf("Pilih role yang akan diganti passwordnya : ");
        scanf("%d", &role); getchar();

        if(role < 0 || role > 3){
            printf("Pilihan salah!");
        }else{
            strcpy(file_temp_r, nama_file[role-1]);
            strcpy(file_temp_w, nama_file_temp[role-1]);

            data_user      = fopen(file_temp_r, "rb");
            data_user_temp = fopen(file_temp_w, "wb");

            printf("Ganti password role %s\n", roles[role-1]);
            printf("Masukkan username : "); gets(input.username);

            while(fread(&check, sizeof(check), 1, data_user) == 1){
                if(strcmp(input.username, check.username) == 0){
                    strcpy(input.nickname, check.nickname);
                    strcpy(input.username, check.username);
                    data_ada = 1;
                    break;
                }
            }

            konfirmasi = 0;
            if(data_ada){
                do{
                    printf("Masukkan password baru       : "); gets(input.password);
                    printf("Masukkan konfirmasi password : "); gets(confirm);

                    if(strcmp(input.password, confirm)!= 0){
                        konfirmasi = 1;
                        printf("Password dan konfirmasinya tidak cocok!");
                    }
                }while(konfirmasi == 1);

                while(fread(&check, sizeof(check), 1, data_user) == 1){
                    if(strcmp(input.username, check.username) != 0){
                        fwrite(&check, sizeof(check), 1, data_user_temp);
                    }
                }

                //MENYALIN DATA YANG DIGANTI PASSWORDNYA KE DATABASE
                fwrite(&input, sizeof(input), 1, data_user_temp);
                
                fclose(data_user);
                fclose(data_user_temp);

                remove(file_temp_r);
                rename(file_temp_w, file_temp_r);

                printf("Password berhasil diganti\n");
            }else{
                printf("Akun yang dicar tidak ada!\n");
            }
        }

    }while(role < 0 || role > 3);

    printf("Sistem akan kembali ke menu utama...\n");
    system("pause");
    menu_admin();
}

void hapus_akun(){
    system("cls");

    char confirm[300];
    char file_temp_r[300];
    char file_temp_w[300];

    int role;
    int data_ada;
    int konfirmasi;

    FILE *data_user;
    FILE *data_user_temp;
    struct users check;
    struct users input;

    printf("Pilihan role yang tersedia :\n1. Cashier\n2. Logistician\n3. Manager\n");

    do{
        printf("Pilih role yang akan diganti passwordnya : ");
        scanf("%d", &role); getchar();

        if(role < 0 || role > 3){
            printf("Pilihan salah!");
        }else{
            strcpy(file_temp_r, nama_file[role-1]);
            strcpy(file_temp_w, nama_file_temp[role-1]);

            data_user      = fopen(file_temp_r, "rb");
            data_user_temp = fopen(file_temp_w, "wb");

            printf("Ganti password role %s\n", roles[role-1]);
            printf("Masukkan username : "); gets(input.username);

            while(fread(&check, sizeof(check), 1, data_user) == 1){
                if(strcmp(input.username, check.username) == 0){
                    data_ada = 1;
                    break;
                }
            }

            konfirmasi = 0;
            if(data_ada){
                do{
                    printf("Masukkan password baru       : "); gets(input.password);
                    printf("Masukkan konfirmasi password : "); gets(confirm);

                    if(strcmp(input.password, confirm)!= 0){
                        konfirmasi = 1;
                        printf("Password dan konfirmasinya tidak cocok!");
                    }
                }while(konfirmasi == 1);

                while(fread(&check, sizeof(check), 1, data_user) == 1){
                    if(strcmp(input.username, check.username) != 0){
                        fwrite(&check, sizeof(check), 1, data_user_temp);
                    }
                }

                //MENYALIN DATA YANG DIGANTI PASSWORDNYA KE DATABASE
                fwrite(&input, sizeof(input), 1, data_user_temp);
                
                fclose(data_user);
                fclose(data_user_temp);

                remove(file_temp_r);
                rename(file_temp_w, file_temp_r);

                printf("Akun berhasil dihapus!\n");
            }else{
                printf("Akun yang dicari tidak ada!\n");
            }
        }

    }while(role < 0 || role > 3);

    printf("Sistem akan kembali ke menu utama...\n");
    system("pause");
    menu_admin();
}

void registrasi_akun(){
    system("cls");

    char confirm[300];
    char file_temp_a[300];

    int role;
    int konfirmasi;

    FILE *data_user;
    FILE *data_user_temp;
    struct users check;
    struct users input;

    printf("Pilihan role yang tersedia :\n1. Cashier\n2. Logistician\n3. Manager\n");

    do{
        printf("Pilih role yang akan didaftarkan : ");
        scanf("%d", &role); getchar();

        if(role < 0 || role > 3){
            printf("Pilihan salah!");
        }else{
            strcpy(file_temp_a, nama_file[role-1]);

            data_user      = fopen(file_temp_a, "ab");

                printf("Menambahkan akun untuk role %s\n", roles[role-1]);
                printf("Masukkan nickname            : "); gets(input.nickname);
                printf("Masukkan username            : "); gets(input.username);

            konfirmasi = 0;
            do{
                printf("Masukkan password baru       : "); gets(input.password);
                printf("Masukkan konfirmasi password : "); gets(confirm);

                if(strcmp(input.password, confirm)!= 0){
                    konfirmasi = 1;
                    printf("Password dan konfirmasinya tidak cocok!");
                }else{
                    konfirmasi = 0;
                }
            }while(konfirmasi == 1);

            fwrite(&check, sizeof(check), 1, data_user);


            //MENYALIN DATA YANG DIGANTI PASSWORDNYA KE DATABASE
            
            fclose(data_user);

            printf("Akun berhasil ditambahkan!\n");
        }

    }while(role < 0 || role > 3);

    printf("Sistem akan kembali ke menu utama...\n");
    system("pause");
    menu_admin();
}