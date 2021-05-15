#include <stdio.h>
#include <stdlib.h>


//  Declaração das funções (para o compilador não assumir errado);
//  Suponho que funcionaria se eu colocasse as funções antes de main também.

//FUNÇÕES DE LEITURA

int *readInteger() {
    FILE* file = stdin;
    int* num;
    size_t size = 2, count = 0; //tamanho default e contagem para array

    num = malloc(sizeof(int) * size); // aloca memória ao num de tamanho *num (int) vezes size (2)

    while (EOF != (num[count] = fgetc(file)) && num[count] != '\n') {
        /*  EOF != (num[count] = fgetc(stdin))
            lê o número fgetc(stdin) e o coloca
            dentro da array num[count], depois
            confirma que não é EOF.*/

            /*  num[count++] != '\n'
                compara o número lido com '\n',
                e depois incrementa count. */

        if (count + 1 == size) {
            /*  vê se a contagem bateu perto do
                limite da array, se sim realoca
                mais espaço para ser utilizado:*/

            num = realloc(num, sizeof(int) * (size += 1));
            /*  size+=1 incrementa size e depois faz a
                operação.*/
        }

        count++;
    }
    // se a condição do while é falsa, num[count] = '\n' ou EOF.

    // portanto deve ser retornado, com tamanho [count]:
    // o último digito deve ser -1, para servir de parada na hora de printar
    num[count] = -1; 
    return num;

    //retorna um ponteiro apontando para um vetor de inteiros.
}

char *readChar() {
    FILE* file = stdin;
    char* num;
    size_t size = 2, count = 0; //tamanho default e contagem para array

    num = malloc(sizeof(char) * size); // aloca memória ao num de tamanho *num (int) vezes size (2)

    while (EOF != (num[count] = fgetc(file)) && num[count] != '\n') {
        /*  EOF != (num[count] = fgetc(stdin))
            lê o número fgetc(stdin) e o coloca
            dentro da array num[count], depois
            confirma que não é EOF.*/

            /*  num[count++] != '\n'
                compara o número lido com '\n',
                e depois incrementa count. */

        if (count + 1 == size) {
            /*  vê se a contagem bateu perto do
                limite da array, se sim realoca
                mais espaço para ser utilizado:*/

            num = realloc(num, sizeof(char) * (size += 1));
            /*  size+=1 incrementa size e depois faz a
                operação.*/
        }

        count++;
    }

    // se a condição do while é falsa, num[count] = '\n' ou EOF.

    // portanto deve ser retornado, com tamanho [count]:    
    num[count] = '\0';
    return num;

    // retorna um ponteiro apontando para um vetor de caracteres.
}

//FUNÇÕES DE CONVERSÃO

int *decBin(int flag, int *input) {

    int *output;

    if (flag == 0) {    //!------------------------------------------------------------------------------------------
        //flag = 0 ; dec -> bin
    }
    else if (flag == 1) {   //!------------------------------------------------------------------------------------------
        //flag = 1 ; bin -> dec
    }
    else {
        printf("ERROR, função binOct FLAG INVÁLIDA");
    }

    return output;
}

int *decOct(int flag, int *input) {

    int *output;

    if (flag == 0) {        //!------------------------------------------------------------------------------------------
        //flag = 0 ; dec -> oct
        //!primeiro extrair o número em si da array absorvida em input:

        //achar o tamanho da array
        int size = sizeof(input)/sizeof(int); // eu tive problema com isso, porque que eu usando sizeof(endereço) funciona??

        /*  então arranjar a array em reverso (-1 deve permanecer no final visto que é a ordem de parada)
        não é possível criar uma array de carry que saiba o tamanho do input sem ser um ponteiro com malloc.*/
        int *carry = malloc(sizeof(input));
        //então podemos extrair o reverso

        //dados imaginários para exemplificar e me ajudar a pensar
        //input = {0, 1, 2, 3, 4, -1} > {4, 3, 2, 1, 0, -1} ; size = 5, não pode contar o -1
        for( int i = size, j = 0; i>0; i--, j++){ // i = 5, vai contar até que i = 1, então um total de 5 vezes 
            //passa array[4,3,2,1,0] para carry[0,1,2,3,4]
            carry[j] = input[i-1];
        }
    }
    else if (flag == 1) {   //!------------------------------------------------------------------------------------------
        //flag = 1 ; oct -> dec
    }
    else {
        printf("ERROR, função binOct FLAG INVÁLIDA");
    }

    return output;
}

