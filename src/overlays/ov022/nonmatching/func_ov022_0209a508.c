extern int func_02035924(int a);
extern void func_ov022_020aa824(int p, int param2, int param4, int flag);
extern int func_ov022_020882f8(void);
extern int func_01fffde0(int i);
extern int func_ov022_020ad61c(int a, int param4);

unsigned int func_ov022_0209a508(int obj, int param2, int param3, int param4) {
    int *p = *(int **)(obj + 0x18c);
    unsigned int uVar4 = 1;
    int i;
    if (*(unsigned short *)((int)p + 0x12) == 0) goto ret0;
    i = 0;
    if ((*(unsigned long long *)p & 0x20000LL) != 0) goto ret0;
    if ((*(unsigned long long *)p & 0x100LL) != 0) goto ret0;
    switch (param3) {
    case 0: case 1: case 2: case 3: case 4: case 5:
        break;
    case 6: case 7: case 8: case 9: case 10: case 11: case 12:
        if (func_02035924(*(unsigned char *)((int)p + 9)) != 0) uVar4 = 0;
        else func_ov022_020aa824((int)p, param2, param4, uVar4);
        break;
    case 13:
        if (func_ov022_020882f8() > 0) {
            do {
                if (func_ov022_020ad61c(func_01fffde0(i), param4) != 0) { uVar4 = 0; goto done; }
                i++;
            } while (i < func_ov022_020882f8());
        }
        break;
    case 14:
        break;
    }
done:
    return uVar4;
ret0:
    return 0;
}
