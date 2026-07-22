/* Opens the two resources named by data_ov023_0208a074 / data_ov023_0208a084 (mode 0xe),
 * binds the first into the descriptor at +0xc and registers it as display 5 with parameters
 * 0x15 / 2, then stores the second handle at +0. */
extern int func_0201ef9c(char *name, int mode);
extern void func_02024c94(char *dst, int h, int a, int b, int c);
extern void func_02024ba4(int a, int b, int c, int d, int e, int f);
extern int func_02024c1c(char *dst, char *name, int mode);
extern char data_ov023_0208a074[];
extern char data_ov023_0208a084[];

void func_ov023_020832e4(char *self) {
    int zero = 0;
    *(int *)(self + 4) = func_0201ef9c(data_ov023_0208a074, 0xe);
    func_02024c94(self + 0xc, *(int *)(self + 4), zero, zero, zero);
    func_02024ba4(5, *(int *)(self + 0xc), *(int *)(self + 0x10), *(int *)(self + 0x14),
                  0x15, 2);
    *(int *)self = func_02024c1c(self + 8, data_ov023_0208a084, 0xe);
}
