/* Teardown hook: when the +0x1c4 status has bits 1/3, drop the owner's (+0x430) +0x3c child via
 * func_0203c650, request pose 2 while no request is pending and the current kind is not one of
 * 0/1/3/2/0xf (typed request bytes: a raw +0x1c7 store shares the ldrsb base), and release the three +0x428/+0x424/+0x42c handles; then the common release. */
struct Req { char pad[0x1c6]; signed char kind; signed char req; };
extern void func_0203c650(int a, int b);
extern void func_ov107_020cb100();
extern void func_ov107_020c7ca4(int self);

void func_ov273_020d07d8(int self) {
    if ((*(unsigned char *)(self + 0x1c4) & 0xa) != 0) {
        if (*(int *)(*(int *)(self + 0x430) + 0x3c) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x430) + 0x3c));
            *(int *)(*(int *)(self + 0x430) + 0x3c) = 0;
        }
        if (((struct Req *)self)->req == -1) {
            signed char s = ((struct Req *)self)->kind;
            if (s != 0 && s != 1 && s != 3 && s != 2 && s != 0xf) {
                ((struct Req *)self)->req = 2;
            }
        }
        if (*(int *)(self + 0x428) != 0) {
            func_ov107_020cb100();
            *(int *)(self + 0x428) = 0;
        }
        if (*(int *)(self + 0x424) != 0) {
            func_ov107_020cb100();
            *(int *)(self + 0x424) = 0;
        }
        if (*(int *)(self + 0x42c) != 0) {
            func_ov107_020cb100();
            *(int *)(self + 0x42c) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}
