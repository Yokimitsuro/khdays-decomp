/*
 * [nonmatching: byte-marshal: the uninitialized-then-masked stack byte build (buf[0]&0xfc|.. ; buf[0]&3|..|0x80) and the local_c=param_2 store lower to a different shape (20B short)]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
extern unsigned short func_01fffe14(void);
extern void func_02031258(int arg0, unsigned short *arg1, int arg2);

void func_ov022_020947a4(int arg0, int arg1) {
    unsigned char buf[4];
    int extra;
    buf[0] = buf[0] & 0xfc | *(unsigned char *)(*(int *)(arg0 + 0x328) + 9) & 3;
    buf[0] = buf[0] & 3 | (unsigned char)(((unsigned int)func_01fffe14() << 0x1d) >> 0x1b) | 0x80;
    extra = arg1;
    func_02031258(0x10, (unsigned short *)buf, 8);
    (void)extra;
}
