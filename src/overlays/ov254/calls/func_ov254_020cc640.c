extern void func_0202a440(char *p);
extern void func_0203c7e8(int h);
extern void func_ov107_020c9eac(int h);
extern void NNSi_FndDestroyDoubleList(char *list);
extern void func_ov107_020c68ec(char *self);

/* Releases everything the node owns: the two animation blocks, its two sprites, the actor pool,
 * the eight row sprites and the row list. */
void func_ov254_020cc640(char *self) {
    int i;
    func_0202a440(self + 0x38c);
    func_0202a440(self + 0x3b0);
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x388));
    func_ov107_020c9eac(*(int *)(self + 0x430));
    for (i = 0; i < 8; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(long long) + 0x4e8));
    }
    NNSi_FndDestroyDoubleList(self + 0x34 + 0x400);
    func_ov107_020c68ec(self);
}
