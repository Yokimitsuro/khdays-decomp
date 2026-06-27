typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void MIi_CpuClear16(u16 data, void *destp, u32 size);
extern u32 data_02042498;

struct A {
    u8 pad0[6];
    u16 count;
    u8 pad8[0xc];
    u16 offs[1];
};

struct C {
    u8 pad0[8];
    struct A *a;
    u32 g;
    u8 pad10[9];
    u8 n;
    u16 arr[1];
};

void func_0202e0ec(struct C *self, struct A *a) {
    u32 i;
    u16 *offs;
    self->a = a;
    self->g = data_02042498;
    self->n = 2;
    MIi_CpuClear16(0, self->arr, (u32)self->n << 1);
    offs = a->offs;
    i = 0;
    while (i < a->count) {
        self->arr[i] = (u32)(*(u32 *)((char *)a + offs[i]) >> 24) | 0x100;
        i++;
    }
}
