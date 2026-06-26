struct S {
    char *base;
    char pad[6];
    unsigned short idx;
};

char *func_02011548(struct S *p) {
    return p->base + (p->idx << 4);
}
