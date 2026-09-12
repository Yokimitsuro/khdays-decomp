typedef unsigned short u16;

typedef void *(*VoiceEntryFn)(void);

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov043_020b3290(void *pObj);
extern void func_ov043_020b37dc(void *root);
extern void func_ov043_020b4734(void *root);
extern void func_ov022_020a4798(void *pActor, short nId, u16 nArg2);
extern void *func_ov022_0209fb24(void);

/* Initialize the voice decoder for pObj, then hand back the entry point
 * (func_ov022_0209fb24) without calling it -- the caller invokes it later. */
VoiceEntryFn func_ov043_020b3234(void *pObj) {
    void *root = NNSi_FndGetCurrentRootHeap();

    func_ov043_020b3290(pObj);
    func_ov043_020b37dc(root);
    func_ov043_020b4734(root);
    func_ov022_020a4798(root, 0x4f, 0xc4);

    return (VoiceEntryFn)func_ov022_0209fb24;
}
