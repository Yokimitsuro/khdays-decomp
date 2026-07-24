/* func_ov000_0205a4d4 -- leave the title and start the next scene.
 *
 * Tears the title down (func_ov000_02059f50), publishes the scene block in
 * data_ov000_0205ac3c, then loads and instantiates one of two scenes depending on the
 * transition mode at heap+0xd138: mode 0 goes to the movie player (ov012), anything else
 * to ov011.  The new object is parked at heap+0xd13c and the state machine advances to
 * func_ov000_0205a5e8.
 *
 * Both overlay ids are the ADDRESS of a linker-absolute symbol -- the NitroSDK
 * FS_OVERLAY_ID idiom, which dsd emits into arm9.lcf as `OVERLAY_11_ID = 11;` /
 * `OVERLAY_12_ID = 12;`.  Spelled as plain integers the two pool words disappear and the
 * function comes out 8 bytes short.
 */
typedef unsigned int u32;
typedef u32 FSOverlayID;
typedef void *StateFn;

extern u32 OVERLAY_11_ID[1];
extern u32 OVERLAY_12_ID[1];
#define FS_OVERLAY_ID_ov011 ((FSOverlayID)(u32) & (OVERLAY_11_ID))
#define FS_OVERLAY_ID_ov012 ((FSOverlayID)(u32) & (OVERLAY_12_ID))

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void func_ov000_02059f50(void);
extern void func_0201e470(int target, FSOverlayID id);
extern void *func_02023930(void *classDesc, int arg);
extern void *data_ov000_0205ac3c;
extern int data_ov011_0205e8a0;
extern int data_ov012_0205c2bc;
extern void func_ov000_0205a5e8(void);

StateFn func_ov000_0205a4d4(void) {
    char *heap = (char *)NNSi_FndGetCurrentRootHeap();
    void *obj;

    func_ov000_02059f50();
    data_ov000_0205ac3c = heap;
    if (*(int *)(heap + 0xd138) == 0) {
        func_0201e470(0, FS_OVERLAY_ID_ov012);
        obj = func_02023930((void *)&data_ov012_0205c2bc, 1);
    } else {
        func_0201e470(0, FS_OVERLAY_ID_ov011);
        obj = func_02023930((void *)&data_ov011_0205e8a0, 1);
    }
    *(void **)(heap + 0xd13c) = obj;
    return (StateFn)func_ov000_0205a5e8;
}
