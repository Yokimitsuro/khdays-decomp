/* func_ov006_020559dc -- start a horizontal wipe to a new title sub-state, ov006.
 * If the title object exists, kicks a scroll animation on the title layer (base+0x9544) from
 * x=-0x10000 to 0 over 1000 units, commits it (func_02035ffc), and latches the pending sub-state
 * id (base+0x94f4 = arg). Returns 1 when started, 0 if there is no title object. */
extern void func_02035fb0(unsigned int *anim, int a, int from, int to, int dur);
extern void func_02035ffc(int anim);
extern int  data_ov006_02056664;

int func_ov006_020559dc(int state) {
    if (data_ov006_02056664 != 0) {
        func_02035fb0((unsigned int *)(data_ov006_02056664 + 0x9544), 0, -0x10000, 0, 1000);
        func_02035ffc(data_ov006_02056664 + 0x9544);
        *(int *)(data_ov006_02056664 + 0x94f4) = state;
        return 1;
    }
    return 0;
}
