/* func_ov008_0205e058 -- Ov008_UploadTileSlot (156 B, 6 relocs).
 * Uploads tile slot arg1 (0x800 bytes) into the work buffer and, when arg2 != 0, draws it.
 * Copies 0x800 bytes from arg0->field2f0[arg1] to (func_020303b4(arg0+0xac))->field20[arg1]
 * (both indexed by arg1 * 0x800) with MIi_CpuCopyFast. If arg2 == 0 it stops there. Otherwise,
 * when func_02013814(arg0->fieldcc, arg0->fieldd0, arg2) >= 0x52 it latches fieldcc to the
 * func_ov008_02050ea4 handle, renders via func_02030278(arg0+0xac, 0x14, arg1*16+3, arg3, arg2,
 * 1), and finally sets arg0->fieldcc to the func_ov008_02050e74 handle. */
extern char *func_020303b4(void *p);
extern int   func_ov008_02050e74(void);
extern int   func_ov008_02050ea4(void);
extern int   func_02013814(int a, int b, int c);
extern void  MIi_CpuCopyFast(const void *src, void *dst, unsigned int size);
extern void  func_02030278(void *surface, int a, int b, int c, int d, int e);

void func_ov008_0205e058(void *arg0, int arg1, int arg2, int arg3)
{
    char *p = (char *)arg0;
    char *buf = func_020303b4(p + 0xac);
    char *dst = *(char **)(buf + 0x20);
    int r4 = func_ov008_02050e74();
    int newval = func_ov008_02050ea4();

    MIi_CpuCopyFast(*(char **)(p + 0x2f0) + arg1 * 0x800, dst + arg1 * 0x800, 0x800);
    if (arg2 == 0) {
        return;
    }
    if (func_02013814(*(int *)(p + 0xcc), *(int *)(p + 0xd0), arg2) >= 0x52) {
        *(int *)(p + 0xcc) = newval;
    }
    func_02030278(p + 0xac, 0x14, arg1 * 16 + 3, arg3, arg2, 1);
    *(int *)(p + 0xcc) = r4;
}
