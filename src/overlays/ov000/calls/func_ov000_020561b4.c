extern long long func_020031d4(void);

struct Entry {
    char pad0[2];
    unsigned short h2;       /* 0x02 */
    unsigned short h4;       /* 0x04 */
    char pad6[8 - 6];
    int w8;                  /* 0x08 */
    char padc[0xc - 0xc];
    long long thresh;        /* 0x0c */
    long long acc;           /* 0x14 */
    long long prev;          /* 0x1c */
    unsigned char bit0 : 1;  /* 0x24 bit 0 */
    unsigned char bit1 : 1;  /* 0x24 bit 1 */
    char pad25[0x28 - 0x25]; /* 0x25 */
    int w28;                 /* 0x28 */
    int *arr2c;              /* 0x2c */
};

struct Obj {
    char pad0[0x10];
    struct Entry *entries;   /* 0x10 */
    char pad14[0x34 - 0x14];
    int count;               /* 0x34 */
    char pad38[0x3c - 0x38];
    void (*fn3c)(int);       /* 0x3c */
    char pad40[0x44 - 0x40];
    void (*fn44)(int);       /* 0x44 */
    int (*fn48)(void);       /* 0x48 */
};

void func_ov000_020561b4(struct Obj *o)
{
    long long now;
    int got = -1;
    int doFn44;
    int i;
    int local;
    struct Entry *e;

    now = func_020031d4();

    local = 0x7FFFFFFF;

    for (i = 0; i < o->count; i++) {
        e = &o->entries[i];
        if (!e->bit1) continue;
        if (!e->bit0) continue;
        if (e->h4 >= e->h2 - 1) {
            if (e->w8 == 1) continue;
        }
        e->acc += now - e->prev;
        e->prev = now;
        if ((unsigned long long)e->acc <= (unsigned long long)e->thresh) continue;

        e->h4++;
        if (e->h4 >= e->h2) {
            if (e->w8 == 1) {
                e->h4 = e->h2 - 1;
            } else {
                e->h4 = e->h4 % e->h2;
            }
        }
        {
            int doFn44;
            if (o->fn48 != 0) {
                got = o->fn48();
            }
            doFn44 = (o->fn44 != 0 && e->w28 != local);
            if (doFn44)
                o->fn44(e->w28);
            o->fn3c(e->arr2c[e->h4]);
            if (doFn44)
                o->fn44(got);
        }
        e->acc = (unsigned long long)e->acc % (unsigned long long)e->thresh;
    }
}
