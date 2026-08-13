/* Read one value out of a session slot, or nothing at all if the session is not up.
 *
 * The session block starts 0x8bcc into the root context and opens with four slots of 0x2c bytes:
 * a handle, one more word, then nine values. The caller picks a slot and an index into those
 * values. The result is returned as a halfword, which is why the word that comes out of the array
 * is shifted left and back right rather than masked.
 *
 * Ghidra carries the layout as Ov002SessionSlot inside Ov002SessionBlock.
 */

typedef unsigned short u16;

typedef struct {
    int nHandle;                /* +0x00 */
    int nUnk04;                 /* +0x04 */
    int aValues[9];             /* +0x08 */
} Ov002SessionSlot;

extern int func_02030694(void);
extern char *data_ov002_0207fa00;

u16 func_ov002_0206bdcc(int slot, int index) {
    Ov002SessionSlot *slots = (Ov002SessionSlot *)(data_ov002_0207fa00 + 0x8bcc);

    if (func_02030694() == 0) {
        return 0;
    }
    return (u16)slots[slot].aValues[index];
}
