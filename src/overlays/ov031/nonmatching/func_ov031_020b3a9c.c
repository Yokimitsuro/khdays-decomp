/* func_ov031_020b3a9c (x4 family: ov050/070/088) - NON-MATCHING (1 instr / few bytes).
 * A 452B state machine. Everything matches after these cracks: two u64 AND-compares
 * spelled `(*(unsigned long long*)((char*)this+0x464) & MASK)` (the `char*` cast + ULL
 * mask forces the DIRECT hi load [this+0x468] the orig uses here, vs the split this+0x64+0x404
 * form); the `0x2f||0x30` bare-return OR via double-negation `if(!(x!=0x2f&&x!=0x30))return;`
 * (defeats range-reduction); 7-case jump-table switch with all 6 non-zero bodies + the case-5
 * break->post-block. SOLE remaining diff: the empty `case 0`/`default` returns - the original
 * inlines two `pop` instructions directly in the jump table; mwcc branches both to a shared
 * return epilogue (+1 instr with an explicit case 0; a byte-layout diff without it). Switch
 * empty-case return-inlining tie - not steerable by case-0 presence/order. asm stub byte-exact. */
extern int func_ov022_02095524(int a);
extern void func_ov031_020b3a38(int a, int b, int c);
extern int func_0202a818(void *a, int b);
extern void func_ov031_020b3a00(int a);

void func_ov031_020b3a9c(int this, int param_2, int param_3) {
    int base2c2c = this + 0x2c2c;
    int state = *(int *)(param_2 + 4);
    if (state != 0) {
        if (state != 6 && *(int *)(this + 0x6bc) != 0x2e &&
            (*(unsigned long long *)((char *)this + 0x464) & 0x10000ULL) == 0 &&
            func_ov022_02095524(this + 0x22f8) == 0) {
            func_ov031_020b3a38(param_2, 2, 0xf000);
            *(int *)(param_2 + 4) = 6;
        }
        if ((*(unsigned long long *)((char *)this + 0x464) & 0x4000000000ULL) != 0) {
            *(int *)(param_2 + 4) = 0;
        }
    }
    switch (*(int *)(param_2 + 4)) {
    case 0:
        return;
    case 1:
        if (func_0202a818((void *)(param_2 + 8), param_3) == 0) return;
        func_ov031_020b3a38(param_2, 1, 0);
        *(int *)(param_2 + 4) = 2;
        return;
    case 2:
        func_0202a818((void *)(param_2 + 8), param_3);
        return;
    case 3:
        func_0202a818((void *)(param_2 + 8), param_3);
        {
            int t = *(int *)(param_2 + 0x114) + param_3;
            *(int *)(param_2 + 0x114) = t;
            if (t < *(int *)(param_2 + 0x110)) return;
        }
        {
            int s = 2;
            if (*(int *)base2c2c != 0) s = 3;
            func_ov031_020b3a38(param_2, s, 0);
        }
        *(int *)(param_2 + 4) = 4;
        return;
    case 4:
        if (func_0202a818((void *)(param_2 + 8), param_3) != 0) *(int *)(param_2 + 4) = 5;
        return;
    case 5:
        break;
    case 6:
        if (func_0202a818((void *)(param_2 + 8), param_3) != 0) *(int *)(param_2 + 4) = 0;
        return;
    default:
        return;
    }
    if (!(*(int *)(this + 0x6bc) != 0x2f && *(int *)(this + 0x6bc) != 0x30)) return;
    if (func_ov022_02095524(this + 0x22f8) == 0) {
        *(int *)(param_2 + 4) = 0;
        return;
    }
    func_ov031_020b3a00(param_2);
}
