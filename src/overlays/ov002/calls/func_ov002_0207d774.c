/* Script opcode: resolve the entry named by operands 0 and 8, and report whether
 * it is still usable. Only kind-6 entries are actually consulted -- for anything
 * else the answer is a plain yes. Reports 1 when func_ov002_0207a744 says the
 * entry is free, 0 when it hands something back.
 *
 * The two operands are narrowed on the way in (byte and halfword, hence the
 * lsl/lsr pairs rather than an `and`), the same shape as
 * func_ov002_0207d450. */
extern int func_02021980(void *self, void *arg);
extern void *func_ov002_0207679c(unsigned char a, unsigned short b);
extern int func_ov002_0207a744(void *entry);

int func_ov002_0207d774(void *self, char *args) {
    int busy = 0;
    int a = func_02021980(self, args);
    int b = func_02021980(self, args + 8);
    void *entry = func_ov002_0207679c((unsigned char)a, (unsigned short)b);

    if (*(unsigned short *)(*(int *)((char *)entry + 8) + 0x4c) == 6) {
        busy = func_ov002_0207a744(entry);
    }

    if (busy != 0) {
        return 0;
    }
    return 1;
}
