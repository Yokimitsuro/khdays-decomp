/*
 * func_ov268_020d0ea8 -- x3. Pick the node in the owner's list that best faces the owner's forward
 * axis. fwd = transform(self+0xa0, data_02042258). Walk the list at state+0xa8 (state = self[1]);
 * for each visible node (hw60.lo bit0 set), dir = normalise(node(+0xb0) - self(+0xb0)) and score it by
 * dot(dir, fwd); keep the highest. Return the best node (0 if none); if out != 0, write the best score
 * to *out.
 */
struct hw60 { unsigned short lo : 8, hi : 8; };
extern void func_0202f384(void *out, void *src, void *w);
extern int  func_01fffd70(int list);
extern int  func_01fffd8c(int list);
extern void VEC_Subtract(void *a, void *b, void *c);
extern void func_01ff8d18(void *a, void *b);
extern int  VEC_DotProduct(void *a, void *b);
extern int  data_02042258;

int func_ov268_020d0ea8(int self, int *out) {
    int best = 0x80000001;
    int bestnode = 0;
    int state = *(int *)(self + 4);
    int fwd[3];
    int v[3];
    int it, node;

    func_0202f384(fwd, (void *)(self + 0xa0), &data_02042258);
    it = func_01fffd70(state + 0xa8);
    node = it == 0 ? 0 : *(int *)it;
    while (node != 0) {
        if (((struct hw60 *)(node + 0x60))->lo & 1) {
            int dot;
            VEC_Subtract((void *)(node + 0xb0), (void *)(self + 0xb0), v);
            func_01ff8d18(v, v);
            dot = VEC_DotProduct(v, fwd);
            if (dot > best) {
                best = dot;
                bestnode = node;
            }
        }
        it = func_01fffd8c(state + 0xa8);
        node = it == 0 ? 0 : *(int *)it;
    }
    if (bestnode != 0) {
        if (out != 0) {
            *out = best;
        }
        return bestnode;
    }
    return 0;
}
