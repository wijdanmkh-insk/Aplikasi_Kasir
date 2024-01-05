#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//DEKLARASIKAN FUNGSI DISINI
void login_cashier();
void header();
void layar_kasir();

struct barang store[100];

void login_cashier(int limit){
    struct users check;
    struct users input;

    int ada;

    FILE *data_cashier; 
    data_cashier = fopen("data_cashier.dat", "rb");

    if(data_cashier != NULL){
        printf("Masukkan username : "); gets(input.username);
        printf("Masukkan password : "); gets(input.password);

        ada = 0;
        while(fread(&check, sizeof(check), 1, data_cashier) != 0){
            if(strcmp(check.username, input.username) == 0 && strcmp(input.password, check.password) == 0){
                strcpy(input.nickname, check.nickname);
                ada = 1;
                break;
            }else{
                ada = 0;
            }
        }

        fclose(data_cashier);
    }else{
        printf("Data tidak ada, coba untuk meregistrasikan akun kasir terlebih dulu\nTekan apapun untuk melanjutkan...\n");
        getchar();
        pilih_role();
    }

    if(ada){
        layar_kasir(check.nickname);
    }else{
       if(limit > 1){
            system("cls");
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
    printf("\t\t\tCOUNTER HARGA BARANG\t\t\n");
    printf("====================================================================================\n");
    printf("Selamat datang, %s\nSilahkan bekerja ya!\n\n", nickname);
}

void layar_kasir(char nickname[300]){
    time_t waktu_beli;
    waktu_beli = time(NULL);
    struct tm tm = *localtime(&waktu_beli);

    system("cls");
    header(nickname);
    struct barang check;
    struct barang input;
    struct barang kembalikan;

    int lanjut;
    int hitung = 0;

    FILE *data_barang;
    FILE *data_barang_temp;
    FILE *laporan_penjualan;

    lanjut = 0;
    int tidak_ada;
    data_barang = fopen("data_barang.dat", "rb");
    if(data_barang != NULL){ 
        do{
            //rewind(data_barang);
            //fseek(data_barang, 0, SEEK_SET);
            do{
                tidak_ada = 1;
                printf("Masukkan kode barang                     : "); scanf("%d", &input.kode); getchar();
                fseek(data_barang, 0, SEEK_SET);
                //printf("%d ", check.kode);
                while(fread(&check, sizeof(check), 1, data_barang) == 1){
                    if(check.kode == input.kode){
                        tidak_ada = 0;
                        break;
                    }else{
                        tidak_ada = 1;
                    }
                }if(tidak_ada){
                    printf("Data tidak ada!\n");
                }
            }while(tidak_ada);

            if(!tidak_ada){
                printf("Masukkan banyak barang yang ingin dibeli : "); scanf("%d", &input.stok); getchar();
                
                fseek(data_barang, 0, SEEK_SET);
                //data_barang = fopen("data_barang.dat", "rb");
                while(fread(&check, sizeof(check),1 , data_barang)==1){
                    if(input.kode == check.kode){
                        store[hitung] = check;
                        store[hitung].stok = input.stok;
                        hitung++;

                        //printf("%s\n%d\n", store[hitung].nama, store[hitung].stok);
                    }
                }
                //fclose(data_barang);
            
                int cek;
                cek = 0;
                    do{
                        printf("1. Tambah Barang\n2. Kurangi barang\n3. Konfirmasi pembelian\nSilahkan pilih : ");
                        int pilih; scanf("%d", &pilih); getchar();
                    
                        if(pilih == 1){
                            cek = 0;
                            lanjut = 1;
                        }else if(pilih == 2){
                            int kode;
                            printf("Masukkan kode barang yang ingin dikembalikan : "); scanf("%d", &kode); getchar();
                            for(int a = 0; a < hitung; a++){
                                if(store[a].kode == kode){
                                    strcpy(store[a].nama, "");
                                    strcpy(store[a].tipe, "");
                                    store[a].harga = 0;
                                    store[a].stok = 0;
                                    store[a].kode = 0;
                                }
                            }
                            cek = 1;
                            //fclose(data_barang);
                        }else if(pilih == 3){
                            cek = 0;
                            lanjut = 0;
                        }
                    }while(cek);
            }
        }while(lanjut == 1);
        fclose(data_barang);

        int simpan_data = 0;
        //UBAH STOK SETELAH DIBELI DISINI
        data_barang = fopen("data_barang.dat", "rb");
        data_barang_temp = fopen("data_barang2.dat", "wb");
            while(fread(&check, sizeof(check),1 , data_barang)==1){
                for(int a = 0; a < hitung; a++){
                    if(check.kode == store[a].kode){
                        check.stok = check.stok - store[a].stok;
                    }
                }
                if(fwrite(&check, sizeof(check),1, data_barang_temp) == 1){
                    simpan_data = 1;
                }
            }

        if(simpan_data){
            printf("Data berhasil disimpan!\n");
        }else{
            printf("ERROR\n");
        }

        fclose(data_barang);
        fclose(data_barang_temp);

        remove("data_barang.dat");
        rename("data_barang2.dat", "data_barang.dat");

        //TULIS LAPORAN PENJUALAN DISINI
        system("cls");
        laporan_penjualan = fopen("laporan_penjualan.dat", "ab");
        printf("===================================================================\n");
        printf("=====================  Ringkasan Pembelian  =======================\n");
        printf("===================================================================\n");

        printf("Hari ini tanggal : %d - %d - %d\n", tm.tm_mday, tm.tm_mon+1,  tm.tm_year+1900);

        printf("Nama barang\t\t|\tqtc\t|\tHarga\t\n");
        for(int a = 0; a < hitung; a++){
            if(store[a].stok != 0){
                store[a].tanggal_masuk.hari = tm.tm_mday;
                store[a].tanggal_masuk.bulan = tm.tm_mon + 1;
                store[a].tanggal_masuk.tahun = tm.tm_year + 1900;
                store[a].waktu_masuk.jam = tm.tm_hour;
                store[a].waktu_masuk.menit = tm.tm_min;
                store[a].waktu_masuk.detik = tm.tm_sec;

                printf("%s\t\t\t|\t%d\t|\t\t%d\t\n", store[a].nama, store[a].stok, store[a].harga*store[a].stok);
                fwrite(&store[a], sizeof(store[a]), 1, laporan_penjualan);
            }
        }

        long long int total= 0;
        for(int a = 0; a < hitung; a++){
            total = total + store[a].harga * store[a].stok;
        }

        printf("-------------------------------------------------------------------\n");
        printf("Total : Rp%lld\n\n", total);
        printf("Terima kasih atas kunjungan anda!\nTekan apapun untuk melanjutkan\n");
        fclose(laporan_penjualan);

        getchar();
        system("cls");
        printf("Menu :\n1. Bersihkan layar dan lanjut\n2. Keluar dari akun\n3. Keluar dari aplikasi\nSilahkan pilih : ");
        int ans; scanf("%d", &ans);

        if(ans == 1){
            system("cls");
            layar_kasir(nickname);
        }
        else if(ans == 2){
            pilih_role();
        }
        else if(ans == 3){
            exit(0);
        }
    }else{
        printf("Anda belum menambahkan barang apapun disini. Silahkan tambahkan dulu di menu logistik\nAplikasi akan keluar dari akun anda\nTekan apapun untuk melanjutkan...");
        getchar();
    }
    pilih_role();
}

void menu_utama(){
    printf("Anda akan masuk sebagai cashier\n");
    system("pause");
    login_cashier(limit);
}
