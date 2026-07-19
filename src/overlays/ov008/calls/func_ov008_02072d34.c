extern void func_ov008_02050c3c(void);
extern int func_ov008_02050ff8(void);
extern int func_ov008_02051028(void);
extern void func_ov008_02070c58(char *self);
extern void func_ov008_02070a08(char *self);
extern void func_ov008_02070dd8(char *self);
extern void func_ov008_02070b20(char *self);
extern void func_ov008_02070b44(char *self);

/* Draws the shop row in the style the current mode calls for. */
void func_ov008_02072d34(char *self) {
    func_ov008_02050c3c();
    if (func_ov008_02050ff8() != 0) {
        if (func_ov008_02051028() != 0) {
            func_ov008_02070c58(self);
            return;
        }
        func_ov008_02070a08(self);
        func_ov008_02070dd8(self);
        return;
    }
    if (*(int *)(self + 0x38) != 0) {
        func_ov008_02070b20(self);
    } else {
        func_ov008_02070b44(self);
    }
    func_ov008_02070dd8(self);
}
