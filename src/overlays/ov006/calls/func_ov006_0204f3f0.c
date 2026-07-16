/* func_ov006_0204f3f0 -- Mission Mode: commit or cancel the highlighted menu entry.
 * When the scene reports state 1 the entry is accepted: the scene object moves to the
 * accept state (func_ov006_0204eda4), the 0x3ec-byte selection scratch at obj+0x40 is
 * wiped, the pending-transition slot at obj+0x28 is cleared and the sound is silenced.
 * Otherwise it moves to the cancel state (func_ov006_0204ecdc) and runs the scene tick.
 * Returns whether the entry was accepted. */
extern int  func_02001030(void);
extern void func_02023a44(int scene, int next);
extern void MI_CpuFill8(void *dst, int data, unsigned int size);
extern void func_ov105_020bf8c8(int a);
extern void func_ov006_0204db2c(void);
extern void func_ov006_0204eda4(void);
extern void func_ov006_0204ecdc(void);
extern int  data_ov006_020565e4;

#define OBJ   (*(int **)&data_ov006_020565e4)
#define SCENE (*(int *)((int)&data_ov006_020565e4 + 4))

int func_ov006_0204f3f0(void) {
    int accepted = 0;
    if (func_02001030() == 1) {
        func_02023a44(SCENE, (int)func_ov006_0204eda4);
        MI_CpuFill8((char *)OBJ + 0x40, accepted, 0x3ec);
        OBJ[0xa] = accepted;
        func_ov105_020bf8c8(accepted);
        accepted = 1;
    } else {
        func_02023a44(SCENE, (int)func_ov006_0204ecdc);
        func_ov006_0204db2c();
    }
    return accepted;
}
