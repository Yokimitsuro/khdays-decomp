/* NONMATCHING: instruction-scheduling tie — the ROM stores the resolved row straight from r0
 * (`str r0,[r5,#4]`) right after the call; mwcc moves the store after the next call's argument
 * setup and stores from r1. Identical otherwise. */
/* func_ov025_0209bfcc -- point a slot widget at item id param_2: stores the id, resolves its
 * table row (func_ov025_0208843c) into +4, and copies the row's 8-byte record
 * (func_ov025_020884c8) into the widget at +8. */
extern int  func_ov025_02084a7c(void);
extern int  func_ov025_0208843c(int ctx, int id);
extern unsigned short *func_ov025_020884c8(int ctx, int row);
extern void MI_CpuCopy8(const void *src, void *dst, unsigned int size);

void func_ov025_0209bfcc(short *param_1, short param_2) {
    int ctx = func_ov025_02084a7c();
    int row;
    *param_1 = param_2;
    row = func_ov025_0208843c(ctx, *param_1);
    *(int *)(param_1 + 2) = row;
    MI_CpuCopy8(func_ov025_020884c8(ctx, row), param_1 + 4, 8);
}
