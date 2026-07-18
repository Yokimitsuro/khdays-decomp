/* func_ov186_020cfed4 -- x3. Retune the rig at +0x384 for a kind selector, then reset it.
 * For kind 3 the two rig slots 0 and 3 are each reprogrammed in full: seed slot i with
 * be9c(rig, i, be68(rig, i, 0)) then arm it with babc(rig, i, 0, arg). Any other kind just retunes
 * both slots with the kind as a signed 16-bit selector via b9fc(rig, {0,3}, (short)kind, arg).
 * Always finishes with a reset (0203c7ac). */
extern int  func_0203be68(int rig, int idx, int idx2);
extern void func_0203be9c(int rig, int idx, int val);
extern void func_0203babc(int rig, int idx, int c, int arg);
extern void func_0203b9fc(int rig, int a, short kind, int arg);
extern void func_0203c7ac(int rig, int a);

void func_ov186_020cfed4(int self, int kind, int arg) {
    if (kind == 3) {
        func_0203be9c(*(int *)(self + 0x384), 0, func_0203be68(*(int *)(self + 0x384), 0, 0));
        func_0203babc(*(int *)(self + 0x384), 0, 0, arg);
        func_0203be9c(*(int *)(self + 0x384), 3, func_0203be68(*(int *)(self + 0x384), 3, 0));
        func_0203babc(*(int *)(self + 0x384), 3, 0, arg);
    } else {
        func_0203b9fc(*(int *)(self + 0x384), 0, (short)kind, arg);
        func_0203b9fc(*(int *)(self + 0x384), 3, (short)kind, arg);
    }
    func_0203c7ac(*(int *)(self + 0x384), 0);
}
