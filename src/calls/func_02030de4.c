/*
 * List_TryInvokeEntry - run func_02030a4c on the indexed list entry if it is active.
 *
 * The manager global data_0204c22c points at a table whose entry array is at [+4]; each entry is
 * 0xc bytes. For index param_1, if the entry's activeness field (u16 at +4) is non-zero, the
 * global list context data_0204c02c is swapped in via func_0202362c (saving the previous one),
 * func_02030a4c is run on (entry, entryArray), then the previous context is restored. Returns 1
 * when it ran, 0 when the manager is null or the entry is inactive.
 */

extern int *data_0204c22c;
extern int data_0204c02c;
extern int func_0202362c(int list);
extern void func_02030a4c(int entry, int base);

int func_02030de4(int param_1)
{
    int *ctx = data_0204c22c;
    int off;
    int saved;

    if (ctx == 0)
        return 0;
    off = param_1 * 0xc;
    if (*(unsigned short *)(ctx[1] + off + 4) == 0)
        return 0;
    saved = func_0202362c(data_0204c02c);
    func_02030a4c(ctx[1] + off, ctx[1]);
    func_0202362c(saved);
    return 1;
}
