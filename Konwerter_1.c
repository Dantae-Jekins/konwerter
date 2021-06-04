#include <stdio.h>
#include <stdlib.h>

//  Declaração das funções (para o compilador não assumir errado);
//  Suponho que funcionaria se eu colocasse as funções antes de main também.
//  eu tõ exagerando nos comentários para eu mesmo montar o programa


//FUNÇÕES DE LEITURA
int *readInput()
{
    FILE *file = stdin;
    int *num;
    size_t size = 2, count = 0; //tamanho default e contagem para array

    num = malloc(sizeof(int) * size); // aloca memória ao num de tamanho *num (int) vezes size (2)

    while (EOF != (num[count] = fgetc(file)) && num[count] != '\n')
    {
        /*  EOF != (num[count] = fgetc(stdin))
            lê o número fgetc(stdin) e o coloca
            dentro da array num[count], depois
            confirma que não é EOF.*/

        /*  num[count++] != '\n'
                compara o número lido com '\n',
                e depois incrementa count. */

        if (count + 1 == size)
        {
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


//FUNÇÕES MATEMÁTICAS
int arraySum(int *array, int size)
{
    int sum = 0;
    for (size_t i = 1, j = size; j > 0; i *= 10, j--, size--)
        sum += array[j - 1] * i;
    return sum;
}

int podniesc(int num, int i)
{
    //função de potênciação

    if (i == 0)
        return 1;

    else if (i == 1)
        return num;

    else if (i > 1)
    {
        int carry = num;
        while (i > 1)
        {
            num *= carry;
            i--;
        }
        return num;
    }
}

int lg(int base, int num)
{
    // esta operação retorna quantas casas um número decimal tem, não é exatamente um logarítmo, pois senão
    // teria de aceitar floats e causaria muitos outros problemas neste algorítmo
    int i;
    for (i = 1; num > base; i++)
        num /= base;
    return i;
}


//FUNÇÕES DE CONVERSÃO
int *integerValue(int flag, int *input)
{
    //Converte números do readInteger em inteiros, bem como A, B, C com base em hexa, e remove os zeros iniciais.
    //Para que se adote um sistema específico de símbolos como base (9, 10, A, B, #, !, *...) deve ser alterado os valores aqui
    //porém serão feitas alterações no futuro para que seja possível definir quais símbolos devem representar os números após A.

    //primeiramente deve-se retirar os zeros inicias
    int wait = 0;
    int size = 0;

    while (input[wait] == 0)
        wait++;
    while (input[size] != -1)
        size++;
    size -= wait;

    // se existem 0's iniciais, temos que retirar eles e realocar um espaço correto para output
    if (wait > 0)
    {
        int *carry;
        carry = malloc(sizeof(int) * size + 1);
        for (size_t i = 0, j = wait; i <= size; i++, j++)
        {
            //input começa a contar a partir de wait, ou seja, a partir dos zeros
            // e então carry recebe estes valores
            carry[i] = input[j];
        }
        input = carry;
    }

    //se a flag é 0 então o programa deve rodar ao inverso (torna inteiros em ASCII)
    if (flag == 0)
    {
        for (size_t i = 0; input[i] != -1; i++)
        {
            if (input[i] >= 48 || input[i] <= 57) // se os valores estão entre 0 e 9.
                input[i] -= 48;                   //subtrai 48 para ter o valor em decimal.

            else if (input[i] >= 65 || input[i] <= 70) //se os valores estão entre A e F
                input[i] -= 55;                        //subtrai 55 para ter o valor em decimal.
        }
    }
    //se o objetivo é tornar inteiros para seus correspondentes ASCII e 10, 11, (...) em hexa, então a flag deve ser ==1
    else if (flag == 1)
    {
        for (size_t i = 0; input[i] != -1; i++)
        {
            if (input[i] >= 0 && input[i] <= 9)
                input[i] += 48;

            else if (input[i] >= 10 && input[i] <= 15)
                input[i] += 55;
        }
    }

    return input;
}

int *decKonwerter(int flag, int sys, int *input)
{

    int *output;
    int size = 0;
    int dec = 0;
    int hex = 0;

    //extrair o tamanho da array importada na função, até -1
    while (input[size] != -1)
        size++;
    
    if (flag == 0)
    {
        //flag = 0 ; dec -> sys
        //primeiro nós devemos extrair o inteiro total da array, da seguinte forma:
        dec = arraySum(input, size);
        size = 0;
        //com  o número inteiro, nós somos capazes de realizar a matemática para extrair o valor em binário :)
        int carry = dec;
        while (carry >= sys)
        {
            //primeiramente deve-se achar o tamanho que output terá
            carry /= sys;
            size++;
        }
        //após ter conhecimento disso alocamos um espaço
        output = malloc(sizeof(int) * (size + 2));
        output[size + 1] = -1; //ordem de parada
        //e então adicionamos os valores para output reversamente, ou seja, os restos das divisões.
        for (carry = dec; size >= 0; size--)
        {
            output[size] = carry % sys;
            carry /= sys;
        }

        //faz com que seja retornado ASCII como valor
        if(sys > 10)
            output = integerValue(1, output);
        //FEITO
    }
    else if (flag == 1)
    {
        //flag = 1 ; sys -> dec

        //extraimos os valores da função abaixo, inversamente
        for (int i = size - 1, j = 0; i >= 0; i--, j++)
            dec += input[i] * podniesc(sys, j);
        //podniesc é a função de potência

        // infelizmente estamos trabalhando com array's, por isto não é possível devolver dec como inteiro, para isso
        // devemos transferir ele em uma array, usaremos o logarítmo de 10 para achar seu tamanho, com o intúito de
        // saber qual tamanho devemos alocar para a array que irá absorver o elemento, e por final realizar
        // operações para colocar cada elemento em seu devido lugar.

        size = lg(10, dec);                      //descobrimos o tamanho do decimal gerado
        output = malloc(sizeof(int) * size + 1); //alocamos o espaço que outpur deve ter
        output[size] = -1;                       //ordem de parada
        //e então  absorvemos o decimal em output.
        //output[size] é a ordem de parada, portanto podemos começar a contar só a partir de size-1.
        for (int i = size - 1; i >= 0; i--, dec /= 10)
            output[i] = dec % 10;
    }
    else
    {
        printf("ERROR, função decOct FLAG INVÁLIDA");
    }

    return output;
}


//clear input
void clearinput(void)
{
    while (getchar() != '\n')
        ;
}


// main
void main()
{
    int base;
    int *bin = NULL, *oct = NULL, *dec = NULL, *hex = NULL;

    printf("\n\n Conversor hex/dec/oct/bin\n --------------------------------------------");
    printf("\n\n Por favor informe a base do valor de entrada: \n [0]-Hexa  [1]-Deci  [2]-Octa  [3]-Bin \n ");

    do
    {
        scanf("%d", &base);
        if (base != 0 && base != 1 && base != 2 && base != 3)
            printf("\n Este número não corresponde a uma base, insira um correto");

    } while (base != 0 && base != 1 && base != 2 && base != 3);
    // O scanf_s anterior consegue alterar a próxima leitura, isso quebra as funções readInput e readInput.
    // para isso existe uma função com o único objetivo de limpar o leitor
    clearinput();

    printf("\n\n Base do valor de entrada selecionada: ");

    switch (base)
    {
    case 0:

        printf(" Hexadecimal\n Insira o valor: ");

        //lê em hexa
        hex = readInput();
        if (hex == NULL)
        {
            printf("ERRO HEX==NULL");
            break;
        }

        //converte em decimal

        //converte em binário

        //converte em octal

        //printa o valor em hexadecimal
        printf("\n hex : ");
        for (size_t i = 0; hex[i] != -1; i++)
            printf("%c", hex[i]);

        break;

    case 1:

        printf(" Decimal\n Insira o valor: ");

        //Lê em decimal
        dec = integerValue(0, readInput());
        if (dec == NULL)
        {
            printf("ERRO DEC==NULL");
            break;
        }
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i]);

        //converte em hexadecimal
        hex = decKonwerter(0, 16, dec);
        printf("\n hex : ");
        for (size_t i = 0;hex[i]!=-1; i++)
            printf("%c",hex[i]);

        //converte em binário
        bin = decKonwerter(0, 2, dec);
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
            printf("%d", bin[i]);

        //converte em octal
        oct = decKonwerter(0, 8, dec);
        printf("\n oct : ");
        for (size_t i = 0; oct[i] != -1; i++)
            printf("%d", oct[i]);

        break;

    case 2:

        printf(" Octal\n Insira o valor: ");

        //lê em octal
        oct = integerValue(0, readInput());
        if (oct == NULL)
        {
            printf("ERRO OCT==NULL");
            break;
        }
        printf("\n oct : ");
        for (size_t i = 0; oct[i] != -1; i++)
            printf("%d", oct[i]);

        //converte em decimal
        dec = decKonwerter(1, 8, oct);
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i]);

        //converte em hexadecimal
        hex = decKonwerter(0, 16, dec);
        printf("\n hex : ");
        for (size_t i = 0;hex[i]!=-1; i++)
            printf("%c",hex[i]);

        //converte em binário
        bin = decKonwerter(0, 2, dec);
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
            printf("%d", bin[i]);

        break;

    case 3:

        printf(" Binário\n Insira o valor: ");

        //lê em binário
        bin = integerValue(0, readInput());
        if (bin == NULL)
        {
            printf("ERRO BIN==NULL");
            break;
        }
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
            printf("%d", bin[i]);

        //converte em decimal
        dec = decKonwerter(1, 2, bin);
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i]);

        //converte em hexadecimal
        hex = decKonwerter(0, 16, dec);
        printf("\n hex : ");
        for (size_t i = 0;hex[i]!=-1; i++)
            printf("%c",hex[i]);

        //converte em octal
        oct = decKonwerter(0, 8, dec);
        printf("\n oct : ");
        for (size_t i = 0; oct[i] != -1; i++)
            printf("%d", oct[i]);

        break;

    default:
        printf(" ERRO CASE=()");
    }

    printf("\n\n");
}
