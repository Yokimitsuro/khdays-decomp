extern char *func_ov025_02084b14(void);
extern char *func_ov025_02084fa8(void);
extern void func_ov025_0208488c(int a);
extern void func_ov025_020848e0(int a);
extern void func_ov025_020af4fc(void);
extern int func_02024ee8(void *name, int slot);
extern void func_ov025_020af608(int a);
extern void func_ov025_020af6a0(void);
extern void func_ov025_020af748(void);
extern void func_ov025_020af34c(void);
extern int data_ov025_020b56bc;
extern int data_ov025_020b56d0;

/* Brings the shop screen up: republishes the current entry, loads the two sprite sets and
 * initialises the widgets. */
int func_ov025_020af848(void) {
    char *self = func_ov025_02084b14();
    func_ov025_0208488c(*(int *)(func_ov025_02084fa8() + 0xc));
    func_ov025_020848e0(*(int *)(func_ov025_02084fa8() + 0xc) == 0);
    func_ov025_020af4fc();
    *(int *)(self + 0x30) = func_02024ee8(&data_ov025_020b56bc, 0xe);
    *(int *)(self + 0x34) = func_02024ee8(&data_ov025_020b56d0, 0xe);
    func_ov025_020af608(1);
    func_ov025_020af6a0();
    func_ov025_020af748();
    func_ov025_020af34c();
    return 1;
}
