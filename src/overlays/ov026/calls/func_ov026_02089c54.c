/* func_ov026_02089c54 -- Ov008_SetupMenuScreen (216 B, 8 relocs).
 * Initializes a menu screen from the shared panel context (*data_ov026_02091368): sets up the
 * display region at ctx+0xc214 (func_0203011c 8,0x10,0xb6,0x70), zero-clears the 0x400-byte
 * buffer at ctx+0x728, sets bit 1 of the flags at ctx+0x2aac, then registers eight entries
 * (arr[1..8] at ctx+0xc4f4) into the handle at ctx+0xbfb4 via func_02032450. Clears three
 * trailing fields and disables widget id 6 (ctx+0x7530), then func_ov026_02086210.
 * NOTE: the clear buffer's address is written as (u8 (*)[0x480])(ctx+0x2a8) + 1 so mwcc emits the
 * base(ctx+0x2a8) + 0x480 split the original uses, rather than folding ctx+0x728 into one add. */
typedef unsigned char u8;

extern char *data_ov026_02091368;
extern void  func_0203011c(void *dst, int a, int b, int c, int d);
extern void  INITi_CpuClear32_0x01ff86fc(int value, void *dst, unsigned int size);
extern void  func_02032450(void *a, int v);
extern void *func_ov026_0208427c(void *ctx, int id);
extern void  func_ov026_020843e8(void *ctx, void *widget, int flag);
extern void  func_ov026_02086210(void);

void func_ov026_02089c54(void)
{
    char *ctx = data_ov026_02091368;
    int  *arr = (int *)(ctx + 0xc4f4);
    void *handle = *(void **)(ctx + 0xbfb4);
    char *w = ctx + 0x7530;
    int i;

    func_0203011c(ctx + 0xc214, 8, 0x10, 0xb6, 0x70);
    INITi_CpuClear32_0x01ff86fc(0, (u8 (*)[0x480])(ctx + 0x2a8) + 1, 0x400);
    *(int *)(ctx + 0x2aac) |= 2;
    for (i = 0; i < 4; i++) {
        func_02032450(handle, arr[i + 1]);
        func_02032450(handle, arr[i + 5]);
    }
    arr[0xa] = 0;
    *(int *)(ctx + 0xc31c) = 0;
    *(int *)(ctx + 0xc314) = 0;
    func_ov026_020843e8(w, func_ov026_0208427c(w, 6), 0);
    func_ov026_02086210();
}
