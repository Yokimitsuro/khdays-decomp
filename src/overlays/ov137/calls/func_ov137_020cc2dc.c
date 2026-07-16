/* func_ov137_020cc2dc -- retune the rig, then re-arm the emitter for kinds 6 and 7 only.
 * The rig at +0x388 is always retuned with the kind as a signed 16-bit selector and reset.
 * Kinds 6 and 7 then re-arm the emitter through func_ov107_020c09a0 with the anchor at +0x9c+0x30
 * and mode 5, differing only in the fifth argument (0 for kind 6, 1 for kind 7); the handle comes
 * back into +0x390's +0xc. Any other kind stops after the retune. */
extern void func_0203b9fc(int rig, int a, short kind, int arg);
extern void func_0203c7ac(int rig, int a);
extern int func_ov107_020c09a0(int a, int b, int mode, int anchor, int e, int f);

void func_ov137_020cc2dc(int self, int kind, int arg) {
    func_0203b9fc(*(int *)(self + 0x388), 0, (short)kind, arg);
    func_0203c7ac(*(int *)(self + 0x388), 0);

    if (kind == 6) {
        *(int *)(*(int *)(self + 0x390) + 0xc) =
            func_ov107_020c09a0(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390) + 8), 5,
                                *(int *)(self + 0x9c) + 0x30, 0, 0);
    } else if (kind == 7) {
        *(int *)(*(int *)(self + 0x390) + 0xc) =
            func_ov107_020c09a0(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x390) + 8), 5,
                                *(int *)(self + 0x9c) + 0x30, 1, 0);
    }
}
