/* Rebuild the +0x384 work list for the actor at *(+0x3a8): copy the const pose table to
 * a local buffer, seed the entry from *(owner+0x88), query the ov107 pose (buffer indexed
 * by +0x310), append the result, then re-init and finalize the owner list (flag from bit 0
 * of +0x311). */
extern void func_0202a440(int a);
extern void func_02014b5c(int a, int b);
extern int func_ov107_020c9440(int a, int b);
extern void func_0202a388(int a, int b, int c, int d);
extern void func_0203b9ac(int a, int b);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c7ac(int a, int b);
struct Buf_020ce7fc { int w[27]; };
extern const struct Buf_020ce7fc data_ov230_020d63e0;
struct b0_020ce7fc { unsigned char b0 : 1; };
void func_ov230_020d243c(int param_1) {
    struct Buf_020ce7fc buf = data_ov230_020d63e0;
    int owner = *(int *)(*(int *)(param_1 + 0x3a8) + 0x88);
    func_0202a440(param_1 + 0x384);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    func_0202a388(param_1 + 0x384, owner,
                  func_ov107_020c9440(param_1, buf.w[*(signed char *)(param_1 + 0x310)]), 0xc);
    func_0203b9ac(*(int *)(param_1 + 0x3a8), param_1 + 0x384);
    func_0203b9fc(*(int *)(param_1 + 0x3a8), 0, 0,
                  ((struct b0_020ce7fc *)(param_1 + 0x311))->b0);
    func_0203c7ac(*(int *)(param_1 + 0x3a8), 0);
}
