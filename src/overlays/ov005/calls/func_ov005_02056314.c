/* func_ov005_02056314 -- select the list entry whose id the caller names: resolve it with
 * func_ov005_0204d434 and hand the result to func_ov005_0204d4c8, both on the widget at +8 of the
 * ov005 context. The id is an `int` parameter narrowed with `(unsigned short)` at the call -- a
 * `unsigned short` PARAMETER would emit no extension at all (the ABI assumes the caller did it),
 * and the ROM's `lsl #0x10 ; lsr #0x10` says it does extend here. */
extern int func_ov005_0204d434(int obj, int id);
extern void func_ov005_0204d4c8(int obj, int v);
extern int data_ov005_0205b810;

void func_ov005_02056314(int id) {
    int ctx = *(int *)&data_ov005_0205b810;
    func_ov005_0204d4c8(ctx + 8, func_ov005_0204d434(ctx + 8, (unsigned short)id));
}
