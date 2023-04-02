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


%token <sv> E_R E_C E_L E_I E_V 
%token <dv> DECIMAL T_PREFIX
%token <iv> INTEGER
%type <dv> value

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
    | inductor
    | current_source
    | voltage_source
    ;

resistor:
    E_R INTEGER INTEGER value {
        printf("Resistor : %s ,node %d --> %d ,value = %f OHM.\n",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

capacitor:
    E_C INTEGER INTEGER value {
        printf("Capacitor : %s ,node %d --> %d ,value = %f FARAD.\n",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

inductor:
    E_L INTEGER INTEGER value {
        printf("Inductor : %s ,node %d --> %d ,value = %f Henry.\n",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

current_source:
    E_I INTEGER INTEGER value {
        printf("Current Source : %s ,node %d --> %d ,value = %f A.\n",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

voltage_source:
    E_V INTEGER INTEGER value {
        printf("Voltage Source : %s ,node %d --> %d ,value = %f V.\n",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;
value:
      DECIMAL
    | DECIMAL T_PREFIX  {$$ = $1 * $2;}
    ; 
%%
