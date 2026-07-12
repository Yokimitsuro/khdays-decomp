/* Rebuild the +0x394 work list for the actor at *(+0x384): reset it, seed the entry
 * from *(owner+0x88), query the ov107 pose (index at +0x310, +1), append the result,
 * then re-init and finalize the owner list (flag from bit 0 of +0x311). */
extern void func_0202a440(int a);
extern void func_02014b5c(int a, int b);
extern int func_ov107_020c9440(int a, int b);
extern void func_0202a388(int a, int b, int c, int d);
extern void func_0203b9ac(int a, int b);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c7ac(int a, int b);
struct b0_020cc4d8 { unsigned char b0 : 1; };
void func_ov231_020cc4d8(int param_1) {
    int owner = *(int *)(*(int *)(param_1 + 0x384) + 0x88);
    func_0202a440(param_1 + 0x394);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    func_0202a388(param_1 + 0x394, owner,
                  func_ov107_020c9440(param_1, *(signed char *)(param_1 + 0x310) + 1), 0xc);
    func_0203b9ac(*(int *)(param_1 + 0x384), param_1 + 0x394);
    func_0203b9fc(*(int *)(param_1 + 0x384), 0, 0,
                  ((struct b0_020cc4d8 *)(param_1 + 0x311))->b0);
    func_0203c7ac(*(int *)(param_1 + 0x384), 0);
}
