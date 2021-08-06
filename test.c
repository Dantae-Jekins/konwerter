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
				error(01);
	    	*output*=10;
	    	*output+=reader;
        }
		return output;
    }

	else if(cmpStr(flag, "-c") == 0){
	
		char *output;
		size_t size = 1, counter= 0;
		output = malloc(sizeof(char)*size);
		
		while( EOF!=(output[counter]=fgetc(file)) && output[counter]!='\n'){
			counter++;

			if(counter==size)
				output = realloc(output,sizeof(char)*(size+=1));
		}
		output[counter] = '\0';
		return output;
	}

	return NULL;
}

int main(int argc, char *argv[])
{
	if(argc== 2)
	{	
		if(cmpStr(argv[1],"file") == 0)
		{
			//char *input = "FILLER";
			//scanner(input, argv[1], stdin);
		}

		else if(cmpStr(argv[1],"char") == 0)
		{
			//char *input = "FILLER";
			//scanner(input, argv[1],stdin);
		}

		else if(cmpStr(argv[1],"-i") == 0)
		{
			
			int *input = scanner("-i",stdin);
			printf("\n Endereço: %p\n", input);
			printf("\n Valor   : %d\n",*input);
		}
	}
}

