extern void func_0203d194(int h);
extern void func_0202a440(int h);
extern void func_0203c7e8(int h);
extern void func_ov107_020c68ec(char *self);

/* Releases everything the node owns: the three texture blocks, the three animation pairs, the
 * three own sprites and the eight sub-node sprites with their table. */
void func_ov277_020cc6fc(char *self) {
    int i;
    func_0203d194(*(int *)(self + 0x400));
    func_0203d194(*(int *)(self + 0x404));
    func_0203d194(*(int *)(self + 0x408));
    func_0202a440(*(int *)(self + 0x390));
    func_0203d194(*(int *)(self + 0x390));
    func_0202a440(*(int *)(self + 0x394));
    func_0203d194(*(int *)(self + 0x394));
    func_0202a440(*(int *)(self + 0x398));
    func_0203d194(*(int *)(self + 0x398));
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x388));
    func_0203c7e8(*(int *)(self + 0x38c));
    for (i = 0; i < 8; i++) {
        func_0203c7e8(*(int *)(*(int *)(self + 0x40c) + i * sizeof(long long)));
    }
    func_0203d194(*(int *)(self + 0x40c));
    func_ov107_020c68ec(self);
}
