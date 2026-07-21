/* NON-MATCHING: pool-load scheduling tie (2 instructions swapped).
 * Family of 4: ov033_020b350c / ov051_020b5d0c / ov071_020b83ec / ov089_020baaac.
 *
 * Reset the enemy's state flags, re-arm its animation slot, rebuild the model handle from the
 * shared descriptor, reinit the 0xca-byte scratch block at +0xda0, then mark it built (flags |= 9).
 * The flag/model pair lives at obj+0x22f8 +0x334/+0x340; holding that base in a local keeps it in a
 * callee-saved register across the calls, exactly as the ROM does (without it mwcc re-derives
 * obj+0x2000 at each access, +4 bytes).
 *
 * With that fixed the size is exact and the only residue is the position of the descriptor's
 * literal-pool load relative to the 4th argument's add:
 *      ROM : ldr r2,[r5,#0x20] ; ldrb r1,[r5,#9] ; add r3,r2,#4 ; ldr r0,[pc] ; mov r2,#0 ; bl
 *      mwcc: ldr r2,[r5,#0x20] ; ldrb r1,[r5,#9] ; ldr r0,[pc] ; add r3,r2,#4 ; mov r2,#0 ; bl
 * mwcc hoists the `ldr [pc]` ahead of the argument arithmetic and will not be talked out of it:
 * precomputing the 4th argument into a local, and declaring the descriptor local after it, both
 * leave the pair swapped. build_sweep reports "8 off" on every one of the 27 builds, so no
 * available compiler schedules it the ROM's way -- the same retail-scheduler pool-hoist difference
 * already filed for ov030_020b3f30.
 */

extern void func_ov022_020b15b0(int slot, int mode);
extern int func_ov022_020b14a4(int desc, int slot, int flag, int params);
extern void func_ov022_020b1cec(int block, int size);
extern char data_ov033_020b4b3c[];

void func_ov033_020b350c(int obj) {
    char *blk = (char *)(obj + 0x22f8);
    *(unsigned char *)(blk + 0x334) = 0;
    func_ov022_020b15b0(*(unsigned char *)(obj + 9), 1);
    *(int *)(blk + 0x340) = func_ov022_020b14a4((int)data_ov033_020b4b3c,
                                                *(unsigned char *)(obj + 9), 0,
                                                *(int *)(obj + 0x20) + 4);
    func_ov022_020b1cec(obj + 0xda0, 0xca);
    *(unsigned char *)(blk + 0x334) |= 9;
}
