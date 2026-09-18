/* Node initialiser of the ov241 enemy (x3: ov241/242/243): resets the actor's +0x1c6 state and
 * +0x1c7 sub-state request, clears the +4/+8 heading pair (chained, which pins the zero's
 * register), points +0xc at the actor's +0xb0 pose and installs the three slot handlers
 * (1: 020d075c, 0: 020d0514, 2: 020d06ec). */
extern void func_0203c634(void *obj, int idx, void *value);
extern void func_ov243_020d4208(void);
extern void func_ov243_020d3fe4(void);
extern void func_ov243_020d4198(void);
void func_ov243_020d3f70(int *node) {
    int *state = (int *)node[1];
    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = 0xff;
    state[2] = state[1] = 0;
    state[3] = *state + 0xb0;
    func_0203c634(node, 1, func_ov243_020d4208);
    func_0203c634(node, 0, func_ov243_020d3fe4);
    func_0203c634(node, 2, func_ov243_020d4198);
}
