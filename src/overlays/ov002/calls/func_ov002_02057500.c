/* Publish request kind 9 to the display list at +0xbc with priority 8 and mask
 * 0xf, then raise the scene's pending event 0x48 and close the request. Does
 * nothing at all while the object at +0x4c is absent -- and note the handle is
 * fetched BEFORE that check, which is why the ROM calls func_ov002_02053bb8
 * ahead of loading the context. */
typedef struct {
    char pad00[0x4c];
    int pTarget;            /* +0x4c */
    char pad50[0x6c];
    int aDisplayList[1];    /* +0xbc */
} Ov002SceneRoot;

extern int func_ov002_02053bb8(int kind);
extern void func_0203034c(void *list, int handle, int a, int b, int mask);
extern void func_ov002_0205e288(int a);
extern void func_ov002_02053558(int event);
extern void func_ov002_020535a4(void);
extern void func_ov002_02053cd4(int kind);

extern Ov002SceneRoot *data_ov002_0207f614;

void func_ov002_02057500(void) {
    int handle = func_ov002_02053bb8(9);
    Ov002SceneRoot *ctx = data_ov002_0207f614;

    if (ctx->pTarget == 0) {
        return;
    }

    func_0203034c(ctx->aDisplayList, handle, 8, 0, 0xf);
    func_ov002_0205e288(1);
    func_ov002_02053558(0x48);
    func_ov002_020535a4();
    func_ov002_02053cd4(9);
}
