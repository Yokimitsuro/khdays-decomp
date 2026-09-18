/* Fills the 5-word mission tally `out`: [4] whether the current level's flag is set (8704; when
 * clear everything stays zero), [3] the number of records the ov302 record set (overlay 0x12e,
 * built from the overlay's +0xba7ec init triple with the level from 235d0 kind 9 in the middle)
 * holds, [1] how many of them are done (+0xc flag or bit 1 of +0x14), [2] how many are unlocked
 * (their +2 id x 3 + 0x28e4 at kind-3 level 2 or more) and [0] how many are both. The overlay is
 * loaded around the walk. */
typedef unsigned char u8;
typedef unsigned short u16;

struct RecordInit {
    int nFile;
    int nLevel;
    int nMode;
};

struct Record {
    char pad000[2];
    u16 nId;                /* +0x02 */
    char pad004[8];
    u8 bDone;               /* +0x0c */
    char pad00d[7];
    u8 nFlags14;            /* +0x14 */
};

extern void MI_CpuFill8(void *dst, int value, int size);
extern int func_ov069_020b8704(void);
extern unsigned int func_020235d0(int id, int kind);
extern void func_0201e470(int processor, int overlay);
extern void func_0201e4a8(int processor, int overlay);
extern void func_ov302_020cc64c(void *set, struct RecordInit *init);
extern int func_ov302_020cc718(void *set);
extern struct Record *func_ov302_020cc6dc(void *set, struct Record *cur);
extern void func_ov302_020cc6ac(void *set);
extern const struct RecordInit data_ov069_020ba7ec;

void func_ov069_020b876c(int *out)
{
    char set[0x24];
    struct RecordInit init;
    int level;
    int done;
    struct Record *rec;
    int ok;

    init = data_ov069_020ba7ec;
    MI_CpuFill8(out, 0, 0x14);
    if (func_ov069_020b8704() == 0) {
        out[4] = 0;
        return;
    }
    out[4] = 1;
    level = func_020235d0(0, 9);
    func_0201e470(0, 0x12e);
    init.nLevel = level;
    func_ov302_020cc64c(set, &init);
    out[3] = func_ov302_020cc718(set);
    for (rec = func_ov302_020cc6dc(set, 0); rec != 0; rec = func_ov302_020cc6dc(set, rec)) {
        if (rec->bDone != 0 || (rec->nFlags14 & 2) != 0) {
            done = 1;
        } else {
            done = 0;
        }
        out[1] += done;
        ok = func_020235d0(rec->nId * 3 + 0x28e4, 3) >= 2 ? 1 : 0;
        if (ok != 0) {
            out[2]++;
            out[0] += done;
        }
    }
    func_ov302_020cc6ac(set);
    func_0201e4a8(0, 0x12e);
}
