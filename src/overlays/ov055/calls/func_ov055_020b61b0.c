/* Starts one sequence slot of the ov036 enemy (x4: ov036/054/074/091): clears its timer, sets
 * phase 1, binds tracks 0 and 2 of its animation to its own blend table (+0xe4) and rewinds
 * them, draws three random offsets scaled by 0x99a/0x1000 into +0x110/+0x114/+0x118, and resets
 * the rig's state pair at +0x2da0 (the +0x2da4 word only when the state was not 2). */
typedef long long s64;

extern void func_0202accc(void *animation, int track, void *table, short mode);   /* BindAnimTrack */
extern void func_01fff774(void *animation, int track, int frame);                /* Anim_SetFrameWrapped */
extern int func_0203084c(void);                                                  /* Session_RandNext */
extern char *data_ov055_020b7740;

void func_ov055_020b61b0(char *slot)
{
    char *rig = data_ov055_020b7740 + 0x194 + 0x2c00;
    int randomOffset;

    *(int *)(slot + 0x10c) = 0;
    *(int *)slot = 1;
    func_0202accc(slot + 4, 0, slot + 0xe4, 0);
    func_0202accc(slot + 4, 2, slot + 0xe4, 0);
    func_01fff774(slot + 4, 0, 0);
    func_01fff774(slot + 4, 2, 0);
    randomOffset = func_0203084c() - 0x800;
    *(int *)(slot + 0x110) = (int)(((s64)randomOffset * 0x99a + 0x800) >> 12);
    randomOffset = func_0203084c() - 0x800;
    *(int *)(slot + 0x114) = (int)(((s64)randomOffset * 0x99a + 0x800) >> 12);
    randomOffset = func_0203084c() - 0x800;
    *(int *)(slot + 0x118) = (int)(((s64)randomOffset * 0x99a + 0x800) >> 12);
    if (*(int *)(rig + 0xc) != 2) {
        *(int *)(rig + 0x10) = 0;
    }
    *(int *)(rig + 0xc) = 0;
}
