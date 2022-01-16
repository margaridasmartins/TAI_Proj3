#include <stdlib.h>
#include <stdio.h>

int compress_solo(FILE *fptr_db){

}

int compress_cat(FILE *fptr_sample, FILE *fptr_db){

}

int normalized_compression_distance(FILE *fptr_sample, FILE *fptr_db, int solo_test){
    //iterate through each sample
        int solo_db = compress_solo(fptr_db);
        int cat_db = compress_cat(fptr_sample,fptr_db);
        //calculate distance according to formula
}