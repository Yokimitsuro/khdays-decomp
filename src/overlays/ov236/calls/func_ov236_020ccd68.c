/* Hit-point sync: after the base 020c8500 step, each of the two riders (+0x3b4 / +0x3b8) gets
 * half of this actor's +0x218 max as both its +0x218 max and +0x21a current, and half of its
 * own current plus one written to its +0x3be threshold and copied to +0x3bc / +0x3d2 -> +0x3d0. */
extern void func_ov107_020c8500(int self);

void func_ov236_020ccd68(int self) {
    func_ov107_020c8500(self);
    if (*(int *)(self + 0x3b4) != 0) {
        int rider = *(int *)(self + 0x3b4);
        short v = (short)(*(short *)(self + 0x200 + 0x18) / 2);
        *(short *)(rider + 0x200 + 0x18) = v;
        *(short *)(rider + 0x200 + 0x1a) = v;
        rider = *(int *)(self + 0x3b4);
        *(short *)(rider + 0x300 + 0xbe) = (short)(*(short *)(rider + 0x200 + 0x1a) / 2 + 1);
        *(short *)(rider + 0x300 + 0xbc) = *(short *)(rider + 0x300 + 0xbe);
    }
    if (*(int *)(self + 0x3b8) != 0) {
        int rider = *(int *)(self + 0x3b8);
        short v = (short)(*(short *)(self + 0x200 + 0x18) / 2);
        *(short *)(rider + 0x200 + 0x18) = v;
        *(short *)(rider + 0x200 + 0x1a) = v;
        rider = *(int *)(self + 0x3b8);
        *(short *)(rider + 0x300 + 0xd2) = (short)(*(short *)(rider + 0x200 + 0x1a) / 2 + 1);
        *(short *)(rider + 0x300 + 0xd0) = *(short *)(rider + 0x300 + 0xd2);
    }
}
