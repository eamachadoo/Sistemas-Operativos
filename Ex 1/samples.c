#include <stdio.h>
#include <stdlib.h>

char *substr(const char *src, int numeroAleatorio, int tamanho){
    
    int length = tamanho;

    char *res = (char *)malloc(sizeof(char) * (length+1));

    for(int i = numeroAleatorio; i < (numeroAleatorio + tamanho) && (*(src+i) != '\0');i++){
        *res = *(src+i);
        res++;
    }
    *res = '\0';

    return res - length;
}

int main(int argc,char *argv[]){

    
    FILE *ptr = fopen(argv[1],"r");
    char *n1 = argv[2];
    char *n2 = argv[3];

    int inteiro1 = atoi(n1);
    int inteiro2 = atoi(n2);

    fseek(ptr,0,SEEK_END);
    int tamanhoficheiro = ftell(ptr);
    fseek(ptr,0,SEEK_SET);

    char *string = malloc(sizeof(char) * (tamanhoficheiro + 1));

    char c;
    int i = 0;

    if (ptr == NULL){

        printf("\nError: Cannot open this file");
        return 0;

    }

    while((c = fgetc(ptr)) != EOF)
    {
        string[i] = c;
        i++;
    }
    string[i] = '\0';
    fclose(ptr);

    int j = 0;
    int numeroAleatorio;
    srand(0);


while(j<inteiro1){
    numeroAleatorio = 0 + rand() % (tamanhoficheiro - inteiro2);
    char *res = substr(string,numeroAleatorio,inteiro2);
    printf(">%s<\n",res);
    j++;
    }
    return 0;
}
