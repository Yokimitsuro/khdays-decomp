/* func_ov025_020a8f58 -- rebuild the ov025 panel's live sub-views. Clears the "ready" flag
 * (obj[0x141]) while rebuilding each present part, then marks ready and clears the dirty flag
 * (obj[0x140]). */
extern void func_ov025_020a84dc(unsigned int *obj);
extern void func_ov025_020a8578(int obj);
extern void func_ov025_020a85d8(unsigned int *obj);
extern void func_ov025_020a88e8(int obj);

void func_ov025_020a8f58(unsigned int *param_1) {
    param_1[0x141] = 0;
    if (param_1[0xc] != 0) {
        func_ov025_020a84dc(param_1);
    }
    if (param_1[0xd] != 0) {
        func_ov025_020a8578((int)param_1);
    }
    if (param_1[0x1a] != 0) {
        func_ov025_020a85d8(param_1);
    }
    if (*(unsigned short *)(param_1 + 0x17) != 0) {
        func_ov025_020a88e8((int)param_1);
    }
    param_1[0x141] = 1;
    param_1[0x140] = 0;
}
