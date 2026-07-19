extern void func_0202a440(int h);
extern void func_0203d194(int h);
extern void func_0203c7e8(int h);
extern void func_ov107_020c68ec(char *self);

/* Releases everything the node owns: the two animation pairs, the three sprite handles, the two
 * texture blocks, the two entries of the sub-node table and the table itself. */
void func_ov253_020cc9fc(char *self) {
    int i;
    func_0202a440(*(int *)(self + 0x388));
    func_0203d194(*(int *)(self + 0x388));
    func_0202a440(*(int *)(self + 0x390));
    func_0203d194(*(int *)(self + 0x390));
    func_0203c7e8(*(int *)(self + 0x384));
    func_0203c7e8(*(int *)(self + 0x38c));
    func_0203c7e8(*(int *)(self + 0x3a8));
    func_0203d194(*(int *)(self + 0x458));
    func_0203d194(*(int *)(self + 0x45c));
    for (i = 0; i < 2; i++) {
        func_0203c7e8(*(int *)(*(int *)(self + 0x468) + i * sizeof(long long)));
    }
    func_0203d194(*(int *)(self + 0x468));
    func_ov107_020c68ec(self);
}
