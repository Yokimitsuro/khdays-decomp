typedef unsigned char u8;
typedef unsigned short u16;

/* The seat window of the root context.  It starts at the offset table because
 * that is the anchor the compiler builds the two field addresses from. */
typedef struct Ov002SeatBlock {
    void *pOffsetTable;             /* +0x00, root +0x8d7c */
    u16 wSeatMask;                  /* +0x04, root +0x8d80 */
    signed char cModuleId;          /* +0x06, root +0x8d82 */
} Ov002SeatBlock;

typedef struct Ov002RootContext {
    char pad0000[0x8d7c];
    Ov002SeatBlock seats;           /* +0x8d7c */
} Ov002RootContext;

extern Ov002RootContext *data_ov002_0207fa00;
extern u8 data_0204c240;                        /* mode and day clock */

extern int func_ov002_02076468(int nModuleId);  /* module id -> table slot */
extern int func_ov002_0207a23c(int nSlot, int nKey);

/* Clear one seat's bit in the mask, given the key that names it.
 *
 * Outside the plain mode the clock byte has to read as bit 0 set and bit 1
 * clear for the clear to happen at all.  After that the current module's slot
 * table is asked which bit the key maps to, and a key the table does not know
 * leaves the mask alone.
 *
 * The first argument is the callback's context and is not used here.
 */
void func_ov002_0206dd1c(int nUnused, int nKey)
{
    Ov002SeatBlock *pSeats;
    u8 bMode;
    int nSlot;
    int nBit;

    pSeats = &data_ov002_0207fa00->seats;
    bMode = data_0204c240;
    if (bMode != 0) {
        if ((bMode & 1) == 0) {
            return;
        }
        if ((bMode & 2) != 0) {
            return;
        }
    }

    if (pSeats->cModuleId < 0) {
        return;
    }

    nSlot = func_ov002_02076468(pSeats->cModuleId);
    nBit = func_ov002_0207a23c(nSlot, nKey);
    if (nBit < 0) {
        return;
    }

    pSeats->wSeatMask &= ~(1 << nBit);
}
