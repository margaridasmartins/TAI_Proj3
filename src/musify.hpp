#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>
#include <algorithm>

using namespace std;

int gzip_compress(char *filename)
{
    char command[100];
    sprintf(command, "gzip -k -c -9 %s > ../compressed_files/%s.gz", filename, filename+3);
    system(command);
    char cmp_filename[50];
    sprintf(cmp_filename,"../compressed_files/%s.gz", filename+3);
    FILE *fp = fopen(cmp_filename, "rb");
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

int lzma_compress(char *filename)
{
    char command[100];
    sprintf(command, "lzma -k -c -9 %s > ../compressed_files/%s.lzma", filename, filename+3);
    system(command);
    char cmp_filename[50];
    sprintf(cmp_filename,"../compressed_files/%s.lzma", filename+3);
    FILE *fp = fopen(cmp_filename, "rb");
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

int bzip2_compress(char *filename)
{
    char command[100];
    sprintf(command, "bzip2 -k -c -9 %s > ../compressed_files/%s.bz2", filename, filename+3);
    system(command);
    char cmp_filename[50];
    sprintf(cmp_filename,"../compressed_files/%s.bz2", filename+3);
    FILE *fp = fopen(cmp_filename, "rb");
    fseek(fp, 0, SEEK_END);
    return ftell(fp);
}

void compress_solo(char *filename, int *solo_array)
{
    solo_array[0] = gzip_compress(filename);
    solo_array[1] = lzma_compress(filename);
    solo_array[2] = bzip2_compress(filename);
}

void compress_cat(char *filename, char *path, char *d_name, int *cat_array)
{
    char command[150];
    char cat_files[50]="../cat_files/";
    sprintf(command, "cat %s %s > ../cat_files/%s", filename, strcat(path, d_name), d_name);
    system(command);
    compress_solo(strcat(cat_files, d_name), cat_array); 
}

void normalized_compression_distance(char *filename, DIR *path_dir, string *best_choice)
{
    char path[40] = "../comp_samples/";
    struct dirent *entry;

    int solo_test[3];
    compress_solo(filename, solo_test);

    int tmp_solo[3];
    int tmp_cat[3];
    float tmp_ncd[3];
    float best_size[3]={1,1,1};

    char path_copy[50];

    if ((path_dir = opendir(path)) == NULL)
        perror("opendir() error");
    else
    {
        while ((entry = readdir(path_dir)) != NULL)
        {   
            if (entry->d_name[0] == '.') {
                continue;
            }
            memset(path_copy,0,sizeof(path_copy));
            strcat(path_copy,path);
            compress_solo(strcat(path_copy, entry->d_name), tmp_solo);
            memset(path_copy,0,sizeof(path_copy));
            strcat(path_copy,path);
            compress_cat(filename, path_copy, entry->d_name, tmp_cat);
            for (int i = 0; i < 3; i++)
            {
                tmp_ncd[i] = (float)(tmp_cat[i] - min(solo_test[i], tmp_solo[i])) /
                             (float)max(solo_test[i], tmp_solo[i]);
                if (tmp_ncd[i]< best_size[i]){
                    best_size[i] = tmp_ncd[i];
                    best_choice[i] = entry->d_name;
                }
            }
        }
        closedir(path_dir);
    }
}
