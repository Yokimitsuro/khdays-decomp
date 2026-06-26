extern int func_02023eb4();
extern int func_0203c634();

typedef struct { int a, b, c; } Vec3;

extern Vec3 data_02041dc8;

typedef struct {
    char pad[0x60];
    unsigned short f60 : 8;
    unsigned short f60h : 8;
} Inner;

void func_ov228_020cf878(unsigned char *obj) {
    unsigned char *mid = *(unsigned char **)(obj + 4);
    Inner *inner = *(Inner **)(mid + 0);
    if (inner->f60 & 1) {
        int base = *(int *)((unsigned char *)inner + 0x224);
        int diff = *(int *)((unsigned char *)inner + 0x228) - base;
        if (diff < 0) diff = -diff;
        *(int *)(mid + 0x54) = base + func_02023eb4(diff + 1);
        *(unsigned char *)(mid + 0x60) = 0xff;
        *(Vec3 *)(mid + 0x28) = data_02041dc8;
        *(int *)(mid + 8) = 0;
        *(unsigned char *)(mid + 0x64) = 0;
        {
            unsigned char *in2 = *(unsigned char **)(mid + 0);
            *(signed char *)(in2 + 0x1c7) = *(signed char *)(in2 + 0x1c9);
        }
        func_0203c634(obj, *(signed char *)(obj + 0x20), 0);
    }
}
