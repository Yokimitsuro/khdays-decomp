extern void func_0202a440(char *p);
extern void func_0203c7e8(int h);
extern void func_0203d194(int h);
extern void func_ov107_020c68ec(char *self);

/* Releases everything the node owns: the two animation blocks, the eight sub-node sprites and
 * their table, the two texture blocks and the two own sprites. */
void func_ov213_020cc464(char *self) {
    int i;
    func_0202a440(self + 0x38c);
    func_0202a440(self + 0x3b0);
    for (i = 0; i < 8; i++) {
        func_0203c7e8(*(int *)(*(int *)(self + 0x430) + i * sizeof(long long)));
    }
    func_0203d194(*(int *)(self + 0x430));
    func_0203d194(*(int *)(self + 0x3e0));
    func_0203d194(*(int *)(self + 0x3e4));
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x388));
    func_ov107_020c68ec(self);
}
