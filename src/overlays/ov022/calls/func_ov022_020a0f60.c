/* Refresh the shared panel: if the local player still owns the slot, hand the entry at +0x4ec
 * and its object to the panel refresh, then reset the four scroll words at +0x47c..+0x4b4.
 *
 * Matched byte-exact 2026-07-23, closing an old park filed as a register-coloring residue.
 * It was a DROPPED ARGUMENT: func_ov107_020c1fb4 takes (obj, entry) -- it reads [r0,#0xf8] and
 * moves r1 into r4 -- and the park declared it `void (void)`. With both arguments live, `entry`
 * has to survive the load of its own field and mwcc puts it in r1, which is the whole residue.
 * The size was right the entire time, which is exactly why the arity was never suspected. */
extern int func_ov022_020882bc(unsigned int arg0);
extern int func_01fffe14(void);
extern void func_ov107_020c1fb4(int obj, int *ent);

void func_ov022_020a0f60(int arg0) {
    unsigned int s = func_ov022_020882bc(*(unsigned char *)(arg0 + 9));
    int a = func_01fffe14();
    int off;
    if (s == a) {
        int *ent = *(int **)(arg0 + 0x4ec);
        if (ent != 0 && ent[1] != 0) {
            func_ov107_020c1fb4(ent[1], ent);
        }
    }
    off = 0x4b4;
    *(int *)(arg0 + off) = 0xf000;
    *(int *)(arg0 + off - 0x30) = 0;
    *(int *)(arg0 + off - 0x34) = *(int *)(arg0 + off - 0x30);
    *(int *)(arg0 + off - 0x38) = *(int *)(arg0 + off - 0x34);
}
