/*
 * Ov002_SceneHidePanel - drop the panel off screen without tearing the scene
 * down.
 *
 * The surfaces are closed, both text contexts are torn down (each only if it was
 * opened), the cursor is dismissed, and the three windows are folded away at
 * once. The scene goes back to state 0 and waits there.
 *
 * THUMB.
 */

extern int data_ov002_0207f624;

extern void func_0202ffbc(void *pContext);
extern void func_02023a44(int nObject, void *pStep);

extern void func_ov002_02053b28(int a, int b, int c, int d, int e);
extern void func_ov002_0205eb78(void);
extern void func_ov002_0205ec50(int nValue);
extern int func_ov002_0205ef08(void);

void func_ov002_0205f3f4(void)
{
    int *ctx;

    ctx = *(int **)&data_ov002_0207f624;
    func_ov002_0205eb78();

    if (*(int *)((char *)ctx + 0x7b8) != 0) {
        func_0202ffbc((char *)ctx + 0x6f8);
        *(int *)((char *)ctx + 0x7b8) = 0;
    }
    if (*(int *)((char *)ctx + 0x7bc) != 0) {
        func_0202ffbc((char *)ctx + 0x734);
        *(int *)((char *)ctx + 0x7bc) = 0;
    }

    func_ov002_0205ec50(0);
    func_ov002_02053b28(0xa, 0, 0, 0x20, 0x18);
    func_ov002_02053b28(9, 0, 0, 0x20, 0x18);
    func_ov002_02053b28(0xb, 0, 0, 0x20, 0x18);

    ctx[0] = 0;
    func_02023a44(*(int *)((char *)ctx + 0x6a4), func_ov002_0205ef08);
}
