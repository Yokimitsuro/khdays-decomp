/* func_ov006_020552ac -- Mission Mode: enter menu page 1.
 * Resets the page's resource block at OBJ+8, reloads it from data_ov006_02056598, rebuilds
 * layer 0 and layer 1, re-applies the current Mission Mode sub-state (OBJ+0x94f4) to the model and
 * the text, and starts the page-1 entry animation. */
extern void func_ov006_0204d4e4(int *block);
extern void func_ov006_0204d160(int block, int desc);
extern void func_ov006_02053cdc(int layer, int a, int b);
extern void func_ov006_020538a4(int state);
extern void func_ov006_0205227c(int state);
extern void func_ov006_020551a4(int anim, int a, int b, int c, int d);
extern int *data_ov006_02056664;
extern int  data_ov006_02056598;

void func_ov006_020552ac(void) {
    func_ov006_0204d4e4((int *)((char *)data_ov006_02056664 + 8));
    func_ov006_0204d160((int)((char *)data_ov006_02056664 + 8), (int)&data_ov006_02056598);
    func_ov006_02053cdc(0, 0, 0);
    func_ov006_02053cdc(1, 0, 0);
    func_ov006_020538a4(*(int *)((char *)data_ov006_02056664 + 0x94f4));
    func_ov006_0205227c(*(int *)((char *)data_ov006_02056664 + 0x94f4));
    func_ov006_020551a4(1, 0, 0, 0, 0);
}
