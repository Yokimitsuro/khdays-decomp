/* Pick the next strafe direction: turn the stored angle into a table index, read the sin/cos
 * pair, and slew the heading at rate 0x300. Then, unless the busy byte at state[0x11] says
 * otherwise, roll a d100 and set the action byte to 6 on a low roll or 5 otherwise.
 *
 * Three details are load-bearing: the y component is written BETWEEN the two table reads (the
 * ROM materialises its zero before the multiply), the d100 goes through the documented
 * `func_02023eb4(N) + (v - v)` copy artifact with an uninitialised scratch and a K&R extern,
 * and the 6/5 choice is an if/else -- as a ternary mwcc colours the pair r2/r1 instead of r1/r0.
 *
 * One of five byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;

extern void func_01ffa724(int a, void *b, void *c);
extern int func_02023eb4();
extern void func_0203c634(void *node, int idx, void *cb);
extern short data_0203d210[];

void func_ov143_020d4a5c(int *node) {
    int *state = (int *)node[1];
    VecFx32 v;
    int a;
    int roll;
    int scratch;

    a = (int)(unsigned short)((unsigned int)(((long long)state[2] * 0x28be60db9391LL + 0x80000000000LL) >> 32) >> 12) >> 4;
    v.x = data_0203d210[a * 2];
    v.y = 0;
    v.z = data_0203d210[a * 2 + 1];
    func_01ffa724(0x300, &v, state + 6);
    if (*(unsigned char *)state[0x11] != 0) {
        return;
    }
    roll = func_02023eb4(0x65) + (scratch - scratch);
    if (roll < 0x28) {
        *(char *)(state[0] + 0x1c7) = 6;
    } else {
        *(char *)(state[0] + 0x1c7) = 5;
    }
    func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
}
