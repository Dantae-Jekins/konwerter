#include <stdio.h>
#include <stdlib.h>


//  Declaração das funções (para o compilador não assumir errado);
//  Suponho que funcionaria se eu colocasse as funções antes de main também.
//  eu tõ exagerando nos comentários para eu mesmo montar o programa
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

int *decBin(int flag, int input[]) {

    int *output;
    int size = 1;
    //!primeiro extrair o número em si da array absorvida em input reversamente:

    //achar o tamanho da array
    //primeira tentativa foi utilizar sizeof(array), porem o compilador não compreende esta função com ponteiros,
    //por isso é necessário achar o tamanho através de uma contagem até -1, que é a ordem de parada
    //por causa da ordem de parada é necessário que size conte 1 a mais, para que represente o tamanho real
    while(input[size-1]!=-1)
    size++;
    /*  então arranjar a array em reverso (-1 deve permanecer no final visto que é a ordem de parada)
    não é possível criar uma array de carry que saiba o tamanho do input sem ser um ponteiro com malloc.*/
    int *carry = malloc(sizeof(int)*size);
    //então podemos extrair o reverso
    //dados imaginários para exemplificar e me ajudar a pensar
    //input = {0, 1, 2, 3, 4, -1} > {4, 3, 2, 1, 0, -1} ; size = 5, não pode contar o -1
    for( int i = size-1, j = 0; i>0; i--, j++) // i = 5, vai contar até que i = 1, então um total de 5 vezes 
        //i tem que ser size-1, razão:
            /*
            size representa o tamanho total da array, mas ele conta a partir de 1, diferentemente do computador
                não se pode mudar porque para alocar tamanho para o carry através de size ELE PRECISA SER ASSIM, já que sizeof(0)
                é um valor nulo, e seria necessário partir do sizeof(1).
                Por isso que para usar size na array, ele deve ser subtraido por 1, já que size=6 é a mesma coisa que
                array[0,1,2,3,4,5,6];

            */
        //passa array[4,3,2,1,0] para carry[0,1,2,3,4]
        carry[j] = input[i-1];
        //Input tem que ser i-1 porque o último elemento de input(-1) não deve ser transferido.

    carry[size-1]=-1; // adiciona ordem de parada em carry :I..

    //TESTE
    printf("\n input invertido: ");
    for (int i = 0; carry[i]!=-1; i++)
        printf("%d", carry[i]);

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
    int size = 1;
    //!primeiro extrair o número em si da array absorvida em input reversamente:

    //achar o tamanho da array
    //primeira tentativa foi utilizar sizeof(array), porem o compilador não compreende esta função com ponteiros,
    //por isso é necessário achar o tamanho através de uma contagem até -1, que é a ordem de parada
    //por causa da ordem de parada é necessário que size conte 1 a mais, para que represente o tamanho real
    while(input[size-1]!=-1)
    size++;
    /*  então arranjar a array em reverso (-1 deve permanecer no final visto que é a ordem de parada)
    não é possível criar uma array de carry que saiba o tamanho do input sem ser um ponteiro com malloc.*/
    int *carry = malloc(sizeof(int)*size);
    //então podemos extrair o reverso
    //dados imaginários para exemplificar e me ajudar a pensar
    //input = {0, 1, 2, 3, 4, -1} > {4, 3, 2, 1, 0, -1} ; size = 5, não pode contar o -1
    for( int i = size-1, j = 0; i>0; i--, j++) // i = 5, vai contar até que i = 1, então um total de 5 vezes 
        //i tem que ser size-1, razão:
            /*
            size representa o tamanho total da array, mas ele conta a partir de 1, diferentemente do computador
                não se pode mudar porque para alocar tamanho para o carry através de size ELE PRECISA SER ASSIM, já que sizeof(0)
                é um valor nulo, e seria necessário partir do sizeof(1).
                Por isso que para usar size na array, ele deve ser subtraido por 1, já que size=6 é a mesma coisa que
                array[0,1,2,3,4,5,6];

            */
        //passa array[4,3,2,1,0] para carry[0,1,2,3,4]
        carry[j] = input[i-1];
        //Input tem que ser i-1 porque o último elemento de input(-1) não deve ser transferido.

    carry[size-1]=-1; // adiciona ordem de parada em carry :I..

    //TESTE
    printf("\n input invertido: ");
    for (int i = 0; carry[i]!=-1; i++)
        printf("%d", carry[i]);

    if (flag == 0) {        //!------------------------------------------------------------------------------------------
        //flag = 0 ; dec -> oct
    
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
        //printa e transforma o valor decimal de ASCII para inteiros
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i]-='0');
        
        //converte em hexadecimal

        //converte em binário
        bin = decBin(0, dec);
        //converte em octal
        oct = decOct(0, dec);

        break;

    case 2:

        printf(" Octal\n Insira o valor: ");

        //lê em octal
        oct = readInteger();
        if(oct==NULL){
            printf("ERRO OCT==NULL");
            break;
        }
        //printa e transforma o valor octal de ASCII para inteiros
        printf("\n oct : ");
        for (size_t i = 0; oct[i] != -1; i++)
            printf("%d", oct[i]-='0');

        //converte em hexadecimal

        //converte em binário
        //bin = binOct(1, oct);

        //converte em decimal
        dec = decOct(1, oct);

        break;

    case 3:

        printf(" Binário\n Insira o valor: ");
        
        //lê em binário
        bin = readInteger();
        if(bin==NULL){
            printf("ERRO BIN==NULL");
            break;
        }
        //printa e transforma o valor binário de ASCII para inteiros
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
            printf("%d",bin[i]-='0');

        //converte em hexadecimal

        //converte em decimal
        dec = decBin(1, bin);
        
        //converte em octal
        //oct = binOct(0, bin);

        break;

    default:
        printf(" ERRO CASE=()");
    }

    printf("\n\n");
}
