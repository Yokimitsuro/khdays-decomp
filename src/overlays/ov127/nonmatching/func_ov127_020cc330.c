/* NONMATCHING: equivalent C, but mwcc register-coloring tie.
 * Semantics: destroy + re-init the double-list at this_+0x398, then for each
 * 4-byte word of src[] (nbytes/4 words) allocate a node (func_01fffca8(list,4,
 * 0x64)) and store the word into it.
 * Codegen diff is purely callee-saved assignment: the original colors this_/
 * nbytes descending from r9/r8, this version lands them in r4/r5. Byte-exact
 * except for register numbers; no C-level lever flips the coloring order. */
extern void func_01fffc5c(int list);
extern void func_01fffc24(int list);
extern int *func_01fffca8(int list, int a, int b);

void func_ov127_020cc330(int this_, unsigned int nbytes, int *src) {
    int i;
    func_01fffc5c(this_ + 0x398);
    func_01fffc24(this_ + 0x398);
    nbytes >>= 2;
    for (i = 0; i < (int)nbytes; i++) {
        int *node = func_01fffca8(this_ + 0x398, 4, 0x64);
        *node = *src++;
    }
}
