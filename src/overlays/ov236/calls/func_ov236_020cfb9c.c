/* Roll entry: the first time (+0x3c0 latch) both riders (+0x3b4 / +0x3b8) are told to launch
 * through their +0x1cc hook; then, with bit 2 of +0x52 set, the +0x14 lift is 1.0, pose 0 plays
 * (looping) and the +0x28 timer is 8.0, otherwise the lift is 0, pose 0 plays once and the timer
 * is rand(0x2001) + 2.0. The node moves to 020cfc64. */
struct Bits52 { unsigned char b0 : 1, b1 : 1, b2 : 1; };
typedef void (*LaunchHook)(int part, int arg);
extern void func_ov107_020c9264(int a, int b, int c);
extern int  func_02023eb4(int bound);
extern void func_0203c634(void *node, int idx, void *value);
extern void func_ov236_020cfc64(void);

void func_ov236_020cfb9c(int *node) {
    int *state = (int *)node[1];
    if (*(int *)(*state + 0x3c0) == 0) {
        *(int *)(*state + 0x3c0) = 1;
        {
            int rider = *(int *)(*state + 0x3b4);
            LaunchHook hook = *(LaunchHook *)(rider + 0x1cc);
            if (hook != 0) hook(rider, 0);
        }
        {
            int rider = *(int *)(*state + 0x3b8);
            LaunchHook hook = *(LaunchHook *)(rider + 0x1cc);
            if (hook != 0) hook(rider, 0);
        }
    }
    if (((struct Bits52 *)((char *)state + 0x52))->b2 != 0) {
        state[5] = 0x1000;
        func_ov107_020c9264(*state, 0, 1);
        state[0xa] = 0x8000;
    } else {
        state[5] = 0;
        func_ov107_020c9264(*state, 0, 0);
        state[0xa] = func_02023eb4(0x2001) + 0x2000;
    }
    func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov236_020cfc64);
}
