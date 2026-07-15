/* NONMATCHING (ldm/stm pointer register tie): the 11-word struct copy is exact but
 * mwcc 139 assigns the source pointer to ip and dest to lr, while the ROM uses ip for
 * dest and lr for source (2-byte add/ldm/stm encoding swap). No source restructuring
 * (dst-first, src-var, interleaved deref chain) flips it. 4-member family ov206/... .
 * Copy the 11-word transform block at (*(*(param_1+0x84))+0x3d8)+4 into param_1+0x30. */
extern void func_0203bc78(int param_1, int param_2);
struct m11 { int w[11]; };
void func_ov206_020ccb78(int param_1, int param_2) {
    int a = *(int *)(param_1 + 0x84);
    struct m11 *dst = (struct m11 *)(param_1 + 0x30);
    int src = *(int *)(*(int *)a + 0x3d8);
    *dst = *(struct m11 *)(src + 4);
    func_0203bc78(param_1, param_2);
}
