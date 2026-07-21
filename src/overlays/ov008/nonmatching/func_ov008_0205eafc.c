/* Blit the object's cached glyph bitmap (dst +0x2f4, size +0x2ec) from its render context (+0x20),
 * optionally queue a draw command for row param_2 (stride 0xe, +4), then flush the object's gfx
 * command list.
 *
 * NON-MATCHING (equivalent). Everything is right except a 4-byte instruction-scheduling choice
 * around the MIi_CpuCopyFast call: the ROM loads src = *(ctx+0x20) straight out of the call's
 * return register before reusing r0 for dst = *(param_1+0x2f4) (keeping param_1 in r7), whereas
 * mwcc 139 spills the call result with an extra `mov r1,r0`, loads dst first, then src (param_1 in
 * r4). Tried ctx/src temporaries and inlining the call into the argument; the scheduler doesn't
 * budge. */
extern int func_020303b4(int obj);
extern void MIi_CpuCopyFast(void *dst, const void *src, unsigned int size);
extern void func_0203031c(int obj, int a, int b, int p4, int c, int p3);
extern void func_020300f8(int obj);

void func_ov008_0205eafc(int param_1, int param_2, int param_3, int param_4) {
    int ctx = func_020303b4(param_1 + 0xe8);
    MIi_CpuCopyFast(*(void **)(param_1 + 0x2f4), *(void **)(ctx + 0x20), *(unsigned int *)(param_1 + 0x2ec));
    if (param_3 != 0) {
        func_0203031c(param_1 + 0xe8, 8, param_2 * 0xe + 4, param_4, 0xf1, param_3);
    }
    func_020300f8(param_1 + 0xe8);
}
