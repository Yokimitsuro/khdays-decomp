/* func_ov245_020cf978 -- seed a random dwell (RandNextScaled(0x1f79) + 0x88) at +0x34 and aim the
 * node at the caller's XZ pair (+0x18), then put the owner in state 1. */
extern int func_02023eb4(int scale);
extern int func_020050b4(int a, int b);

void func_ov245_020cf978(int *node, int *arg) {
    node[0xd] = func_02023eb4(0x1f79) + 0x88;
    node[6] = func_020050b4(arg[0], arg[2]);
    *(unsigned char *)(node[0] + 0x1c7) = 1;
}
