#include <stdio.h>
#include <stdlib.h>

char* entrada(FILE* read, size_t tam2) {
    char* str;
    size_t tam = 0;
    printf("\n\n Por favor insira o dado de entrada: ");
    str = malloc(sizeof(*str) * tam2);
    while (EOF !=(str[tam]=fgetc(read)) && str[tam++]!= '\n') {
        if (tam+1 == tam2) {
            str = realloc(str, sizeof(*str)*(tam2+=1));
            //2 + 1 (3) == limite, tam2 (3)
            //realloc -> +1 space para memória (tam2+1)
            // tam2 = tam2 + 1 (tam2+=1); limite +1
        }
    }
    return realloc(str, sizeof(*str) * tam);
}
void clearinput(void) {
    while (getchar() != '\n');
}

int square(int valor, int i){
    int valor1 = valor; 
    if (i == 0) { //valor ^0
        return 1;
    }
    else if (i == 1) { //valor ^1
        return valor;
    }
    else {
        while (i>1){ //valor ^+2
            valor = valor * valor1;    
            i--;
            //i = 3
            //valor = valor*valor1;
            //i-- ; i = 2
            //valor = valor*valor1;
            //i-- ; i = 1 ; break;
        }
        return valor;
    }
}

int root(int valor, int root) { // 4 , 2
    if (valor == 1 || valor == 0 || root == 1) { //false
        return valor;
    }
    else { //true
        int i = 0;
        for (int valor1 = 1; valor1 <= valor;) {  //v1<=4
            i++;
            valor1 = square(i, root);
            //i++; v1(1) = i(1)^2 = 0  
            //i++; v1(2) = i(2)^2 = 2 
            //i++; v1(4) = i(3)^2 = 9  
            // 9 <= 4; false; break; i== 3 
            // resposta deve ser == 2; i-1
        }
        return (i-1);
    }
    //terminar função de raiz
    //Nem sei se vou usar isso
}

int log10(int num){
    int i;
    for(i = 0;num>=10;i++){
        num /= 10;
    }
    return i;
}

int decbin(char* dado, int reverse) {
    int j = 0, i = 0;
    size_t x = 0, size=2;
    int *bin;
    if (reverse == 0) {    
        bin = malloc(sizeof(int) * size);   
         if (!bin) {
            printf("\n Erro ao alocar memória");
            abort();
        }
        i = atoi(dado);
        //importa array de characters
        // char -> int
        //ATOI NÃO PODE SER USADO FORA DE PONTEIROS!

        for (j = i; j > 0;) { 
            j = j / 2;
            bin = realloc(bin, sizeof(int) * (size += 1)); //definição de tamanho
            x++;//contagem de quantos elementos vão ser;
                //+ 1 elemento = +1 relloc = +1 espaço;
        }
        bin[x] = -1;
        for (j = i; j > 0;) {
            x--;//contagem regressiva da quantidade anterior
            bin[x] = j % 2; // adesão dos valores ao ponteiro
            j = j / 2;
        }
        return realloc(bin, sizeof(int)*size);
    }
    else {
        bin = malloc(sizeof(int) * size);
        if (!bin) {
            printf("\n Erro ao alocar memória");
            abort();
        }
        for (x = 0; dado[x] != '\n'; x++) {
            bin[x] = dado[x] - '0';
            bin = realloc(bin, sizeof(int) * (size += 1));
        }
        while(x>0) {
            x--;
            j +=bin[x]*square(2, i);  
            i++;
        }

        x = log10(j) + 1;
        free(dado);
        dado = malloc(sizeof(char) * x);
        dado[x] = '\n';

        for (i = x; i >= 0;) {
            i--;
            dado[i] =((j % 10) + '0'); 
            j = j / 10;
        }
        return dado;
    }
}

int decoct(char* dado, int reverse) {
    int j = 0, i = 0;
    size_t x = 0, size=2;
    int *oct;
    if (reverse == 0) {    
        oct = malloc(sizeof(int) * size);   
         if (!oct) {
            printf("\n Erro ao alocar memória");
            abort();
        }
        i = atoi(dado);
        //importa array de characters
        // char -> int
        //ATOI NÃO PODE SER USADO FORA DE PONTEIROS!

        for (j = i; j > 0;) { 
            j = j / 8;
            oct = realloc(oct, sizeof(int) * (size += 1)); //definição de tamanho
            x++;//contagem de quantos elementos vão ser;
                //+ 1 elemento = +1 relloc = +1 espaço;
        }
        oct[x] = -1;
        for (j = i; j > 0;) {
            x--;//contagem regressiva da quantidade anterior
            oct[x] = j % 8; // adesão dos valores ao ponteiro
            j = j / 8;
        }
        return realloc(oct, sizeof(int)*size);
    }
    else {
        oct = malloc(sizeof(int) * size);
        if (!oct) {
            printf("\n Erro ao alocar memória");
            abort();
        }
        for (x = 0; dado[x] != '\n'; x++) {
            oct[x] = dado[x] - '0';
            oct = realloc(oct, sizeof(int) * (size += 1));
        }
        while(x>0) {
            x--;
            j +=oct[x]*square(8, i);  
            i++;
        }

        x = log10(j) + 1;
        free(dado);
        dado = malloc(sizeof(char) * x);
        dado[x] = '\n';

        for (i = x; i >= 0;) {
            i--;
            dado[i] =((j % 10) + '0'); 
            j = j / 10;
        }
        return dado;
        // Trabalhando aqui no momento
        // Objetivo: limpar o char dado e usar o mesmo como output, absorvendo o valor de j 
        // como um vetor de characters e retornado como ponteiro para aonde a função foi chamada.
    }
}

void dechex() {

}


int main(){

    int i, j = 4;
    char *input=NULL, *outputHEX=NULL;
    int *outputBIN,*outputOCT,*outputDEC;
    

    printf("\n\n----------Conversor de base----------");
    printf("\n\n Por favor insira a base do dado de entrada:");
    printf("\n [0] Hexadecimal  [1] Decimal  [2] Octal  [3] Binário \n ");
    while (j != 0 && j != 1 && j != 2 && j != 3) {
        scanf_s("%d", &j);
        if (j != 0 && j != 1 && j != 2 && j != 3) {
            printf("\n -Valor inválido\n ");
        }
    }
    clearinput();
    switch (j){
        case 0:
            input = entrada(stdin,10);
        break;

        case 1:
            input = entrada(stdin,10);
            outputBIN = decbin(input, 0);
            outputOCT = decoct(input, 1);
            printf("\n\n Valor em binário: ");
            for(i=0; outputBIN[i]!=-1;i++){
                printf("%d",outputBIN[i]);
            }
            printf("\n\n Valor em octal: ");
            for (i = 0; outputOCT[i] != -1; i++) {
                printf("%d", outputOCT[i]);
            }

            
        break;
        
        case 2:
            input = entrada(stdin,10);
            outputDEC = decoct(input, 1);
            printf("\n\n Valor em decimal: %s", outputDEC);
        break;

        case 3:
            input = entrada(stdin,10);
            outputDEC = decbin(input, 1);
            printf("\n\n Valor em decimal: %s", outputDEC);  
        break;
    }
}