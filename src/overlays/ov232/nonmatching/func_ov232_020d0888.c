/* Try to acquire a reaction target: gather candidates (func_ov107_020c8eb8 for a specific target
 * param_2, else func_ov107_020c8f44 by kind param_3), then for the first candidate whose reaction
 * bit (index at +2) is not yet consumed in node+0x4d and that func_ov107_020ca918 accepts, mark the
 * bit, copy the spawn params at +0x190 (bumping the mid field by 0x2000), fire the reaction
 * (func_ov107_020c0b90) and return 1; else return 0.
 *
 * This is the representative of a 5-member byte-identical group (ov231_020ccc48, ov232_020d0888,
 * ov263/ov265/ov280_020d0890) -- a single match would propagate to all five via dedupprop.
 *
 * NON-MATCHING (equivalent), size-exact (272). The whole body -- the candidate loop with the inline
 * `1<<bit` mask, the ldmia/stmia struct copy of the 3-word spawn block, and the struct-by-value
 * call -- reproduces. The only residue is register allocation: the ROM eager-loads the stack
 * argument param_5 into r4 at entry (before node), so the callee-saved colouring is
 * param_5=r4/list=r5/node=r6, whereas mwcc 139 loads param_5 lazily at its first use in the loop
 * and colours node=r5/.../param_5=r8, shifting register fields across ~54 bytes. build_sweep: no
 * mwcc build (1.2/2.0/3.0/dsi) reproduces the eager load under our flags; a `int flag = param_5;`
 * hoist does not move it. An eager-vs-lazy stack-arg-load compiler difference. */
typedef struct { int x, y, z; } SpawnParams;

extern int func_ov107_020c8eb8(int owner, int target, int *outList);
extern int func_ov107_020c8f44(int owner, int kind, int *outList);
extern int func_ov107_020ca918(int cand, int a, int b, int flag, int arg, int zero);
extern void func_ov107_020c0b90(int owner, int b, SpawnParams sp, int c);

int func_ov232_020d0888(int param_1, int param_2, int param_3, int param_4, int param_5) {
    int list[4];
    int *node = *(int **)(param_1 + 4);
    int count;
    int i;
    if (param_2 == 0) {
        count = func_ov107_020c8f44(*node, param_3, list);
    } else {
        count = func_ov107_020c8eb8(*node, param_2, list);
    }
    i = 0;
    if (count > 0) {
        do {
            unsigned int bit = (1 << *(unsigned short *)(list[i] + 2)) & 0xff;
            if ((*(unsigned char *)((char *)node + 0x4d) & bit) == 0 &&
                func_ov107_020ca918(list[i], *node, *node, param_5 & 0xff, param_4, 0) != 0) {
                SpawnParams sp = *(SpawnParams *)(list[i] + 0x190);
                sp.y += 0x2000;
                *(unsigned char *)((char *)node + 0x4d) |= bit;
                func_ov107_020c0b90(*node, 0, sp, 0);
                return 1;
            }
            i++;
        } while (i < count);
    }
    return 0;
}
