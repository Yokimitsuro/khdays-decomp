/* NONMATCHING: semantics correct; register-spill tie — the ROM reserves a stack slot and spills
 * the duration temp across the setup (160B), our mwcc keeps it in registers (136B). Not
 * steerable from C. */
/* func_ov006_02055a54 -- request a Mission Mode-screen menu-state transition to state param_1.
 * Duration: 0 if param_2==0, else 1000, but forced to 1 when transitioning to a non-blank state
 * while the current state (ctx+0x94f4) is 0xe. Kicks func_ov006_020551a4; on the blank state
 * (10) also clears ctx+0x956c and resets the shared tween (ctx+0x9544). Returns 0 if no ctx. */
extern void func_ov006_020551a4(unsigned int state, int dur, int c, int d);
extern void func_02035f84(unsigned int *interp);
extern int  data_ov006_02056664;   /* -> Mission Mode-screen context */

int func_ov006_02055a54(unsigned int param_1, int param_2) {
    int dur;
    if (data_ov006_02056664 == 0) {
        return 0;
    }
    dur = (param_2 == 0) ? 0 : 1000;
    if (param_1 != 10 && *(int *)(data_ov006_02056664 + 0x94f4) == 0xe) {
        dur = 1;
    }
    func_ov006_020551a4(param_1, dur, 0, -0x10);
    if (param_1 == 10) {
        *(int *)(data_ov006_02056664 + 0x956c) = 0;
        func_02035f84((unsigned int *)(data_ov006_02056664 + 0x9544));
    }
    return 1;
}
