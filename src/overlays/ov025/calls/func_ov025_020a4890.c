/* func_ov025_020a4890 -- Ov008_BuildMenuList (144 B, 9 relocs).
 * Gated by data_ov025_020b575c: builds a display list on the stack (NNS_FndInitList, link offset
 * 0x28) and runs the begin/collect/finalize walker over it -- func_ov025_020874dc seeds it from
 * the game-state id table at data_0204be18+0xee0 into the work buffer, func_ov025_02087260 and
 * func_ov025_0208772c collect, func_ov025_020a4408 applies the menu step, and
 * func_02053464 finalizes. The iterator (0x100 B), list (NNSFndList) and buffer (0x1e0 B) live in
 * one stack frame so their offsets (0x0/0xc/0x10c) match the original layout. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct NNSFndList {
    u16 numObjects;
    u16 offset;
    void *head;
    void *tail;
} NNSFndList;

typedef struct Ov008IterFrame {
    NNSFndList list;   /* 0x000 */
    u8 iter[0x100];    /* 0x00c */
    u8 buffer[0x1e0];  /* 0x10c */
} Ov008IterFrame;

extern int   data_ov025_020b575c;
extern char *data_0204be18;
extern void  NNS_FndInitList(NNSFndList *list, int offset);
extern void  func_ov025_020871d4(void *self, int a);
extern void  func_ov025_020874dc(void *self, void *entries, NNSFndList *list, u16 *ids);
extern void  func_ov025_02087260(void *self, void *entries, NNSFndList *list);
extern void  func_ov025_020a4408(void *self);
extern void  func_ov025_0208772c(void *self, void *entries, NNSFndList *list);
extern void  WM_EndKeySharing_0x02087254(void *self);

void func_ov025_020a4890(void)
{
    Ov008IterFrame f;

    if (data_ov025_020b575c == 0) {
        return;
    }
    NNS_FndInitList(&f.list, 0x28);
    func_ov025_020871d4(f.iter, 0);
    func_ov025_020874dc(f.iter, f.buffer, &f.list, (u16 *)(data_0204be18 + 0xee0));
    func_ov025_02087260(f.iter, f.buffer, &f.list);
    func_ov025_020a4408(f.iter);
    func_ov025_0208772c(f.iter, f.buffer, &f.list);
    WM_EndKeySharing_0x02087254(f.iter);
}
