/* Teardown: release the two model handles, then the five 8-byte attachment
 * slots at +0x3dc (only the first word of each pair owns anything), free the
 * slot block and let the base class finish. */
extern void func_0203c7e8(void *handle);
extern void func_ov107_020c9eac(void *model);
extern void func_0203d194(void *block);
extern void func_ov107_020c68ec(void *self);

typedef struct {
    void *pHandle;
    void *pExtra;
} Ov202Slot;

typedef struct {
    char pad0000[0x384];
    void *pModelA;      /* +0x384 */
    void *pModelB;      /* +0x388 */
    char pad038c[0x50];
    Ov202Slot *pSlots;  /* +0x3dc */
} Ov202Object;

void func_ov202_020cc218(Ov202Object *self) {
    int i;

    func_0203c7e8(self->pModelA);
    func_ov107_020c9eac(self->pModelB);

    for (i = 0; i < 5; i++) {
        func_0203c7e8(self->pSlots[i].pHandle);
    }

    func_0203d194(self->pSlots);
    func_ov107_020c68ec(self);
}