int *binOct(int flag, int *input) { 

    if (flag == 0) {        //!------------------------------------------------------------------------------------------
        //flag = 0 ; bin -> oct
        int *carry = decBin(1, input);
        return decOct(0, carry);
    }
    else if(flag == 1){     //!------------------------------------------------------------------------------------------
        //flag = 1 ; oct -> bin
        int *carry = decOct(1, input);
        return decBin(0, carry);
    }
    else {
        printf("ERROR, função binOct FLAG INVÁLIDA");
    }

}


// hexadecimais tem que receber um tratamento especial :I
int hexInput(char input, int b) {
    //deve retornar um tipo int
}
char hexOutput(int input, int b) {
    //deve retornar um tipo char

}




//FUNÇÕES MATEMÁTICAS

//clear input
void clearinput(void) {
    while (getchar() != '\n');
}

// main

void main() {
    int base;
    int *bin=NULL, *oct=NULL, *dec=NULL;
    char *hex=NULL;

    printf("\n\n Conversor hex/dec/oct/bin\n --------------------------------------------");
    printf("\n\n Por favor informe a base do valor de entrada: \n [0]-Hexa  [1]-Deci  [2]-Octa  [3]-Bin \n ");

    do {
        scanf("%d", &base);
        if(base != 0 && base != 1 && base != 2 && base != 3)
            printf("\n Este número não corresponde a uma base, insira um correto");

    } while (base != 0 && base != 1 && base != 2 && base != 3);
    // O scanf_s anterior consegue alterar a próxima leitura, isso quebra as funções readChar e readInteger.
    // para isso existe uma função com o único objetivo de limpar o leitor
    clearinput();

    printf("\n\n Base do valor de entrada selecionada: ");

    switch (base){
    case 0:

        printf(" Hexadecimal\n Insira o valor: ");

        //lê em hexa
        hex = readChar();
        if(hex==NULL){
            printf("ERRO HEX==NULL");
            break;
        }

        //converte em decimal

        //converte em binário

        //converte em octal

        //printa o valor em hexadecimal
        printf("\n hex : ");
        for (size_t i = 0; hex[i] != '\0'; i++)
            printf("%c", hex[i]);
        

        break;

    case 1:

        printf(" Decimal\n Insira o valor: ");

        //Lê em decimal
        dec = readInteger();
        if(dec==NULL){
            printf("ERRO DEC==NULL");
            break;
        }        
        
        //converte em hexadecimal

        //converte em binário

        //converte em octal

        //printa o valor em decimal
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i] - '0');
        

        break;

    case 2:

        printf(" Octal\n Insira o valor: ");

        //lê em octal
        oct = readInteger();
        if(oct==NULL){
            printf("ERRO OCT==NULL");
            break;
        }

        //converte em hexadecimal

        //converte em binário

        //converte em decimal

        //printa o valor em octal
        printf("\n oct : ");
        for (size_t i = 0; oct[i] != -1; i++)
            printf("%d", oct[i] - '0');
        
        break;

    case 3:

        printf(" Binário\n Insira o valor: ");
        
        //lê em binário
        bin = readInteger();
        if(bin==NULL){
            printf("ERRO BIN==NULL");
            break;
        }

        //converte em hexadecimal

        //converte em decimal

        //converte em octal

        //printa o valor em binário
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
            printf("%d",bin[i]-'0');

        break;

    default:
        printf(" ERRO CASE=()");
    }

    printf("\n\n");
}
