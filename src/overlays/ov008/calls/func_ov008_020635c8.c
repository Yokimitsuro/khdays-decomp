/* func_ov008_020635c8 -- Ov008_SetupMenuDisplay (212 B, 12 relocs).
 * One-shot display setup for a menu screen. Builds the two SRT/display objects embedded in the
 * scene struct (func_0203034c on p+0x124 with params 4,0xe and on p+0x250 with 0xf,0xf), advances
 * the first (func_020300f8) and binds the second to p->field2e0 (func_02030094), enables the 0x5c
 * cell (func_ov008_0205da10) and re-links it (func_ov008_02054cc4 / func_ov008_0205cbb0 on the
 * widget from func_ov008_02054788), then registers the screen via func_ov008_0205eafc with the
 * count from func_ov008_02055c84(p+0x28c, 8). Takes 5 args (arg5 on the stack). */
typedef unsigned char u8;
typedef struct Ov008Setup {
    u8  pad_0000[0x124];
    u8  field124[0x250 - 0x124];   /* 0x124: SRT/display object A */
    u8  field250[0x28c - 0x250];   /* 0x250: SRT/display object B */
    u8  field28c[0x2e0 - 0x28c];   /* 0x28c */
    int field2e0;                  /* 0x2e0 */
} Ov008Setup;

extern void  func_0203034c(void *base, int a, int b, int c, int d);
extern void  func_ov008_0205f54c(Ov008Setup *p, int a, int b);
extern void  func_020300f8(void *base);
extern void  func_02030094(void *base, int target, int update);
extern void  func_ov008_0205da10(void *ctx, int id, int flag);
extern void *func_ov008_02054788(void *ctx, int id);
extern void  func_ov008_02054cc4(void *ctx, void *widget);
extern void  func_ov008_0205cbb0(void *widget);
extern int   func_ov008_02055c84(void *base, int n);
extern void  func_ov008_0205eafc(Ov008Setup *p, int a, int b, int c);

void func_ov008_020635c8(Ov008Setup *p, void *arg2, int arg3, int arg4, int arg5)
{
    func_0203034c(&p->field124, arg3, 4, 0xe, 0);
    func_ov008_0205f54c(p, arg4, arg5 + 1);
    func_020300f8(&p->field124);
    func_0203034c(&p->field250, arg3, 0xf, 0xf, 0);
    func_02030094(&p->field250, p->field2e0, 1);
    func_ov008_0205da10(arg2, 0x5c, 1);
    func_ov008_02054cc4(arg2, func_ov008_02054788(arg2, 0x5c));
    func_ov008_0205cbb0(func_ov008_02054788(arg2, 0x5c));
    func_ov008_0205eafc(p, 0, func_ov008_02055c84(&p->field28c, 8), 0xf3);
}
