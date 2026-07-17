/* func_ov002_02054290 -- re-resolve which entry of this tag-tracker table the pointer is over,
 * and notify on change.
 *
 * The table asks func_ov002_02054080 for the current probe: a `struct key`
 * {x, y, id, mode}. Nothing to do if it fails, or if the id equals the one already
 * snapshotted at +0x1c (the snapshot IS a struct key; +0x20 is its .id). On a real
 * change:
 *   id != 0, mode == 0 -> walk the entry list for the first entry that has a hit
 *     callback (+0x24), is not disabled (bit 0 of +0x20) and whose box contains the
 *     probe point (func_ov002_02053ec0). That entry becomes the active one
 *     (+0x18), its hit callback fires, and if it carries a payload at +0x28 the
 *     table's notify callback (+0x3c) is handed that payload.
 *   id == 0 -> the pointer left everything: if an entry was active and had a payload,
 *     notify with the entry itself and clear +0x18.
 * The snapshot is refreshed on every path (inside the loop on a hit, in the tail
 * otherwise) -- `flag` exists only to keep it from being copied twice.
 *
 * The equality test really is spelled as an XOR against zero: mwcc emits `teq` for
 * `(a ^ b) == 0` but if-converts a plain `a == b` into the preceding branch (292 B).
 * The notify callback takes an argument -- that is why the ROM keeps r0 live and
 * loads the payload into r1. */
typedef void (*fn0)(void);
typedef void (*fn1)(int);
struct key { unsigned short a, b, c, d; };
struct bit0 { unsigned int b : 1; };
extern int func_ov002_02054080(int obj, struct key *out);
extern void *NNS_FndGetNextListObject(void *list, void *prev);
extern int func_ov002_02053ec0(unsigned int a, unsigned int b, int e);
extern void MI_CpuCopy8(void *dst, void *src, unsigned int n);
void func_ov002_02054290(unsigned int *param_1, unsigned int param_2, unsigned int param_3,
                         unsigned int param_4) {
    struct key k;
    int e;
    int flag = 1;
    struct key *snap = (struct key *)((char *)param_1 + 0x1c);

    if (!func_ov002_02054080((int)param_1, &k)) goto done;
    if ((k.c ^ snap->c) == 0) goto done;
    if (k.c != 0) {
        if (k.d == 0) {
            for (e = (int)NNS_FndGetNextListObject(param_1, 0); e != 0;
                 e = (int)NNS_FndGetNextListObject(param_1, (void *)e)) {
                if (*(int *)(e + 0x24) != 0 && ((struct bit0 *)(e + 0x20))->b == 0 &&
                    func_ov002_02053ec0(k.a, k.b, e)) {
                    MI_CpuCopy8(&k, snap, 8);
                    flag = 0;
                    (*(fn1) * (int *)(e + 0x24))(e);
                    param_1[6] = e;
                    if (*(int *)(e + 0x28) != 0) {
                        (*(fn1)param_1[0xf])(*(int *)(e + 0x28));
                    }
                    break;
                }
            }
        }
    } else {
        if (param_1[6] != 0 && *(int *)(param_1[6] + 0x28) != 0) {
            (*(fn1)param_1[0xf])(param_1[6]);
            param_1[6] = 0;
        }
    }
done:
    if (flag) {
        MI_CpuCopy8(&k, snap, 8);
    }
}
