#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ALTURA 1025
#define MAX_LARGURA 1025
#define TAM_MAX_LINHA 25
#define MIN( x, y ) ( ( x ) < ( y ) ? ( x ) : ( y ) ) 
//int x, y;if( x < y ){MIN = x}else{ MIN = y};

int matrizPgm[1025][MAX_LARGURA];
int matrizPPM[1025][MAX_LARGURA];

FILE* carregaDadosPgm(int* altura, int* largura, int* maxK, char* nomePgm);

void salvaPgm(char* nomeArClaro, int vetorPgm[][MAX_LARGURA], int altura, int largura, int maxK);

void montaMatrizPgm(int vetorPgm[][MAX_LARGURA], int* altura, int* largura, int* maxK, char* nomePgmEntrada);

void clareia(int matrizPgm[1025][1025]);

void negativo(int matrizPgm[1025][1025]);



FILE* carregaDadosPPM(int* altura2, int* largura2, int* maxK2, char* nomePPMEntrada);

void montaMatrizPPM(int vetorPPM[][MAX_LARGURA], int* altura2, int* largura2, int* maxK2, char* nomePPMEntrada);

void salvaPPM(char* nomeNovoPPM, int vetorPPM[][MAX_LARGURA], int altura2, int largura2, int maxK2);





// ############################################
// #########  M  A  I  N   ####################
// ############################################

int main( void ){
   

    int altura  = 0;
    int largura = 0;
    int maxK = 0;
    int altura2 = 0;
    int largura2 = 0;
    int maxK2 = 0;

    char escolha;
    char refNome;
    
    char* nomePgmEntrada = &refNome;
 
    char* nomeArClaro = "ImagemClareada.pgm";
    char* nomeArNegativo = "ImagemNegativo.pgm";

    char* momePPMentrada = &refNome;
    char* nomeNovoPPM = "novoPGM.pgm";



    while(!(escolha == 'a' || escolha == 'b' || escolha == 'c' || escolha == 'd')){

        

        printf("\n Escolha uma opcao: \n");
        printf("(a) Clarear uma imagem PGM\n");
        printf("(b) Aplicar um filtro negativo ao PGM\n");
        printf("(c) Clarear e filtrar uma PGM simultaneamente\n");
        printf("(d) Converter ima imagem PPM em PGM\n");

        scanf("%c", &escolha);
       
        switch(escolha){
            case 'a':
                printf(" \nClarear Imagem PGM");
                printf("\nQual o nome do arquivo de origem?");
                scanf("%s", &refNome);

                montaMatrizPgm(matrizPgm, &altura, &largura, &maxK, nomePgmEntrada);
                clareia(matrizPgm);
                salvaPgm (nomeArClaro, matrizPgm, altura, largura, maxK);

                system("clear");
                printf("\n\nimagem Clareada, arquivo salvo com o nome: \n    ==> ImagemClareada.pgm\n\n");
                
                escolha = 'a';
                break;

            case 'b':
                printf(" \nFiltro negativo ao PGM");
                printf("\nQual o nome do arquivo de origem?");
                scanf("%s", &refNome);

                montaMatrizPgm(matrizPgm, &altura, &largura, &maxK, nomePgmEntrada);
                negativo(matrizPgm);
                salvaPgm (nomeArNegativo, matrizPgm, altura, largura, maxK);

                system("clear");
                printf("\n\nArquivo salvo com sucesso com o nome: \n    ==> ImagemNegativo.pgm\n\n");

                escolha = 'b';
                break;

            case 'c':
                printf(" \nClarear e filtrar uma PGM");
                printf("\nQual o nome do arquivo de origem?");
                scanf("%s", &refNome);

                montaMatrizPgm(matrizPgm, &altura, &largura, &maxK, nomePgmEntrada);
                clareia(matrizPgm);
                salvaPgm (nomeArClaro, matrizPgm, altura, largura, maxK);
                negativo(matrizPgm);
                salvaPgm (nomeArNegativo, matrizPgm, altura, largura, maxK);

                system("clear");
                printf("\n\nArquivos criados com os nomes: \n    ==> ImagemClareada.pgm\n");
                printf(" \n    ==> ImagemNegativo.pgm\n\n");

                escolha = 'c';
                break;


            case 'd':
                printf(" \nConverter uma imagem PPM em PGM");
                printf("\nQual o nome do arquivo PPM a ser convertido?");
                scanf("%s", &refNome);

                montaMatrizPPM(matrizPPM, &altura2, &largura2, &maxK2, momePPMentrada);
                salvaPPM(nomeNovoPPM, matrizPPM, altura2, largura2, maxK2 );

                system("clear");
                printf("\n\nImagem convertida, arquivo salvo com o nome \n    ==> novoPGM.pgm\n\n");
                
    
                escolha = 'd';
                break;
        }



    }

    
    // pra rodar na mao ##############

    //char* nomePgmEntrada = "aaaaa.pgm";
    //char* nomeArClaro = "Claro";
    //char* nomeArNegativo = "Negativ";

    //char* momePPMentrada = "snail.ppm";
    //char* nomeNovoPPM = "Cinza";


    //montaMatrizPgm(matrizPgm, &altura, &largura, &maxK, nomePgmEntrada);

    //clareia(matrizPgm);

    //salvaPgm (nomeArClaro, matrizPgm, altura, largura, maxK);

    //negativo(matrizPgm);
    //salvaPgm (nomeArNegativo, matrizPgm, altura, largura, maxK);

    //montaMatrizPPM(matrizPPM, &altura2, &largura2, &maxK2, momePPMentrada);
   // salvaPPM(nomeNovoPPM, matrizPPM, altura2, largura2, maxK2 );
    
    


    return 0 ;
}


