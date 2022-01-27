#include "shazam.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>


using namespace std;

int main(int argc, char *argv[])
{

    string help_text =
      "Usage:\n"
      "  ./shazam models_dir filename_t\n"
      "Required:\n"
      "  models_dir     The name of the directory with the language models"
      "  filename_t       The name of the file with the text under analysis\n"
      "Example:\n"
      "  ./shazam ?? 2 0.5\n";

    if (argc < 2) {
        printf("ERR: Incorrect number of arguments\n\n%s", help_text.c_str());
        exit(1);
    }

    
    char models_dir[100];
    sprintf(models_dir, "../%s", argv[1]);

    char file_test[100];
    sprintf(file_test, "../%s", argv[2]);

    DIR *dp;
    dp = opendir(models_dir);

    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
        return -1;
    }

    string best_choice[3];
    string compressors[3] = {"gzip", "lzma", "bzip2"};

    normalized_compression_distance(file_test, dp, best_choice);

    for(int i=0; i<3; i++){
        printf("%s: %s\n",best_choice[i].c_str(),compressors[i].c_str());
    }
    
    return 0;
}