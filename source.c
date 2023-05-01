#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "circuit.h"
#include "log.h"
#include "source.h"

struct SINE_s *create_sine_s(double offset, double amplitude, double phase, double freq, double delay){

    struct SINE_s *sine = NULL;

    sine = (struct SINE_s *)malloc(sizeof(struct SINE_s));
    if(sine == NULL){
        log_fatal("SINE source allocaton faield!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    sine -> offset = offset;
    sine -> amplitude = amplitude;
    sine -> phase = phase;
    sine -> freq = freq;
    sine -> delay = delay;

    return sine;
}

struct PULSE_s *create_pulse_s(double v_on, double v_off, double t_on, double t_period, double delay){

    struct PULSE_s *pulse = NULL;

    pulse = (struct PULSE_s *)malloc(sizeof(struct PULSE_s));
    if(pulse == NULL){
        log_fatal("PULSE source allocaton faield!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    pulse -> v_on = v_on;
    pulse -> v_off = v_off;
    pulse -> t_on = t_on;
    pulse -> t_period = t_period;
    pulse -> delay = delay;

    return pulse;
}

struct STEP_s *create_step_s(double v_on, double delay){

    struct STEP_s *step = NULL;

    step = (struct STEP_s *)malloc(sizeof(struct STEP_s));
    if(step == NULL){
        log_fatal("STEP source allocaton faield!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    step -> v_on = v_on;
    step -> delay = delay;

    return step;
}

struct RAMP_s *create_ramp_s(double delay){

    struct RAMP_s *ramp = NULL;

    ramp = (struct RAMP_s *)malloc(sizeof(struct RAMP_s));
    if(ramp == NULL){
        log_fatal("RAMP source allocaton faield!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    ramp -> delay = delay;

    return ramp;
}

struct DC_s *create_dc_s(double value){

    struct DC_s *dc = NULL;

    dc = (struct DC_s *)malloc(sizeof(struct DC_s));
    if(dc == NULL){
        log_fatal("DC source allocaton faield!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    dc -> value = value;

    return dc;
}

struct AC_s *create(double amplitude, double phase){

    struct AC_s *ac = NULL;

    ac = (struct AC_s *)malloc(sizeof(struct AC_s));
    if(ac == NULL){
        log_fatal("AC source allocaton faield!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    ac -> phase = phase;
    ac -> amplitude = amplitude;

    return ac;
}

struct DEPENDENT_s *create_dep_s(double value){

    struct DEPENDENT_s *dep = NULL;

    dep = (struct DEPENDENT_s *)malloc(sizeof(struct DEPENDENT_s));
    if(dep == NULL){
        log_fatal("DEPENDENT source allocaton faield!");
        //safe exit
        exit(EXIT_FAILURE);
    }

    dep -> value = value;

    return dep;
}

void step_src_update(CKTcircuit *circuit, SRC_TAB *stab){
    double tic = 0;

    stab -> value = (double *)calloc(circuit -> step_num, sizeof(double));

    for(int i = 0;i <= circuit -> simulate_type;i++, tic += circuit -> Tstep){
        if(tic >= stab -> step_src -> delay){
            stab -> value[i] = stab -> step_src -> v_on;
        }
    }
}