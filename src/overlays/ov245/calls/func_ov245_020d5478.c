/* Notify func_ov107_020c5c54; if owner flag bit1 (param_1+0x40) is set, invoke the owner's
 * hook (*(param_1+0xc))(param_1,0) when present. Re-arm via func_0203c7ac(owner->f384,0),
 * and if the owner is in state 1 (+0x50), forward param_3 to func_ov245_020d5ab8. */
extern void func_ov107_020c5c54(int a, int b);
extern void func_0203c7ac(int a, int b);
extern void func_ov245_020d5ab8(int *a, void *b);
void func_ov245_020d5478(int param_1, int param_2, void *param_3, int param_4) {
    func_ov107_020c5c54(param_1, param_2);
    if ((*(int *)(param_1 + 0x40) << 0x1e) >> 0x1f) {
        void (*fn)(int, int) = *(void (**)(int, int))(param_1 + 0xc);
        if (fn != 0) {
            fn(param_1, 0);
        }
    }
    func_0203c7ac(*(int *)(param_1 + 0x384), 0);
    if (*(int *)(param_1 + 0x50) == 1) {
        func_ov245_020d5ab8(*(int **)(param_1 + 0x214), param_3);
    }
}
