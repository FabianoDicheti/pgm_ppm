#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct estrutura_pgm{
    int largura;
    int altura;
    int max;
    int **valPixel;
} estrutura_pgm;

//alocar memoria dinamica da matriz
int** alocaMmemoria(int linhas, int colunas){
    int **matriz;

    //alocando as linhas
    matriz = (int **) malloc(linhas * sizeof(int *));
    // alocando para as colunas de cada linha
    int i;
    for(i = 0; i<linhas; i++){
        matriz[i] = (int *) malloc(colunas * sizeof(int));

    }
    return matriz;

}


estrutura_pgm* lerPGM(const char *file_name, estrutura_pgm *dados)
{
    FILE *pgmFile;
    char versao[3];
    int i, j;
    int menor, maior;
    pgmFile = fopen(file_name, "rb");
    if (pgmFile == NULL) {
        perror("Arquivo vazio!");
        exit(EXIT_FAILURE);
    }
    fgets(versao, sizeof(versao), pgmFile);
    if (strcmp(versao, "P5")) {
        fprintf(stderr, "Versao do arquivo = P5, incompativel!\n");
        exit(EXIT_FAILURE);
    }
 
    dados->valPixel = alocaMmemoria(dados->largura, dados->altura);
    if (dados->max > 255) {
        for (i = 0; i < dados->largura; ++i) {
            for (j = 0; j < dados->altura; ++j) {
                maior = fgetc(pgmFile);
                menor = fgetc(pgmFile);
                dados->valPixel[i][j] = (maior << 8) + menor;
            }
        }
    }else{
        for (i = 0; i < dados->largura; ++i) {
            for (j = 0; j < dados->altura; ++j) {
                menor = fgetc(pgmFile);
                dados->valPixel[i][j] = menor;
            }
        }
    }
 
    fclose(pgmFile);
    return dados;
 
}
 







int main(){

    char arquivo[100];
    printf("/n Leitura de arquivos PGM e PPM /n Qual o nome do arquivo? ");
    scanf("%c", &arquivo);

    estrutura_pgm* lerPGM(const char *arquivo, estrutura_pgm *dados);

    int altura = lerPGM.altura ;
    int largura = lerPGM.largura;



    int li, co;
    for(li = 0; li < altura; li++){
        for(co = 0; co < largura; co++){
            estrutura_pgm dados.**valPixel[li][co] = (estrutura_pgm dados.**valPixel[li][co]) + 5;
        }
    }


    int i, j, temp = 0;
    
  
    char titulo[30];
    fflush(stdin);
    printf("\ndigite um nome para o trabalho:\n");
    scanf("%s", &titulo);

   
    // assinatura F D
    int image[3][7] = {

      { 156, 150, 145, 0, 150, 140, 000},
      { 155, 120, 000, 0, 155, 000, 145},
      { 160, 000, 000, 0, 160, 150, 000}
    };
  
    FILE* pgmimg;

    char extensao[] = ".pgm";
    strcat(titulo,extensao);
    pgmimg = fopen(titulo,"wb");
  
    // Writing Magic Number to the File
    fprintf(pgmimg, "P2\n"); 
  
    // Writing Width and Height
    fprintf(pgmimg, "%d %d\n", largura, altura); 
  
    // Writing the maximum gray value
    fprintf(pgmimg, "255\n"); 
    int count = 0;
    for (i = 0; i < altura; i++) {
        for (j = 0; j < largura; j++) {
            temp = dados.**valpixel[i][j];
  
            // Writing the gray values in the 2D array to the file
            fprintf(pgmimg, "%d ", temp);
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg);

}
