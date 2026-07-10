/*
 * [nonmatching: byte-copy-loop register-class tie: the original keeps dst/src/n in caller-saved r1/r2/r3 (no calls in the loop); mwcc parks them in callee-saved r4/r5/r6, changing the push set]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted
 * register allocation / block layout. Left uncarved (byte-exact in the blob).
 */
extern void func_ov022_02082960(void);
extern void func_0201e470(int arg0, int arg1);
extern int func_02023930(void *cls, void *buf);
extern void func_ov002_02078ef8(void);
extern int data_ov022_020b28bc;
extern int data_ov106_020b8aa0;
extern int data_ov022_020b2e60;

void func_ov022_020829f4(void) {
    char buf[72];
    func_ov022_02082960();
    func_0201e470(0, 0x6a);
    {
        char *dst = buf;
        char *src = (char *)&data_ov106_020b8aa0;
        int n = 0x18;
        do {
            *dst = *src;
            src = src + 1;
            dst = dst + 1;
            n = n - 1;
        } while (n != 0);
    }
    *(int *)(buf + 0x44) = 0;
    *(int *)((char *)&data_ov022_020b2e60 + 8) = func_02023930(&data_ov022_020b28bc, buf);
    func_ov002_02078ef8();
}
