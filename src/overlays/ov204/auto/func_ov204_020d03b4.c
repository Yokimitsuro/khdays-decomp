struct actor_ss { signed char _pad[0x1c6]; signed char cur; signed char req; };

int func_ov204_020d03b4(int this_) {
    struct actor_ss *s = (struct actor_ss *)(**(int **)(this_ + 0x214));
    if (s->cur == 9) {
        return 0;
    }
    if (s->req == -1) {
        s->req = 0xa;
        return 1;
    }
    return 0;
}
