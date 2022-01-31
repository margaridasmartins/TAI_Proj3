#include "musify.hpp"

#include <stdlib.h>
#include <stdio.h>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <string.h>
#include <getopt.h>
#include <unistd.h>


using namespace std;

int main(int argc, char *argv[])
{

    string help_text =
      "Usage:\n"
      "  ./musify filename_t\n"
      "Required:\n"
      "  filename_t       The name of the file under analysis\n"
      "Options:\n"
      "  -c N       Compression level (1-9)\n"
      "  -h         Help message"
      "Example:\n"
      "  ./musify ??\n";

    if (argc < 1) {
        printf("ERR: Incorrect number of arguments\n\n%s", help_text.c_str());
        exit(1);
    }

    int option, comp_lvl;
    comp_lvl=5;
    while((option = getopt(argc, argv, "hc:")) != -1){ //get option from the getopt() method
        switch(option){
            case 'h':
                cout << help_text;
                break;
            case 'c':
                comp_lvl=stoi(optarg);
                if(comp_lvl>9||comp_lvl<1){
                    printf("Compression level out of range (1-9)");
                    exit(1);
                }
                break;
            case '?': //used for some unknown options
                printf("Unknown option: %c\n", optopt);
                cout << help_text;
                break;
        }
    }

    char models_dir[100]="../comp_samples";

    char command[100];
    sprintf(command,"python3 ../max_freqs.py -f ../%s",argv[argc-1]);
    system(command);

    char* sub_str=strtok(argv[argc-1],".");

    char file_test[100];
    sprintf(file_test, "../comp_test/%s.freqs", sub_str);

    DIR *dp;
    dp = opendir(models_dir);

    if (dp == NULL) {
        perror("opendir: Path does not exist or could not be read.");
        return -1;
    }

    string best_choice[3];
    string compressors[3] = {"gzip", "lzma", "bzip2"};
    double cmp_time[3];

    normalized_compression_distance(file_test, dp, best_choice,comp_lvl,cmp_time);

    for(int i=0; i<3; i++){
        printf("%s: %s : %f ms\n",best_choice[i].c_str(),compressors[i].c_str(),cmp_time[i]);
    }
    
    return 0;
}

// TODO: Opção de escolher apenas um conversor
// Remover os ficheiro depois de comprimir
// Tentar gravar a demo com musica live
// Relatorio
//   Overview
//   Program Options
//   Functions
//   Results
//      Amostrar plots de frequencia
//      As mesmas amostras de som com ou sem ruido
//      Testar para cada tipo de compressor diferente
//      Testar para musicas que não estejam lá e ver se dá genero semelhante (pimba com pimba, metal com metal etc)
//   Conclusion
