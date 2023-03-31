%{
    #include <stdio.h>
    #include <stdlib.h>

    extern int yylex();
    extern void yyerror();

%}

%union{
    char *sv;
    double dv;
    int iv;
}


%token <sv> E_R E_C E_G
%token <dv> DECIMAL
%token <iv> INTEGER

%error-verbose

%%
netlist:
    | netlist statement
    ;
statement:
    | element '\n'
    | element YYEOF
    | '\n'
    ;
element:
      resistor
    | capacitor
    | vccs
    ;
resistor:
    E_R INTEGER INTEGER DECIMAL {
        printf("resistor recognized!\n");
    }
    ;
capacitor:
    E_C INTEGER INTEGER DECIMAL {
        printf("Capacitor recognized!\n");
    }
    ;
vccs:
    E_G INTEGER INTEGER INTEGER INTEGER DECIMAL DECIMAL {
        printf("vccs recognized!\n");
    }
    ;
%%
