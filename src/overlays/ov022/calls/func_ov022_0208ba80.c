/* func_ov022_0208ba80 -- run one tick of every live sub-object of the battle entry
 * currently selected by obj+0xc, and then the entry's own trailing task.
 *
 * The entry is obj[0x18/4 + index]. Each of its arg-count sub-objects (stride 0x150,
 * array at entry+0x168) carries a kind byte at +0x14c; a non-zero kind selects a
 * handler from data_ov022_020b29bc and the handler receives its own address as the
 * fourth argument. A truthy handler return decrements the entry's live counter at +2.
 * Returns 1 only when nothing ran, i.e. the entry is idle.
 *
 * The counter at +2 is an UNSIGNED byte (plain ldrbne), and the loop is written as a
 * guarded do/while with the counter initialised above the guard and the byte offset
 * inside it: that is what puts the ROM's `mov r6,#1` ahead of `mov r7,#0` and sinks
 * the offset's zero into the loop preheader. */
extern int func_0202a818(int a, int b);
extern void *data_ov022_020b29bc[];

typedef int (*Handler0208ba80)(int obj, int sub, int a1, void *fn);

int func_ov022_0208ba80(int obj, int a1) {
    int e = *(int *)(obj + *(int *)(obj + 0xc) * 4 + 0x18);
    int r = 1;
    int cnt = 0;
    int off;

    if (cnt < *(unsigned char *)(e + 1)) {
        off = 0;
        do {
            int sub = *(int *)(e + 0x168) + off;
            unsigned int h = *(unsigned char *)(sub + 0x14c);
            if (h != 0) {
                Handler0208ba80 fn = (Handler0208ba80)data_ov022_020b29bc[h];
                r = 0;
                if (fn(obj, sub, a1, fn) != 0) {
                    *(unsigned char *)(e + 2) = *(unsigned char *)(e + 2) - 1;
                }
            }
            cnt++;
            off += 0x150;
        } while (cnt < *(unsigned char *)(e + 1));
    }
    if (*(int *)(e + 0x170) != 0) {
        if (func_0202a818(e + 8, a1) != 0) *(int *)(e + 0x170) = 0;
        r = 0;
    }
    return r;
}
