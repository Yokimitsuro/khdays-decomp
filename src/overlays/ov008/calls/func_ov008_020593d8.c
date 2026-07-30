/* func_ov008_020593d8 -- Ov008_SetupMenuSurfaces (236 B, 14 relocs).
 * Configures the menu's two render surfaces (arg0+0x10 and arg0+0x4c) from style templates and
 * draws a value onto the second. Copies the two 0x28-byte style templates (data_ov008_0208e974,
 * data_ov008_0208e99c) to locals, overrides each one's field18 (func_ov008_02050c7c(9)) and
 * field20 (func_ov008_02050e74()), then applies them with func_0202ff8c. Sets arg0->field74 = 1,
 * ticks func_ov008_020579a8, renders a cell built from func_ov008_02055c84(arg0+4, 9) onto the
 * arg0+0x4c surface (func_02030278(.., 0x56, 0, 2, cell, 0)), flushes both surfaces
 * (func_020300f8), and releases slot 9 (func_ov008_02050b3c). */
typedef unsigned char u8;

typedef struct Style28 {
    u8  pad_0000[0x18];
    int field18;        /* 0x18 */
    u8  pad_001c[4];
    int field20;        /* 0x20 */
    u8  pad_0024[4];
} Style28;

extern Style28 data_ov008_0208e974;
extern Style28 data_ov008_0208e99c;
extern int  func_ov008_02050e74(void);
extern int  func_ov008_02050c7c(int a);
extern void func_0202ff8c(void *dst, Style28 *src);
extern void func_ov008_020579a8(void *p);
extern int  func_ov008_02055c84(void *p, int v);
extern void func_02030278(void *surface, int a, int b, int c, int d, int e);
extern void func_020300f8(void *surface);
extern void func_ov008_02050b3c(int a);

void func_ov008_020593d8(void *arg0)
{
    char *p = (char *)arg0;
    Style28 s1 = data_ov008_0208e974;
    Style28 s2 = data_ov008_0208e99c;

    s1.field20 = func_ov008_02050e74();
    s1.field18 = func_ov008_02050c7c(9);
    s2.field20 = func_ov008_02050e74();
    s2.field18 = func_ov008_02050c7c(9);
    func_0202ff8c(p + 0x10, &s1);
    func_0202ff8c(p + 0x4c, &s2);
    *(int *)(p + 0x74) = 1;
    func_ov008_020579a8(arg0);
    func_02030278(p + 0x4c, 0x56, 0, 2, func_ov008_02055c84(p + 4, 9), 0);
    func_020300f8(p + 0x4c);
    func_020300f8(p + 0x10);
    func_ov008_02050b3c(9);
}
