/* NONMATCHING: address-CSE tie, 4 bytes short. `tbl + idx*2` appears in the guard
 * read, the first table store and the final result store; the original recomputes
 * it each time (`add r,tbl,idx,lsl#1` / `[tbl, idx2]` base+offset forms) while mwcc
 * CSEs it into one held register, saving the last recompute. Tried volatile reads,
 * operand association, and index-first addressing; none defeats the CSE. The bitfield
 * marshal, the RandNextScaled byte, and the 0xFFFF guard all reproduce. Semantics exact. */
extern int func_02030788(void);
extern int func_02023eb4(int max);
extern int func_02031384(int a, void *buf, int c);
extern int data_ov022_020b2ea4;

struct Buf02089fe8 {
    unsigned short w0;
    unsigned char b2;
    unsigned char b3;
    unsigned char lo3 : 3;
    unsigned char mid3 : 3;
    unsigned char hi2 : 2;
    unsigned char pad5;
};

void func_ov022_02089fe8(int idx, unsigned short param_2, unsigned char param_3) {
    int tbl = *(int *)&data_ov022_020b2ea4;
    struct Buf02089fe8 buf;
    if (tbl == 0) return;
    if (func_02030788() != 0) return;
    tbl += 0x14;
    if (*(unsigned short *)(tbl + idx * 2 + 0x9c) != 0xffff) return;
    buf.mid3 = idx;
    buf.w0 = param_2;
    buf.b2 = param_3;
    buf.b3 = (unsigned char)func_02023eb4(0xff);
    buf.lo3 = 0;
    *(unsigned short *)(tbl + idx * 2) = param_2;
    *(unsigned char *)(tbl + idx + 8) = param_3;
    *(unsigned char *)(tbl + idx + 0xc) = buf.b3;
    *(short *)(tbl + idx * 2 + 0x9c) = (short)func_02031384(0xf, &buf, 6);
}
