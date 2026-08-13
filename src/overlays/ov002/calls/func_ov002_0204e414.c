extern void *NNSi_FndGetCurrentRootHeap(void);
extern int func_02023c40(void);

int func_ov002_0204e414(int angleA, int angleB)
{
    int difference;
    int limit;

    NNSi_FndGetCurrentRootHeap();
    difference = (unsigned short)(angleB - angleA);
    limit = func_02023c40() == 1 ? 0x600 : 0x400;
    if (limit >= difference) {
        goto return_false;
    }
    limit = func_02023c40() == 1 ? 0x600 : 0x400;
    if (limit < 0x10000 - difference) {
        goto return_true;
    }
return_false:
    return 0;
return_true:
    return 1;
}
