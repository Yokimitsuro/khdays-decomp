/* Ov274_EnterMoveState -- resets the owner's move state (+0x1c6 = 0, +0x1c7 = -1), clears the two
 * +0x40/+0x44 timers, points the state at the owner's +0xb0 / +0x74 blocks and the rig's +0xad busy
 * byte, raises bits 1|2 in the high byte of the owner's +0x60 flags and installs the three slot
 * handlers (1: 020d1458, 0: 020d115c, 2: 020d136c). */
extern void func_0203c634(int node, int slot, void *handler);
extern void func_ov274_020d1458(void);
extern void func_ov274_020d115c(void);
extern void func_ov274_020d136c(void);

void func_ov274_020d10a4(int node)
{
    int *state = *(int **)(node + 4);
    unsigned short w;

    *(signed char *)(*state + 0x1c6) = 0;
    *(signed char *)(*state + 0x1c7) = -1;
    state[0x11] = state[0x10] = 0;
    state[1] = *state + 0xb0;
    state[2] = *state + 0x74;
    state[4] = 0;
    state[3] = *(int *)(*state + 0x384) + 0xad;
    w = *(unsigned short *)(*state + 0x60);
    *(unsigned short *)(*state + 0x60) =
        (unsigned short)((w & ~0xff00)
                         | (((((unsigned int)w << 0x10) >> 0x18 | 6) << 0x18) >> 0x10));
    func_0203c634(node, 1, &func_ov274_020d1458);
    func_0203c634(node, 0, &func_ov274_020d115c);
    func_0203c634(node, 2, &func_ov274_020d136c);
}
