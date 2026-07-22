/* func_ov002_02075528 -- split a path at the offset func_ov002_020754bc reports: the tail goes to
 * the caller's `b` buffer and the head (minus the two-character separator) replaces `a`.
 * Both buffers are cleared to 0x100 bytes first.
 * The stack layout is the offset at sp+0 and the 0x100-byte scratch at sp+4, which is why the
 * scratch is declared FIRST -- mwcc gives the lower address to the later declaration. */
extern void INITi_CpuClear32_0x01ff86fc(int value, void *dst, unsigned int size);
extern int func_ov002_020754bc(char *a, int *out);
extern void func_0201f924(char *dst, const char *src);
extern char *strncpy(char *dst, const char *src, unsigned int n);

void func_ov002_02075528(char *a, char *b) {
    char buf[0x100];
    int n;

    n = 0;
    INITi_CpuClear32_0x01ff86fc(0, b, 0x100);
    if (func_ov002_020754bc(a, &n) == 0) {
        return;
    }
    INITi_CpuClear32_0x01ff86fc(0, buf, 0x100);
    func_0201f924(b, a + n);
    strncpy(buf, a, n - 2);
    func_0201f924(a, buf);
}
