/* If the card-transfer owner is already busy (+0x49c set) bail out; otherwise try to begin a
 * transfer via func_ov105_020bf5a8. On success return the follow-up handler; on failure flag
 * +0x4f0 and return null.
 *
 * NON-MATCHING (equivalent). Correct size (84) and instruction stream; the only residue is
 * register allocation: the ROM materialises the return value 0 in r0 up front and runs the
 * busy-field pointer chain through r1, while mwcc 139 runs the chain through r0 and re-zeroes it
 * with a movne. 12 bytes differ, all the r0<->r1 swap propagating. Tried: early-return vs
 * result-variable structures and both branch polarities. build_sweep: no mwcc build reproduces
 * it under our flags (1.2/sp3/sp4 hit size 84 but a different stream; not our toolchain). */

struct CardXferOwner {
    char _pad0[0x49c];
    int nBusy;                          /* +0x49c */
    char _pad1[0x4f0 - 0x49c - 4];
    unsigned char bStartFailed;         /* +0x4f0 */
};

extern struct CardXferOwner *data_ov008_02090f24;
extern int func_ov105_020bf5a8(void);
extern void func_ov008_0207a168(void);

void *func_ov008_0207a1c4(void) {
    if (data_ov008_02090f24->nBusy != 0) {
        return 0;
    }
    if (func_ov105_020bf5a8() != 0) {
        return (void *)func_ov008_0207a168;
    }
    data_ov008_02090f24->bStartFailed = 1;
    return 0;
}
