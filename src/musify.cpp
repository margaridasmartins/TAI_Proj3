#include "musify.hpp"

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
      "  ./musify filename_t\n"
      "Required:\n"
      "  filename_t       The name of the file under analysis\n"
      "Example:\n"
      "  ./musify ??\n";

    if (argc < 1) {
        printf("ERR: Incorrect number of arguments\n\n%s", help_text.c_str());
        exit(1);
    }

    char models_dir[100]="../comp_samples";

    char command[100];
    sprintf(command,"python3 ../max_freqs.py -f ../%s",argv[1]);
    system(command);

    char* sub_str=strtok(argv[1],".");

    char file_test[100];
    sprintf(file_test, "../%s.freqs", sub_str);

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
