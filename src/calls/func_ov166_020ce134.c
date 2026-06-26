extern int func_ov107_020c5c54();

struct Vec3 {
    int x;
    int y;
    int z;
};

struct Obj {
    char _pad0[0x60];
    unsigned short flags : 8;   /* 0x60, bits [7:0] */
    unsigned short _bf : 8;     /* 0x60, bits [15:8] */
    char _pad1[0x390 - 0x62];
    struct Vec3 vec;            /* 0x390 */
};

void func_ov166_020ce134(struct Obj *this, int arg1, struct Vec3 *src) {
    func_ov107_020c5c54(this);
    this->vec = *src;
    this->_bf |= (unsigned short)1;
}
