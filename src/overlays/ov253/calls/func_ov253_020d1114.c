/* func_ov253_020d1114 -- spawn the 0x28-byte sub-object of kind 0x64 (tick 020d1170, finish
 * 020d1220) linked to the actor, seeded with the +0x3b0 item's +8 handle. */
extern int func_0203c5c0(int scene, int kind, int size, void *cb, void *cb2, int **out);
extern void func_ov253_020d1170(void);
extern void func_ov253_020d1220(void);

int func_ov253_020d1114(int self) {
    int *out;
    int rc = func_0203c5c0(*(int *)(self + 0x3c), 100, 0x28, func_ov253_020d1170, func_ov253_020d1220, &out);
    out[0] = self;
    out[1] = *(int *)(*(int *)(out[0] + 0x3b0) + 8);
    return rc;
}
