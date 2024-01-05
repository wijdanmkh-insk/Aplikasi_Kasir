#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "file_struct.h"
//#include "setup.h"

//DEFINISIKAN FUNGSI ADMIN DISINI
void login_admin();
void menu_admin();
void ganti_username();
void ganti_password();
void hapus_akun();
void registrasi_akun();

//DEFINISIKAN FUNGSI SPESIFIK DARI ADMIN DISINI
void login_admin(int limit){
    system("cls");
    struct users input;
    struct users check;

    printf("================================ LOGIN ADMIN ================================\n");
    printf("Masukkan username : "); gets(input.username);
    printf("Masukkan password : "); gets(input.password);

    FILE *data_admin;
    data_admin = fopen("data_admin.dat", "rb");

    while(fread(&check, sizeof(check), 1, data_admin) == 1){
        if(strcmp(input.username, check.username) == 0 && strcmp(input.password, check.password) == 0){
        fclose(data_admin);
        menu_admin();
        }else{
            if(limit > 0){
                system("cls");
                printf("Username atau password salah! Kesempatan login tersisa %d lagi\n", limit-1);
                login_admin(limit-1);
            }else{
                printf("Kesempatan login habis!\nTekan apapun untuk kembali ke menu utama...\n");
                fclose(data_admin);
                getchar();
                pilih_role();
            }
        }
    }
}

void menu_admin(){
    bool admin = true;
    system("cls");
    int pilih; 
    printf("================================ MENU ADMIN ================================\n");
    printf("Menu tersedia admin :\n1. Ganti password user\n2. Hapus akun user\n3. Registrasi akun\n4. Ganti username user\n5. Keluar akun\n6. Keluar aplikasi\n");

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
            ganti_username();
            case 5 :
            pilih_role();
            case 6 :
            exit(0);
            default : 
            printf("Pilihan salah!");
        }
    }while(pilih <= 0 || pilih > 5);
}

void ganti_password(){
    system("cls");

    printf("================================ GANTI PASSWORD ================================\n");
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

    printf("Pilihan role yang tersedia :\n1. Cashier\n2. Logistician\n3. Manager\n4. Admin\n");

        printf("Pilih role yang akan diganti passwordnya : ");
        scanf("%d", &role); getchar();

        if(role < 0 || role > 4){
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
            if(data_ada == 1){
                do{
                    printf("Masukkan password baru       : "); gets(input.password);
                    printf("Masukkan konfirmasi password : "); gets(confirm);

                    if(strcmp(input.password, confirm)!= 0){
                        konfirmasi = 1;
                        printf("Password dan konfirmasinya tidak cocok!");
                    }
                }while(konfirmasi == 1);

                while (fread(&check, sizeof(check), 1, data_user) == 1) {
                    if (strcmp(input.username, check.username) != 0) {
                        fwrite(&check, sizeof(check), 1, data_user_temp);
                    } else {
                        // Modify only the password, other data remains unchanged
                        strcpy(check.password, input.password);
                        fwrite(&check, sizeof(check), 1, data_user_temp);
                    }
                }


                //MENYALIN DATA YANG DIGANTI PASSWORDNYA KE DATABASE
                fwrite(&input, sizeof(input), 1, data_user_temp);
                
                fclose(data_user);
                fclose(data_user_temp);

                remove(file_temp_r);
                rename(file_temp_w, file_temp_r);

                printf("Password untuk role %s berhasil diganti\n", roles[role-1]);
            }else{
                printf("Akun yang dicari tidak ada!\n");
            }

            fclose(data_user);
            fclose(data_user_temp);
        }


    printf("Tekan apapun untuk kembali ke menu utama...\n");
    getchar();
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

    printf("================================ HAPUS AKUN ================================\n");
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

                while (fread(&check, sizeof(check), 1, data_user) == 1) {
                    if (strcmp(input.username, check.username) != 0) {
                        fwrite(&check, sizeof(check), 1, data_user_temp);
                    }
                }
 
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

    printf("Tekan apapun untuk kembali ke menu utama...\n");
    getchar();
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

    printf("================================ REGISTRASI AKUN ================================\n");
    printf("Pilihan role yang tersedia :\n1. Cashier\n2. Logistician\n3. Manager\n");

    do{
        printf("Pilih role yang akan didaftarkan : ");
        scanf("%d", &role); getchar();

        if(role < 0 || role > 3){
            printf("Pilihan salah!");
        }else{
            strcpy(file_temp_a, nama_file[role-1]);

            data_user      = fopen(file_temp_a, "ab");
            fseek(data_user, 0, SEEK_END);

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

            fwrite(&input, sizeof(input), 1, data_user);
            //MENYALIN DATA YANG DIGANTI PASSWORDNYA KE DATABASE
            
            fclose(data_user);

            printf("Akun berhasil ditambahkan!\n");
        }

    }while(role < 0 || role > 3);

    printf("Tekan apapun untuk kembali ke menu utama...\n");
    getchar();
    menu_admin();
}

void ganti_username(){
    system("cls");

    printf("================================ GANTI USERNAME ================================\n");

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

    printf("Pilihan role yang tersedia :\n1. Cashier\n2. Logistician\n3. Manager\n4. Admin\n");

    do {
        printf("Pilih role yang akan diganti username-nya : ");
        scanf("%d", &role);
        getchar();  // consume the newline character left in the buffer

        if(role < 1 || role > 4){
            printf("Pilihan salah!\n");
        }
    } while(role < 1 || role > 4);

    strcpy(file_temp_r, nama_file[role-1]);
    strcpy(file_temp_w, nama_file_temp[role-1]);

    data_user = fopen(file_temp_r, "rb");
    data_user_temp = fopen(file_temp_w, "wb");

    printf("Ganti username role %s\n", roles[role-1]);
    //if(role != 4){
        printf("Masukkan username yang ingin diubah: ");
        gets(input.username);
    //}

    data_ada = 0;

    while(fread(&check, sizeof(check), 1, data_user) == 1){
        if(strcmp(input.username, check.username) == 0){
            strcpy(input.nickname, check.nickname);
            data_ada = 1;
            break;
        }
    }

    if(data_ada == 1){
        printf("Masukkan username baru: ");
        gets(input.username);

        konfirmasi = 0;

        while (fread(&check, sizeof(check), 1, data_user) == 1) {
            if (strcmp(input.username, check.username) != 0) {
                fwrite(&check, sizeof(check), 1, data_user_temp);
            } else {
                strcpy(check.password, input.password);
                fwrite(&check, sizeof(check), 1, data_user_temp);
            }
        }

        // MENYALIN DATA YANG DIGANTI USERNAME-NYA KE DATABASE
        fwrite(&input, sizeof(input), 1, data_user_temp);

        fclose(data_user);
        fclose(data_user_temp);

        remove(file_temp_r);
        rename(file_temp_w, file_temp_r);

        printf("Username untuk role %s berhasil diganti\n", roles[role-1]);
    } else {
        printf("Akun yang dicari tidak ada!\n");
        fclose(data_user);
        fclose(data_user_temp);
    }

    printf("Tekan apapun untuk kembali ke menu utama...\n");
    getchar(); 
    menu_admin();
}