// ############################################
// ######### F U N C O E S ####################
// ############################################


FILE* carregaDadosPgm(
    int* altura,
    int* largura,
    int* maxK,  // maior valor da matriz
    char* nomePgm 
){
    static FILE* pegaDoArquivo = 0L ;
    char cabecalho[3] =  { '\0' } ;

    char pula[80] = { '\0' } ;
    memset ( ( void * ) pula, '\0', 80 ) ;

    pegaDoArquivo = fopen ( nomePgm, "r" ) ;

    if( pegaDoArquivo ){
        fscanf ( pegaDoArquivo, "%2c\n", cabecalho);
        if ( ! strcmp ( cabecalho, "P2" ) ){

            fscanf ( pegaDoArquivo, "%i", largura);

            fscanf ( pegaDoArquivo, "%i", altura);

            fscanf ( pegaDoArquivo, "%i", maxK);
        }

    }

    return pegaDoArquivo ;
}







void salvaPgm(
    char* nomeArClaro, 
    int vetorPgm[][MAX_LARGURA],
    int altura,
    int largura,
    int maxK 
){
    int linha = 0 ;
    int coluna = 0 ;
    FILE* pegaDoArquivo = fopen (nomeArClaro, "w");
    
    if( pegaDoArquivo ){
        fprintf (pegaDoArquivo, "P2\n");

        fprintf (pegaDoArquivo, "%u %u\n", largura, altura);

        fprintf (pegaDoArquivo, "%u\n", maxK);


        for(linha = 0 ; linha < altura ; linha ++){
            for(coluna = 0 ; coluna < largura ; coluna ++ ){
                fprintf (pegaDoArquivo, "%u", vetorPgm[linha][coluna]);

                if ( TAM_MAX_LINHA > 1 ){
                    fprintf ( pegaDoArquivo, " ");
                }
                if ( (coluna % TAM_MAX_LINHA) == 0){
                    fprintf ( pegaDoArquivo, "\n");
                }
            }

            if(coluna % TAM_MAX_LINHA){
                fprintf(pegaDoArquivo, "\n");
            }
        }
        fclose (pegaDoArquivo);
    }
    return ;
}



void montaMatrizPgm( 
    int vetorPgm[][MAX_LARGURA],
    int* altura,
    int* largura,
    int* maxK,
    char* nomePgmEntrada 
){
    int linha = 0 ;
    int coluna = 0 ;
    FILE* pegaDoArquivo = carregaDadosPgm (altura, largura, maxK, nomePgmEntrada);
    char pula = ' ';
    char escala = ' '; //treshold

    if (pegaDoArquivo ){
        for (linha = 0 ; linha < MIN( MAX_ALTURA - 1, *altura ) ; linha ++){
            for (coluna = 0 ; coluna < MIN( MAX_LARGURA -1, *largura ) ; coluna ++){
                fscanf (pegaDoArquivo, "%i", &vetorPgm[linha][coluna]);
            }
        }
        fclose (pegaDoArquivo);
    }

    return;
}





