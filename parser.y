%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "log.h"
    #include "parser.h"
    extern int yylex();
    extern void yyerror();

%}

%union{
    char *sv;
    double dv;
    int iv;
}


%token <sv> E_R E_C E_L E_I E_V VCCS VCVS CCVS CCCS
%token <dv> DECIMAL T_PREFIX
%token <iv> INTEGER
%token END G2 DC TRAN
%type <dv> value


%define parse.error verbose
%%
netlist:
    | netlist statement
    | netlist END
    ;
statement:
    | element '\n'
    | control '\n'
    | element YYEOF
    | '\n'
    ;

control:
      dc
    | tran
    ;

element:
      resistor
    | capacitor
    | inductor
    | current_source
    | voltage_source
    | voltage_controled_voltage_source
    | voltage_controled_current_source
    | current_controled_voltage_source
    | current_controled_current_source
    ;

resistor:
      E_R INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,1);
        log_trace("Resistor : %s ,node %d --> %d ,value = %f OHM.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    | E_R INTEGER INTEGER value G2 {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,2);
        log_trace("Resistor : %s ,node %d --> %d ,value = %f OHM.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

capacitor:
      E_C INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,1);
        log_trace("Capacitor : %s ,node %d --> %d ,value = %f FARAD.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    | E_C INTEGER INTEGER value G2 {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,2);
        log_trace("Capacitor : %s ,node %d --> %d ,value = %f FARAD.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

inductor:
      E_L INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,2);
        log_trace("Inductor : %s ,node %d --> %d ,value = %f Henry.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

current_source:
      E_I INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_I($1,$2,$3,$4,1);
        log_trace("Current Source : %s ,node %d --> %d ,value = %f A.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    | E_I INTEGER INTEGER value G2 {
        add_node($2);
        add_node($3);
        add_I($1,$2,$3,$4,2); 
        log_trace("Current Source : %s ,node %d --> %d ,value = %f A.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

voltage_source:
    E_V INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_V($1,$2,$3,$4);
        log_trace("Voltage Source : %s ,node %d --> %d ,value = %f V.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;
voltage_controled_voltage_source:
    VCVS INTEGER INTEGER INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_node($4);
        add_node($5);
        add_VCVS($1, $2, $3, $4, $5, $6, 2);
        log_trace("VCVS : %s ,control : %d --> %d ,out : %d --> %d ,value = %f",$1, $2, $3, $4, $5, $6);
        free($1);
    }
voltage_controled_current_source:
    VCCS INTEGER INTEGER INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_node($4);
        add_node($5);
        add_VCCS($1, $2, $3, $4, $5, $6, 1);
        log_trace("VCCS : %s ,control : %d --> %d ,out : %d --> %d ,value = %f",$1, $2, $3, $4, $5, $6);
        free($1);
    }
current_controled_voltage_source:
    CCVS INTEGER INTEGER INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_node($4);
        add_node($5);
        log_trace("CCVS : %s ,control : %d --> %d ,out : %d --> %d ,value = %f",$1, $2, $3, $4, $5, $6);
        free($1);
    }
current_controled_current_source:
    CCCS INTEGER INTEGER INTEGER INTEGER value {
        add_node($2);
        add_node($3);
        add_node($4);
        add_node($5);
        log_trace("CCCS : %s ,control : %d --> %d ,out : %d --> %d ,value = %f",$1, $2, $3, $4, $5, $6);
        free($1);
    }
dc:
    DC {
        log_trace("DC Analysis Detected!");
        set_simultaor_dc();
    }
    ;
tran:
    TRAN value value {
        log_trace("Transient Analysis Detected!,stop time = %lf, step = %lf", $2, $3);
        set_simultaor_tran($2, $3);
    }
value:
      DECIMAL
    | DECIMAL T_PREFIX  {$$ = $1 * $2;}
    ; 
%%