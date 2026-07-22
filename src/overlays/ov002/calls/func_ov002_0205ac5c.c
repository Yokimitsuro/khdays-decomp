/* Clear the two 0x1c-byte blocks at +0x200 and +0x240 of request kind 9's
 * object, then close the request. */
extern char *func_ov002_02053bb8(int kind);
extern void MIi_CpuClear16(int value, void *dst, int size);
extern void func_ov002_02053cd4(int kind);

void func_ov002_0205ac5c(void) {
    char *obj = func_ov002_02053bb8(9);

    MIi_CpuClear16(0, obj + 0x200, 0x1c);
    MIi_CpuClear16(0, obj + 0x240, 0x1c);
    func_ov002_02053cd4(9);
}
