/* Second halfword of the entry cached at +0x4a4 of the ov002 root context, or 0 when
 * no entry is cached.  Twin of func_ov002_0205e1b8; see that file for why the +0x4a4
 * step is a separate, cast, constant-on-the-left assignment. */
extern int data_ov002_0207f620;

unsigned int func_ov002_0205e1d4(void) {
    char *ctx;
    int entry;
    unsigned int value;

    ctx = *(char **)&data_ov002_0207f620;
    value = 0;
    ctx = (char *)(0x4a4 + (int)ctx);
    entry = *(int *)ctx;
    if (entry != 0) {
        value = *(unsigned short *)(entry + 2);
    }
    return value;
}
