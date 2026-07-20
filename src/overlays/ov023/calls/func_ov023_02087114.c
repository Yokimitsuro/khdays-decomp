/* Script-VM command: fetch four operands and route to one of two handlers on the
 * fourth. Byte-identical twin of func_ov106_020b83c4 -- same code, same relocs,
 * so the same command exists in both overlays and both call the SAME pair of
 * handlers (one living in ov023, one in ov106).
 *
 * The first operand is biased by -0x10 before use, which is why it is computed
 * into a local rather than passed inline.
 */
extern int func_02021980(void *self, void *desc);
extern void func_ov023_02083d2c(int a, int b, int c);
extern void func_ov106_020b81e4(int a, int b);

int func_ov023_02087114(void *self, char *descs) {
    int base;
    int arg;
    int extra;

    base = func_02021980(self, descs) - 0x10;
    arg = func_02021980(self, descs + 0x8);
    extra = func_02021980(self, descs + 0x10);
    if (func_02021980(self, descs + 0x18) == 0) {
        func_ov023_02083d2c(extra, base, arg);
    } else {
        func_ov106_020b81e4(base, arg);
    }
    return 1;
}
