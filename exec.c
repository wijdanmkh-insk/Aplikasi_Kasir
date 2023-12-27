#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "admin.h"
#include "cashier.h"
#include "logisticians.h"
#include "setup.h"
//#include "file_struct.h"

int main(){
    FILE *check;

    check = fopen("data_admin.dat", "rb");

    if(check == NULL){
        fclose(check);
        setup();
    }
    pilih_role();
}

