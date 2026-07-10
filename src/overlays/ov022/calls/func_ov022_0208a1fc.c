extern int func_ov022_020882f8(void);
extern int func_ov022_020886f8(int i);
extern int func_ov022_020882bc(int i);
extern int data_ov022_020b2ea4;

void func_ov022_0208a1fc(void) {
    int i;
    int iVar1 = func_ov022_020882f8();
    int iVar2 = data_ov022_020b2ea4;
    int base;
    if (iVar2 == 0) {
        return;
    }
    base = iVar2 + 0x14;
    i = 0;
    if (0 < iVar1) {
        do {
            if (func_ov022_020886f8(i) == 0) {
                int iVar4 = func_ov022_020882bc(i) * 6 + base;
                *(unsigned short *)(iVar4 + 0x86) =
                    ~*(unsigned short *)(iVar4 + 0x88) & *(unsigned short *)(iVar4 + 0x84);
                *(unsigned short *)(iVar4 + 0x88) = *(unsigned short *)(iVar4 + 0x84);
            }
            i = i + 1;
        } while (i < iVar1);
    }
}
