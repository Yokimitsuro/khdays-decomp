/*
 * [nonmatching: large-offset addressing split: the byte at 0x2c24 is reached via param_1+0xc20+0x2000 (reusing the counter base split) in the original; mwcc uses a different split (+4B)]
 *
 * Equivalent C; mwcc 3.0/139 diverges in the noted codegen. Left uncarved.
 */
extern int func_020307f4(int arg0);
extern void func_ov022_0209be44(int arg0);
extern void func_ov022_0209bec8(unsigned int *arg0);

void func_ov022_0209be64(unsigned int *arg0, int arg1) {
    unsigned int v = arg0[0xb08];
    arg0[0xb08] = v + arg1;
    if ((int)(v + arg1) < 0x384000) {
        return;
    }
    if (*(unsigned char *)((int)arg0 + 0x2c24) < func_020307f4(100)) {
        *(unsigned char *)((int)arg0 + 0x2c24) += 10;
        arg0[0xb08] = 0;
        return;
    }
    func_ov022_0209be44((int)arg0);
    func_ov022_0209bec8(arg0);
}
