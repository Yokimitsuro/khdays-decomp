/* Enter the "circle-strafe" state: cancel the current action (mode 6), face a random heading from
 * the RNG (angle -> sin/cos table into node[5]/[7]), zero the velocity via two kVecZero pushes
 * (modes 2 and 4), reset the strafe timers/flags and seed a fresh strafe duration (0x14 + d11) at
 * +0x6f, set the turn speed at +0x5c to 0x5000, and re-register the think callback.
 *
 * Rep of a 5-overlay byte-identical group (ov214/215/216/217/264).
 *
 * NON-MATCHING (equivalent), size-exact (320). Every idiom reproduces: the 0x28be60db9391 angle
 * divide into data_0203d210, the struct-by-value kVecZero pushes (ldmia/stmia), and the RNG
 * `+ 0x14`. The only residue is register allocation of the angle-math temporaries: the ROM colours
 * the 64-bit-multiply low half and the sin/cos table base with SCRATCH registers (r12, r3), while
 * mwcc 139 puts them in a callee-saved r6 (adding r3/r6 to the push list) -- 34 bytes of cascading
 * register fields. The matched template func_ov120_020ccd90 uses the identical angle idiom and
 * colours it with scratch, so this is a per-function register-pressure difference, not the idiom;
 * build_sweep shows no build reproduces it, and cast-chain / inlined-RNG spellings do not move it. */
struct Vec3 { int x, y, z; };
extern void func_ov107_020c9264(int owner, int mode, int b);
extern int func_02023f08(void);
extern short data_0203d210[];
extern struct Vec3 data_02041dc8;
extern void func_ov107_020c0b90(int owner, int mode, struct Vec3 v, int c);
extern int func_02023eb4();
extern void func_0203c634(int self, int idx, void *cb);
extern void func_ov214_020cdf24(void);

void func_ov214_020cdde4(int param_1) {
    int *node = *(int **)(param_1 + 4);
    int idx;
    struct Vec3 v;
    func_ov107_020c9264(*node, 6, 0);
    idx = (int)(((unsigned)(((long long)func_02023f08() * 0x28be60db9391LL + 0x80000000000LL) >> 0x20) << 4) >> 0x10) >> 4;
    node[5] = data_0203d210[idx * 2];
    node[6] = 0;
    node[7] = data_0203d210[idx * 2 + 1];
    v = data_02041dc8;
    func_ov107_020c0b90(*node, 2, v, 0);
    func_ov107_020c0b90(*node, 4, v, 0);
    *(char *)((char *)node + 0x70) = 0;
    *(char *)((char *)node + 0x71) = 0;
    *(char *)((char *)node + 0x73) = 0;
    *(char *)((char *)node + 0x6e) = 0;
    *(char *)((char *)node + 0x6f) = func_02023eb4(0xb) + 0x14;
    *(char *)((char *)node + 0x74) = 0;
    *(int *)((char *)node + 0x58) = 0;
    *(int *)((char *)node + 0x78) = 0;
    *(int *)((char *)node + 0x5c) = 0x5000;
    *(int *)((char *)node + 0x60) = 0;
    func_0203c634(param_1, *(signed char *)((char *)param_1 + 0x20), &func_ov214_020cdf24);
}
