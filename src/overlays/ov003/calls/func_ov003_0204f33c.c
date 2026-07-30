typedef struct Ov003RootTail {
    unsigned char pad0000[0x1774];
    int nStateTicks;
} Ov003RootTail;

extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_ov105_020bd7c4(void);
extern void func_ov003_0204e91c(void *p);
extern void func_ov003_0204d6c8(int i, int v);
extern void GFXi_EnqueueCommand(int a, int b, void *p, int n);
extern void func_ov003_0204ef68(void *p);
extern int func_ov003_0204f460(void);

int func_ov003_0204f33c(void)
{
    unsigned short *root;
    unsigned int uVar3;
    int iVar4;
    int iVar5;
    int d;

    root = (unsigned short *)NNSi_FndGetCurrentRootHeap();
    iVar4 = 0;
    if (*(int *)(root + 0xf08) == 0) {
        *(int *)(root + 0xf0a) = func_ov105_020bd7c4();
    }
    func_ov003_0204e91c(root);
    if (*(int *)(root + 0xbba) == 0) {
        uVar3 = *root;
        iVar5 = 0;
        if (0 < (int)uVar3) {
            do {
                if (((int *)root)[iVar5 + 0xb] < (int)(uVar3 - 1)) {
                    func_ov003_0204d6c8(iVar5, ((int *)root)[iVar5 + 0xb]);
                }
                uVar3 = *root;
                iVar5 = iVar5 + 1;
            } while (iVar5 < (int)uVar3);
        }
        GFXi_EnqueueCommand(9, 0, root + 0xbdc, 0x600);
        GFXi_EnqueueCommand(0x19, 0, root + 0xbdc, 0x600);
        *(int *)(root + 0xf06) = 0x10;
    } else {
        GFXi_EnqueueCommand(0x19, 0, root + 0xbdc, 0x600);
        d = 0x10 - *(int *)(root + 0xbba);
        *(int *)(root + 0xf06) = d;
        if (d <= 0) {
            *(int *)(root + 0xf06) = 0;
            iVar4 = (int)func_ov003_0204f460;
        }
    }
    func_ov003_0204ef68(root);
    if (iVar4 == 0) {
        ((Ov003RootTail *)root)->nStateTicks =
            ((Ov003RootTail *)root)->nStateTicks + 1;
    } else {
        ((Ov003RootTail *)root)->nStateTicks = 0;
    }
    return iVar4;
}
