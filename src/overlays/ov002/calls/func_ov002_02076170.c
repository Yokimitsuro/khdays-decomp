typedef struct {
    char pad00[4];
    char *pContext;                 /* +0x04 */
} Ov002SceneRef;

extern Ov002SceneRef data_ov002_0207fa20;

extern void func_02030d10(int nMode);
extern void func_ov002_0207640c(void);
extern void func_02024fd4(int pObject);
extern void func_02020aa8(int nId, int nFlags);
extern void func_0201e4a8(int nKind, int nHandle);

/* Tear down the scene: stop the sub-object it owns, release the reserved slot
 * if one is held, and drop the context reference. */
void func_ov002_02076170(void)
{
    func_02030d10(5);
    func_ov002_0207640c();

    if (*(int *)(data_ov002_0207fa20.pContext + 0x60) != 0) {
        func_02024fd4(*(int *)(data_ov002_0207fa20.pContext + 0x60));
        *(int *)(data_ov002_0207fa20.pContext + 0x60) = 0;
    }

    if (*(signed char *)(data_ov002_0207fa20.pContext + 0x260) != -1) {
        func_02020aa8(*(signed char *)(data_ov002_0207fa20.pContext + 0x260) + 5, 0);
        func_0201e4a8(0, *(int *)(data_ov002_0207fa20.pContext + 0x264));
        *(signed char *)(data_ov002_0207fa20.pContext + 0x260) = -1;
    }

    data_ov002_0207fa20.pContext = 0;
}
