/* NONMATCHING - 8 B compiled vs 12 B in the ROM, i.e. this C is one instruction
 * short of the real function; it is not an alternative spelling of it.
 *
 * The index name is a shape match and almost certainly wrong: 172 functions in this
 * ROM carry the WM_EndKeySharing name and they tail-call 76 different targets. Do not
 * trust the name to tell you what this should do -- read the reloc.
 *
 * Found by audit_shadowed.py: it was sitting in calls/ (counted as matched) while the
 * asm_stubs twin was what actually built the ROM. The stub stays; this file does not
 * build. */
extern int func_ov107_020c7c1c();

int WM_EndKeySharing_ov292_0x020d3ac0(int a, int b, int c, int d) {
    return func_ov107_020c7c1c(a, b, c, d);
}
