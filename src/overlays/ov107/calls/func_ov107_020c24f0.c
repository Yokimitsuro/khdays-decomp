extern void func_0203c7e8(int h);
extern void NNSi_FndDestroyDoubleList(char *list);
extern void func_ov107_020c2c44(char *self);

/* Releases the emitter's two own sprites and the four per-slot ones, then its three lists. */
void func_ov107_020c24f0(char *self) {
    int i;
    func_0203c7e8(*(int *)(self + 0x100));
    func_0203c7e8(*(int *)(self + 0x104));
    for (i = 0; i < 4; i++) {
        func_0203c7e8(*(int *)(self + i * sizeof(int) + 0x108));
    }
    NNSi_FndDestroyDoubleList(self + 0x80);
    NNSi_FndDestroyDoubleList(self + 0xa8);
    NNSi_FndDestroyDoubleList(self + 0xd0);
    func_ov107_020c2c44(self);
}
