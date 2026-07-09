/* NONMATCHING: predicate-vs-branch tie. Original branches to separate return
 * blocks (and r,#8; cmp #0; bgt ret1 / tst #4; beq ret0), mwcc predicates the
 * guards inline (movgt/bxgt, moveq/movne) no matter the C shape. Tried: &&
 * chain, nested ifs, (x&8)>0 form, result-var. All collapse to predication.
 * Semantics: returns 1 if bit3 or bit2 of *arg0 is set, else 0. */
int func_ov022_0209344c(unsigned char *arg0) {
    return (*arg0 & 0xc) != 0;
}
