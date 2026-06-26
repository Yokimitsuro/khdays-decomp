struct Bits {
    unsigned int b0 : 3;
    unsigned int flag : 1;
    unsigned int rest : 28;
};

struct Elem {
    struct Bits bits;
    char pad2[0x8c - 4];
};

struct Outer {
    char pad[0x7c];
    struct Elem arr[1];
};

void func_02032760(struct Outer *base, int index, int value) {
    if (index < 0) return;
    base->arr[index].bits.flag = (value != 0);
}