void clareia(int matrizPgm[1025][1025]){
    
    float tom;
    tom = 1.3;

    for (int i = 0; i < MAX_ALTURA; i++){
        for (int j = 0; j < MAX_LARGURA; j++){
            if(tom*matrizPgm[i][j]<= 255){
                matrizPgm[i][j] = tom*matrizPgm[i][j];
            }else{
                matrizPgm[i][j] = 255;
            }
        }
    }

}



void negativo(int matrizPgm[1025][1025]){
    for (int i = 1; i < MAX_ALTURA; i++) {
        for (int j = 1; j < MAX_LARGURA; j++) {
              matrizPgm[i][j] = 255 - matrizPgm[i][j];
        }
    }

}


FILE* carregaDadosPPM(
    int* altura2,
    int* largura2,
    int* maxK2,  // maior valor da matriz
    char* nomePPMEntrada 
){
    static FILE* pegaDoArquivo2 = 0L ;
    char cabecalho[3] =  { '\0' } ;

    char pula[80] = { '\0' } ;
    memset ( ( void * ) pula, '\0', 80 ) ;

    pegaDoArquivo2 = fopen (nomePPMEntrada, "r" ) ;

    if( pegaDoArquivo2 ){
        fscanf ( pegaDoArquivo2, "%2c\n", cabecalho);
        if ( ! strcmp ( cabecalho, "P3" ) ){

            fscanf ( pegaDoArquivo2, "%i", largura2);

            fscanf ( pegaDoArquivo2, "%i", altura2);

            fscanf ( pegaDoArquivo2, "%i", maxK2);
        }

    }

    return pegaDoArquivo2 ;
}



void montaMatrizPPM( 
    int vetorPPM[][MAX_LARGURA],
    int* altura2,
    int* largura2,
    int* maxK2,
    char* nomePPMEntrada 
){
    int linha2 = 0 ;
    int coluna2 = 0 ;
    FILE* pegaDoArquivo2 = carregaDadosPPM(altura2, largura2, maxK2, nomePPMEntrada);
  
    int red, green, blue;
    if (pegaDoArquivo2){
        for (linha2 = 0 ; linha2 < MIN( MAX_ALTURA - 1, *altura2 ) ; linha2 ++){
            for (coluna2 = 0 ; coluna2 < MIN( MAX_LARGURA -1, *largura2 ) ; coluna2++){
                fscanf (pegaDoArquivo2, "%i %i %i", &red, &green, &blue);
                vetorPPM[linha2][coluna2] = ((red*0.30)+(green*0.59)+(blue*0.11));
                
                
            }
        
        }
        fclose (pegaDoArquivo2);
    }
    printf("\n");
    return;
}


void salvaPPM(
    char* nomeNovoPPM,
    int vetorPPM[][MAX_LARGURA],
    int altura2,
    int largura2,
    int maxK2 
){
    int linha = 0;
    int coluna = 0;
    FILE* pegaDoArquivo = fopen (nomeNovoPPM, "w");
    
    if( pegaDoArquivo ){
        fprintf (pegaDoArquivo, "P2\n");

        fprintf (pegaDoArquivo, "%u %u\n", largura2, altura2);

        fprintf (pegaDoArquivo, "%u\n", maxK2);


        for(linha = 0 ; linha < altura2 ; linha ++){
            for(coluna = 0 ; coluna < largura2 ; coluna ++ ){
                fprintf (pegaDoArquivo, "%u", vetorPPM[linha][coluna]);

                if ( TAM_MAX_LINHA > 1 ){
                    fprintf ( pegaDoArquivo, " ");
                }
                if ( (coluna % TAM_MAX_LINHA) == 0){
                    fprintf ( pegaDoArquivo, "\n");
                }
            }

            if(coluna % TAM_MAX_LINHA){
                fprintf(pegaDoArquivo, "\n");
            }
        }
        fclose (pegaDoArquivo);
    }
    return ;
}
