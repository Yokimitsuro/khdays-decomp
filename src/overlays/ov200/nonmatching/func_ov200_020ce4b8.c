/*
 * NON-MATCHING: byte-exact (384B) EXCEPT ~11 bytes of register colouring on the `self+0x100` base in
 * blocks 1 and 3. The mode/dirty bytes are read with ldrsb, whose offset is 8-bit, so they must load
 * as `add rX,self,#0x100; ldrsb [rX,#0xc6/0xc7]` -- expressed as ((signed char*)(self+0x100))[0xc6]
 * (the store of +0x1c7 keeps a plain 12-bit strb). The ROM colours the base r0 (block1) / r5 (block3)
 * with dirty->r2 and the loop zero->r6; mwcc 3.0/139 colours base->r2 / r6 with dirty->r1 and zero->r5.
 * Reversing the ==-1 test and reordering did not flip it -- a self+0x100-base register-allocation tie.
 * Result is identical.
 */
/*
 * func_ov200_020ce4b8 -- x3 (ov200/...). Deactivate the aim sub-nodes and release the spawned
 * sub-objects on state exit. If either "leaving" bit (1 or 3) of *(self+0x1c4) is set, deactivate all
 * three sub-nodes (020d0508) and, when the dirty byte +0x1c7 is -1 and the mode +0x1c6 is not one of
 * {0,1,3,8,9}, latch +0x1c7 = 8. Deactivate node 0 if it is in mode 1 and the state mode is not 6;
 * deactivate nodes 1 and 2 if they are in mode 1 and the mode is not 7. Release the primary sub-object
 * +0x3b4 unless mode 6; release +0x3b8 (unless mode 7, and only once both side nodes' 0x38 nibble is
 * zero); release +0x3b0 unless mode 6 or 7. Finish by ticking 020c7ca4(self).
 */
extern void func_ov200_020d0508(int node, int flag);
extern int func_ov200_020d0540(int node);
extern int func_ov200_020d055c(int node);
extern void func_ov107_020cb100(int handle);
extern void func_ov107_020c7ca4(int self);

void func_ov200_020ce4b8(int self) {
    int i;

    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0) {
        func_ov200_020d0508(*(int *)(self + 0x390), 0);
        for (i = 1; i < 3; i++) {
            func_ov200_020d0508(((int *)self)[i + 0xe4], 0);
        }
        if (((signed char *)(self + 0x100))[0xc7] == -1) {
            signed char m = ((signed char *)(self + 0x100))[0xc6];
            if (m != 0 && m != 1 && m != 3 && m != 8 && m != 9) {
                *(signed char *)(self + 0x1c7) = 8;
            }
        }
    }
    if (func_ov200_020d0540(*(int *)(self + 0x390)) != 0 && ((signed char *)(self + 0x100))[0xc6] != 6) {
        func_ov200_020d0508(*(int *)(self + 0x390), 0);
    }
    for (i = 1; i < 3; i++) {
        if (func_ov200_020d0540(((int *)self)[i + 0xe4]) != 0 &&
            ((signed char *)(self + 0x100))[0xc6] != 7) {
            func_ov200_020d0508(((int *)self)[i + 0xe4], 0);
        }
    }
    if (((signed char *)(self + 0x100))[0xc6] != 6 && *(int *)(self + 0x3b4) != 0) {
        func_ov107_020cb100(*(int *)(self + 0x3b4));
        *(int *)(self + 0x3b4) = 0;
    }
    if (((signed char *)(self + 0x100))[0xc6] != 7 &&
        func_ov200_020d055c(*(int *)(self + 0x398)) != 0 &&
        func_ov200_020d055c(*(int *)(self + 0x394)) != 0 &&
        *(int *)(self + 0x3b8) != 0) {
        func_ov107_020cb100(*(int *)(self + 0x3b8));
        *(int *)(self + 0x3b8) = 0;
    }
    if (((signed char *)(self + 0x100))[0xc6] != 6 && ((signed char *)(self + 0x100))[0xc6] != 7 &&
        *(int *)(self + 0x3b0) != 0) {
        func_ov107_020cb100(*(int *)(self + 0x3b0));
        *(int *)(self + 0x3b0) = 0;
    }
    func_ov107_020c7ca4(self);
}
