/*
 * func_ov272_020d060c -- x3 (ov119/...). Pick the best-facing valid target within range.
 * Build the aim vector at aim[] from the owner node (*(self+0x390)+4) via 0202f384 with the const
 * basis data_02042258. Walk the entity list at *(self+4)+0xa8: for each live+targetable entity (bit 1
 * of *(e+0x40) set and bit 0 of *(e+0x60) set), form the direction e+0x74 -> owner (*(self+0x390)+0x14)
 * with VEC_Subtract, normalise it (distance = 01ff8d18), and dot it with aim (VEC_DotProduct). Keep the
 * closest entity whose dot is in (0xc00, +) and whose distance beats the running best AND is under the
 * range gate FX_MUL(*(self+0x2d8), dot). Return the chosen entity (0 if none).
 */
struct flags16 { unsigned short lo : 8; unsigned short hi : 8; };

extern void func_0202f384(int *out, int *node, void *basis);
extern int *func_01fffd70(int list);
extern int *func_01fffd8c(int list);
extern void VEC_Subtract(int *a, int *b, int *out);
extern int func_01ff8d18(int *v, int *out);
extern int VEC_DotProduct(int *a, int *b);
extern int data_02042258;

int func_ov272_020d060c(int self, int p2, int p3, int p4) {
    int best = 0;
    int best_dist = 0x7fffffff;
    int mgr = *(int *)(self + 4);
    int aim[3];
    int dir[3];
    int *pe;
    int e;

    func_0202f384(aim, (int *)(*(int *)(self + 0x390) + 4), &data_02042258);
    pe = func_01fffd70(mgr + 0xa8);
    e = (pe == 0) ? 0 : *pe;
    while (e != 0) {
        if (((*(int *)(e + 0x40) << 0x1e) >> 0x1f) != 0 &&
            (((struct flags16 *)(e + 0x60))->lo & 1) != 0) {
            int dist, dot;
            VEC_Subtract((int *)(e + 0x74), (int *)(*(int *)(self + 0x390) + 0x14), dir);
            dist = func_01ff8d18(dir, dir);
            dot = VEC_DotProduct(aim, dir);
            if (dot >= 0 && dot > 0xc00 && dist < best_dist &&
                dist < (int)(((long long)*(int *)(self + 0x2d8) * dot + 0x800) >> 12)) {
                best_dist = dist;
                best = e;
            }
        }
        pe = func_01fffd8c(mgr + 0xa8);
        e = (pe == 0) ? 0 : *pe;
    }
    return best;
}
