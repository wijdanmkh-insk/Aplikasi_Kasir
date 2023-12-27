#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

FILE *file;

// DEFINISIKAN VARIABEL GLOBAL DISINI
int limit = 3;

// DEFINISIKAN STRUCT DISINI
struct users {
    char nickname[300];
    char username[300];
    char password[300];
};

struct Presensi {
    char username[50];
    char nama[50];
    char tanggal[20];
};

// PROTOTIPE FUNGSI
void login_manager(int limit, FILE *file);
int cekAbsensiHariIni(FILE *file, struct Presensi *presensi);
void catatPresensi(FILE *file, struct Presensi *presensi);
void lihatPresensi(FILE *file);
void menu_manager(FILE *file);

//login admin
void login_manager(int limit, FILE *file) {
    struct users input;
    struct Presensi presensi;
    printf("Masukkan username : ");
    fgets(presensi.username, sizeof(presensi.username), stdin);
    presensi.username[strcspn(presensi.username, "\n")] = '\0';

    printf("Masukkan password : ");
    fgets(input.password, sizeof(input.password), stdin);
    input.password[strcspn(input.password, "\n")] = '\0';

    if (strcmp(presensi.username, "manager") == 0 && strcmp(input.password, "manager") == 0) {

        time_t t = time(NULL);
        struct tm tm = *localtime(&t);

        snprintf(presensi.tanggal, sizeof(presensi.tanggal), "%02d/%02d/%04d %02d:%02d:%02d",tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,tm.tm_hour, tm.tm_min, tm.tm_sec);

        if (cekAbsensiHariIni(file, &presensi)) {
            printf("Admin sudah absen hari ini.\n");
            system("pause");
            menu_manager(file);
        } else {
            // Jika belum absen hari ini, catat presensi
            catatPresensi(file, &presensi);
            printf("Presensi berhasil dicatat.\n");
            system("pause");
            menu_manager(file);
        }

    } else {
        if (limit > 0) {
            printf("Username atau password salah! Kesempatan login tersisa %d lagi\n", limit - 1);
            login_manager(limit - 1, file);
        } else {
            printf("Kesempatan login habis!\n");
            exit(0); // or handle accordingly
        }
    }
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
    printf("\nDaftar Presensi:\n");

    while (fread(&presensi, sizeof(struct Presensi), 1, file) == 1) {
        printf("Nama: %s\n", presensi.username);
        printf("Tanggal: %s\n", presensi.tanggal);
        printf("----------------------------\n");
    }
}

void menu_manager(FILE *file) {
    system("cls");
    int pilih;
    printf("Menu tersedia manager :\n1. Rekap Presensi\n2. Rekap penjualan\n3. Keluar");

    do {
        printf("\nSilahkan pilih : ");
        scanf("%d", &pilih);
        getchar();

        switch (pilih) {
            case 1:
                lihatPresensi(file);
                break;
            // ... (other cases)
        }
    } while (pilih <= 0 || pilih > 3);
}

int main() {
    file = fopen("presensi.dat", "ab+");

    if (file == NULL) {
        fprintf(stderr, "Gagal membuka file presensi.dat\n");
        return 1;
    }

    login_manager(limit, file);

    fclose(file);

    return 0;
}
