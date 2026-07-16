/* func_ov008_020818e0 -- set roster slot `slot`'s payload and visibility.
 * The slot's value lives at OBJ+0x9510, its cell handle at OBJ+0x9704 and its current
 * visibility at OBJ+0x9534, all indexed by slot. When the visibility actually changes the
 * cell is bound into (func_020325ec + func_020326cc) or dropped from (func_020326a8) the
 * renderer list at OBJ+0x4a8c. Returns 0 if the manager context is gone.
 *
 * PROVENANCE: byte-identical twin of func_ov006_02055b70 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void func_020325ec(int list, int cell, int a);
extern void func_020326cc(int list, int cell);
extern void func_020326a8(int list, int cell);
extern int *data_ov008_02090fa4;

int func_ov008_020818e0(int slot, int value, int visible) {
    char *obj;
    int cell;
    int was;

    if (data_ov008_02090fa4 == 0) {
        return 0;
    }
    *(int *)((char *)data_ov008_02090fa4 + slot * 4 + 0x9510) = value;
    obj = (char *)data_ov008_02090fa4;
    cell = *(int *)(obj + slot * 4 + 0x9704);
    if (cell != 0) {
        was = *(int *)(obj + slot * 4 + 0x9534);
        if (was == 0 && visible != 0) {
            func_020325ec((int)(obj + 0x4a8c), cell, 0);
            func_020326cc((int)((char *)data_ov008_02090fa4 + 0x4a8c),
                          *(int *)((char *)data_ov008_02090fa4 + slot * 4 + 0x9704));
        } else if (was != 0 && visible == 0) {
            func_020326a8((int)(obj + 0x4a8c), cell);
        }
    }
    *(int *)((char *)data_ov008_02090fa4 + slot * 4 + 0x9534) = visible;
    return 1;
}
