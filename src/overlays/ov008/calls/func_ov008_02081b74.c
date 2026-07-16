/* func_ov008_02081b74 -- show or hide the currently selected 3D draw slot.
 * The slot index lives at OBJ+0x96dc (negative = none) and the 0x8c-byte slot array starts
 * at OBJ+0x4b08; bit 2 of a slot's first word is its visible flag. The slot is registered
 * with or removed from the renderer list at OBJ+0x4a8c either way.
 *
 * PROVENANCE: byte-identical twin of func_ov006_02055e04 -- same code, this overlay's own
 * globals, propagated mechanically and verified byte-exact.
 * The scene-identity phrasing that came with the twin source (Mission Mode / char select /
 * ov025 panel) is the REP's, NOT established for ov008, so it was removed rather than
 * carried over. What IS measured: ov008's own strings include UI/mlt/res.p2 (the same pack
 * ov006 loads) plus UI/cm/*.p2 and ba/ch/*, so resource detail naming those is sound; the
 * scene label is not. The offsets and logic below are this function's -- the code is
 * byte-identical to the rep.
 */
extern void func_020326a8(int list, int idx);
extern void func_020326cc(int list, int idx);
extern int *data_ov008_02090fa4;

struct Ov006DrawSlot {
    unsigned pad0 : 2;
    unsigned visible : 1;
    unsigned pad1 : 29;
    char rest[0x88];
};

void func_ov008_02081b74(int on) {
    int idx = *(int *)((char *)data_ov008_02090fa4 + 0x96dc);
    if (idx >= 0) {
        struct Ov006DrawSlot *slots =
            (struct Ov006DrawSlot *)((char *)data_ov008_02090fa4 + 0x4b08);
        slots[idx].visible = on != 0;
    }
    if (on != 0) {
        func_020326a8((int)((char *)data_ov008_02090fa4 + 0x4a8c),
                      *(int *)((char *)data_ov008_02090fa4 + 0x96dc));
        return;
    }
    func_020326cc((int)((char *)data_ov008_02090fa4 + 0x4a8c),
                  *(int *)((char *)data_ov008_02090fa4 + 0x96dc));
}
