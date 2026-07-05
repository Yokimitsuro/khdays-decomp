/* NONMATCHING: equivalent C, single callee-saved coloring tie (count=6, 140B).
 * Byte-exact EXCEPT the r6/r7 assignment of `result` vs `node`: the original
 * puts the call-return `result` in r7 and the reloaded `node` in r6 (so it
 * `str r0` and `movs r7`), mwcc here swaps them (`movs r6`, `str r6`). Only 5
 * bytes differ (the movs dest + the store src). No source change flips it
 * (operand order, decl order, node-before-call, pointer typing, inline store).
 * Semantics: result = func_ov107_020cab14(*holder, &local); holder->4 = result;
 * result==0 -> return; diff = FX_Sqrt(local) - (result->0x80 + node->0x80);
 * diff > (*holder)->0x2d8 -> return; holder->0x34 -= (*this)->0x2c; >=0 ->
 * return; (*holder)->0x1c7 = 4; advance func_0203c634(this,(s8)0x20,0). */
extern int func_ov107_020cab14(int node, int *out);
extern int FX_Sqrt(int x);
extern int func_0203c634();

void func_ov142_020d0ad8(int this_) {
    int holder = *(int *)(this_ + 4);
    int local;
    int node;
    int result;
    int diff;

    result = func_ov107_020cab14(*(int *)holder, &local);
    *(int *)(holder + 4) = result;
    if (result == 0) return;

    node = *(int *)holder;
    diff = FX_Sqrt(local) -
           (*(int *)(result + 0x80) + *(int *)(node + 0x80));
    local = diff;
    if (diff > *(int *)(*(int *)holder + 0x2d8)) return;

    *(int *)(holder + 0x34) -= *(int *)(*(int *)this_ + 0x2c);
    if (*(int *)(holder + 0x34) >= 0) return;

    *(signed char *)(*(int *)holder + 0x1c7) = 4;
    func_0203c634(this_, *(signed char *)(this_ + 0x20), 0);
}
