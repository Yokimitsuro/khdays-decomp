struct vec3 { int x, y, z; };

extern int func_ov107_020cab14(int obj, int b);
extern void func_0203c634(int obj, int slot, void *cb);
extern void func_ov107_020c9264(int obj, int anim, int flag);
extern void func_ov107_020c0b90(int obj, int cmd, struct vec3 v, int flag);
extern struct vec3 data_02041dc8;
extern void func_ov179_020d38e8(void);

/* ★ func_ov107_020c9264 takes THREE arguments (obj, anim, flag). This file declared two, and the
 * dropped 0 is the ROM's `mov r2, #0` at +0x28 -- hoisted ABOVE the branch because it serves as the
 * 3rd argument to BOTH arms: func_0203c634's callback in the no-target case, and 020c9264's flag
 * here. With two args that 0 is unaccounted for and the function will not match. (2026-07-17)
 *
 * Begin the "guard/block" pose: acquire the guard object (020cab14); if none,
 * fall back to sub-state 2. Otherwise play the pose, push a fixed offset vector
 * to the render hook twice (cmds 3 and 8), reset the timer, and advance to the
 * hold handler (020ce2e4). */
void func_ov179_020d3810(int param_1) {
    int *piVar5 = *(int **)(param_1 + 4);
    int iVar1 = func_ov107_020cab14(*piVar5, 0);

    piVar5[3] = iVar1;
    if (iVar1 == 0) {
        *(unsigned char *)(*piVar5 + 0x1c7) = 2;
        func_0203c634(param_1, *(signed char *)(param_1 + 0x20), 0);
        return;
    }
    func_ov107_020c9264(*piVar5, 5, 0);
    {
        struct vec3 v = data_02041dc8;
        func_ov107_020c0b90(*piVar5, 3, v, 0);
        func_ov107_020c0b90(*piVar5, 8, v, 0);
    }
    piVar5[0x12] = 0;
    func_0203c634(param_1, *(signed char *)(param_1 + 0x20), func_ov179_020d38e8);
}
