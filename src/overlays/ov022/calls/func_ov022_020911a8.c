/* Run a node's value through the transform its kind (+4) selects, using the context at +8 of
 * the owner: kind 0 goes to func_ov022_020a0fb8, kind 1 to func_ov022_020a1064, and any other
 * kind passes the value through untouched.
 *
 * The nesting has to be inverted -- `if (kind != 0) { if (kind == 1) ... } else { ... }` -- so
 * that the kind-1 arm sits physically first and the kind-0 arm is the one branched to, which is
 * how the original lays them out. Written the natural way round (`if (kind == 0) ... else if`),
 * mwcc emits the two arms in source order and the branches come out inverted; written as a
 * switch it grows an extra compare. */
extern int func_ov022_020a1064(int ctx, int value, int arg);
extern int func_ov022_020a0fb8(int ctx, int value, int arg);

int func_ov022_020911a8(int *owner, int *node, int value, int arg) {
    int kind = node[1];
    int ctx = owner[2];
    if (kind != 0) {
        if (kind == 1) value = func_ov022_020a1064(ctx, value, arg);
    } else {
        value = func_ov022_020a0fb8(ctx, value, arg);
    }
    return value;
}
