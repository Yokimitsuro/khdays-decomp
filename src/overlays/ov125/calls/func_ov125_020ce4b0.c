/* Spawn a size-0x38 registry entry (func_0203c5c0, callback ce5b0, no teardown) into *entry,
 * link it back to this actor and seed its five parameters from the actor's +0x39c descriptor
 * (+8, +0x10, +0x40, +0x20, +0x18), then return the entry. */
extern void func_0203c5c0();
extern void func_ov125_020ce5b0(void);

int *func_ov125_020ce4b0(int this_) {
    int *entry;
    func_0203c5c0(*(int *)(this_ + 0x3c), 100, 0x38, func_ov125_020ce5b0, 0, &entry);
    *entry = this_;
    entry[1] = *(int *)(*(int *)(*entry + 0x39c) + 8);
    entry[2] = *(int *)(*(int *)(*entry + 0x39c) + 0x10);
    entry[3] = *(int *)(*(int *)(*entry + 0x39c) + 0x40);
    entry[4] = *(int *)(*(int *)(*entry + 0x39c) + 0x20);
    entry[5] = *(int *)(*(int *)(*entry + 0x39c) + 0x18);
    return entry;
}
