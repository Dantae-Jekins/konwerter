#include <stdio.h>
#include <stdlib.h>


//  Declaração das funções (para o compilador não assumir errado);
//  Suponho que funcionaria se eu colocasse as funções antes de main também.
int* readInteger();
char* readChar();

//clear input
void clearinput(void) {
    while (getchar() != '\n');
}

// main

int main() {
    int base=NULL;
    int* bin=NULL, * oct=NULL, * dec=NULL;
    char* hex=NULL;

    printf("\n\n Conversor hex/dec/oct/bin\n --------------------------------------------");
    printf("\n\n Por favor informe a base do valor de entrada: \n [0]-Hexa  [1]-Deci  [2]-Octa  [3]-Bin");

    scanf_s("%d", &base);
    while (base != 0 && base != 1 && base != 2 && base != 3)
    {
        printf("\n Este número não corresponde a uma base, insira um correto");
        scanf_s("%d", &base);
    }
    // O scanf_s anterior consegue alterar a próxima leitura, isso quebra as funções readChar e readInteger.
    // para isso existe uma função com o único objetivo de limpar o leitor
    clearinput();

    printf("\n\n Base do valor de entrada selecionada: ");

    switch (base)
    {
    case 0:

        printf(" Hexadecimal\n Insira o valor: ");
        hex = readChar();
        break;

    case 1:

        printf(" Decimal\n Insira o valor: ");
        dec = readInteger();

        break;

    case 2:

        printf(" Octal\n Insira o valor: ");
        oct = readInteger();
        break;

    case 3:

        printf(" Binário\n Insira o valor: ");
        bin = readInteger();
        break;

    default:
        printf(" ERRO");
    }

    printf("\n\n Teste.");

    if (hex != NULL) {
        printf("\n hex : ");
        for (size_t i = 0; hex[i] != '\n'; i++)
        {
            printf("%c", hex[i]);
        }
    }
       
    // os fors procuram o digito de parada descrito na função de leitura, que é "-1".
    if (dec != NULL) {
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
        {
            printf("%d", dec[i]);
        }
    }
    if (oct != NULL) {
        printf("\n oct : ");
        for (size_t i = 0; oct[i] != -1; i++)
        {
            printf("%d", oct[i]);
        }
    }
    if (bin != NULL) {
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
        {
            printf("%d", bin[i]);
        }
    }
}


//FUNÇÕES DE LEITURA

int* readInteger() {
    FILE* file = stdin;
    int* num;
    size_t size = 2, count = 0; //tamanho default e contagem para array

    num = malloc(sizeof(*num) * size); // aloca memória ao num de tamanho *num (int) vezes size (2)

    while (EOF != (num[count] = fgetc(file)) && num[count++] != '\n') {
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

            num = realloc(num, sizeof(*num) * (size += 1));
            /*  size+=1 incrementa size e depois faz a
                operação.*/
        }
    }
    // se a condição do while é falsa, num[count] = '\n' ou EOF.

    // portanto deve ser retornado, com tamanho [count]:
    // o último digito deve ser -1, para servir de parada na hora de printar
    num[count] = -1; 
    return realloc(num, sizeof(*num) * count);

    //retorna um ponteiro apontando para um vetor de inteiros.
}

char* readChar() {
    char* num;
    size_t size = 2, count = 0; //tamanho default e contagem para array

    num = malloc(sizeof(*num) * size); // aloca memória ao num de tamanho *num (int) vezes size (2)

    while (EOF != (num[count] = fgetc(stdin)) && num[count++] != '\n') {
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

            num = realloc(num, sizeof(*num) * (size += 1));
            /*  size+=1 incrementa size e depois faz a
                operação.*/
        }
    }

    // se a condição do while é falsa, num[count] = '\n' ou EOF.

    // portanto deve ser retornado, com tamanho [count]:    
    num[count] = '\n';
    return realloc(num, sizeof(*num) * count);

    // retorna um ponteiro apontando para um vetor de caracteres.
}

//FUNÇÕES DE CONVERSÃO



//FUNÇÕES MATEMÁTICAS