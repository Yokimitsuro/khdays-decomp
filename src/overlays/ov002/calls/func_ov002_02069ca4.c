/* Tear the pause object down: hand it back, mark the slot empty again and raise
 * the redraw byte. When the companion flag byte says the pause was modal, also
 * un-quiesce with func_ov002_0206e718(1).
 *
 * The slot sits at +0x8c94 of the root context, far past the 12-bit immediate,
 * so it is reached through a HELD pointer and the two neighbouring flag bytes
 * are read as small offsets from it -- that is what keeps the far offset in a
 * callee-saved register instead of being rematerialised at every use. */
typedef struct {
    int nObject;                /* +0x00 (root +0x8c94) */
    char pad04[0x72];
    unsigned char bModal;       /* +0x76 */
    unsigned char bRedraw;      /* +0x77 */
} Ov002PauseSlot;

extern void WM_EndKeySharing_0x02023ad0(int object);
extern void func_ov002_0206e718(int mode);

extern char *data_ov002_0207fa00;

void func_ov002_02069ca4(void) {
    Ov002PauseSlot *slot = (Ov002PauseSlot *)(data_ov002_0207fa00 + 0x8c94);

    if (slot->nObject == -1) {
        return;
    }

    WM_EndKeySharing_0x02023ad0(slot->nObject);
    slot->nObject = -1;
    slot->bRedraw = 1;

    if (slot->bModal & 1) {
        func_ov002_0206e718(1);
    }
}
