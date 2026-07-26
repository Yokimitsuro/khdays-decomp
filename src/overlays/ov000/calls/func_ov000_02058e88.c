/* func_ov000_02058e88 -- Scene 1: bring up the menu scene's display objects.
 *
 * Copies the resource-tracker capacity table onto the stack and initialises the
 * scene's tracker (+0x10c) with it, registers the menu archive subfile #6, applies
 * tag 0 and caches the entries for tags 1 and 2. Then it builds two display objects
 * from six-word descriptors: the title object at +0x158 (character subfile #5,
 * palette #4, 2 cells) with both of its extra cells hidden, and the cursor object at
 * +0x3d8+0x4800 (character #2, palette #1, 0x15 cells) whose cells 2/3/1 are cached
 * and whose cell 1 is made visible.
 *
 * Subfile handles use the archive idiom already matched in func_ov000_020526fc and
 * spelled as a macro in func_ov000_0204f838:
 *     ((base[0x21] + 0x8000 & 0x00fffffc) << 7) | 0x8000000N
 *
 * WHY THE THREE ADDRESS LOCALS ARE LOAD-BEARING, because it is not obvious and it is
 * the whole reason this function took a long time to match:
 *
 * mwcc rematerialises `base + constant` at every use, so `ctx`, `title` and `cursor`
 * produce EXACTLY the same instructions as writing `(char *)base + 0x10c` inline --
 * the same `add rN, r4, #imm` at every call site, byte for byte. What they change is
 * the size of the intermediate representation, and that turns out to matter.
 *
 * Written with the addresses inline, the function is byte-exact except for five words
 * in the SECOND descriptor block: the ROM computes the cell handle into r1 and stores
 * it to [sp] immediately, while mwcc computes it into ip and stores it one slot later,
 * after the [sp,#0x10] store. Nothing local to that block fixes it. What finally
 * identified the cause was a leave-one-out sweep over the whole function: deleting ANY
 * statement BEFORE the second block restores the ROM's schedule, and deleting any
 * statement AFTER it changes nothing. So the deferred store is a cumulative allocator
 * effect driven by the size of everything preceding it, not by the block itself --
 * which is why ~4000 compiled variants of that block (all 720 permutations of its six
 * assignments, all 720 of the first block's, 256 hoisting combinations, every capacity
 * spelling and struct layout, declaration orders, qualifiers, scopes, pragmas, compiler
 * flags and all 27 mwccarm builds) left the residue at exactly five words.
 *
 * Naming the three repeated addresses shrinks the expression tree by nine subtrees and
 * puts the allocator back under the threshold, at zero cost in emitted code. All three
 * are required: any one or two of them alone still leaves the five-word residue.
 *
 * The general lesson, worth more than this function: when a residue survives every
 * transformation of the code around it, stop varying the residue and bisect the
 * function for the construct that OWNS it. The owner routinely has no textual
 * relationship to the diff.
 */
typedef unsigned char  u8;
typedef unsigned int   u32;

/* Same five-word shape the matched func_ov000_0204f838 passes to this initialiser. */
typedef struct Ov000ResourceTrackerConfig {
    u32 entryCapacity;
    u32 nodeCapacity;
    u32 auxiliaryCapacity;
    void (*entryCallback)(void);
    void (*nodeCallback)(void);
} Ov000ResourceTrackerConfig;

extern const Ov000ResourceTrackerConfig data_ov000_0205a95c;

extern int *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_0205647c(void *tracker, const Ov000ResourceTrackerConfig *config);
extern void func_ov000_02056544(void *tracker, u32 archiveHandle);
extern int  func_ov000_02056818(void *tracker, unsigned int tag);
extern void func_ov000_020568ac(void *tracker, int entry);
extern void func_ov000_020556c8(void *object, int *descriptor);
extern int  func_ov000_02055b48(void *object, int cellId);
extern void func_ov000_02055cb4(void *object, int cell, int visible);

void func_ov000_02058e88(void)
{
    Ov000ResourceTrackerConfig capacity = data_ov000_0205a95c;
    int desc[6];
    int *base;
    char *cursorBase;
    char *ctx;
    char *title;
    char *cursor;

    base = NNSi_FndGetCurrentRootHeap();
    cursorBase = (char *)base + 0x3d8;
    ctx = (char *)base + 0x10c;
    title = (char *)base + 0x158;
    cursor = cursorBase + 0x4800;

    func_ov000_0205647c(ctx, &capacity);
    func_ov000_02056544(ctx, ((base[0x21] + 0x8000 & 0xfffffc) << 7) | 0x80000006);
    func_ov000_020568ac(ctx, func_ov000_02056818(ctx, 0));
    base[0x3450] = func_ov000_02056818(ctx, 1);
    base[0x3451] = func_ov000_02056818(ctx, 2);

    desc[0] = ((base[0x21] + 0x8000 & 0xfffffc) << 7) | 0x80000005;
    desc[1] = 1;
    desc[2] = 0;
    desc[3] = 0;
    desc[4] = 2;
    desc[5] = ((base[0x21] + 0x8000 & 0xfffffc) << 7) | 0x80000004;
    func_ov000_020556c8(title, desc);
    func_ov000_02055cb4(title, func_ov000_02055b48(title, 1), 0);
    func_ov000_02055cb4(title, func_ov000_02055b48(title, 2), 0);

    desc[0] = ((base[0x21] + 0x8000 & 0xfffffc) << 7) | 0x80000002;
    desc[1] = 2;
    desc[2] = 0;
    desc[3] = 0;
    desc[4] = 0x15;
    desc[5] = ((base[0x21] + 0x8000 & 0xfffffc) << 7) | 0x80000001;
    func_ov000_020556c8(cursor, desc);
    base[0x3452] = func_ov000_02055b48(cursor, 2);
    base[0x3453] = func_ov000_02055b48(cursor, 3);
    base[0x3454] = func_ov000_02055b48(cursor, 1);
    func_ov000_02055cb4(cursor, base[0x3454], 1);
}
