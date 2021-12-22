// Function to scan stdinput
void *scanner(char flag, FILE *file)
{
  if (flag == 'f')
  {
    printf("\n Flag not yet available");
    return NULL;
  }

  else if (flag == 'i')
  {
    char reader;
    int halt = 1;
    int *output = malloc(sizeof(int));
    *output = 0; 

    while (EOF != (reader = fgetc(file)) && reader != '\n')
    {
      if (reader != '0' && halt != 0)
        halt = 0; // ignore starting zeros.

      if (halt != 1)
      {
        if (reader >= 48 && reader <= 57)
          reader -= 48;

        *output *= 10;
        *output += reader;
      }
    }

    return output;
  }

  else if (flag == 's')
  {

    int halt = 1;
    char *output;
    size_t counter = 0;
    output = malloc(sizeof(char) * 1);

    while (EOF != (output[counter] = fgetc(file)) && output[counter] != '\n')
    {
      if (output[counter] != '0' && halt != 0)
        halt = 0; //ignore starting zeros
                  //strings could actually take them, but i'll make a flag
                  //later on for this, currently it's mainly about reading hexa.

      if (halt != 1)
        output = realloc(output, sizeof(char) * ((counter += 1) + 1));
    }

    output[counter] = '\0';
    return output;
  }

  else
  {
    return NULL;
  }
}

