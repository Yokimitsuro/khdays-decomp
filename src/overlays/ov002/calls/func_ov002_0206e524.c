typedef unsigned char u8;
typedef unsigned short u16;
typedef signed char s8;
typedef signed short s16;

typedef struct Ov002Vec3 {
    int x, y, z;
} Ov002Vec3;

extern char *data_ov002_0207fa00;
extern u8 data_0204c240;
extern u16 data_0204c23c;

extern int func_ov002_0206b84c(void);
extern int func_02030788(void);
extern void func_ov002_0206cf4c(int nId);
/* Declared with one parameter on purpose. The callee reads four, and passes
 * the last two on to the archive loader, but the ROM sets only r0 here and
 * leaves the rest holding whatever the previous call left behind - so this
 * translation unit had the one-argument declaration. */
extern void func_ov002_0206e0f0(int bAlternate);
extern char *func_ov002_0206e144(int nKey);
extern int func_020235d0(int nField, int nWidth);
extern int func_ov002_02077b30(void);
extern void func_ov002_02077b64(int nIndex, int nGroup, int nSlot, int nKind,
                                Ov002Vec3 *pPlace, int nFlags, int nLevel);
extern void func_ov002_0206e184(void);

/* Put out the spots the current state's table asks for.
 *
 * Only the first seat does this, and only when bit 1 of the mode flags is
 * clear. Three ids are queued for loading and the offset table is brought in,
 * then the table for the current state word is walked: each row whose bit is
 * already set in the saved field is skipped, and the rest get a spot spawned
 * at the row's own place, with the row's angle stamped into the context's
 * per-slot table. The buffer is released either way.
 */
void func_ov002_0206e524(void)
{
    char *pCtx;
    int nKey;
    char *pTable;
    char *pRow;
    Ov002Vec3 *pPlace;
    int i;
    int nBits;

    pCtx = data_ov002_0207fa00;
    nKey = func_ov002_0206b84c();
    if ((data_0204c240 & 2) == 0 && func_02030788() == 0) {
        func_ov002_0206cf4c(0x1c2);
        func_ov002_0206cf4c(0x1c3);
        func_ov002_0206cf4c(0x1c4);
        func_ov002_0206e0f0(1);

        pTable = func_ov002_0206e144(nKey);
        if (pTable != 0) {
            i = 0;
            if (*(s8 *)(pTable + 2) > 0) {
                pRow = pTable;
                pPlace = (Ov002Vec3 *)(pTable + 0xc);
                do {
                    nBits = func_020235d0(data_0204c23c * 4 + 0x92b, 4);
                    if ((nBits & (1 << *(s8 *)(pRow + 4))) == 0) {
                        func_ov002_02077b64(func_ov002_02077b30(), 0xf,
                                            (u16)*(s8 *)(pRow + 4),
                                            *(s8 *)(pRow + 5), pPlace, 3, 0);
                        *(s16 *)(pCtx + *(s8 *)(pRow + 4) * 4 + 0x8d4c) =
                            *(s16 *)(pRow + 8);
                    }
                    i++;
                    pRow += 0x14;
                    pPlace = (Ov002Vec3 *)((char *)pPlace + 0x14);
                } while (i < *(s8 *)(pTable + 2));
            }
        }
        func_ov002_0206e184();
    }
}
