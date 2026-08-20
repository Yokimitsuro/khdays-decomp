extern int data_ov002_0207f624;

extern int func_02013814(int pSource, int nChannel, int nEntry);

int func_ov002_0205e60c(int *pnMax)
{
    int nCount;
    int i;
    int pSource;
    int *pOwner;
    int nMax;

    pOwner = *(int **)&data_ov002_0207f624;
    nMax = 0;
    pSource = pOwner[0x6f0 / 4];
    nCount = 0;

    for (i = 0; i < 3; i++) {
        int nValue;
        int nEntry;

        nEntry = pOwner[i + 0x7c4 / 4];
        if (nEntry == 0) {
            break;
        }

        nValue = func_02013814(pSource, 0, nEntry);
        if (nMax < nValue) {
            nMax = nValue;
        }
        nCount++;
    }

    *pnMax = nMax;
    return nCount;
}
