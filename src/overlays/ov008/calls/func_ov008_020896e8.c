extern int func_ov008_020882d8(void);
extern void FS_UnloadOverlayImage_0x020362ec(void *image);
extern void func_ov008_02082bf4(void);
extern void func_ov008_020878c4(void);
extern void func_ov008_02089c5c(void);
extern char *data_ov008_02090fac[];

void *func_ov008_020896e8(void)
{
    void *result;

    if (func_ov008_020882d8() != 0) {
        result = func_ov008_02089c5c;
    } else {
        result = 0;
    }

    FS_UnloadOverlayImage_0x020362ec(data_ov008_02090fac[0] + 0xc0fc);
    func_ov008_02082bf4();
    func_ov008_020878c4();

    return result;
}
