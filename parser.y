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

%token <sv> RE_T CE_T LE_T EE_T FE_T GE_T HE_T VE_T IE_T ELM_T
%token <iv> INT_T
%token <dv> DEC_T PREF_T
%token TS_T DS_T AS_T G2_T END_T DC_T AC_T SINE_T PULSE_T RAMP_T STEP_T PLT_T
%type <dv> value

%define parse.error verbose

%%
netlist:
    | netlist statement
    | netlist END_T
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
    | plot
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
      RE_T INT_T INT_T value {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,1);
        log_trace("Resistor : %s ,node %d --> %d ,value = %.16f OHM.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    | RE_T INT_T INT_T value G2_T {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,2);
        log_trace("Resistor : %s ,node %d --> %d ,value = %.16f OHM.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

capacitor:
      CE_T INT_T INT_T value {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,1);
        log_trace("Capacitor : %s ,node %d --> %d ,value = %.16f FARAD.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    | CE_T INT_T INT_T value G2_T {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,2);
        log_trace("Capacitor : %s ,node %d --> %d ,value = %.16f FARAD.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

inductor:
      LE_T INT_T INT_T value {
        add_node($2);
        add_node($3);
        add_RLC($1,$2,$3,$4,2);
        log_trace("Inductor : %s ,node %d --> %d ,value = %.16f Henry.",$1,$2,$3,$4);
        free($1);   //DeAllocating sv memory which we allocatd in lexer
    }
    ;

current_source:
        IE_T INT_T INT_T value {
            add_node($2);
            add_node($3);
            add_I($1,$2,$3,$4,1);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",$1,$2,$3,$4);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T DC_T value {
            add_node($2);
            add_node($3);
            add_I($1,$2,$3,$5,1);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",$1,$2,$3,$5);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T AC_T value value {
            add_node($2);
            add_node($3);
            add_ac_i($1,$2,$3,$5,$6,1);
            log_trace("AC Current Source : %s ,node %d --> %d ,amp = %f A, phase = %f deg.",$1,$2,$3,$5,$6);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T SINE_T '(' value value value value value value ')' {
            add_node($2);
            add_node($3);
            add_sine_i($1,$2,$3,$6,$7,$8,$9,$10,$11,1);
            log_trace("SINE Current Source : %s ,node %d --> %d ,freq = %f, amp = %f, offset = %f, phase = %f, delay = %f A.",$1,$2,$3,$6,$7,$8,$9,$10);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T PULSE_T '(' value value value value value value value ')' {
            add_node($2);
            add_node($3);
            add_pulse_i($1,$2,$3,$6,$7,$8,$9,$10,$11,$12,1);
            log_trace("PULSE Current Source : %s ,node %d --> %d ,Voff = %f, Von = %f, Ton = %f, Tperiod = %f, delay = %f A.",$1,$2,$3,$6,$7,$8,$9,$10);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T RAMP_T '(' value ')' {
            add_node($2);
            add_node($3);
            add_ramp_i($1,$2,$3,$6,1);
            log_trace("RAMP Current Source : %s ,node %d --> %d ,delay = %f s.",$1,$2,$3,$6);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T STEP_T '(' value value ')' {
            add_node($2);
            add_node($3);
            add_step_i($1,$2,$3,$6,$7,1);
            log_trace("DC Current Source : %s ,node %d --> %d ,Von = %f A, delay = %f s.",$1,$2,$3,$6,$7);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T value G2_T {
            add_node($2);
            add_node($3);
            add_I($1,$2,$3,$4,2);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",$1,$2,$3,$4);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T DC_T value G2_T {
            add_node($2);
            add_node($3);
            add_I($1,$2,$3,$5,2);
            log_trace("DC Current Source : %s ,node %d --> %d ,value = %.16f A.",$1,$2,$3,$5);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T AC_T value value G2_T {
            add_node($2);
            add_node($3);
            add_ac_i($1,$2,$3,$5,$6,2);
            log_trace("AC Current Source : %s ,node %d --> %d ,amp = %f A, phase = %f deg.",$1,$2,$3,$5,$6);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T SINE_T '(' value value value value value value ')' G2_T {
            add_node($2);
            add_node($3);
            add_sine_i($1,$2,$3,$6,$7,$8,$9,$10,$11,2);
            log_trace("SINE Current Source : %s ,node %d --> %d ,freq = %f, amp = %f, offset = %f, phase = %f, delay = %f A.",$1,$2,$3,$6,$7,$8,$9,$10);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T PULSE_T '(' value value value value value value value ')' G2_T{
            add_node($2);
            add_node($3);
            add_pulse_i($1,$2,$3,$6,$7,$8,$9,$10,$11,$12,2);
            log_trace("PULSE Current Source : %s ,node %d --> %d ,Voff = %f, Von = %f, Ton = %f, Tperiod = %f, delay = %f A.",$1,$2,$3,$6,$7,$8,$9,$10);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T RAMP_T '(' value ')' G2_T {
            add_node($2);
            add_node($3);
            add_ramp_i($1,$2,$3,$6,2);
            log_trace("RAMP Current Source : %s ,node %d --> %d ,delay = %f s.",$1,$2,$3,$6);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   IE_T INT_T INT_T STEP_T '(' value value ')' G2_T {
            add_node($2);
            add_node($3);
            add_step_i($1,$2,$3,$6,$7,2);
            log_trace("DC Current Source : %s ,node %d --> %d ,Von = %f A, delay = %f s.",$1,$2,$3,$6,$7);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    ;

voltage_source:
        VE_T INT_T INT_T value {
            add_node($2);
            add_node($3);
            add_V($1,$2,$3,$4);
            log_trace("DC Voltage Source : %s ,node %d --> %d ,value = %.16f V.",$1,$2,$3,$4);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   VE_T INT_T INT_T DC_T value {
            add_node($2);
            add_node($3);
            add_V($1,$2,$3,$5);
            log_trace("DC Voltage Source : %s ,node %d --> %d ,value = %.16f V.",$1,$2,$3,$5);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   VE_T INT_T INT_T AC_T value value {
            add_node($2);
            add_node($3);
            add_ac_v($1,$2,$3,$5,$6);
            log_trace("AC Voltage Source : %s ,node %d --> %d ,amp = %f V, phase = %f deg.",$1,$2,$3,$5,$6);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   VE_T INT_T INT_T SINE_T '(' value value value value value value ')' {
            add_node($2);
            add_node($3);
            add_sine_v($1,$2,$3,$6,$7,$8,$9,$10,$11);
            log_trace("SINE Voltage Source : %s ,node %d --> %d ,freq = %f, amp = %f, offset = %f, phase = %f, delay = %f V.",$1,$2,$3,$6,$7,$8,$9,$10);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   VE_T INT_T INT_T PULSE_T '(' value value value value value value value ')' {
            add_node($2);
            add_node($3);
            add_pulse_v($1,$2,$3,$6,$7,$8,$9,$10,$11,$12);
            log_trace("PULSE Voltage Source : %s ,node %d --> %d ,Voff = %f, Von = %f, Ton = %f, Tperiod = %f, delay = %f V.",$1,$2,$3,$6,$7,$8,$9,$10);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   VE_T INT_T INT_T RAMP_T '(' value ')' {
            add_node($2);
            add_node($3);
            add_ramp_v($1,$2,$3,$6);
            log_trace("RAMP Voltage Source : %s ,node %d --> %d ,delay = %f s.",$1,$2,$3,$6);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    |   VE_T INT_T INT_T STEP_T '(' value value ')' {
            add_node($2);
            add_node($3);
            add_step_v($1,$2,$3,$6,$7);
            log_trace("STEP Voltage Source : %s ,node %d --> %d ,Von = %f V, delay = %f s.",$1,$2,$3,$6,$7);
            free($1);   //DeAllocating sv memory which we allocatd in lexer
        }
    ;
voltage_controled_voltage_source:
    EE_T INT_T INT_T INT_T INT_T value {
        add_node($2);
        add_node($3);
        add_node($4);
        add_node($5);
        add_VCVS($1, $2, $3, $4, $5, $6, 2);
        log_trace("VCVS : %s ,control : %d --> %d ,out : %d --> %d ,value = %.16f",$1, $2, $3, $4, $5, $6);
        free($1);
    }
voltage_controled_current_source:
    GE_T INT_T INT_T INT_T INT_T value {
        add_node($2);
        add_node($3);
        add_node($4);
        add_node($5);
        add_VCCS($1, $2, $3, $4, $5, $6, 1);
        log_trace("VCCS : %s ,control : %d --> %d ,out : %d --> %d ,value = %.16f",$1, $2, $3, $4, $5, $6);
        free($1);
    }
current_controled_voltage_source:
    HE_T INT_T INT_T ELM_T value {
        if($4[0] != 'V'){
            log_fatal("A voltage source must be enterd!");
            exit(EXIT_FAILURE);
        }
        add_node($2);
        add_node($3);
        add_CCCS($1, $4, $2, $3, $5, 2);
        log_trace("CCVS : %s ,control : %s ,out : %d --> %d ,value = %.16f",$1 ,$4 ,$2 ,$3 ,$5);
        free($1);
        free($4);
    }
current_controled_current_source:
    FE_T INT_T INT_T ELM_T value {
        if($4[0] != 'V'){
            log_fatal("A voltage source must be enterd!");
            exit(EXIT_FAILURE);
        }
        add_node($2);
        add_node($3);
        add_CCCS($1, $4, $2, $3, $5, 1);
        log_trace("CCCS : %s ,control : %s ,out : %d --> %d ,value = %.16f",$1 ,$4 ,$2 ,$3 ,$5);
        free($1);
        free($4);
    }
dc:
    DS_T {
        log_trace("DC Analysis Detected!");
        set_simultaor_dc();
    }
    ;
tran:
    TS_T value value {
        log_trace("Transient Analysis Detected!,stop time = %.16f, step = %.16f", $2, $3);
        set_simultaor_tran($2, $3);
    }
plot:
      PLT_T INT_T {
        char buff[20];
        sprintf(buff, "%d",$2);
        set_output(buff);
    }
    | PLT_T ELM_T{
        set_output($2);
        free($2);
    }  
value:
      INT_T         {$$ = (double)$1;}
    | DEC_T
    | DEC_T PREF_T  {$$ = $1 * $2;}
    ; 
%%