#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "log.h"
#include "source.h"
#include <math.h>
#define PI 3.14159265358979323846

void pulse_src_update(CKTcircuit *circuit, SRC_TAB *stab){
    // Vo -> initial voltage
    // V1 -> peak voltage
    // Td -> initial delay time
    // Tr -> rise time
    // Tf -> fall time
    // Tw -> pulse-width
    // To -> period of wave
    stab -> value = (double *)calloc(circuit -> step_num, sizeof(double));
    double time = 0;
    double	V1, V2, TD, TR, TF, PW, PER;

    V1 = stab -> src_coefficient[pulse_Vo];
    V2 = stab -> src_coefficient[pulse_V1];
    TD = stab -> src_coefficient[pulse_Td];
    TR = stab -> src_coefficient[pulse_Tr];
    TF = stab -> src_coefficient[pulse_Tf];
    PW = stab -> src_coefficient[pulse_Tw];
    PER = stab -> src_coefficient[pulse_To];

    double	basetime = 0;
    time -= TD;
    for(int i = 0;i < circuit -> step_num;i++,time += circuit -> Tstep){
        if(time > PER){
            /* repeating signal - figure out where we are */
            /* in period */
            basetime = PER * floor(time/PER);
            time -= basetime;
        }
        if(time <= 0 || time >= TR + PW + TF){
            stab -> value[i] = V1;
        }
        else if (time >= TR && time <= TR + PW){
            stab -> value[i] = V2;
        }
        else if (time > 0 && time < TR){
            stab -> value[i] = V1 + (V2 - V1) * (time) / TR;
        }
        else{ /* time > TR + PW && < TR + PW + TF */
            stab -> value[i] = V2 + (V1 - V2) * (time - (TR + PW)) / TF;
        }
    }
}

void sine_src_update(CKTcircuit *circuit, SRC_TAB *stab){
    stab -> value = (double *)calloc(circuit -> step_num, sizeof(double));
    #define VO stab -> src_coefficient[sine_Vo]
    #define VA stab -> src_coefficient[sine_Va]
    #define FREQ stab -> src_coefficient[sine_Fo]
    #define TD stab -> src_coefficient[sine_Td]
    #define THETA stab -> src_coefficient[sine_a]
    #define PHI stab -> src_coefficient[sine_phi]
    double time = 0;
    time -= stab -> src_coefficient[sine_Td];
    for(int i = 0;i < circuit -> step_num;i++,time += circuit -> Tstep){
        if(time <= 0){
            stab -> value[i] = VO;
        }
        else{
            stab -> value[i] = VO + VA * sin(2.0 * PI * FREQ * time + PHI) * exp(-(THETA * time));
        }
    }
}

void step_src_update(CKTcircuit *circuit, SRC_TAB *stab){
    stab -> value = (double *)calloc(circuit -> step_num, sizeof(double));
    double time = 0;
    time -= stab -> src_coefficient[step_Td];
    for(int i = 0;i < circuit -> step_num;i++,time += circuit -> Tstep){
        if(time <= 0){
            stab -> value[i] = 0;
        }
        else{
            stab -> value[i] = stab -> src_coefficient[step_V1];
        }
    }
}

void dc_src_update(CKTcircuit *circuit, SRC_TAB *stab){
    stab -> value = (double *)calloc(circuit -> step_num, sizeof(double));
    for(int i = 0;i < circuit -> step_num;i++){
        stab -> value[i] = stab -> src_coefficient[dc_V1];
    }
}

void ramp_src_update(CKTcircuit *circuit, SRC_TAB *stab){
    stab -> value = (double *)calloc(circuit -> step_num, sizeof(double));
    double time = 0;
    time -= stab -> src_coefficient[ramp_Td];
    for (int i = 0; i < circuit -> step_num; i++, time += circuit -> Tstep){
        if(time <= 0){
            stab -> value[i] = 0;
        }
        else{
            stab -> value[i] = time;
        }
    }
    
}

void transient_source_update(CKTcircuit *circuit, HASH_TAB *htab){
    for(int i = 0;i < htab -> s_size;i++){
        if(htab -> s_table[i] == NULL)
            continue;
        SRC_TAB *temp = htab -> s_table[i];
        while(temp){
            switch(temp -> src_type){
                case SINE:
                    sine_src_update(circuit, temp);
                    break;
                case PULSE:
                    pulse_src_update(circuit, temp);
                    break;
                case RAMP:
                    ramp_src_update(circuit, temp);
                    break;
                case STEP:
                    step_src_update(circuit, temp);
                    break;
                case DC:
                    dc_src_update(circuit, temp);
                    break;
                default:
                    break;
            }
            temp = temp -> next;
        }
    }
}