/* Push this enemy's animation argument into its +0x2644 part record and the record at +0x30,
 * then run the follow-up pass in func_ov062_020b6324. */
extern void func_ov022_0209145c(int part, int a);
extern void func_ov062_020b6324(int this_);

void func_ov062_020b62ec(int this_, int a) {
    func_ov022_0209145c(*(int *)(this_ + 0x2000 + 0x644), a);
    func_ov022_0209145c(*(int *)(this_ + 0x2000 + 0x644) + 0x30, a);
    func_ov062_020b6324(this_);
}
