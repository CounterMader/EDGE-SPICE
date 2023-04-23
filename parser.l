%option noyywrap yylineno

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "parser.tab.h"
    #include "log.h"

    #define  RLC        1
    #define  I_IV       2
    #define  D_IV_EG    3
    #define  D_IV_FH    4
    #define  SIM_DC     5
    #define  SIM_TRAN   6
    #define  SIM_AC     7

    int node_num = 0;
    int current_elm = 0;
    int value_num = 0;
    int control_parameter_num = 0;
    extern int yyparse();
    extern void yyerror();
%}

%s INT_INPUT
%s DEC_INPUT
%s PRE_INPUT
%s ELM_INPUT

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

[Gg]"2"                     {
                                return G2;
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
<INITIAL>^"E"{ELM_ID}/{WS}  {
                                yylval.sv = malloc(yyleng * sizeof(char));
                                strcpy(yylval.sv, yytext);
                                BEGIN INT_INPUT;
                                node_num = 4;
                                current_elm = D_IV_EG;
                                //printf("There is a Voltage source named as : %s\n",yytext);
                                return VCVS;
                            }
<INITIAL>^"F"{ELM_ID}/{WS}  {
                                yylval.sv = malloc(yyleng * sizeof(char));
                                strcpy(yylval.sv, yytext);
                                BEGIN INT_INPUT;
                                node_num = 2;
                                current_elm = D_IV_FH;
                                //printf("There is a Voltage source named as : %s\n",yytext);
                                return CCCS;
                            }
<INITIAL>^"G"{ELM_ID}/{WS}  {
                                yylval.sv = malloc(yyleng * sizeof(char));
                                strcpy(yylval.sv, yytext);
                                BEGIN INT_INPUT;
                                node_num = 4;
                                current_elm = D_IV_EG;
                                //printf("There is a Voltage source named as : %s\n",yytext);
                                return VCCS;
                            }
<INITIAL>^"H"{ELM_ID}/{WS}  {
                                yylval.sv = malloc(yyleng * sizeof(char));
                                strcpy(yylval.sv, yytext);
                                BEGIN INT_INPUT;
                                node_num = 2;
                                current_elm = D_IV_FH;
                                //printf("There is a Voltage source named as : %s\n",yytext);
                                return CCVS;
                            }

<INT_INPUT>{NUM}+           {
                                yylval.iv = atoi(yytext);
                                //printf("node num:%d is %d\n",node_num,atoi(yytext));
                                if((--node_num) == 0){
                                    switch(current_elm){
                                        case RLC:
                                            BEGIN DEC_INPUT;
                                            value_num = 1;
                                            break;
                                        case I_IV:
                                            BEGIN DEC_INPUT;
                                            value_num = 1;
                                            break;
                                        case D_IV_EG:
                                            BEGIN DEC_INPUT;
                                            value_num = 1;
                                            break;
                                        case D_IV_FH:
                                            BEGIN ELM_INPUT;
                                            break;
                                        
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
                                        case D_IV_EG:
                                        case D_IV_FH:
                                        case I_IV:
                                        case SIM_TRAN:
                                            BEGIN INITIAL;
                                            current_elm = 0;
                                            break;
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
<ELM_INPUT>"V"{ELM_ID}      {
                                yylval.sv = malloc(yyleng * sizeof(char));
                                strcpy(yylval.sv, yytext);
                                value_num = 1;
                                BEGIN DEC_INPUT;
                                return V_CONT;
                            }
<INITIAL>".DC"              {
                                return DC;
                            }
<INITIAL>".TRAN"            {
                                value_num = 2;
                                current_elm = SIM_TRAN;
                                BEGIN DEC_INPUT;
                                return TRAN;
                            }                            
<INITIAL>".END"             {
                                return END;
                            }
.                           {yyerror("ERROR!\n");}
%%