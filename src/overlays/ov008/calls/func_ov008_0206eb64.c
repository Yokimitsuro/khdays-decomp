/* func_ov008_0206eb64 -- draw a page-B element while the gate at data_ov008_02090f20 is set,
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

extern int func_ov008_02050cec(void);
extern void func_ov008_0206d46c(int page, int p1, int a, int p2, void *pExtra, int one);
extern int data_ov008_02090f20;

int func_ov008_0206eb64(int param_1, int param_2, ...) {
    va_list ap;
    int page = func_ov008_02050cec();
    if (data_ov008_02090f20 != 0) {
        va_start(ap, param_2);
        func_ov008_0206d46c(page, param_1, 0, param_2, ap, 1);
        return 1;
    }
    return 0;
}
