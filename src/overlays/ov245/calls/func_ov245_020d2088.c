extern int func_0203b9fc();
extern int func_0203c7ac();

struct S {
    char pad0[0x310];
    signed char b310;       /* +0x310 */
    unsigned char bit0 : 1; /* +0x311, bit 0 */
    char pad312[0x384 - 0x312];
    void *p384;             /* +0x384 */
};

void func_ov245_020d2088(struct S *this) {
    func_0203b9fc(this->p384, 0, this->b310, this->bit0);
    func_0203c7ac(this->p384, 0);
}
