extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov105_020bd7c4(void);
extern void func_ov003_0204e91c(void *p);
extern void func_ov003_0204ef68(void *p);
extern int func_ov003_0204f08c(void);

int func_ov003_0204f5cc(void) {
    unsigned short *root;
    int iVar3;
    int iVar4;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    iVar4 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_ov105_020bd7c4();
    }
    func_ov003_0204e91c(root);
    if (*(int *)(root + 0xbba) == 0) {
        *(int *)(root + 0xbd8) = 0;
        *(int *)(root + 0xbda) = 0x1f;
    } else {
        iVar3 = *(int *)(root + 0xbd8);
        *(int *)(root + 0xbd8) = iVar3 - 6;
        if (iVar3 - 6 < -0xbf) {
            *(int *)(root + 0xbd6) = 1;
            *(int *)(root + 0xbd8) = -0xbf;
            *(int *)(root + 0xbba) = 0;
            iVar4 = (int)func_ov003_0204f08c;
            *(int *)(root + 0xbbc) = 1;
        }
        iVar3 = *(int *)(root + 0xbda);
        *(int *)(root + 0xbda) = iVar3 - 1;
        if (iVar3 - 1 < 0) {
            *(int *)(root + 0xbda) = 0;
        }
    }
    func_ov003_0204ef68(root);
    if (iVar4 == 0) {
        *(int *)(root + 0xbba) = *(int *)(root + 0xbba) + 1;
    }
    return iVar4;
}
