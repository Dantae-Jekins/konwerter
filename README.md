### README.md
# KONWERTER

Konwerter.c should not be considered since it's an older version.

Konwerter_1.c is a newer one with the intent to be more readable and easier to fix.

I know i can change numeric systems easily with other functions, but this is a
training for me.

And finally, you're not supposed to understand what's in here, if you do, either ur a genius or you think you are and got everything wrong.

## Done

- main function numeric system caller
- input reader for char/int arrays with dynamic memory allocation  

## To fix

- realloc(num, sizeof(*num)*count) returning wrong values ;

## To do

The examples listed should not be functional, and syntax may be wrong, i mean, it's just an idea grouping.
- numeric systems change ideas
    -
    - mult function planning examples
    ```c
        // YEA I KNOW I DIDNT DECLARE THE FUNCTION TYPES (int chars etc)

        binhex(int *input){ 
        /* 
            1. bin to dec

            find int array size to count down later, ends with '\n'.
            maybe for(size_t size, array[size]!='\n', size++)?

            extract the binary array and apply math to it while counting 
            down, apply the function (input[size--]* 2 ^ count++), 
            while summing the results to extract the decimal number.

            2.dec to hex

            divide the decimal number by 16 in a loop until it's less than
            16 with the intent to find out the size so we can alocate
            memory dynamically; maybe for(size_t size; dec<16; dec/=16, size++)?

            then do the same thing, but now adding the rest values (%16) to a 
            char array while counting down, also changing the values "10, 
            11, 12, 13, 14, 15" to "A, B, C, D, E, F" (i'll think about how
            im going to do this later)

                *REMEMBER TO ADD +'\0' TO CONVERT INTEGERS INTO CHARS
                *change option? if(dec%16==10){ hexchar[size++]='A'}? 
            
            return the hex char array POINTER
            (char array should be a pointer so i can use it in other functions)
            
        */


        }

        binoct(int *input){

        /* 
            1. bin to dec

            find int array size to count down later, ends with '\n'.
            maybe for(size_t size, array[size]!='\n', size++)?

            extract the binary array and apply math to it while counting 
            down, apply the function (input[size--]* 2 ^ count++), 
            while summing the results to extract the decimal number.

            2.dec to oct

            divide the decimal number by 8 in a loop until it's less than
            8 with the intent to find out the size so we can alocate
            memory dynamically; maybe for(size_t size; dec<8; dec/=8, size++)?

            then do the same thing, but now adding the rest values (%8) to a 
            int array. (I always forget where to use an/a, sowwy D': )
            
            return the oct int array POINTER
            (int array should be a pointer so i can use it in other functions)            
        */
            
        }

        bindec(int *input){
            
        
        /* 
            1. bin to dec

            find int array size to count down later, ends with '\n'.
            maybe for(size_t size, array[size]!='\n', size++)?

            extract the binary array and apply math to it while counting 
            down, apply the function (input[size--]* 2 ^ count++), 
            while summing the results to extract the decimal number.      
        */

        }
    ```
    - single function planning example

    ```c
        //this is SO CONFUSING OH GOD, no

        Konwerter(int in_sys, int out_sys, char *HEXinput, int *input){

        /*
            in_sys could be used to define which type of value is the input,
            like 0 == bin, 1 == octa, etc..

            out_sys then should be the type of the output value.
            
        */

        //switch(in_sys){} ?!?!?!
        //or tons of if's (hate switch so i'll go with ifs)
        if(in_sys==0){
            //binary input
        
            if(out_sys==0){
                //just WHO would try to change binary to binary? like what?
                return *input; 
            }
            if(out_sys==1){
                //octa output
                //do a bunch of math listed in the codes above 
                return octal array 

            }

            // AND A WHOLE BUNCH OF IF AND ELSES (no.)
        }


        }
    ```
  
- Conversions?
    -
    - Just add it inside each function (?)
    - Make a specific functions to do them (?) example:

    ```c
        bindec(int *input){
            // do the bin to dec stuff listed in the codes above
            //return a decimal number in a pointer

            return realloc(dec, sizeof(dec)*size);
        }

        dechex(int *input){
        /*
            intput (haha..) pointer would end up being the previous 
            returned pointer or the one created and written from stdin
        */

            //do the dec to bin stuff listed above
            //return a hexa number in a char pointer
        }
        
        // And then cascade the functions (reason why i think it's the best way)

        binhex(int *input){
            int *intPointer;
            char *charPointer;

            intPointer = bindec(input);
            //should i do bindec(*input) or bindec(input)? gotta research

            //return the char pointer from the previous function

            return dechex(localPointer);
    ```

