struct actor_ext {
    signed char _pad0[0x17a];
    unsigned char flag_b0 : 1;
    unsigned char _flagrest : 7;
    signed char _pad1[0x4b];
    signed char cur;
    signed char req;
};

int func_ov284_020cc770(int this_) {
    struct actor_ext *s = (struct actor_ext *)(**(int **)(this_ + 0x214));
    int cur = s->cur;
    if (cur == 9) {
        s->req = 0;
        return 1;
    }
    if (s->req == 8 || cur == 8) {
        goto ret0;
    }
    if (s->flag_b0 == 0) {
        goto ret0;
    }
    if (cur == 2) {
        s->req = 8;
    }
ret0:
    return 0;
}
