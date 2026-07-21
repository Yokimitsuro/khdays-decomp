/* Look up a per-id parameter word from the shared table at data_02090fb0: id 0x1a0 -> +0x150,
 * 0xe8 -> +0x154, 0x1c8 -> +0x14c, 0x1c9 -> +0x148; any other id yields 1.
 *
 * NON-MATCHING (equivalent), size-exact. Same compiler-aggressiveness tie as func_ov008_0208a5e8
 * (the boolean sibling of this lookup): (1) the ROM places all four field-return blocks out of
 * line and branches to them (bge/beq), while build 139 inlines the first ones; (2) writing the
 * lower bound as `id >= 0x1c8` makes mwcc range-fold `id==0x1c8 || id==0x1c9` away (8 bytes short),
 * while `id > 0x1c7` makes it derive 0x1c7 by sub. Neither reproduces the ROM's explicit
 * per-value compares with out-of-line blocks. */
struct Ov008ParamTable {
    char _pad[0x148];
    int f148;
    int f14c;
    int f150;
    int f154;
};
extern struct Ov008ParamTable *data_ov008_02090fb0;

int func_ov008_0208a55c(int id) {
    if (id <= 0x1a0) {
        if (id == 0x1a0) {
            return data_ov008_02090fb0->f150;
        }
        if (id == 0xe8) {
            return data_ov008_02090fb0->f154;
        }
    } else if (id <= 0x1c9 && id > 0x1c7) {
        if (id == 0x1c8) {
            return data_ov008_02090fb0->f14c;
        }
        if (id == 0x1c9) {
            return data_ov008_02090fb0->f148;
        }
    }
    return 1;
}
