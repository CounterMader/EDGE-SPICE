%option noyywrap yylineno

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "parser.tab.h"
    #include "log.h"

    extern int yyparse();
    extern void yyerror();
%}

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

 //Group Identifier
G_ID        [Gg]"2"

 //End token
END         ^".END"

 //Simulator tyoe token
DC          ^".DC"
TRAN        ^".TRAN"
AC          ^".AC"

 //Source Type
DC_S        "DC"
AC_S        "AC"
SINE_S      "SINE"
PULSE_S     "PULSE"
RAMP_S      "RAMP"
STEP_S      "STEP"

 //Output tokens
PLOT        ^".PLOT"
ELEMENT      ("I"{ELM_ID}|"V"{ELM_ID}|"E"{ELM_ID}|"F"{ELM_ID}|"G"{ELM_ID}|"H"{ELM_ID}|"R"{ELM_ID}|"L"{ELM_ID}|"C"{ELM_ID})

%%
"%".*$                  {/*Comment*/}
{WS}                    {/*Ignore*/}

"("                     {
                            return '(';
                        }
")"                     {
                            return ')';
                        }
"\n"                    {
                            return '\n';
                        }

^"R"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return RE_T;
                        }

^"C"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return CE_T;
                        }

^"L"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return LE_T;
                        }

^"E"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return EE_T;
                        }

^"F"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return FE_T;
                        }

^"G"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return GE_T;
                        }

^"H"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return HE_T;
                        }

^"V"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return VE_T;
                        }

^"I"{ELM_ID}/{WS}       {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return IE_T;
                        }
{ELEMENT}               {
                            yylval.sv = (char *)malloc(yyleng * sizeof(char));
                            strcpy(yylval.sv, yytext);
                            return ELM_T;
                        }
{NUM}+                  {
                            yylval.iv = atoi(yytext);
                            return INT_T;
                        }

{DEC}                   {
                            yylval.dv = atof(yytext);
                            return DEC_T;
                        }

{DEC}/{PREFIX}          {
                            yylval.dv = atof(yytext);
                            BEGIN PRE_INPUT;
                            return DEC_T;
                        }

<PRE_INPUT>{PREFIX}        {
                                switch(*yytext){
                                    case 'f':   yylval.dv = 1e-15; break;
                                    case 'p':   yylval.dv = 1e-12; break;
                                    case 'n':   yylval.dv = 1e-9;  break;
                                    case 'u':   yylval.dv = 1e-6;  break;
                                    case 'm':   yylval.dv = 1e-3;  break;
                                    case 'c':   yylval.dv = 1e-2;  break;
                                    case 'k':   yylval.dv = 1e+3;  break;
                                    case 'K':   yylval.dv = 1e+3;  break;
                                    case 'M':   yylval.dv = 1e+6;  break;
                                    case 'G':   yylval.dv = 1e+9;  break;
                                    case 'T':   yylval.dv = 1e+12; break;
                                    case 'P':   yylval.dv = 1e+15; break;
                                }
                                BEGIN INITIAL;
                                return PREF_T;
                            }


{G_ID}                      {
                                return G2_T;
                            } 

{DC_S}                      {
                                return DC_T;
                            }

{AC_S}                      {
                                return AC_T;
                            } 

{STEP_S}                    {
                                return STEP_T;
                            } 

{RAMP_S}                    {
                                return RAMP_T;
                            }  

{SINE_S}                    {
                                return SINE_T;
                            } 

{PULSE_S}                   {
                                return PULSE_T;
                            }               

{DC_S}                      {
                                return DC_T;
                            }                                                                                         
{DC}                        {
                                return DS_T;
                            }

{TRAN}                      {
                                return TS_T;
                            }
{AC}                        {
                                return AS_T;
                            }
{PLOT}                      {
                                return PLT_T;
                            }
{END}                       {
                                return END_T;
                            }
.                           {yyerror("ERROR!, %c in line %d", *yytext, yylineno);}
%%