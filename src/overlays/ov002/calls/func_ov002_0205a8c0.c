typedef struct {
    char pad0000[0x5f4];
    int aPrimary[11];               /* +0x5f4 */
    int aSecondary[6];              /* +0x620 */
} Ov002IconSet;

extern Ov002IconSet *data_ov002_0207f620;
extern unsigned short data_ov002_0207de38[];    /* 11 primary ids */
extern unsigned short data_ov002_0207de2c[];    /* 6 secondary ids */

extern int func_ov002_02053558(int nId);
extern void func_ov002_02053510(int nFirst, int nSecond);

/* Resolve every icon the panel uses and install the pair the header shows. */
void func_ov002_0205a8c0(void)
{
    Ov002IconSet *pSet;
    int i;

    pSet = data_ov002_0207f620;

    for (i = 0; i < 11; i++) {
        pSet->aPrimary[i] = func_ov002_02053558(data_ov002_0207de38[i]);
    }

    for (i = 0; i < 6; i++) {
        pSet->aSecondary[i] = func_ov002_02053558(data_ov002_0207de2c[i]);
    }

    func_ov002_02053510(pSet->aSecondary[2], pSet->aPrimary[0]);
}
