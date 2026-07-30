/* func_ov008_02057ac4 -- Ov008_DrawMenuValue (184 B, 9 relocs).
 * Draws a computed value onto the menu surface at arg0+0x4c. Bails if arg0 is null or if
 * func_ov008_020547d8 (fed the func_ov008_02050c54 context) returns null. Reads a value via
 * func_ov008_02057328(obj->fieldC); when it is >= 0 it is stored (u16) to arg0->field5c4. When
 * cue 0x200c is active (func_02023588) the value is replaced by 0x20 if func_ov008_0204ed3c()
 * reports idle, else -1; a negative value aborts the draw. Otherwise it builds a cell from the
 * value (func_ov008_02055c84 on arg0+4) and renders it onto the surface
 * (func_02030158 / func_02030278(.., 0x56, 0, 2, cell, 1) / func_020300f8). */
typedef unsigned short u16;

extern void *func_ov008_02050c54(void);
extern void *func_ov008_020547d8(void *ctx);
extern int   func_ov008_02057328(int a);
extern int   func_02023588(int flag);
extern int   func_ov008_0204ed3c(void);
extern int   func_ov008_02055c84(void *p, int v);
extern void  func_02030158(void *surface);
extern void  func_02030278(void *surface, int a, int b, int c, int d, int e);
extern void  func_020300f8(void *surface);

void func_ov008_02057ac4(void *arg0)
{
    char *p = (char *)arg0;
    void *ctx = func_ov008_02050c54();
    void *obj;
    int r4;

    if (p == 0) {
        return;
    }
    obj = func_ov008_020547d8(ctx);
    if (obj == 0) {
        return;
    }
    r4 = func_ov008_02057328(*(int *)((char *)obj + 0xc));
    if (r4 >= 0) {
        *(u16 *)(p + 0x5c4) = r4;
    }
    if (func_02023588(0x200c) != 0) {
        r4 = (func_ov008_0204ed3c() == 0) ? 0x20 : -1;
    }
    if (r4 < 0) {
        return;
    }
    r4 = func_ov008_02055c84(p + 4, r4);
    func_02030158(p + 0x4c);
    func_02030278(p + 0x4c, 0x56, 0, 2, r4, 1);
    func_020300f8(p + 0x4c);
}
