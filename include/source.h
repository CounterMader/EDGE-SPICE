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

//Source coefficient map(index in src_coefficient array)
//Pulse source
#define pulse_Vo          0        //v_off
#define pulse_V1          1        //v_on
#define pulse_Td          2        //delay 
#define pulse_Tr          3        //raise time
#define pulse_Tf          4        //fall time
#define pulse_Tw          5        //pulse width
#define pulse_To          6        //pulse period

//Sine source
#define sine_Vo           0       //offset voltage
#define sine_Va           1       //amplitude voltage
#define sine_Fo           2       //frequency
#define sine_Td           3       //delay
#define sine_a            4       //damping factor
#define sine_phi          5       //phase

//step source
#define step_Td           0       //delay
#define step_V1           1       //v_on

//ramp source
#define ramp_Td           0       //delay

//dc source
#define dc_V1             0       //dc value

//ac source
#define ac_amp            0       //ac amplitude
#define ac_phi            1       //ac phase

//dependent source
#define dep_value         0       //dependent source value


//Function Prototype
void pulse_src_update(CKTcircuit *circuit, SRC_TAB *stab);
void sine_src_update(CKTcircuit *circuit, SRC_TAB *stab);
void step_src_update(CKTcircuit *circuit, SRC_TAB *stab);
void dc_src_update(CKTcircuit *circuit, SRC_TAB *stab);
void ramp_src_update(CKTcircuit *circuit, SRC_TAB *stab);
void transient_source_update(CKTcircuit *circuit, HASH_TAB *htab);