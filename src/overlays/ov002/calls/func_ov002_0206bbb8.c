/* Post one change to the mission tally.
 *
 * Does nothing unless a session is live and the value is non-zero. Kinds 2 and
 * 5 are session-wide rather than per-slot, so they reject a positive index and
 * force the slot to zero; kind 1 first clears the posted bit for its index.
 *
 * The kind then selects the accumulator: 3 adds to the scalar, 2 adds the two
 * halves of a packed pair component-wise, 1 appends the index to the first free
 * entry of the id list, and 7 adds to one of five slot totals, raising its bit
 * or clearing it when the total returns to zero. Kinds 0, 4 and 5 build a small
 * record and hand it to the deferred handler. Kind 6 and anything above 7 are
 * ignored.
 *
 * Called from ov022 and ov234 as well as from inside ov002.
 */
typedef unsigned short u16;
typedef unsigned char u8;

/* The record the deferred handler consumes: kind, index and value. */
typedef struct {
    u8 nKind;
    u8 nIndex;
    u8 pad0002[2];
    int nValue;
} Ov002Request;

extern char *data_ov002_0207fa00;

extern int func_02030694(void);
extern void func_ov002_020679c4(int nPacked, short *pHi, short *pLo);
extern void func_ov002_0206c2a0(Ov002Request *pRequest);

void func_ov002_0206bbb8(int nIndex, int nKind, int nValue) {
    char *root = data_ov002_0207fa00;
    char *session = root + 0x8bcc;
    int nSlot = nIndex;
    Ov002Request req;

    if (func_02030694() == 0 || nValue == 0) {
        return;
    }

    if (nKind == 5 || nKind == 2) {
        if (nIndex > 0) {
            return;
        }
        nSlot = 0;
    } else if (nKind == 1) {
        *(u8 *)(session + 0xbe) = (u8)(*(u8 *)(session + 0xbe) &
                                       ~(1 << nIndex));
    }

    /* The case bodies are laid out 2, 3, 7, 1, then the shared tail. */
    switch (nKind) {
    case 2: {
        short nAddX;
        short nAddY;
        short nCurX;
        short nCurY;

        nAddX = 0;
        nAddY = 0;
        nCurX = 0;
        nCurY = 0;
        func_ov002_020679c4(nValue, &nAddX, &nAddY);
        func_ov002_020679c4(*(int *)(root + 0x8b78), &nCurX, &nCurY);
        nCurX = (short)(nCurX + nAddX);
        nCurY = (short)(nCurY + nAddY);
        *(int *)(root + 0x8b78) = ((int)nCurX << 16) | (u16)nCurY;
        *(u16 *)(root + 0x8b6a) |= 2;
        return;
    }
    case 3:
        *(short *)(root + 0x8b6c) =
            (short)(*(short *)(root + 0x8b6c) + nValue);
        *(u16 *)(root + 0x8b6a) |= 1;
        return;
    case 7:
        {
            short nCur = *(short *)(root + 0x8b6e + nSlot * 2);

            *(short *)(root + 0x8b6e + nSlot * 2) =
                (short)(nCur + nValue);
        }
        if (((short *)(root + 0x8b6e))[nSlot] == 0) {
            *(u16 *)(root + 0x8b6a) &= ~(1 << (nSlot + 3));
            return;
        }
        *(u16 *)(root + 0x8b6a) |= 1 << (nSlot + 3);
        return;
    case 1: {
        int i = 0;

        do {
            char *pEntry = session + i;

            if (pEntry[0xb9] == -1) {
                pEntry[0xb9] = (char)nIndex;
                break;
            }
            i++;
        } while (i < 5);
        *(u16 *)(root + 0x8b6a) |= 4;
        return;
    }
    case 0:
    case 4:
    case 5:
        req.nKind = (u8)nKind;
        req.nIndex = (u8)nIndex;
        req.nValue = nValue;
        func_ov002_0206c2a0(&req);
        break;
    default:
        break;
    }
}
