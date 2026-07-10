/*
 * [nonmatching: param-spill tie: func_ov022_02090c04 5-arg call spills the incoming params to the stack differently than the original (same class as 02091298)]
 *
 * Structurally equivalent; mwcc 3.0/139 diverges only in the noted
 * register allocation / block layout. Left uncarved (byte-exact in the blob).
 */
extern void func_ov022_02090c04(int arg0, int arg1, unsigned short *arg2, int arg3, int arg4);
extern void func_ov022_02090c7c(unsigned char *arg0, int arg1, unsigned int *arg2, unsigned char arg3);

void func_ov022_02091254(int arg0, int arg1, unsigned int *arg2, unsigned short *arg3) {
    int i;
    func_ov022_02090c04(arg0, arg1, arg3, 1, (int)*(char *)((int)arg3 + 0x4c));
    i = 0;
    if ((int)*(unsigned char *)(arg0 + 0x19) > 0) {
        int off = 0;
        do {
            func_ov022_02090c7c((unsigned char *)(*(int *)(arg0 + 0xc) + off),
                                *(unsigned char *)(arg1 + 9), arg2, (unsigned char)i);
            off = off + 0x1c8;
            i = i + 1;
        } while (i < *(unsigned char *)(arg0 + 0x19));
    }
}
