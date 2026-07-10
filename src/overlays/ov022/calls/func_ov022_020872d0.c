extern int NNSi_FndGetCurrentRootHeap(void);
extern int func_02023c40(void);
extern void func_ov022_0209fb50(int on);
extern void FS_UnloadOverlayImage_0x020362ec(int a);
extern int func_02030788(void);
extern void func_ov022_0208739c(int a);
extern void func_ov022_02087ac0(int a);
extern void func_ov022_020876f0(int a);
extern void func_ov022_02087f7c(void);
extern void func_ov022_020b201c(int a);
extern void func_ov022_02087f30(void);
extern int data_0204be04;

int func_ov022_020872d0(void) {
    int heap = NNSi_FndGetCurrentRootHeap();
    unsigned int mode;
    func_ov022_0209fb50(func_02023c40() == 1);
    FS_UnloadOverlayImage_0x020362ec(heap + 0x4c);
    mode = *(unsigned char *)&data_0204be04;
    if (mode == 0) {
        int t = func_02030788();
        if (t == 0) func_ov022_0208739c(t);
        else func_ov022_02087ac0(t);
    } else {
        func_ov022_020876f0(mode);
    }
    func_ov022_02087f7c();
    func_ov022_020b201c(heap + 0x68);
    func_ov022_02087f30();
    return 0;
}
