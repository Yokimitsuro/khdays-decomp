/* func_ov253_020d182c -- spawn the 8-byte sub-object of kind 0x64 (tick 020d1894, finish
 * 020d1aa0) linked to the actor and its +0x3b8 item, whose bit 1 of +0x5c is cleared. */
extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov253_020d1894(void);
extern void func_ov253_020d1aa0(void);

int func_ov253_020d182c(int self) {
    int *out;
    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 8, func_ov253_020d1894, func_ov253_020d1aa0, &out);
    out[0] = self;
    out[1] = *(int *)(self + 0x3b8);
    *(int *)(out[1] + 0x5c) &= ~2;
    return rc;
}
