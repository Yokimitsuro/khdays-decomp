/* func_ov008_0206a700 -- Ov008_SetupMenuSurface (108 B, 7 relocs).
 * Configures the primary menu surface (ctx+0x10) from a single style template. Copies the
 * 0x28-byte template data_ov008_0208f618 to a local, binds the cell table data_ov008_0209078c to
 * the list at ctx+4 (func_ov008_02055c4c), overrides the template's field18
 * (func_ov008_02050c7c(9)) and field20 (func_ov008_02050e74()), and applies it with func_0202ff8c.
 * The one-surface counterpart of func_ov008_020593d8 (Ov008_SetupMenuSurfaces). */
typedef unsigned char u8;

typedef struct Style28 {
    u8  pad_0000[0x18];
    int field18;        /* 0x18 */
    u8  pad_001c[4];
    int field20;        /* 0x20 */
    u8  pad_0024[4];
} Style28;

extern Style28 data_ov008_0208f618;
extern int  data_ov008_0209078c;
extern void *func_ov008_02050cd4(void);
extern void func_ov008_02055c4c(void *p, void *tbl);
extern int  func_ov008_02050e74(void);
extern int  func_ov008_02050c7c(int a);
extern void func_0202ff8c(void *dst, Style28 *src);

void func_ov008_0206a700(void)
{
    Style28 s = data_ov008_0208f618;
    char *ctx = (char *)func_ov008_02050cd4();

    func_ov008_02055c4c(ctx + 4, &data_ov008_0209078c);
    s.field20 = func_ov008_02050e74();
    s.field18 = func_ov008_02050c7c(9);
    func_0202ff8c(ctx + 0x10, &s);
}
