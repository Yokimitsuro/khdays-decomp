/* Detach the entry: run the owner's detach hook if it has one, then drop bit 2
 * at +0x12. An entry that is not attached is left alone. Mirror of
 * Ov002_FireEntryOnce over the other hook slot and the other flag bit. */
typedef struct {
    char pad0000[0x14];
    void (*pDetach)(void *entry);   /* +0x14 */
} Ov002EntryOwner;

typedef struct {
    char pad0000[8];
    Ov002EntryOwner *pOwner;    /* +8 */
    char pad000c[6];
    unsigned short wFlags;      /* +0x12 */
} Ov002Entry;

void func_ov002_02076af0(Ov002Entry *self) {
    if ((self->wFlags & 4) == 0) {
        return;
    }

    if (self->pOwner->pDetach != 0) {
        self->pOwner->pDetach(self);
    }

    self->wFlags &= ~4;
}
