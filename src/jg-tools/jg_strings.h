// Arquivo para agrupar funções referentes à:
// strings
// conversões
// vetores

#ifndef JGROUP_H
#define JGROUP_H
    // funções existentes
    //j_string.h
    int str_len(char *string);
    char *str_copy(char *array);
    char *str_crop(unsigned int start, unsigned int end, char *str1);
    void str_mov(unsigned int i, char *str1, char *str2);
    int str_match(char *str1, char *str2);

    //j_arrays.h
    int *cpy_array(int *array, int tam);
    void clr_array(int *array, int tam);
    void inv_array(int *array, int tam);

    //j_transform.h
    char* to_str(int *array, int tam);
    char *ret_str(int num);
    unsigned ret_uns(char *str1);
    int ret_int(char *str1);

    //j_math.h
    int int_pow(int num1, int base);
    int int_sqr(int num1);
    int int_fat(int num1);
    int int_log(int num1, int base);
    int int_mod(int num1, int num2);

    #include "j_strings.h"
    #include "j_arrays.h"
    #include "j_transform.h"
    #include "j_math.h"
#endif 