/* Rebuild the two rider work lists (+0x38c for the +0x384 rider, +0x390 for the +0x388 one) for
 * move `slot`: copy the const 23-entry pose table to a local buffer, seed each list from the
 * rider's *(+0x88) owner, append the slot's pose from the actor's pool (020c9440), bind the rider
 * with channel 0 = (0, flag) and re-init it. Moves 0xd / 0xe / 0xf show the +0x3b0 prop's +0x28
 * rig (clear +0x5c bit 1) and set its channels 0, 2, 4, 1 to (0, 0), (1, 1) or (2, 0); any other
 * move hides it. Unless the move is 0xd or 0xe, the +0x3c4 effect is released and cleared. */
extern void func_0202a440(int a);
extern void func_02014b5c(int a, int b);
extern int func_ov107_020c9440(int a, int b);
extern void func_0202a388(int a, int b, int c, int d);
extern void func_0203b9ac(int a, int b);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_0203c7ac(int a, int b);
extern void func_ov107_020cb100(int a);
struct Buf23 { int w[23]; };
extern const struct Buf23 data_ov236_020d62b8;

void func_ov236_020cca44(int self, int slot, int flag) {
    struct Buf23 buf = data_ov236_020d62b8;
    int owner;
    int kind;
    int rig;

    func_0202a440(*(int *)(self + 0x38c));
    owner = *(int *)(*(int *)(self + 0x384) + 0x88);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    kind = buf.w[slot];
    func_0202a388(*(int *)(self + 0x38c), owner, func_ov107_020c9440(self, kind), 0xc);
    func_0203b9ac(*(int *)(self + 0x384), *(int *)(self + 0x38c));
    func_0203b9fc(*(int *)(self + 0x384), 0, 0, flag);
    func_0203c7ac(*(int *)(self + 0x384), 0);

    func_0202a440(*(int *)(self + 0x390));
    owner = *(int *)(*(int *)(self + 0x388) + 0x88);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    func_0202a388(*(int *)(self + 0x390), owner, func_ov107_020c9440(self, kind), 0xc);
    func_0203b9ac(*(int *)(self + 0x388), *(int *)(self + 0x390));
    func_0203b9fc(*(int *)(self + 0x388), 0, 0, flag);
    func_0203c7ac(*(int *)(self + 0x388), 0);

    if (slot == 0xd) {
        rig = *(int *)(*(int *)(self + 0x3b0) + 0x28);
        *(int *)(rig + 0x5c) &= ~2;
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 0, 0, 0);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 2, 0, 0);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 4, 0, 0);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 1, 0, 0);
    } else if (slot == 0xe) {
        rig = *(int *)(*(int *)(self + 0x3b0) + 0x28);
        *(int *)(rig + 0x5c) &= ~2;
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 0, 1, 1);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 2, 1, 1);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 4, 1, 1);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 1, 1, 1);
    } else if (slot == 0xf) {
        rig = *(int *)(*(int *)(self + 0x3b0) + 0x28);
        *(int *)(rig + 0x5c) &= ~2;
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 0, 2, 0);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 2, 2, 0);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 4, 2, 0);
        func_0203b9fc(*(int *)(*(int *)(self + 0x3b0) + 0x28), 1, 2, 0);
    } else {
        *(int *)(*(int *)(*(int *)(self + 0x3b0) + 0x28) + 0x5c) |= 2;
    }

    if (slot != 0xd && slot != 0xe && *(int *)(self + 0x3c4) != 0) {
        func_ov107_020cb100(*(int *)(self + 0x3c4));
        *(int *)(self + 0x3c4) = 0;
    }
}
