extern int func_02023eb4(int);
extern void func_0203c634(int, int, void *);
extern void func_ov203_020d4770(void);
extern void func_ov203_020d44cc(void);
extern void func_ov203_020d4684(void);

struct flagword { unsigned f8 : 8; };

void func_ov203_020d43cc(int param_1) {
    int *obj = *(int **)(param_1 + 4);
    unsigned short h;
    int lo, range;

    *(char *)(*obj + 0x1c6) = 0;
    *(char *)(*obj + 0x1c7) = -1;
    ((struct flagword *)(*(int *)(*obj + 0x38c) + 8))->f8 &= ~1;
    obj[0xf] = *obj + 0xb0;
    obj[0x10] = *obj + 0x74;
    obj[0x11] = *(int *)(*obj + 900) + 0xad;
    h = *(unsigned short *)(*obj + 0x60);
    *(unsigned short *)(*obj + 0x60) =
        h & ~0xff00 | (((((unsigned int)h << 0x10) >> 0x18 | 6) << 0x18) >> 0x10);
    lo = *(int *)(*obj + 0x224);
    range = *(int *)(*obj + 0x228) - lo;
    if (range < 0) {
        range = -range;
    }
    obj[0xc] = lo + func_02023eb4(range + 1);
    func_0203c634(param_1, 1, func_ov203_020d4770);
    func_0203c634(param_1, 0, func_ov203_020d44cc);
    func_0203c634(param_1, 2, func_ov203_020d4684);
}
