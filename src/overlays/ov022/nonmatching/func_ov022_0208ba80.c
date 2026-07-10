/* NONMATCHING: constant-materialization scheduler tie, byte-exact structure. The
 * original schedules the function result init (`mov r6,#1`) before the loop-counter
 * init (`mov r7,#0`); mwcc places the counter zero first regardless of source order.
 * A do-while form gets the init order right but its guard becomes `!= 0` (bne) where
 * the original uses a for/while entry check (`ble`); the for/while form fixes the
 * guard but re-orders the inits. Neither satisfies both (5 forms tried). Semantics
 * exact: for each of the entry's sub-objects, dispatches a handler from the table at
 * data_ov022_020b29bc by its kind byte (+0x14C), passing the handler ptr as arg 4;
 * decrements the entry's counter on a truthy return; then a trailing 0202a818 check. */
extern int func_0202a818(int a, int b);
extern void *data_ov022_020b29bc[];

typedef int (*Handler0208ba80)(int obj, int sub, int a1, void *fn);

int func_ov022_0208ba80(int obj, int a1) {
    int e = *(int *)(obj + *(int *)(obj + 0xc) * 4 + 0x18);
    int r = 1;
    int cnt, off;
    for (cnt = 0, off = 0; cnt < *(unsigned char *)(e + 1); cnt++, off += 0x150) {
        int sub = *(int *)(e + 0x168) + off;
        unsigned int h = *(unsigned char *)(sub + 0x14c);
        if (h != 0) {
            Handler0208ba80 fn = (Handler0208ba80)data_ov022_020b29bc[h];
            r = 0;
            if (fn(obj, sub, a1, fn) != 0)
                *(signed char *)(e + 2) = *(signed char *)(e + 2) - 1;
        }
    }
    if (*(int *)(e + 0x170) != 0) {
        if (func_0202a818(e + 8, a1) != 0) *(int *)(e + 0x170) = 0;
        r = 0;
    }
    return r;
}
