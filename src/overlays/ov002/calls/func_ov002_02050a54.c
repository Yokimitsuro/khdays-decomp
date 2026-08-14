/* Look up the camera distance for a selector, adjusted for depth and world.
 *
 * The base comes from a twelve-byte record table indexed by the selector.
 * Selector 10 alone is interpolated: when the active actor's depth is below
 * -0x10000, the base is pulled toward the selector 0 entry by the reciprocal of
 * how far past that threshold the depth has gone, which is why the second data
 * label is the same word as the first table entry.
 *
 * A second table keyed on the actor's world then adds a fixed offset. Selectors
 * other than 0 and 10 skip it and return the bare base.
 *
 * The early exits are gotos to a shared return placed after the delta is added,
 * because mwcc predicates separate return statements; and the difference
 * feeding the 64-bit multiply is bound to its own local, or the multiply's two
 * operands come out the other way round.
 */
extern char data_ov002_0207e76c[];
extern int data_ov002_0207e764[];

extern int func_01fffe14(void);
extern int func_01fffde0(int nId);
extern int FX_Inv(int nNumerator, int nDenominator);

int func_ov002_02050a54(int nIndex) {
    int nEntry = func_01fffde0(func_01fffe14());
    int nBase = *(int *)(data_ov002_0207e76c + nIndex * 0xc);
    int nDelta;

    if (nIndex != 0) {
        int nDepth;

        if (nIndex != 10) {
            goto done;
        }
        nDepth = *(int *)(nEntry + 0x494);
        if (nDepth >= -0x10000) {
            goto done;
        }
        {
            int nScale = FX_Inv(-0x10000 - nDepth, 0x8000);

            int nDiff = nBase - data_ov002_0207e764[2];

            nBase -= (int)(((long long)nDiff * nScale + 0x800) >> 12);
        }
    }

    nDelta = 0;
    switch (*(int *)(nEntry + 0xc)) {
    case 0:
    case 5:
    case 0xb:
    case 0xe:
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
        nDelta = 0x4cd;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 6:
    case 7:
    case 8:
    case 9:
    case 0xa:
    case 0xc:
    case 0xd:
    case 0xf:
        nDelta = 0xccd;
        break;
    case 0x10:
    case 0x11:
        nDelta = -0x400;
        break;
    }
    nBase += nDelta;

done:
    return nBase;
}
