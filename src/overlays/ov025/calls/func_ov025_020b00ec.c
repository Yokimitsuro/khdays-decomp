extern char *func_ov025_02084b14(void);
extern void func_ov025_020afdb0(void);
extern int func_ov025_02085078(void);
extern int func_020235d0(int id, int a);
extern void func_ov025_020afdd4(void);
extern int func_ov025_02084a64(void);
extern int func_ov025_02084a8c(void);
extern void func_ov025_020afef4(void);
extern void func_ov025_020b0090(void);
extern void func_ov025_020b0484(char *arg);

/* Brings the equip screen up: caches the page and the two active objects, reads the saved
 * category (bumped by one while it is below 6) and initialises the widgets. */
int func_ov025_020b00ec(char *arg) {
    char *self = func_ov025_02084b14();
    func_ov025_020afdb0();
    *(int *)(self + 0x54) = func_ov025_02085078();
    *(int *)(self + 0x58) = func_020235d0(0x44e, 3);
    if (*(int *)(self + 0x58) < 6) {
        *(int *)(self + 0x58) = *(int *)(self + 0x58) + 1;
    }
    func_ov025_020afdd4();
    *(int *)(self + 0x44) = func_ov025_02084a64();
    *(int *)(self + 0x48) = func_ov025_02084a8c();
    func_ov025_020afef4();
    func_ov025_020b0090();
    func_ov025_020b0484(arg);
    return 1;
}
