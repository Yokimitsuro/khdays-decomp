extern int func_02030788(void);
extern void func_ov002_0206cd60(int a, int b);
extern void func_ov022_020a35f4(int obj, int a);
extern int data_0204c240;

void func_ov022_02097d50(int arg0, int arg1) {
    *(int *)(arg0 + 0x698) = 0;
    *(int *)(arg0 + 0x69c) = 0x630;
    *(int *)(arg0 + 0x6a0) = 0;
    if (func_02030788() == 0) {
        *(unsigned long long *)(arg0 + 0x464) |= 0x20LL;
    }
    if (arg1 == 0 && (*(unsigned char *)&data_0204c240 & 4) == 0) {
        if ((*(unsigned int *)arg0 & 0x10000) == 0 && *(unsigned char *)(arg0 + 9) == 0)
            func_ov002_0206cd60(1, 3);
    }
    func_ov022_020a35f4(arg0, 1);
}
