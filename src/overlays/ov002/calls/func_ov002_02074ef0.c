/* Resolve four consecutive 8-byte descriptors (offsets 0, 8, 0x10, 0x18) through
 * func_02021980 and hand the four results to func_ov002_0206ac2c. Always
 * reports success. */
extern int func_02021980(void *self, void *desc);
extern void func_ov002_0206ac2c(int a, int b, int c, int d);

int func_ov002_02074ef0(void *self, char *descs) {
    int a = func_02021980(self, descs);
    int b = func_02021980(self, descs + 8);
    int c = func_02021980(self, descs + 0x10);
    int d = func_02021980(self, descs + 0x18);

    func_ov002_0206ac2c(a, b, c, d);
    return 1;
}
