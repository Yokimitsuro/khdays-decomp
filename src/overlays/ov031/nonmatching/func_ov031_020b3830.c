/* func_ov031_020b3830 (x4 family: ov050/070/088) - NON-MATCHING.
 * Byte-exact except a const-materialization scheduler-slot tie: for each of the 3
 * func_ov022_020b14a4 calls the original computes arg3 (add r3,..) BEFORE loading arg0
 * (ldr r0,[pc] = the &data_ov031_020b4d* pool word); mwcc hoists the pool-load first,
 * swapping those two instructions. Named-temp for arg3 did not move it. Same class as
 * ov149_020cfe6c / the const-slot ties. Everything else (2-arg func_ov022_020b15b0 with
 * stale r2/r3, this+0x22f8 base, split this+0x2644 access) matches. asm stub stays byte-exact. */
extern void func_ov022_020b15b0(int a, int b);
extern int func_ov022_020b14a4(void *a, int b, int c, int d);
extern void func_ov022_020b1cec(int a, int b);
extern int data_ov031_020b4d24;
extern int data_ov031_020b4d34;
extern int data_ov031_020b4d48;

void func_ov031_020b3830(int this, int param_2, int param_3, int param_4) {
    int base = this + 0x22f8;
    *(char *)(base + 0x334) = 0;
    func_ov022_020b15b0(*(unsigned char *)(this + 9), 3);
    {
        int a3 = *(int *)(this + 0x20) + 4;
        *(int *)(base + 0x340) =
            func_ov022_020b14a4(&data_ov031_020b4d24, *(unsigned char *)(this + 9), 0, a3);
    }
    {
        int a3 = *(int *)(*(int *)(this + 0x2644) + 0x6c) + 0x28;
        *(int *)(base + 0x344) =
            func_ov022_020b14a4(&data_ov031_020b4d34, *(unsigned char *)(this + 9), 1, a3);
    }
    {
        int a3 = *(int *)(*(int *)(this + 0x2644) + 0xc) + 0x28;
        *(int *)(base + 0x348) =
            func_ov022_020b14a4(&data_ov031_020b4d48, *(unsigned char *)(this + 9), 2, a3);
    }
    func_ov022_020b1cec(this + 0xda0, 0xcb);
    *(unsigned char *)(base + 0x334) |= 0xf;
}
