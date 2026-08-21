extern void func_ov002_020767ec(void *pSlot);
extern int func_ov002_0206b758(void);
extern void func_ov022_020888ec(int nIndex, int bOn);
extern void func_ov002_020767bc(int arg0, int arg1);

/* Act on a message delivered to a mission slot.
 *
 * The byte at 0x40 packs a count in its low nibble with three flags above it.
 * Message 1 moves the slot to its second phase, remembers the index the message
 * carries, counts one entry off unless the slot is held, and latches once -
 * calling the ready handler only if the slot was armed for it. Messages 2 and 3
 * only move the phase on, and 3 also copies the pending width across and
 * publishes the index.
 */
void func_ov002_0207a838(char *pSlot, unsigned char *pMsg)
{
    signed char nFlags;

    switch (pMsg[0]) {
    case 1:
        *(unsigned char *)(pSlot + 0x2c) = 2;
        *(unsigned char *)(pSlot + 0x3f) = pMsg[4];

        nFlags = *(signed char *)(pSlot + 0x40);
        if ((nFlags & 0x10) == 0) {
            *(signed char *)(pSlot + 0x40) = nFlags & ~0xf;
            *(signed char *)(pSlot + 0x40) |= ((nFlags & 0xf) - 1) & 0xf;
        }

        if ((*(signed char *)(pSlot + 0x40) & 0x80) != 0) {
            return;
        }
        *(signed char *)(pSlot + 0x40) |= 0x80;

        if ((*(signed char *)(pSlot + 0x40) & 0x40) == 0) {
            return;
        }
        func_ov002_020767ec(pSlot);
        return;

    case 2:
        *(unsigned char *)(pSlot + 0x2c) = 5;
        return;

    case 3:
        *(unsigned char *)(pSlot + 0x2c) = 6;
        *(unsigned char *)(pSlot + 0x17) = *(signed char *)(pSlot + 0x2e);
        if (func_ov002_0206b758()) {
            func_ov022_020888ec(*(unsigned char *)(pSlot + 0x3f), 0);
        }
        func_ov002_020767bc(0, *(unsigned char *)(pSlot + 0x3f));
        return;
    }
}
