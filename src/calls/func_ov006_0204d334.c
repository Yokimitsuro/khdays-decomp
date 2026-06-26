extern int func_020236ac();

struct S {
    char pad24[0x24];
    unsigned char flags;   /* 0x24 */
    char pad25[0x2c - 0x25];
    void *ptr;             /* 0x2c */
};

void func_ov006_0204d334(int a, struct S *s) {
    s->flags &= ~2;
    if (s->ptr != 0) {
        func_020236ac(s->ptr);
        s->ptr = 0;
    }
}
