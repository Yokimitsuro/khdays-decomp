/*
 * func_0201c734 - allocate an object entry, bind two resources to it, and apply
 * the caller's config. Reserves the entry (func_0201a4c4) - failing that,
 * returns 0. Resolves its record (func_0201a62c), then fetches resource kind 6
 * from param_3 (func_0201bd30) and kind 1 from param_6 (func_0201bc4c); if either
 * lookup fails it releases the entry (WM_EndKeySharing_0x0201a55c veneer) and
 * returns 0. On success it wires the entry's data pointer from the second
 * resource (func_0201a568), pushes two config bytes from param_5[6]/param_5[7]
 * (func_0201a110/func_0201a150) and a param_6-derived value (func_0201a1c0), and
 * returns 1.
 */
extern void *func_0201a4c4(void *handle, int b, int d);
extern void *func_0201a62c(int index, void *parent);
extern int func_0201bd30(int a, int b, void *rec, int d, unsigned int *out);
extern int func_0201bc4c(int a, int b, void *rec, int d, unsigned int *out);
extern void func_0201a568(void *p, int addr, int v, unsigned int local);
extern void func_0201a110(void *a, int b);
extern void func_0201a150(void *a, int b);
extern void func_0201a1c0(void *a, int b);
extern void WM_EndKeySharing_0x0201a55c(void *p);

int func_0201c734(void *param_1, int param_2, int param_3, int param_4, unsigned char *param_5, int param_6)
{
    void *puVar1;
    void *piVar2;
    unsigned int uStack_20, uStack_24;

    puVar1 = func_0201a4c4(param_1, param_2, param_4);
    if (puVar1 == 0)
        return 0;
    piVar2 = func_0201a62c(param_2, puVar1);
    if (func_0201bd30(param_3, 6, piVar2, 0, &uStack_24) != 0) {
        WM_EndKeySharing_0x0201a55c(puVar1);
        return 0;
    }
    if (func_0201bc4c(param_6, 1, piVar2, 0, &uStack_20) != 0) {
        WM_EndKeySharing_0x0201a55c(puVar1);
        return 0;
    }
    func_0201a568(puVar1, uStack_20 + *(int *)(uStack_20 + 0x18), 0, uStack_24);
    func_0201a110(param_1, param_5[6]);
    func_0201a150(param_1, param_5[7]);
    func_0201a1c0(param_1, param_6);
    return 1;
}
