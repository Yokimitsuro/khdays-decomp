/* func_ov008_0206f4c0 -- Ov008_ScrollPageDown (388 B, 19 relocs).
 * Menu scroll-down input step. Bails early unless the input global is set, the mode getter returns
 * 2 (or ctx+0x44 != 1), and ctx+8 (a busy flag) is clear. It samples a viewport metric via
 * func_ov008_02055c24 (an 8-byte out struct; the second halfword feeds the bound), then combines
 * the field-0x3c offset (minus 8) with that metric through the signed div/mod-16 idioms to get the
 * scroll bound. It counts the visible list objects and, if the list already fits (count <= 8 and
 * bound+row >= count), does nothing. Otherwise it shows entries 0x29/0x51, hides 0x80, applies the
 * control value, drives the scroll (func_ov008_0206c90c), plays a click, hides entry 5, and marks
 * ctx+0x14 dirty. */
typedef unsigned short u16;
typedef unsigned int   u32;

extern int  data_ov008_02090f20;

extern int  func_ov008_02050cec(void);
extern int  OS_IsThreadAvailable_0x02051aa0(void);
extern int  func_ov008_02050c64(void);
extern int  func_ov008_02050c3c(void);
extern void func_ov008_02055c24(int block, void *out);
extern int  NNS_FndGetNextListObject(void *list, int obj);
extern int  func_ov008_02054788(int root, int id);
extern void func_ov008_02054ba4(int root, int entry, int vis);
extern void func_ov008_02050a64(int a);
extern void func_ov008_0206c90c(int ctx, int bound, int b, int c);
extern void func_02033b78(int a, int b);

void func_ov008_0206f4c0(void)
{
    u16 pt[4];
    int ctx = func_ov008_02050cec();
    int block1, block2, getter, base, bound, total, entry;
    int count = 0;

    if (data_ov008_02090f20 == 0)
        return;
    getter = OS_IsThreadAvailable_0x02051aa0();
    if (getter == 2 || *(int *)(ctx + 0x44) == 1)
        return;
    if (*(int *)(ctx + 8) != 0)
        return;

    block1 = func_ov008_02050c64();
    block2 = func_ov008_02050c3c();
    func_ov008_02055c24(block2, pt);
    base = *(int *)(ctx + 0x3c) - 8;
    bound = pt[1] + base % 16;
    total = bound / 16 + base / 16;
    for (entry = NNS_FndGetNextListObject((void *)(ctx + 0x1cc), 0); entry != 0;
         entry = NNS_FndGetNextListObject((void *)(ctx + 0x1cc), entry))
        count++;
    if (count <= 8 && total + base / 16 >= count)
        return;

    entry = func_ov008_02054788(block1, 0x29);
    func_ov008_02054ba4(block1, entry, 1);
    entry = func_ov008_02054788(block1, 0x51);
    func_ov008_02054ba4(block1, entry, 1);
    entry = func_ov008_02054788(block1, 0x80);
    func_ov008_02054ba4(block1, entry, 0);
    func_ov008_02050a64(0);
    func_ov008_0206c90c(ctx, total, 1, 0);
    func_02033b78(0, 0);
    entry = func_ov008_02054788(block1, 5);
    func_ov008_02054ba4(block1, entry, 0);
    *(int *)(ctx + 0x14) = 1;
}
