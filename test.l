%option noyywrap yylineno

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "test.tab.h"

    #define  RLC 1
    #define  I_IV 2
    #define  D_IV 3
    #define  SIM 4
    #define  OUT 5

    int node_num = 0;
    int current_elm = 0;
    int value_num = 0;
    extern int yyparse();
%}

%s INT_INPUT
%s DEC_INPUT
WS          [ \t]
NUM         [0-9]
alph        [a-z]
ALPH        [A-Z]
DEC         [+-]?({NUM}+"."?{NUM}*|{NUM}*"."{NUM}+)
ELM_ID      {NUM}+
NODE_ID     {NUM}+
%%
"%".*$  {/*Comment*/}
{WS}   {/*Ignore*/}
"\n"    {
        BEGIN INITIAL;
        current_elm = 0;
        node_num = 0;
        value_num = 0;
        printf("There is a newline!\n");
        return '\n';
        }
        
<INITIAL>^"R"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 2;
                            current_elm = RLC;
                            printf("There is a resistor named as : %s\n",yytext);
                            return E_R;
                            }
<INITIAL>^"C"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 2;
                            current_elm = RLC;
                            printf("There is a Capacitor named as : %s\n",yytext);
                            return E_C;
                            }
<INITIAL>^"G"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 4;
                            current_elm = D_IV;
                            printf("There is a VCCS named as : %s\n",yytext);
                            return E_G;
                            }

<INT_INPUT>{NUM}+           {
                            yylval.iv = atoi(yytext);
                            printf("node num:%d is %d\n",node_num,atoi(yytext));
                            if((--node_num) == 0){
                                switch(current_elm){
                                    case RLC:
                                        BEGIN DEC_INPUT;
                                        value_num = 1;
                                    case D_IV:
                                        BEGIN DEC_INPUT;
                                        value_num = 2;
                                }
                            }
                            return INTEGER;
                            }
<DEC_INPUT>{DEC}            {
                            yylval.dv = atof(yytext);
                            printf("Value num %d of the element is %f \n",value_num,atof(yytext));
                            if((--value_num) == 0){
                                switch(current_elm)
                                    case RLC:
                                    case D_IV:
                                        BEGIN INITIAL;
                                        current_elm = 0;
                            }
                            return DECIMAL;
                            }
.                           {printf("ERROR!\n");}
%%

void yyerror(char *msg){
    printf("%s\n",msg);
}
int main(int argc, char **argv){
    if(argc > 1){
        if(!(yyin = fopen(argv[1],"r"))){
            printf("Can't open the file!");
            return 1;
        }
    }

    yyparse();
    return 0;
}
