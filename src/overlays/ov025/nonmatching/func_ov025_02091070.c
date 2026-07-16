/* NONMATCHING: the ROM loads the renderer field straight off the call result (`ldr r1,[r0,#0x20]`);
 * mwcc copies the result to r1 first (`mov r1,r0; ldr r1,[r1,#0x20]`), +4B, and picks a different
 * callee-saved reg for the object. Inlining the call into the argument does not remove it. */
/* func_ov025_02091070 -- redraw an ov025 text row: restores the row's backdrop from the saved
 * copy (obj+0x2f4 -> the renderer's buffer, obj+0x2ec bytes), then when there is text (param_3)
 * draws it at y = row*0xe + 4 in colour 0xf1, and flushes the renderer (obj+0xe8). */
extern int  func_020303b4(int renderer);
extern void MIi_CpuCopyFast(void *src, void *dst, unsigned int size);
extern void func_0203031c(int renderer, int x, int y, int arg, int colour, int text);
extern void func_020300f8(int renderer);

void func_ov025_02091070(int param_1, int param_2, int param_3, int param_4) {
    MIi_CpuCopyFast(*(void **)(param_1 + 0x2f4),
                    *(void **)(func_020303b4(param_1 + 0xe8) + 0x20),
                    *(unsigned int *)(param_1 + 0x2ec));
    if (param_3 != 0) {
        func_0203031c(param_1 + 0xe8, 8, param_2 * 0xe + 4, param_4, 0xf1, param_3);
    }
    func_020300f8(param_1 + 0xe8);
}
