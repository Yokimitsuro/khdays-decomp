/* func_ov025_02091a9c -- Ov008_DrawMenuEntry (124 B, 4 relocs).
 * Draws menu entry arg1 (with value arg2) onto the surface at arg0+0x124. Copies the 6-entry text
 * table data_ov025_020b3ce0 to a local, opens the surface (func_02030158), builds a cell from the
 * table's arg1-th id via func_ov025_020898cc(arg0+0x28c, tbl[arg1], work, 0x80, arg2) into a 0x100
 * work buffer, and renders it with func_02030278(arg0+0x124, 0, 0, 0xf3, cell, 1). */
typedef unsigned char u8;

typedef struct Buf18 { int entries[6]; } Buf18;

extern Buf18 data_ov025_020b3ce0;
extern void func_02030158(void *surface);
extern int  func_ov025_020898cc(void *a, int b, void *work, int n, int e);
extern void func_02030278(void *surface, int a, int b, int c, int d, int e);

void func_ov025_02091a9c(void *arg0, int arg1, int arg2)
{
    char *ctx = (char *)arg0;
    Buf18 tbl = data_ov025_020b3ce0;
    u8 work[0x100];

    func_02030158(ctx + 0x124);
    func_02030278(ctx + 0x124, 0, 0, 0xf3,
                  func_ov025_020898cc(ctx + 0x28c, tbl.entries[arg1], work, 0x80, arg2), 1);
}
