#ifndef STATES_H_
#define STATES_H_
enum mission_state {
    NAV_CONVERGE,
    PAD_IDLE,
    ASCENT,
    APOGEE,
    DESCENT,
    LANDED
};
// ------------------ State Change Thresholds ------------------
#define PI_TO_ASCENT_THRESHOLD 50   // ft
#define ASCENT_TO_APOGEE_THRESHOLD -1 // ft/s
#define ASCENT_TO_APOGEE_SUSTAIN 0.5 // s of threshold met to change state
#define APOGEE_TO_DESCENT_DROGUE_THRESHOLD true // drogue deployed
#define DROGUE_TO_DESCENT_MAIN_THRESHOLD 20 // ft/s
#define DROGUE_TO_DESCENT_MAIN_SUSTAIN 0.5 // s of threshold met to change state
#define DESCENT_TO_LANDED_THRESHOLD 0 // ft/s or more specifically, vertical velocity is zero
#define DESCENT_TO_LANDED_SUSTAIN 0.5 // s of threshold met to change state   




// ------------------ State Functions ------------------

void state_nav_converge();
void state_pad_idle();
void state_ascent();
void state_apogee();
void state_descent_drogue();
void state_descent_main();
void state_landed();
void state_recovery();

#endif //STATES_H_