typedef unsigned short u16;
typedef unsigned int u32;

struct Foo {
    u32 a;
    u16 mask;
};

extern struct Foo *data_0204c228;
extern u32 OS_IsTickAvailable_0x01ff8138(void);

u32 func_0203070c(void) {
    struct Foo *p = data_0204c228;
    u16 mask;
    u32 cur;
    u16 out;
    u16 i, j;
    u16 bit_i, bit_j;

    if (p == 0) {
        return 0;
    }
    mask = p->mask;
    cur = OS_IsTickAvailable_0x01ff8138();
    out = 0;
    j = 0;
    for (i = 0; i < 4; i++) {
        bit_i = (u16)(1 << i);
        if (mask & bit_i) {
            if (cur & bit_i) {
                bit_j = (u16)(1 << j);
                out |= bit_j;
            }
            j++;
        }
    }
    return out & 0xf;
}
