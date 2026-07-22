/* Resets a transform block to its defaults: the 16-byte matrix from data_020420f8, the
 * 12-byte vector from data_02041dc8, the three 0x1000 (1.0 fixed-point) scale words, and
 * bits 0 and 1 of the flag byte at +0x28. */
struct Obj {
    int m0[4];
    int m10[3];
    int f1c;
    int f20;
    int f24;
    unsigned char b0 : 1;
    unsigned char b1 : 1;
};

struct A16 { int a; int b; int c; int d; };
struct A12 { int a; int b; int c; };

extern struct A16 data_020420f8;
extern struct A12 data_02041dc8;

void func_0203c960(struct Obj *o) {
    *(struct A16 *)o->m0 = data_020420f8;
    *(struct A12 *)o->m10 = data_02041dc8;
    o->f1c = 0x1000;
    o->f20 = 0x1000;
    o->f24 = 0x1000;
    o->b0 = 1;
    o->b1 = 1;
}
