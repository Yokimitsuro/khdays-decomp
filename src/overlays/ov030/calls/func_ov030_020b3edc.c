extern void func_0202a7dc(void *p);

struct Sub { char data[0x170]; };

struct Obj {
    char pad[0x234];
    struct Sub subs[8];
};

void func_ov030_020b3edc(struct Obj *obj) {
    int i;
    for (i = 0; i < 8; i++) {
        func_0202a7dc(&obj->subs[i]);
    }
}
