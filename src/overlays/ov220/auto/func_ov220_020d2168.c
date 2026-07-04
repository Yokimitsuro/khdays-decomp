struct actor_ss { signed char _pad[0x1c6]; signed char cur; signed char req; };

int func_ov220_020d2168(int this_) {
    struct actor_ss *s = (struct actor_ss *)(**(int **)(this_ + 0x214));
    if (s->cur != 0xb) {
        s->req = 0xb;
        return 1;
    }
    return 0;
}
