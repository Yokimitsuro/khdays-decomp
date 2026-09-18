/* Target finder of the ov291 enemy: walks the owner's +0xa8 actor list for live (+0x40 bit 1),
 * enabled (+0x60 bit 0) actors within 0x3800 of the +0x388 item's +0x40 point in height and,
 * flattened, within 0xa000 beyond their +0x80 radius; beyond 0x1800 the target must also lie
 * ahead of the item's +0x30 orientation (dot >= 0.5). With scene collision (+0x7c) the ray from
 * the actor's +0x74 position to the target must be clear both as a 0x300 sphere cast and as a
 * line (a hit whose +8 is zero rejects it). The last candidate wins. */
struct flags16 { unsigned short lo : 8; unsigned short hi : 8; };

extern void func_0202f384(int *out, int *node, void *basis);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern void VEC_Subtract(int *a, int *b, int *out);
extern int func_01fff8e8(void *collision, int *position, int *direction, int radius, void *ignore);
extern int func_01fff920(void *collision, int *position, int *direction);
extern int func_01ff8d18(int *v, int *out);
extern int VEC_DotProduct(int *a, int *b);
extern int data_02042258;

int func_ov291_020cc670(int self) {
    int best = 0;
    int mgr = *(int *)(self + 4);
    int dir[3];
    int aim[3];
    int *pe;
    int e;
    int zero;

    pe = func_01fffd70(mgr + 0xa8);
    e = (pe == 0) ? 0 : *pe;
    while (e != 0) {
        zero = 0;
        if (((*(int *)(e + 0x40) << 0x1e) >> 0x1f) != 0 &&
            (((struct flags16 *)(e + 0x60))->lo & 1) != 0) {
            int dist;
            int y;
            func_0202f384(aim, (int *)(*(int *)(self + 0x388) + 0x30), &data_02042258);
            VEC_Subtract((int *)(e + 0x74), (int *)(*(int *)(self + 0x388) + 0x40), dir);
            y = dir[1];
            if (y < 0) {
                y = -y;
            }
            if (y <= 0x3800) {
                dir[1] = zero;
                dist = func_01ff8d18(dir, dir) - *(int *)(e + 0x80);
                if (dist <= 0xa000 && (dist < 0x1800 || VEC_DotProduct(aim, dir) >= 0x800)) {
                    int hit;
                    if (*(int *)(mgr + 0x7c) != 0) {
                        VEC_Subtract((int *)(e + 0x74), (int *)(self + 0x74), dir);
                        hit = func_01fff8e8(*(void **)(mgr + 0x7c), (int *)(self + 0x74), dir, 0x300, 0);
                        if (hit != 0 && *(int *)(hit + 8) == 0) {
                            goto next;
                        }
                        hit = func_01fff920(*(void **)(mgr + 0x7c), (int *)(self + 0x74), dir);
                        if (hit != 0 && *(int *)(hit + 8) == 0) {
                            goto next;
                        }
                    }
                    best = e;
                }
            }
        }
next:
        pe = func_01fffd8c(mgr + 0xa8);
        e = (pe == 0) ? 0 : *pe;
    }
    return best;
}
