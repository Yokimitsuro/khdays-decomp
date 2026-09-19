/* Rebuild the two rider work lists (+0x38c for the +0x388 rider, +0x394 for the +0x390 one)
 * for pose slot `slot`: copy the const pose table to a local buffer, seed each entry from the
 * rider's *(+0x88) owner, query the +0x384 pool for the slot's pose, append it, clear the
 * owner's five +2 / +0xca halfword pairs, bind the rider to its list with channel 0 = (0, flag),
 * then run the 020ce984 hook and re-init both riders. */
extern void func_0202a440(int a);
extern void func_02014b5c(int a, int b);
extern int func_ov107_020c9440(int a, int b);
extern void func_0202a388(int a, int b, int c, int d);
extern void func_0203b9ac(int a, int b);
extern void func_0203b9fc(int a, int b, int c, int d);
extern void func_ov236_020ce984(int self);
extern void func_0203c7ac(int a, int b);
struct Buf17 { int w[17]; };
extern const struct Buf17 data_ov236_020d637c;

void func_ov236_020ce820(int self, int slot, int flag) {
    struct Buf17 buf = data_ov236_020d637c;
    int i;
    int owner;
    int kind;

    func_0202a440(*(int *)(self + 0x38c));
    owner = *(int *)(*(int *)(self + 0x388) + 0x88);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    kind = buf.w[slot];
    func_0202a388(*(int *)(self + 0x38c), owner, func_ov107_020c9440(*(int *)(self + 0x384), kind), 0xc);
    for (i = 0; i < 5; i++) {
        ((short *)owner)[i + 1] = -1;
        ((short *)owner)[i + 0x65] = -1;
    }
    func_0203b9ac(*(int *)(self + 0x388), *(int *)(self + 0x38c));
    func_0203b9fc(*(int *)(self + 0x388), 0, 0, flag);

    func_0202a440(*(int *)(self + 0x394));
    owner = *(int *)(*(int *)(self + 0x390) + 0x88);
    func_02014b5c(owner + 0x20, *(int *)(owner + 0x78));
    func_0202a388(*(int *)(self + 0x394), owner, func_ov107_020c9440(*(int *)(self + 0x384), kind), 0xc);
    for (i = 0; i < 5; i++) {
        ((short *)owner)[i + 1] = -1;
        ((short *)owner)[i + 0x65] = -1;
    }
    func_0203b9ac(*(int *)(self + 0x390), *(int *)(self + 0x394));
    func_0203b9fc(*(int *)(self + 0x390), 0, 0, flag);

    func_ov236_020ce984(self);
    func_0203c7ac(*(int *)(self + 0x388), 0);
    func_0203c7ac(*(int *)(self + 0x390), 0);
}
