/* Takes the next free id out of the low band and marks it used by clearing its
 * bit in the stage's free bitmap. A full band reports a negative id, which is
 * handed back untouched. */
extern int func_ov002_02077560(int kind);
extern void func_02025668(void *owner, int id);

typedef struct {
    char pad0000[0x5c];
    void *pFreeBits;            /* +0x5c, set while the id is free */
} Ov002SpotStage;

typedef struct {
    char pad0000[4];
    Ov002SpotStage *pStage;     /* +4 */
} Ov002SpotHolder;

extern Ov002SpotHolder data_ov002_0207fa28;

int func_ov002_02077b30(void) {
    int id = func_ov002_02077560(1);

    if (id >= 0) {
        func_02025668(data_ov002_0207fa28.pStage->pFreeBits, id);
    }

    return id;
}
