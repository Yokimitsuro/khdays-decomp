extern char *func_ov008_02050cec(void);
extern char *func_ov008_02051198(void);
extern void func_ov008_02050a64(int a);
extern void func_ov008_02050ab8(int a);
extern void func_ov008_02078aa4(void);
extern int func_02024ee8(void *name, int slot);
extern void func_ov008_02078bb0(int a);
extern void func_ov008_02078c48(void);
extern void func_ov008_02078cf0(void);
extern void func_ov008_020788f4(void);
extern int data_ov008_02090b88;
extern int data_ov008_02090b9c;

/* Brings the shop screen up: republishes the current entry, loads the two sprite sets and
 * initialises the widgets. */
int func_ov008_02078df0(void) {
    char *self = func_ov008_02050cec();
    func_ov008_02050a64(*(int *)(func_ov008_02051198() + 0xc));
    func_ov008_02050ab8(*(int *)(func_ov008_02051198() + 0xc) == 0);
    func_ov008_02078aa4();
    *(int *)(self + 0x30) = func_02024ee8(&data_ov008_02090b88, 0xe);
    *(int *)(self + 0x34) = func_02024ee8(&data_ov008_02090b9c, 0xe);
    func_ov008_02078bb0(1);
    func_ov008_02078c48();
    func_ov008_02078cf0();
    func_ov008_020788f4();
    return 1;
}
