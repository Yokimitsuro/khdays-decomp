/* Select the link callbacks stored for one roster entry. The switch form is
 * load-bearing because it reproduces the original THUMB branch tree. */
typedef void (*Ov002LinkCallback)(void);

typedef struct Ov002LinkCtx {
    char gap0000[0x0c];
    signed char nLinkMode;
} Ov002LinkCtx;

extern Ov002LinkCtx *data_ov002_0207fa10;

extern int func_ov002_0206b84c(void);
extern void func_ov002_02072ba4(void);
extern void func_ov013_0207fbe4(void);
extern void func_ov020_0207fd28(void);
extern void func_ov020_0207fe4c(void);

void func_ov002_02071804(int nIndex, Ov002LinkCallback *pPrimary,
                         Ov002LinkCallback *pSecondary)
{
    Ov002LinkCallback pFirst = func_ov002_02072ba4;
    Ov002LinkCallback pSecond = 0;
    int nMode = data_ov002_0207fa10->nLinkMode;

    switch (nMode) {
    case 1:
        if (nIndex == 1 && func_ov002_0206b84c() == 0x72) {
            pFirst = func_ov013_0207fbe4;
        }
        break;
    case 4:
        if ((unsigned int)(nIndex - 9) <= 1) {
            pFirst = func_ov020_0207fd28;
            pSecond = func_ov020_0207fe4c;
        }
        break;
    }
    if (pPrimary != 0) {
        *pPrimary = pFirst;
    }
    if (pSecondary != 0) {
        *pSecondary = pSecond;
    }
}
