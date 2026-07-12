/* Append a work-list entry (param_4) seeded from the owner sub-object at *(+0x88): reset
 * it, clear +0xc, bind the owner list, register the entry with tag param_2, then re-init
 * and finalize the owner list with param_3. No-op when param_2 is 0. */
extern void func_0202a440(int a);
extern void func_02014b5c(int a, int b);
extern void func_0202a388(int a, int b, int c, int d);
extern void func_0203b9ac(int a, int b);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c7ac(int a, int b);
void func_ov237_020cd0b0(int param_1, int param_2, int param_3, int param_4) {
    int owner;
    if (param_2 == 0) return;
    func_0202a440(param_4);
    *(int *)(param_4 + 0xc) = 0;
    owner = *(int *)(param_1 + 0x88);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    func_0202a388(param_4, owner, param_2, 0xc);
    func_0203b9ac(param_1, param_4);
    func_0203b9fc(param_1, 0, 0, param_3);
    func_0203c7ac(param_1, 0);
}
