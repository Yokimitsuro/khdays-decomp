struct v3 { int x, y, z; };
extern void func_01ffa724(int scale, void *dst, void *src);
extern void func_0203c634(void *node, int idx, void *value);

void func_ov219_020d120c(int *node) {
    int *state = (int *)node[1];
    *(struct v3 *)((char *)state + 0x24) = *(struct v3 *)((char *)state + 0x30);
    func_01ffa724(0xb00, (char *)state + 0x30, (char *)state + 0x30);
    if (*(unsigned char *)(state[1] + 0xad) != 0) return;
    *(signed char *)(*state + 0x1c7) = 7;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
