/* func_ov025_02095bc8 -- Ov008_SetupMenuGrid (244 B, 10 relocs).
 * Display setup for a grid-style menu screen (variant of func_ov008_020635c8). Builds the first
 * SRT/display object at p+0x124 (func_0203034c params 4,0xe), draws the entry via
 * func_ov025_02091a9c(p, arg4, arg5 + 1), and advances it (func_020300f8). Then, for the two grid
 * rows i = 0,1: builds the display object slot (p+0x160)[i+3] (0x3c stride) with func_0203034c
 * params (id, 0xf), where id runs 0xd, 0x10, and binds it to the row's target
 * ((E16 *)(p+0x2cc))[i].v via func_02030094. Finally enables cells 0x55 and 0x56
 * (func_ov025_0208ff84) and re-links widget 0x56 (func_ov025_0208896c / func_ov025_0208f144 on
 * the widget from func_ov025_0208843c). arg2 is the widget context; takes 5 args (arg5 on the
 * stack). Row target reads use a 16-byte struct subscript so mwcc recomputes p + i*0x10 each
 * iteration (index addressing) instead of adding an induction variable. */
typedef unsigned char u8;

typedef struct DisplayObj {
    u8  b[0x3c];
} DisplayObj;

typedef struct E16 {
    int v;
    u8  pad[12];
} E16;

typedef struct Ov008Setup {
    u8  pad_0000[0x124];
    u8  field124[0x250 - 0x124];   /* 0x124: SRT/display object A */
} Ov008Setup;

extern void  func_0203034c(void *base, int a, int b, int c, int d);
extern void  func_ov025_02091a9c(Ov008Setup *p, int a, int b);
extern void  func_020300f8(void *base);
extern void  func_02030094(void *base, int target, int update);
extern void  func_ov025_0208ff84(void *ctx, int id, int flag);
extern void *func_ov025_0208843c(void *ctx, int id);
extern void  func_ov025_0208896c(void *ctx, void *widget);
extern void  func_ov025_0208f144(void *widget);

void func_ov025_02095bc8(Ov008Setup *p, void *arg2, int arg3, int arg4, int arg5)
{
    int i;
    int id;

    func_0203034c(&p->field124, arg3, 4, 0xe, 0);
    func_ov025_02091a9c(p, arg4, arg5 + 1);
    func_020300f8(&p->field124);
    i = 0;
    id = 0xd;
    for (; i < 2; i++) {
        DisplayObj *slot = (DisplayObj *)((char *)p + 0x160) + (i + 3);
        func_0203034c(slot, arg3, id, 0xf, 0);
        func_02030094(slot, ((E16 *)((char *)p + 0x2cc))[i].v, 1);
        id += 3;
    }
    for (i = 0x55; i <= 0x56; i++) {
        func_ov025_0208ff84(arg2, i, 1);
    }
    func_ov025_0208896c(arg2, func_ov025_0208843c(arg2, 0x56));
    func_ov025_0208f144(func_ov025_0208843c(arg2, 0x56));
}
