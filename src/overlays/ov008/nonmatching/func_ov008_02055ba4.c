/* NONMATCHING: one-instruction compiler-version tie. The ROM loads the count with `ldrh`
 * (unsigned) yet guards the loop with `ble` (a SIGNED <=0 test); our mwcc range-tracks the u16 and
 * emits `beq` for every equivalent C form (`!= 0`, `> 0`, int-cast). Same "our compiler is smarter"
 * class as the dead-narrowing tie (0207350c). Everything else matches byte-for-byte. */
/* func_ov008_02055ba4 -- push (param_3,param_4) to every tag a tracker node watches
 * (node+0x2c is the tag-entry array, node+2 the count), then re-resolve its selected tag
 * (index node+4) via func_ov008_0205589c. */
extern void func_ov008_02055874(int owner, int entry, unsigned short a, unsigned short b);
extern void func_ov008_0205589c(int owner, int entry);

void func_ov008_02055ba4(int param_1, int param_2, unsigned short param_3, unsigned short param_4) {
    int i = 0;
    if (*(unsigned short *)(param_2 + 2) > 0) {
        do {
            func_ov008_02055874(param_1, (*(int **)(param_2 + 0x2c))[i], param_3, param_4);
            i = i + 1;
        } while (i < (int)*(unsigned short *)(param_2 + 2));
    }
    func_ov008_0205589c(param_1,
        *(int *)(*(int *)(param_2 + 0x2c) + *(unsigned short *)(param_2 + 4) * 4));
}
