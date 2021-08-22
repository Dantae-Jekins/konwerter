#include<stdlib.h>
#include<stdio.h>

int cmpStr(char str1[], char str2[])
{
    int x = 0;
    for( int i = 0; str1[i] != '\0'; i++){
	//printf("\nReading cmpstr; index: %d", i);
        if (str1[i] != str2[i]){
            x = 1;
            break;
        }
    }
    return x;
}

void error(int code)
{
	printf("Testin");
}

void *scanner(char flag[], FILE *file)
{
    if(cmpStr(flag, "-f") == 0)
    {
		char **output = NULL;
		return output;
        printf("\n Flag not yet available");
    }

    else if(cmpStr(flag, "-i") == 0)
    {
			char reader;
			int *output = malloc(sizeof(int));
			*output = 0; // goddanm initialize issues

        while   (EOF!=(reader = fgetc(file)) && reader != '\n')
        {
          if ( reader >= 48 && reader <= 57 )
          	reader -= 48;
	    		else
						error(1);
	    	
				*output*=10;
	    	*output+=reader;
        }

			return output;
    }

	else if(cmpStr(flag, "-c") == 0)
	{
	
		int halt = 1;
		char *output;
		size_t counter= 0;
		output = malloc(sizeof(char) * (counter + 1));
		
		while( EOF!=(output[counter]=fgetc(file)) && output[counter]!='\n')
		{
			if ( output[counter] != 0)
				halt = 0;

			if( halt != 1)
			{
				counter++;
				output = realloc(output, sizeof(char) * (counter += 1));
			}
		}

		output[counter] = '\0';
		return output;
	}

	else
	{
		error(2);
		return NULL;
	}
}
int lg(int base, int num)
{
	int i;
	for (i = 1; num > base; i++)
		num /= base;
	
	return i;
}

int podniesc(int num, int i)
{
	if (i == 0)
		return 1;

	else if (i == 1)
		return num;
	
	else if (i > 1)
	{
		int carry = num;
		while (i > 1)
		{
			num*=carry;
			i--;
		}
		return num;
	}	

	return -1; // error
}

int *array(int integer, int size)
{
	int *carry = malloc(sizeof(int) * size);
	while(size > 0)
	{
		carry[size-1] = integer%10;
		integer /= 10;
		size--;
	}

	return carry;
}

void *konwerter(void *input, int insys, int outsys, char *flag)
{
	if(flag == NULL)
	{
		if (insys <=10 && insys >=2)
		{
			int *carry = input;

		if (insys != 10)
			{
				//se o sistema for diferente de 10 devemos transformar
				//o carry em decimal.
				int size = lg(10, *carry); // descobre o tamanho do num
				for(int i = 0; i > size; i++)
				{
				 	printf("%d",i);	
				}	
			}
		}
		else if(insys == 16)
		{
			char *carry = input;
		}
		else
			return NULL;
	}
	else
	{
		return NULL;
	}
}

int main(int argc, char *argv[])
{
	int number = 234;
	int size = lg(10, 234);
	printf("\n size = %d",size);
	int *carry = array(number, 3);
	printf("\n array = %d %d %d", carry[0], carry[1], carry[2]);

	// Array is working.
}

