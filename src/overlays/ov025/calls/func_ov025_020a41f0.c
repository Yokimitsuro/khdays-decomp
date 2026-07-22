/* func_ov025_020a41f0 -- draw a page-B element while the gate at data_ov025_020b575c is set,
 * handing the draw its 5th argument as a pointer to the trailing arguments; returns 1 when drawn.
 *
 * VARIADIC, and the old note had the diagnosis exactly right and only needed the spelling: the ROM
 * builds the extra-argument pointer with the APCS aligned form (`add r2,sp,#0x14 ; bic r2,#3 ;
 * add r2,#4`) and RE-READS param_2 out of the home-save block, which is what `va_start(ap, param_2)`
 * does -- taking the parameter's address is what puts it in memory. Note this is the opposite of the
 * ov221 pair, where the re-read was the residue to remove: here the ROM wants it, so the naive
 * va_start is correct and naming the vararg would be wrong.
 *
 * The last 4 bytes were nothing to do with varargs: the gate was declared `int *` and tested as
 * `*g`, which is two loads. It is a plain `int` global -- one `ldr` for the address, one for the
 * value. */
typedef char *va_list;
#define va_start(ap, last) ((ap) = (char *)(((int)&(last) & ~3) + 4))

extern int func_ov025_02084b14(void);
extern void func_ov025_020a2b00(int page, int p1, int a, int p2, void *pExtra, int one);
extern int data_ov025_020b575c;

int func_ov025_020a41f0(int param_1, int param_2, ...) {
    va_list ap;
    int page = func_ov025_02084b14();
    if (data_ov025_020b575c != 0) {
        va_start(ap, param_2);
        func_ov025_020a2b00(page, param_1, 0, param_2, ap, 1);
        return 1;
    }
    return 0;
}
