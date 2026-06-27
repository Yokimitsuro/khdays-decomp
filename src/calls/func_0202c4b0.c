extern void OS_Terminate(void);
extern void func_02011134(void *);
extern void func_02011320(void *);
extern void func_0202b9f4(unsigned short);
extern void func_0202bc0c(unsigned short);

typedef struct Entry {
    unsigned char pad0[8];
    unsigned char flags;       /* +8 */
    unsigned char pad1[2];
    unsigned char threshold;   /* +0xb */
    unsigned char pad2[0x184 - 0xc];
} Entry;

typedef struct S {
    unsigned char gap_00[0xc4];
    Entry entries[0x40];                /* offset 0xc4, stride 0x184 */
    unsigned char gap_a1d0[0x400c];     /* pad to 0xa1d0 */
    unsigned char arr1[0x10][0x28];     /* offset 0xa1d0 */
    unsigned char arr2[0x10][8];        /* offset 0xa450 */
    unsigned char counter;              /* offset 0xa4d0 */
} S;

extern S *data_0204c208;

void func_0202c4b0(void) {
    S *s;
    int i;
    Entry *e;
    unsigned char flags;
    int new_counter;

    s = data_0204c208;
    if (s->counter == 0) {
        OS_Terminate();
    }
    e = &s->entries[0];
    for (i = 0; i < 0x40; i++) {
        flags = e->flags;
        if ((flags & 4) && e->threshold >= s->counter && !(flags & 0x40)) {
            func_0202b9f4((unsigned short)i);
            if (e->flags & 2) {
                func_0202bc0c((unsigned short)i);
            }
        }
        e = (Entry *)((unsigned char *)e + 0x184);
    }
    new_counter = s->counter - 1;
    s->counter = (unsigned char)new_counter;
    func_02011134(&s->arr1[new_counter & 0xff]);
    func_02011320(&s->arr2[s->counter]);
}
