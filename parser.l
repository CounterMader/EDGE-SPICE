%option noyywrap yylineno

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "parser.tab.h"

    #define  RLC 1
    #define  I_IV 2
    #define  D_IV 3
    #define  SIM 4
    #define  OUT 5

    int node_num = 0;
    int current_elm = 0;
    int value_num = 0;
    extern int yyparse();
    extern void yyerror();
%}

%s INT_INPUT
%s DEC_INPUT
%s PRE_INPUT

WS          [ \t]
EOL         "\n"
 //End of statement ,used in prefix handling
EOS         ({WS}|{EOL}) 
NUM         [0-9]
alph        [a-z]
ALPH        [A-Z]
DEC         [+-]?({NUM}+"."?{NUM}*|{NUM}*"."{NUM}+)
ELM_ID      {NUM}+
NODE_ID     {NUM}+

 //Prefixes
FEMNTO      f
PICO        p
NANO        n
MICRO       u
MILLI       m
CENTI       c
KILO        [kK]
MEGA        M
GIGA        G
TERA        T
PETA        P

PREFIX      ({FEMNTO}|{PICO}|{NANO}|{MICRO}|{MILLI}|{CENTI}|{KILO}|{MEGA}|{GIGA}|{TERA}|{PETA})

%%
"%".*$  {/*Comment*/}
{WS}   {/*Ignore*/}
"\n"    {
        BEGIN INITIAL;
        current_elm = 0;
        node_num = 0;
        value_num = 0;
        return '\n';
        }
        
<INITIAL>^"R"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 2;
                            current_elm = RLC;
                            //printf("There is a resistor named as : %s\n",yytext);
                            return E_R;
                            }
<INITIAL>^"C"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 2;
                            current_elm = RLC;
                            //printf("There is a Capacitor named as : %s\n",yytext);
                            return E_C;
                            }
<INITIAL>^"L"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 2;
                            current_elm = RLC;
                            //printf("There is a Capacitor named as : %s\n",yytext);
                            return E_L;
                            }

<INITIAL>^"I"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 2;
                            current_elm = I_IV;
                            //printf("There is a Current source named as : %s\n",yytext);
                            return E_I;
                            }
<INITIAL>^"V"{ELM_ID}/{WS}  {
                            yylval.sv = malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            BEGIN INT_INPUT;
                            node_num = 2;
                            current_elm = I_IV;
                            //printf("There is a Voltage source named as : %s\n",yytext);
                            return E_V;
                            }

<INT_INPUT>{NUM}+           {
                            yylval.iv = atoi(yytext);
                            //printf("node num:%d is %d\n",node_num,atoi(yytext));
                            if((--node_num) == 0){
                                switch(current_elm){
                                    case RLC:
                                        BEGIN DEC_INPUT;
                                        value_num = 1;
                                    case I_IV:
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
                            //printf("Value num %d of the element is %f \n",value_num,atof(yytext));
                            if((--value_num) == 0){
                                switch(current_elm){
                                    case RLC:
                                    case D_IV:
                                    case I_IV:
                                        BEGIN INITIAL;
                                        current_elm = 0;
                                }
                            }
                            return DECIMAL;
                            }
<DEC_INPUT>{DEC}/{PREFIX}{EOS} {
                            yylval.dv = atof(yytext);
                            BEGIN PRE_INPUT;
                            return DECIMAL;
                            }
<PRE_INPUT>{PREFIX}         {
                            switch(*yytext){
                                case 'f':   yylval.dv = 1e-15; break;
                                case 'p':   yylval.dv = 1e-12; break;
                                case 'n':   yylval.dv = 1e-9; break;
                                case 'u':   yylval.dv = 1e-6; break;
                                case 'm':   yylval.dv = 1e-3; break;
                                case 'c':   yylval.dv = 1e-2; break;
                                case 'k':   yylval.dv = 1e+3; break;
                                case 'K':   yylval.dv = 1e+3; break;
                                case 'M':   yylval.dv = 1e+6; break;
                                case 'G':   yylval.dv = 1e+9; break;
                                case 'T':   yylval.dv = 1e+12; break;
                                case 'P':   yylval.dv = 1e+15; break;
                            }
                            return T_PREFIX;
                            }
.                           {yyerror("ERROR!\n");}
%%
