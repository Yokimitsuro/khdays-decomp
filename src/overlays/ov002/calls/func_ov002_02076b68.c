/* Fire the entry's owner hook once, then latch bit 1 at +0x12 so it never fires
 * again. Skipped entirely when the gate at +0x14/+0x16 reports the entry is not
 * eligible -- only bit 0 of that answer counts. */
extern int func_020235d0(unsigned short key, unsigned char kind);

typedef struct {
    char pad0000[0x10];
    void (*pHandler)(void *entry);  /* +0x10 */
} Ov002EntryOwner;

typedef struct {
    char pad0000[8];
    Ov002EntryOwner *pOwner;    /* +8 */
    char pad000c[6];
    unsigned short wFlags;      /* +0x12 */
    unsigned short wKey;        /* +0x14 */
    unsigned char bKind;        /* +0x16 */
} Ov002Entry;

void func_ov002_02076b68(Ov002Entry *self) {
    if ((self->wFlags & 2) != 0) {
        return;
    }

    {
        int eligible;

        if ((func_020235d0(self->wKey, self->bKind) & 1) != 0) {
            eligible = 1;
        } else {
            eligible = 0;
        }

        if (eligible == 0) {
            return;
        }
    }

    if (self->pOwner->pHandler != 0) {
        self->pOwner->pHandler(self);
    }

    self->wFlags |= 2;
}
