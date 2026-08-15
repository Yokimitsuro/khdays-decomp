/* Store the four-byte link option block and bind it to either the active
 * external roster entry or every available entry. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct Ov002LinkCtx {
    u8 gap0000[0x13];
    u8 bLinkOptionEnabled;
    u8 aLinkOptionValues[3];
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

extern int func_ov022_020882f8(void);
extern char *func_01fffde0(int nIndex);
extern u16 func_01fffe14(void);

void func_ov002_02072a48(int bApplyAll, u8 nValueA, u8 nValueB,
                         u8 nValueC, int bEnabled)
{
    Ov002LinkCtx *pContext = data_ov002_0207fa10;
    int i;

    pContext->aLinkOptionValues[0] = nValueA;
    pContext->aLinkOptionValues[1] = nValueB;
    pContext->aLinkOptionValues[2] = nValueC;
    pContext->bLinkOptionEnabled = bEnabled != 0;
    if (bApplyAll != 0) {
        i = 0;
        if (func_ov022_020882f8() > 0) {
            do {
                *(u8 **)(func_01fffde0(i) + 0x2668) =
                    &pContext->bLinkOptionEnabled;
                i++;
            } while (i < func_ov022_020882f8());
        }
    } else {
        *(u8 **)(func_01fffde0(func_01fffe14()) + 0x2668) =
            &pContext->bLinkOptionEnabled;
    }
}
