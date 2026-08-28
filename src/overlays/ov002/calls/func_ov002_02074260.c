typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    int x, y, z;
} VecFx32;

typedef struct {
    u8 gap0000[0x60];
    u16 nState : 8;         /* 0x60 */
    u16 nStateHigh : 8;
    u8 gap0062[0x4e];
    VecFx32 vHome;          /* 0xb0 -- see the note below */
    u8 gap00bc[0xbd];
    u8 nKind;               /* 0x179 */
    u8 gap017a[0x32];
    u16 nFitFlags;          /* 0x1ac */
} Ov002PieceElement;

extern int func_01ff8e94(const VecFx32 *a, const VecFx32 *b);

/* Answers whether a piece is one the peer should be told about.
 *
 * A piece has to be live, of a kind outside the five the walk skips, and clear
 * of both fit flags.  A negative range takes every piece that got this far;
 * otherwise the piece's home has to be at least that far from the point asked
 * about.
 *
 * Only the low byte of the state word is looked at -- an eight-bit field of
 * the halfword, which is why the ROM extracts it with a shift pair instead of
 * masking -- and the home vector is copied to the frame before the distance
 * call rather than passed in place.
 *
 * That copy is twelve bytes from +0xb0, and its last word is the halfword the
 * tree already calls the piece's home angle.  Either the angle is misplaced or
 * the distance is being taken against a z that is not one; the ROM copies the
 * three words either way, so this keeps the block whole and leaves the
 * question open.
 */
int func_ov002_02074260(Ov002PieceElement *pPiece, const VecFx32 *pPos,
                        int nRange)
{
    VecFx32 vHome;
    u8 nKind;

    if ((pPiece->nState & 1) == 0) {
        return 0;
    }
    nKind = pPiece->nKind;
    if (nKind == 4 || nKind == 5 || nKind == 3 || nKind == 6 || nKind == 7 ||
        (pPiece->nFitFlags & 4) != 0) {
        return 0;
    }
    if ((pPiece->nFitFlags & 2) != 0) {
        return 0;
    }
    if (nRange < 0) {
        return 1;
    }
    vHome = pPiece->vHome;
    return nRange <= func_01ff8e94(&vHome, pPos);
}
