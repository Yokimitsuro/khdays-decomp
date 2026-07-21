extern void func_0203c640(int self);
/* Advance the slot only while the first sub-object is unlocked (+0xaf of subobjects[0]). */
void func_ov257_020d2cf8(int self) {
    if (*(unsigned char *)(*(int *)(*(int *)(*(int *)(self + 4)) + 0x3a4) + 0xaf) != 0) {
        return;
    }
    func_0203c640(self);
}
