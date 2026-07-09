extern void func_ov025_020830d0();
extern void func_ov025_020851a0();
extern void func_ov025_0208527c();
extern int data_ov025_020b5744;

void func_ov025_02083648(void) {
    func_ov025_020830d0();
    func_ov025_020851a0(*(int *)(((int *)&data_ov025_020b5744)[1] + 0x959c));
    func_ov025_0208527c(*(int *)(((int *)&data_ov025_020b5744)[1] + 0x95a0));
}
