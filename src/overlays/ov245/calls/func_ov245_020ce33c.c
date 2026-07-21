/* Recoil push: scale the owner's facing vector (node[3]) by the negated knockback magnitude
 * (-node[0xc]) into the attacker's push slot (*node+0x4c8, +0x2c). Then, if the target lock
 * (node[1]+0xad) is clear, enter the flinch state (2) and re-register the think callback. */
extern void func_01ffa724(int scale, void *dst, void *src);
extern void func_0203c634(int self, int idx, int cb);

void func_ov245_020ce33c(int param_1) {
    int *node = *(int **)(param_1 + 4);
    func_01ffa724(-node[0xc], (void *)(*(int *)(*node + 0x4c8) + 0x2c), node + 3);
    if (*(unsigned char *)(node[1] + 0xad) != 0) {
        return;
    }
    *(char *)(*node + 0x1c7) = 2;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), 0);
}
