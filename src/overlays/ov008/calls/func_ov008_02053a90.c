/* func_ov008_02053a90 -- Ov008_BuildMenuListFrom (136 B, 8 relocs).
 * Sibling of Ov008_BuildMenuList (func_ov008_0206f2a4): builds a display list on the stack
 * (NNS_FndInitList, link offset 0x28) and runs the begin/seed/collect/finalize walker over the
 * one-frame iterator (0x100 B), list (NNSFndList) and buffer (0x1e0 B). Here the seed source is
 * the caller's arg0 (func_ov008_020536ec's 4th argument) rather than the fixed id table. Between
 * collect passes it dispatches on the iterator's result at +0x2c: non-zero runs func_020235a8,
 * zero runs func_020235bc, both with 0x2010. Ends by collecting (func_ov008_0205393c) and
 * finalizing (func_02053464). */
typedef unsigned char  u8;
typedef unsigned short u16;

typedef struct NNSFndList {
    u16   numObjects;
    u16   offset;
    void *head;
    void *tail;
} NNSFndList;

typedef struct Ov008IterFrame {
    NNSFndList list;   /* 0x000 */
    u8 iter[0x100];    /* 0x00c */
    u8 buffer[0x1e0];  /* 0x10c */
} Ov008IterFrame;

extern void NNS_FndInitList(NNSFndList *list, int offset);
extern void func_ov008_020533e4(void *self, int a);
extern void func_ov008_020536ec(void *self, void *entries, NNSFndList *list, void *arg);
extern void func_ov008_02053470(void *self, void *entries, NNSFndList *list);
extern void func_020235a8(int id);
extern void func_020235bc(int id);
extern void func_ov008_0205393c(void *self, void *entries, NNSFndList *list);
extern void WM_EndKeySharing_0x02053464(void *self);

void func_ov008_02053a90(void *arg0)
{
    Ov008IterFrame f;

    NNS_FndInitList(&f.list, 0x28);
    func_ov008_020533e4(f.iter, 0);
    func_ov008_020536ec(f.iter, f.buffer, &f.list, arg0);
    func_ov008_02053470(f.iter, f.buffer, &f.list);
    if (*(int *)(f.iter + 0x2c) != 0) {
        func_020235a8(0x2010);
    } else {
        func_020235bc(0x2010);
    }
    func_ov008_0205393c(f.iter, f.buffer, &f.list);
    WM_EndKeySharing_0x02053464(f.iter);
}
