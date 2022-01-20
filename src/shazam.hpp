#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <dirent.h>
#include <string.h>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filter/bzip2.hpp>

/*
int compress_solo(FILE *fptr_db){
    
}

int compress_cat(FILE *fptr_sample, FILE *fptr_db){

}


int normalized_compression_distance(FILE *fptr_sample, DIR *path_dir, int solo_test){
    char path[40]="../music_samples/";
    struct dirent *entry;

    if ((path_dir = opendir(path)) == NULL)
        perror("opendir() error");
    else {
        while ((entry = readdir(path_dir)) != NULL)
            int solo_db = compress_solo(strcat(path,entry->d_name));
            int cat_db = compress_cat(fptr_sample,strcat(path,entry->d_name));
        closedir(path_dir);
    }
}
*/