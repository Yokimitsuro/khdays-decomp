/* Ov008_MoveMenuCursor -- Ov008_MoveMenuCursor (124 B, 7 relocs).
 * Moves the menu selection by arg0 (delta), wrapping within the current list. Gets the cursor
 * context (Ov008_GetMenuContext) and its list (Ov008_GetPageTableEntry on ctx->field2); wraps
 * (ctx count + arg0) modulo count via func_02020400 (which returns quotient/remainder as a 64-bit
 * value, remainder in the high word). Deselects the old entry list[3 + ctx->field0] and selects
 * the new list[3 + wrapped] via Ov008_ShowItemList(entry, 0/1). Stores the new index, recomputes
 * the cursor pos (Ov008_Config_GetTabTitleRecord -> ctx->field_b4), clears ctx->field_b8, and refreshes. */

#include "nitro/types.h"

typedef struct MenuCursor {
    s16 field0;         /* 0x0: selection index */
    u16 field2;         /* 0x2: list id */
    u8  pad_0004[0xb0];
    int field_b4;       /* 0xb4 */
    int field_b8;       /* 0xb8 */
} MenuCursor;

extern MenuCursor *Ov008_GetMenuContext(void);
extern u8  *Ov008_GetPageTableEntry(int id);
extern long long func_02020400(int num, int den);
extern void Ov008_ShowItemList(int a, int b);
extern int  Ov008_Config_GetTabTitleRecord(int a, unsigned int b, int c);
extern void Ov008_RefreshMenuPage(void);

void Ov008_MoveMenuCursor(int arg0)
{
    MenuCursor *ctx = Ov008_GetMenuContext();
    u8 *list = Ov008_GetPageTableEntry(ctx->field2);
    int cnt = list[2];

    arg0 = (s16)(func_02020400(cnt + arg0, cnt) >> 0x20);
    Ov008_ShowItemList(*(list + ctx->field0 + 3), 0);
    ctx->field0 = arg0;
    Ov008_ShowItemList(*(list + arg0 + 3), 1);
    ctx->field_b4 = Ov008_Config_GetTabTitleRecord(ctx->field2, (u16)ctx->field0, 0);
    ctx->field_b8 = 0;
    Ov008_RefreshMenuPage();
}
