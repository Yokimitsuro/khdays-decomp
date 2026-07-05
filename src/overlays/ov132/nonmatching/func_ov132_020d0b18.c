/* NONMATCHING: equivalent C, single-instruction scheduling tie (count=9 family).
 * Everything is byte-exact EXCEPT the order of two independent instructions in
 * the final block: the original emits `lsl r2,nc,#16` (start of the (short)
 * cast) BEFORE `str nc,[h,#0xc]`, mwcc here emits the store first. Both read nc
 * from the same register and are order-independent; no C-level reordering
 * (temp for the cast, temp for arg0, `<<16>>16` inline, ++, statement reorder)
 * flips mwcc's list-scheduler preference without regressing elsewhere.
 * Semantics: accumulate holder->8 += (*this)->0x2c; below 0x1000 -> return;
 * else if holder->0xc==8 notify (func_0203c640(this)); else reset holder->8,
 * bump holder->0xc, and func_0203b9fc(holder->4, 4, (short)holder->0xc, 1). */
extern void func_0203c640(int this_);
extern void func_0203b9fc(int a, int b, int c, int d);

void func_ov132_020d0b18(int this_) {
    int p = *(int *)this_;
    int h = *(int *)(this_ + 4);
    int acc;

    acc = *(int *)(h + 8) + *(int *)(p + 0x2c);
    *(int *)(h + 8) = acc;
    if (acc < 0x1000) return;
    if (*(int *)(h + 0xc) == 8) {
        func_0203c640(this_);
        return;
    }
    {
        int nc;
        *(int *)(h + 8) = 0;
        nc = *(int *)(h + 0xc) + 1;
        *(int *)(h + 0xc) = nc;
        func_0203b9fc(*(int *)(h + 4), 4, (short)nc, 1);
    }
}
