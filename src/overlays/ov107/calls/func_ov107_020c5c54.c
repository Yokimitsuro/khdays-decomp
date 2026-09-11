/* func_ov107_020c5c54 -- refresh a node then re-run its layout, ov107.
 * 2nd parameter is unused here; real per callers in ov115/ov117/ov107. */
typedef struct { int x, y, z; } VecFx32;
extern void func_0203ca30(void *sub);
extern void func_ov107_020c4ecc(void *node);
void func_ov107_020c5c54(char *node, VecFx32 *v) {
    func_0203ca30(node + 0xa0);
    func_ov107_020c4ecc(node);
}
