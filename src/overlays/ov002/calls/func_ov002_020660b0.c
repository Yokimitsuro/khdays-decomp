/*
 * Turns the peer's touch point into a map panel cell and publishes it.
 *
 * The panel has two layouts. While the slot still holds no value the point is
 * read as a cell in an eleven by two grid whose origin is at forty across and
 * a hundred and sixty-eight down, with cells sixteen wide and twelve tall. Once
 * the slot holds a value the panel is a single row of buttons instead, keyed on
 * x alone: the first two are fixed-width, the rest are twenty-four wide.
 *
 * Either way the cell is clamped to its own layout, offset by two, and handed
 * to the slot publisher along with a sound handle, which is only opened when
 * the caller asks for one.
 *
 * Four things here are load-bearing rather than style.
 *
 * The touch point is an eight-byte local even though only its first two
 * halfwords are read. Declared as four bytes the compiler keeps the frame the
 * same size by pushing a seventh register instead of reserving the space.
 *
 * The sound handle is chosen by an if with both arms rather than assigned zero
 * and then overwritten. That is what predicates the zero onto the test instead
 * of emitting it unconditionally ahead of it.
 *
 * The slot index is read from the context twice: once to reach the slot entry,
 * before the shutdown check, and again for the byte-wide argument afterwards.
 *
 * On the button row a point at or left of the first button leaves the cell
 * unset, and the clamp that follows is what gives it a value. That is what the
 * original does; it is not an oversight in the transcription.
 *
 * ARM.
 */

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct Ov002SlotContext {
    char pad000[4];
    int nSlot;
    char pad008[0x10];
    int aActive[4];
    int bFlag;
} Ov002SlotContext;

typedef struct Ov002SlotEntry {
    int nValue;
    char pad004[0x10];
} Ov002SlotEntry;

typedef struct Ov002TouchPoint {
    u16 nX;
    u16 nY;
    u16 nZ;
    u16 nW;
} Ov002TouchPoint;

extern Ov002SlotContext *data_ov002_0207f99c;
extern Ov002SlotEntry data_ov002_0207f9a0[];

extern int func_ov002_0206b7a4(void);
extern void func_ov002_02066e40(Ov002TouchPoint *pPoint, u8 nSlot);
extern int func_ov002_02053558(u16 nId);
extern void func_ov002_020658c8(u32 nValue, int hSound);

void func_ov002_020660b0(int bWithSound)
{
    Ov002TouchPoint point;
    Ov002SlotContext *pCtx;
    Ov002SlotEntry *pEntry;
    int nCell;
    int nCol;
    int nRow;
    int hSound;

    pCtx = data_ov002_0207f99c;
    pEntry = &data_ov002_0207f9a0[pCtx->nSlot];
    if (func_ov002_0206b7a4() != 0) {
        return;
    }

    func_ov002_02066e40(&point, (u8)pCtx->nSlot);

    if (pEntry->nValue == 0) {
        nCol = (point.nX - 0x28) / 16;
        nRow = (point.nY - 0xa8) / 12;
        if (nCol > 10) {
            nCol = 10;
        } else if (nCol < 0) {
            nCol = 0;
        }
        if (nRow > 1) {
            nRow = 1;
        } else if (nRow < 0) {
            nRow = 0;
        }
        nCell = nRow * 11 + nCol;
    } else {
        if (point.nX > 0x30) {
            if (point.nX < 0x48) {
                nCell = 0x16;
            } else if (point.nX < 0x58) {
                nCell = 0x17;
            } else {
                nCell = (point.nX - 0x58) / 24 + 0x18;
            }
        }
        if (nCell > 0x1d) {
            nCell = 0x1d;
        } else if (nCell < 0x16) {
            nCell = 0x16;
        }
    }

    if (bWithSound == 0) {
        hSound = 0;
    } else {
        hSound = func_ov002_02053558((u16)(nCell + 0x474));
    }
    func_ov002_020658c8(nCell + 2, hSound);
}
