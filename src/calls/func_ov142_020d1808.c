extern int func_ov107_020c6980();

struct Block { int a[11]; };

struct Obj {
    char pad[0xa0];
    struct Block block;
    char pad2[0x388 - 0xa0 - sizeof(struct Block)];
    struct Block **pp;
};

void func_ov142_020d1808(struct Obj *this) {
    func_ov107_020c6980(this);
    *(struct Block *)((char *)(*this->pp) + 0x10) = this->block;
}
