extern void func_ov002_0206ea24(void);
extern void MIi_CpuClear16(int value, void *dst, int size);
extern char *data_ov002_0207fa04;
/* Run the pre-step, then (unless already in state 2) enter it and blank the 8-byte id array. */
void func_ov002_0206eaf8(void) {
    int ctx = (int)data_ov002_0207fa04;
    func_ov002_0206ea24();
    if ((*(unsigned short *)ctx & 2) != 0) {
        return;
    }
    *(unsigned short *)ctx = 2;
    MIi_CpuClear16(0xffff, (void *)(ctx + 2), 8);
}
