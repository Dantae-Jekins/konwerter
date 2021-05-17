#include <stdio.h>
#include <stdlib.h>

//  Declaração das funções (para o compilador não assumir errado);
//  Suponho que funcionaria se eu colocasse as funções antes de main também.
//  eu tõ exagerando nos comentários para eu mesmo montar o programa
//FUNÇÕES DE LEITURA

int *readInteger()
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

char *readChar()
{
    FILE *file = stdin;
    char *num;
    size_t size = 2, count = 0; //tamanho default e contagem para array

    num = malloc(sizeof(char) * size); // aloca memória ao num de tamanho *num (int) vezes size (2)

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

////FUNÇÕES MATEMÁTICAS

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

    if(i == 0)
        return 1;
    
    else if (i == 1)
        return num;
    
    else if (i>1)
    {
        int carry = num;
        while (i > 1 )
        {
            num*=carry;
            i--;
        }
        return num;
    }

    /*else if (i<0) SÓ COM FLOATS, EU ODEIO FLOATS
    {

        while (i < 1 )
        {
            num*=num;
            i++;
        }        
        num= 1/num; 
        return num;
    }
    */
}

int korzen()
{

}

int lg(int base, int num)
{
    // esta operação retorna quantas casas um número decimal tem, não é exatamente um logarítmo, pois senão 
    // teria de aceitar floats e causaria muitos outros problemas neste algorítmo
    int i;
    for (i = 1; num > base; i++)
        num/=base;
    return i;
}

//FUNÇÕES DE CONVERSÃO

int *decKonwerter(int flag, int sys, int *input)
{

    int *output;
    int size = 0;    
    int wait = 0;
    int dec = 0;

    if( sys < 0 || sys == 10)
    {
        printf("Base inválida");
    }
    else if( sys > 10)
    {
    
    }
    else
    {
        //extrair o tamanho da array importada na função, até -1, excluindo-o.
        // wait serve para que size não conte os 0's iniciais.

        while(input[wait]==0)
            wait++;
        while (input[size] != -1)
            size++;
        size -= wait;

        // se existem 0's iniciais, temos que retirar eles e realocar um espaço correto para output
        if(wait > 0)
        {
            int *carry;
            carry = malloc(sizeof(int)*size);
            for (size_t i = 0, j = wait; i<size ; i++, j++)
            {
                carry[i] = input[j];
            }
            input = carry;
        }

        if (flag == 0)
        {
            //flag = 0 ; dec -> bin
            //primeiro nós devemos extrair o inteiro total da array, da seguinte forma:
            dec = arraySum(input, size); 
            //size precisa ser +1, pois arraySum conta a partir de 1
            // enquanto size começou a contar a partir de 
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
            output = malloc(sizeof(int) * (size + 1));
            output[size+1]=-1;//ordem de parada
            //e então adicionamos os valores para output reversamente, ou seja, os restos das divisões.
            for (carry = dec; size >= 0; size--)
            {
                output[size] = carry % sys;
                carry /= sys;
            }

            //FEITO
        }
        else if (flag == 1)
        {
            //flag = 1 ; bin -> dec

            //extraimos os valores da função abaixo, inversamente 
            for (int i = size-1, j = 0; i>=0; i--, j++)
                dec += input[i] * podniesc(sys, j);
                //podniesc é a função de potência

            // infelizmente estamos trabalhando com array's, por isto não é possível devolver dec como inteiro, para isso
            // devemos transferir ele em uma array, usaremos o logarítmo de 10 para achar seu tamanho, com o intúito de
            // saber qual tamanho devemos alocar para a array que irá absorver o elemento, e por final realizar
            // operações para colocar cada elemento em seu devido lugar.

            size = lg(10, dec);  //descobrimos o tamanho do decimal gerado
            output = malloc(sizeof(int)*size+1); //alocamos o espaço que outpur deve ter
            output[size]=-1; //ordem de parada
            //e então  absorvemos o decimal em output.
            //output[size] é a ordem de parada, portanto podemos começar a contar só a partir de size-1.
            for (int i = size-1; i >= 0; i--, dec/=10)
                output[i] = dec%10;

            

        }
        else
        {
            printf("ERROR, função decOct FLAG INVÁLIDA");
        }

        return output;
    }
}

// hexadecimais tem que receber um tratamento especial :I
int hexInput(char input, int b)
{
    //deve retornar um tipo int
}
char hexOutput(int input, int b)
{
    //deve retornar um tipo char
}

//clear input
void clearinput(void)
{
    while (getchar() != '\n');
}

// main

void main()
{
    int base;
    int *bin = NULL, *oct = NULL, *dec = NULL;
    char *hex = NULL;

    printf("\n\n Conversor hex/dec/oct/bin\n --------------------------------------------");
    printf("\n\n Por favor informe a base do valor de entrada: \n [0]-Hexa  [1]-Deci  [2]-Octa  [3]-Bin \n ");

    do
    {
        scanf("%d", &base);
        if (base != 0 && base != 1 && base != 2 && base != 3)
            printf("\n Este número não corresponde a uma base, insira um correto");

    } while (base != 0 && base != 1 && base != 2 && base != 3);
    // O scanf_s anterior consegue alterar a próxima leitura, isso quebra as funções readChar e readInteger.
    // para isso existe uma função com o único objetivo de limpar o leitor
    clearinput();

    printf("\n\n Base do valor de entrada selecionada: ");

    switch (base)
    {
    case 0:

        printf(" Hexadecimal\n Insira o valor: ");

        //lê em hexa
        hex = readChar();
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
        for (size_t i = 0; hex[i] != '\0'; i++)
            printf("%c", hex[i]);

        break;

    case 1:

        printf(" Decimal\n Insira o valor: ");

        //Lê em decimal
        dec = readInteger();
        if (dec == NULL)
        {
            printf("ERRO DEC==NULL");
            break;
        }
        //printa e transforma o valor decimal de ASCII para inteiros
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i] -= '0');

        //converte em hexadecimal
        printf("\n hex : ainda não desenvolvido");

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
        oct = readInteger();
        if (oct == NULL)
        {
            printf("ERRO OCT==NULL");
            break;
        }
        //printa e transforma o valor octal de ASCII para inteiros
        printf("\n oct : ");
        for (size_t i = 0; oct[i] != -1; i++)
            printf("%d", oct[i]-='0');

        //converte em hexadecimal
        printf("\n hex : ainda não desenvolvido");

        //converte em decimal
        dec = decKonwerter(1, 8, oct);
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i]);    

        //converte em binário
        bin = decKonwerter(0, 2, dec);
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
            printf("%d", bin[i]);
    

        break;

    case 3:

        printf(" Binário\n Insira o valor: ");

        //lê em binário
        bin = readInteger();
        if (bin == NULL)
        {
            printf("ERRO BIN==NULL");
            break;
        }
        //printa e transforma o valor binário de ASCII para inteiros
        printf("\n bin : ");
        for (size_t i = 0; bin[i] != -1; i++)
            printf("%d", bin[i]-='0');

        //converte em hexadecimal
        printf("\n hex : ainda não desenvolvido");

        //converte em decimal
        dec = decKonwerter(1, 2, bin);
        printf("\n dec : ");
        for (size_t i = 0; dec[i] != -1; i++)
            printf("%d", dec[i]);

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
