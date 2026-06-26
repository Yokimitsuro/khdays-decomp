typedef struct B B;
typedef struct C C;
typedef struct D D;

struct D {
    char pad[0x2c];
    int f2c;
};

struct C {
    char pad[0xad];
    unsigned char fad;
    char pad2[0x1c7 - 0xad - 1];
    unsigned char f1c7;
};

struct B {
    C *f0;
    C *f4;
    char pad[0x5c - 8];
    int f5c;
};

struct A {
    D *f0;
    B *f4;
};

void func_ov224_020d2360(struct A *a) {
    B *b = a->f4;
    int v = b->f5c - a->f0->f2c;
    b->f5c = v;
    if (v <= 0) {
        b->f5c = 0;
    }
    if (b->f4->fad == 0) {
        b->f0->f1c7 = 6;
    }
}
