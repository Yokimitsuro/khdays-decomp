extern void func_ov025_02084a64(void);
extern int func_ov025_02084e08(void);
extern int func_ov025_02084e38(void);
extern void func_ov025_020a61fc(char *self);
extern void func_ov025_020a5fac(char *self);
extern void func_ov025_020a62bc(char *self);
extern void func_ov025_020a60c4(char *self);
extern void func_ov025_020a60e8(char *self);

/* Draws the shop row in the style the current mode calls for. */
void func_ov025_020a82f8(char *self) {
    func_ov025_02084a64();
    if (func_ov025_02084e08() != 0) {
        if (func_ov025_02084e38() != 0) {
            func_ov025_020a61fc(self);
            return;
        }
        func_ov025_020a5fac(self);
        func_ov025_020a62bc(self);
        return;
    }
    if (*(int *)(self + 0x38) != 0) {
        func_ov025_020a60c4(self);
    } else {
        func_ov025_020a60e8(self);
    }
    func_ov025_020a62bc(self);
}
