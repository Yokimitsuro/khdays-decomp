/* func_ov000_0204d630 -- Scene 1 (boot/logo) class constructor, ov000.
 * Registered as the constructor in the scene-1 class descriptor @0x0205a9c0;
 * RunClassConstructor calls it as ctor(arg) and stores its return as the object's
 * initial state fn (obj+0x14). Grabs the current root heap as the scene's data
 * block, caches it in data_ov000_0205ac20, runs one-time init (func_0201e1d0),
 * then picks the initial state from the launch arg and the boot sub-mode
 * (func_ov000_02054bac): arg 0xfffffffe = respawn/re-enter, arg 0 = default (->2).
 * Fresh-boot path zero-fills the 0x507c-byte block and hands off to
 * func_ov000_0204d7c8 for the real logo setup. Heap word indices:
 *   [0x1311] re-enter flag, [0x1313] boot sub-mode, [0x1317] mode-5 flag. */

typedef void *StateFn;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_0201e1d0(void);
extern int   func_ov000_02054bac(void);
extern int   func_ov000_02054c20(int mode);
extern void  MI_CpuFill8(void *dst, int val, int size);
extern StateFn func_ov000_0204d7c8(int arg);
extern void  func_ov000_0204f6c8(void);   /* state fn (returned by address) */
extern void  func_ov000_0204d560(void);   /* state fn */
extern void *data_ov000_0205ac20;

StateFn func_ov000_0204d630(unsigned int arg) {
    int *heap = (int *)NNSi_FndGetCurrentRootHeap();
    data_ov000_0205ac20 = heap;
    func_0201e1d0();

    if (arg == 0xfffffffe) {
        int mode = func_ov000_02054bac();
        switch (mode) {
        case 3:
            heap[0x1313] = 2;
            return (StateFn)func_ov000_0204f6c8;
        case 5:
            if (func_ov000_02054c20(mode) == 0) {
                heap[0x1313] = 2;
                return (StateFn)func_ov000_0204f6c8;
            }
            break;
        }
    } else {
        int mode = func_ov000_02054bac();
        if (arg != 0 || mode == 3) {
            if (arg == 0) {
                arg = 2;
            }
            heap[0x1313] = arg;
            return (StateFn)func_ov000_0204f6c8;
        }
        if (mode == 5) {
            heap[0x1317] = 1;
            return (StateFn)func_ov000_0204d560;
        }
    }

    MI_CpuFill8(heap, 0, 0x507c);
    if (arg == 0xfffffffe) {
        heap[0x1311] = 1;
    }
    return func_ov000_0204d7c8(0);
}
