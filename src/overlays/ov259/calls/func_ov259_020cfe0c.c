/* If the +0x21a gauge has drained, dispatch 020d16d4; otherwise, unless busy, latch sub-state 2. */
extern int func_0203c634(int, int, void *);
extern int func_ov259_020d16d4(int);
void func_ov259_020cfe0c(int param_1) {
    int owner = *(int *)(param_1 + 4);
    int obj = *(int *)owner;
    if ((short)*(short *)(obj + 0x21a) <= 0) {
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), (void *)&func_ov259_020d16d4);
    } else {
        if (*(unsigned char *)(*(int *)(owner + 4) + 0xad) != 0) return;
        *(unsigned char *)(obj + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
    }
}
