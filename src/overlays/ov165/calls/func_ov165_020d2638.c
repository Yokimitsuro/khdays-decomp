extern int func_02023eb4(int);
extern void func_0203c634(int, int, void *);
extern void func_ov165_020d29d0(void);
extern void func_ov165_020d2734(void);
extern void func_ov165_020d28f4(void);

struct flagword { unsigned f8 : 8; };

void func_ov165_020d2638(int param_1) {
    int *obj = *(int **)(param_1 + 4);
    unsigned short h;
    int lo, range;

    *(char *)(*obj + 0x1c6) = 0;
    *(char *)(*obj + 0x1c7) = -1;
    ((struct flagword *)(*(int *)(*obj + 0x388) + 8))->f8 &= ~1;
    obj[0x14] = *obj + 0xb0;
    obj[0x15] = *obj + 0x74;
    obj[0x16] = *(int *)(*obj + 900) + 0xad;
    h = *(unsigned short *)(*obj + 0x60);
    *(unsigned short *)(*obj + 0x60) =
        h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    lo = *(int *)(*obj + 0x224);
    range = *(int *)(*obj + 0x228) - lo;
    if (range < 0) {
        range = -range;
    }
    obj[0xd] = lo + func_02023eb4(range + 1);
    func_0203c634(param_1, 1, func_ov165_020d29d0);
    func_0203c634(param_1, 0, func_ov165_020d2734);
    func_0203c634(param_1, 2, func_ov165_020d28f4);
}
