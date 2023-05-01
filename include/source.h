//Source Type
#define TIME_DOMAIN 0
#define FREQ_DOMAIN 1

//Time Domain source type
#define SINE        2
#define PULSE       3
#define RAMP        4
#define STEP        5
#define DC          6
#define DEPENDENT   7

//Frequency Domain source type
#define AC          8

//Source Type structures
struct SINE_s{
    double offset;
    double amplitude;
    double phase;
    double freq;
    double delay;
};

struct PULSE_s{
    double v_on;
    double v_off;
    double t_on;
    double t_period;
    double delay;
};

struct STEP_s{
    double v_on;
    double delay;
};

struct RAMP_s{
    double delay;
};

struct DC_s{
    double value;
};

struct AC_s{
    double amplitude;
    double phase;
};

struct DEPENDENT_s{
    double value;
};


struct SINE_s *create_sine_s(double offset, double amplitude, double phase, double freq, double delay);
struct PULSE_s *create_pulse_s(double v_on, double v_off, double t_on, double t_period, double delay);
struct STEP_s *create_step_s(double v_on, double delay);
struct RAMP_s *create_ramp_s(double delay);
struct DC_s *create_dc_s(double value);
struct AC_s *create(double amplitude, double phase);
struct DEPENDENT_s *create_dep_s(double value);
void step_src_update(CKTcircuit *circuit, SRC_TAB *stab);