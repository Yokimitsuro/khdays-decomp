/* func_ov025_0209d44c -- Ov008_MoveMenuCursor (124 B, 7 relocs).
 * Moves the menu selection by arg0 (delta), wrapping within the current list. Gets the cursor
 * context (func_ov025_02084afc) and its list (func_ov025_0209bf40 on ctx->field2); wraps
 * (ctx count + arg0) modulo count via func_02020400 (which returns quotient/remainder as a 64-bit
 * value, remainder in the high word). Deselects the old entry list[3 + ctx->field0] and selects
 * the new list[3 + wrapped] via func_ov025_0209d2d8(entry, 0/1). Stores the new index, recomputes
 * the cursor pos (func_ov025_0209bf18 -> ctx->field_b4), clears ctx->field_b8, and refreshes. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;

typedef struct MenuCursor {
    s16 field0;         /* 0x0: selection index */
    u16 field2;         /* 0x2: list id */
    u8  pad_0004[0xb0];
    int field_b4;       /* 0xb4 */
    int field_b8;       /* 0xb8 */
} MenuCursor;

extern MenuCursor *func_ov025_02084afc(void);
extern u8  *func_ov025_0209bf40(int id);
extern long long func_02020400(int num, int den);
extern void func_ov025_0209d2d8(int a, int b);
extern int  func_ov025_0209bf18(int a, unsigned int b, int c);
extern void func_ov025_0209d2c4(void);

void func_ov025_0209d44c(int arg0)
{
    MenuCursor *ctx = func_ov025_02084afc();
    u8 *list = func_ov025_0209bf40(ctx->field2);
    int cnt = list[2];

    arg0 = (s16)(func_02020400(cnt + arg0, cnt) >> 0x20);
    func_ov025_0209d2d8(*(list + ctx->field0 + 3), 0);
    ctx->field0 = arg0;
    func_ov025_0209d2d8(*(list + arg0 + 3), 1);
    ctx->field_b4 = func_ov025_0209bf18(ctx->field2, (u16)ctx->field0, 0);
    ctx->field_b8 = 0;
    func_ov025_0209d2c4();
}
