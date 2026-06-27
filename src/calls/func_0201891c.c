typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

extern void MIi_CpuClear16(u16 data, void *destp, u32 size);
extern int func_02016f10(void *p, void *q);
extern u32 data_020424a4;

struct A {
    u8 pad0[8];
    u32 off8;
    u8 padc[2];
    u16 offE;
};

struct B {
    u8 pad0[8];
    u32 off8;
    u8 padc[0xc];
    u8 off18;
};

struct C {
    u8 pad0[0xc];
    u32 g;
    u8 pad10[9];
    u8 n;
    u16 arr[1];
};

void func_0201891c(struct C *self, struct A *a1, struct B *a2) {
    char *base;
    u32 i;
    void *saved;
    u32 off;
    int neg1;
    void *r1;
    int r;

    if (a2 != 0 && a2->off8 != 0) {
        saved = (char *)a2 + a2->off8;
    } else {
        saved = (void *)0;
    }
    self->g = data_020424a4;
    {
        u32 n = ((u8 *)a2)[0x18];
        self->n = (u8)n;
        MIi_CpuClear16(0, self->arr, n << 1);
    }

    i = 0;
    if (i < (u32)((u8 *)a1)[9]) {
        off = 0;
        base = (char *)a1 + 8;
        neg1 = -1;
        do {
            if (base != 0 && i < (u32)((u8 *)a1)[9]) {
                char *p = base + a1->offE;
                p = p + *(u16 *)(p + 2);
                r1 = p + off;
            } else {
                r1 = (void *)0;
            }
            if (saved == 0) {
                r = neg1;
            } else {
                r = func_02016f10((char *)saved + 4, r1);
            }
            if (r >= 0) {
                self->arr[r] = (u16)(i | 0x100);
            }
            i++;
            off += 0x10;
        } while (i < (u32)((u8 *)a1)[9]);
    }
}
