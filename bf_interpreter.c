#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX 30000

/*
 * TO DO:
 * This needs cleaned up in a bad way.
 */
void input(int, char **, char *);
void intrptr(char *s1, int *s2);

int main(int argc, char **argv)
{
    char instr_arr[MAX*sizeof(char)];
    int result_arr[MAX] = {0};

    input(argc, argv, instr_arr);
    intrptr(instr_arr, result_arr);

    return 0;

}

void input(int argc, char **argv, char *s)
{
    FILE *input;
    if (argc > 1) {
        if (!strcmp(argv[1],"-")) {
            input = stdin;
        } else {
            input = fopen(argv[1], "r");
            if (!input) {
                fprintf(stderr, "Unable to open '%s': %s\n",
                        argv[1], strerror(errno));
                exit(EXIT_FAILURE);
            }
        }
    } else {
        input = stdin;
    }
    char c;
    while ( (c=fgetc(input))!=EOF ) {
        if(
                c == '>' ||
                c == '<' ||
                c == '+' ||
                c == '-' ||
                c == '.' ||
                c == ',' ||
                c == '[' ||
                c == ']'
          ) {
            *s=c;
            s++;
        }
    }
}

/*
 * TO DO
 * Stack should be used for the brackets.  My way is dumb.  We'll use this
 * sometime in the near future once the novelty of a working interpreter has
 * worn off.
 */
void intrptr(char *instr_arr, int *result_arr)
{
    int *ptr = result_arr;
    int instr = 0;
    int brackets[MAX];

    int i;
    char c;
    for (i=0; (c=instr_arr[i]); ++i) {
        switch(c) {
            case '>' :
                ++ptr;
                break;
            case '<' :
                --ptr;
                break;
            case '+' :
                ++*ptr;
                break;
            case '-' :
                --*ptr;
                break;
            case '.' :
                putchar(*ptr);
                break;
            case ',' :
                *ptr = getchar(); 
                break;
            case '[' :
                if (*ptr>0) {
                    brackets[instr++]=i; 
                } else {
                    while (instr_arr[i] != ']') ++i;
                }
                break;
            case ']' :
                if (*ptr>0) {
                    i=brackets[--instr]; 
                    --i;
                }
                break;
            default  :
                break;

        }
    }
}

