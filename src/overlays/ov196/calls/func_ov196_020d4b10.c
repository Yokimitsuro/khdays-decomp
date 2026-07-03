struct v3 { int a, b, c; };
struct b1 { unsigned char b : 1; };
extern void func_01ffa724(int scale, void *v, void *out);
extern void func_0203c634(void *obj, int idx, void *value);

void func_ov196_020d4b10(int *node) {
    int *state = (int *)node[1];
    *(struct v3 *)(state + 6) = *(struct v3 *)(state + 9);
    func_01ffa724(0xb00, state + 9, state + 9);
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    if (((struct b1 *)(*state + 0x17a))->b || ((struct b1 *)(*state + 0x17c))->b) {
        state[0x11] = 3;
        *(signed char *)(*state + 0x1c7) = 2;
        func_0203c634(node, *(signed char *)(node + 8), (void *)0);
    }
}
