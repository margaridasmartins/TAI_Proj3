#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>

int gzip_compress(char *filename){
    char command[30]="gzip -k -9 ";
    printf("%s\n",filename);
    system(strcat(command, filename));
    char final_filename[50];
    strcpy(final_filename, filename);
    FILE *fp = fopen(strcat(final_filename, ".gz"), "rb");
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}

int lzma_compress(char *filename){
    char command[30]="lzma -k -9 ";
    printf("%s\n",filename);
    system(strcat(command, filename));
    char final_filename[50];
    strcpy(final_filename, filename);
    FILE *fp = fopen(strcat(final_filename, ".lzma"), "rb");
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}

int bzip2_compress(char *filename){
    char command[30]="bzip2 -k -9 ";
    printf("%s\n",filename);
    system(strcat(command, filename));
    char final_filename[50];
    strcpy(final_filename, filename);
    FILE *fp = fopen(strcat(final_filename, ".bz2"), "rb");
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}

int compress_solo(char *filename){
    gzip_compress(filename);
    lzma_compress(filename);
    bzip2_compress(filename);
    return 1;
}

int compress_cat(char *filename, char *file_db){
    return 0;
}


int normalized_compression_distance(char *filename, DIR *path_dir){
    char path[40]="../music_samples/";
    struct dirent *entry;

    if ((path_dir = opendir(path)) == NULL)
        perror("opendir() error");
    else {
        while ((entry = readdir(path_dir)) != NULL){
            int solo_db = compress_solo(strcat(path,entry->d_name));
            int cat_db = compress_cat(filename,strcat(path,entry->d_name));
        }
        closedir(path_dir);
    }
}
