/* func_ov000_0204cac0 -- Scene 1 (boot/logo) object grid setup, ov000.
 * NONMATCHING: register-allocation tie in a 116-instruction function. The retail
 * build holds the heap base in r6 (and pre-initializes the per-object mode in r8
 * before the loops); our mwcc allocates the heap to r4 and lays out the loop-
 * invariant constants differently, drifting by a few instructions. Logic is exact.
 * Kept for the PC port.
 *
 * Registers the logo resource (heap[2] or heap[1]) with the object manager
 * (@heap[0x6c]) via func_02032388, programs the main blend-alpha, then creates 10
 * scene objects (WM_EndKeySharing_0x02032444, stored at heap[0x1301+i]) and, per
 * object index, selects a Y position and mode by a switch and wires each one up
 * (func_020325ec / func_020326cc / func_0203281c / func_0203257c). */

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void  func_02032388(void *mgr, void *desc);
extern void  G2x_SetBlendAlpha_(int reg, int a, int b, int c, int d);
extern void *WM_EndKeySharing_0x02032444(void *mgr, int index, int);
extern void  func_020325ec(void *mgr, void *obj, int);
extern void  func_020326cc(void *mgr, void *obj);
extern void  func_0203281c(void *mgr, void *obj, int);
extern void  func_0203257c(void *mgr, void *obj, int *params);

void func_ov000_0204cac0(void) {
    int *h = (int *)NNSi_FndGetCurrentRootHeap();
    unsigned int addr;
    int i, j;
    struct { unsigned int addr; int a, b, c; } desc;

    if (h[2] != 0) {
        addr = ((h[2] + 0x8000 & 0xfffffc) << 7) | 0x80000001;
    } else {
        addr = ((h[1] + 0x8000 & 0xfffffc) << 7) | 0x80000002;
    }
    desc.addr = addr;
    desc.a = 2;
    desc.b = 0;
    desc.c = 0;
    func_02032388((void *)(h + 0x6c), &desc);

    G2x_SetBlendAlpha_(0x04001050, 0x10, 0x22, 0, 0x10);

    for (i = 0; i < 10; i++) {
        *(void **)((char *)h + 0x4c04 + i * 4) =
            WM_EndKeySharing_0x02032444((void *)(h + 0x6c), i, 0);
    }

    for (j = 0; j < 10; j++) {
        void *obj = *(void **)((char *)h + 0x4c04 + j * 4);
        int params[2];
        int mode;
        int active = 1;
        switch (j) {
        case 0:
            params[0] = 0x8000;
            params[1] = 0x84000;
            mode = 1;
            break;
        case 5:
            params[0] = 0;
            params[1] = 0x58000;
            mode = 0;
            break;
        case 1:
        case 3:
        case 6:
        case 8:
            params[0] = 0;
            params[1] = 0x74000;
            mode = 0;
            break;
        case 2:
        case 4:
        case 7:
        case 9:
            params[0] = 0;
            params[1] = 0x90000;
            mode = 0;
            break;
        default:
            active = 0;
            break;
        }
        if (active) {
            func_020325ec((void *)(h + 0x6c), obj, 0);
            if (mode == 0) {
                func_020326cc((void *)(h + 0x6c), obj);
            }
            func_0203281c((void *)(h + 0x6c), obj, 1);
            func_0203257c((void *)(h + 0x6c), obj, params);
        }
    }
}
