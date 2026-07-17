/* NONMATCHING: semantics correct; register-placement tie -- the ROM parks the return value 0 in
 * r0 up front and computes the guard in r1, mwcc uses r0 for the ctx load and sets 0 predicated.
 * Not steerable via a result local. Same class as func_ov006_02058bac. */
/* func_ov006_0204e35c -- Mission Mode "start" gate: 0 while busy (ctx+0x49c) or until func_ov105_020bf5a8
 * fires; when it fires return the next handler func_ov006_0204e300, else latch ctx+0x4f0 = 1. */
extern int  func_ov105_020bf5a8(void);
extern void func_ov006_0204e300(void);
extern int  data_ov006_020565e4;   /* -> Mission Mode-screen context */

int func_ov006_0204e35c(void) {
    int result = 0;
    if (*(int *)(data_ov006_020565e4 + 0x49c) != 0) {
        return result;
    }
    if (func_ov105_020bf5a8() != 0) {
        return (int)func_ov006_0204e300;
    }
    *(unsigned char *)(data_ov006_020565e4 + 0x4f0) = 1;
    return result;
}
