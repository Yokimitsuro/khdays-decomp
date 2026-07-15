/* func_ov000_0204d72c -- Scene 1 (boot/logo) resource preload, ov000.
 * Called first thing by the fresh-boot setup (func_ov000_0204d7c8). Loads the
 * always-present logo resource into scene-heap slot [1], then by region/variant
 * (func_02024e5c): variant 1 uses no secondary resource (slot [2] = NULL),
 * variants 2..5 load a region-specific secondary resource into slot [2], and any
 * other value (0 or >5) is a fatal configuration error -> OS_Terminate. */

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void *func_02024ee8(void *desc, int mode);
extern int   func_02024e5c(void);
extern void  OS_Terminate(void);
extern char  data_ov000_0205aa18[];
extern char  data_ov000_0205aa24[];

void func_ov000_0204d72c(void) {
    void **h = (void **)NNSi_FndGetCurrentRootHeap();
    h[1] = func_02024ee8(data_ov000_0205aa18, 0xe);
    switch (func_02024e5c()) {
    case 1:
        h[2] = 0;
        break;
    case 2:
    case 3:
    case 4:
    case 5:
        h[2] = func_02024ee8(data_ov000_0205aa24, 0xe);
        break;
    default:
        OS_Terminate();
    }
}
