extern int *NNSi_FndGetCurrentRootHeap(void);
extern int *func_02024ee8(void *res, int b, int *c);
extern void func_ov007_0204d33c(int *out, int arg);
extern int func_020235d0(int a, int b);
extern void *func_ov007_0204d374(int *s, int idx);
extern void func_ov007_0204cac0(void);
extern int *func_0201ef9c(int arg, int b);
extern void func_02024c94(int *a, int *b, int c, int d, int e);
extern void GFXi_EnqueueCommand(int a, int b, int c, int d);
extern void func_02024ae0(int a, int b, int c, int d);
extern void func_02024b04(int a, int b, int c, int d);
extern void func_02032388(int *a, unsigned int *b);
extern int WM_EndKeySharing_0x02032444(int *a, int b, int c);
extern void func_0203257c(int *a, int b, unsigned int *c);
extern void func_0203281c(int *a, int b, int c);
extern void func_0202f7fc(int *a, void *b);
extern void func_0202f834(int *a, int b, int *c, unsigned short *d);
extern void GX_LoadBGPltt(void *a, int b, int c);
extern void func_ov007_0204cf18(void);

extern int data_ov007_0204d420;
extern int data_ov007_0204d3d8;
extern int data_ov007_0204d3e4;
extern int data_ov007_0204d3f8;
extern int data_ov007_0204d3ac;

/* ov007 scene init: grab the root heap, publish it, spawn the framebuffer/dual-screen
 * objects, pick the sub-display layout from the handler code (7..13 -> 1..7), build the
 * OAM/BG resources, configure the scroll box + palette, and return the per-frame update
 * handler (0204cf18). */
void *func_ov007_0204cb80(int param_1, int param_2, int param_3, int param_4) {
    int *heap = NNSi_FndGetCurrentRootHeap();
    int idx;
    struct {
        unsigned int box[2];
        unsigned short blk[8];
        unsigned int l24[4];
    } fr;

    data_ov007_0204d420 = (int)heap;
    heap[0x16b0] = param_1;
    heap[0] = (int)func_02024ee8(&data_ov007_0204d3d8, 0xf, heap + 0x1400);
    func_ov007_0204d33c(heap + 2, (int)&data_ov007_0204d3e4);

    heap[0x16ae] = func_020235d0(0, 9);
    switch (heap[0x16ae]) {
    case 7:  idx = 1; break;
    case 8:  idx = 2; break;
    case 9:  idx = 3; break;
    case 10: idx = 4; break;
    case 11: idx = 5; break;
    case 12: idx = 6; break;
    case 13: idx = 7; break;
    default: idx = 0; break;
    }
    heap[0x1d] = (int)func_ov007_0204d374(heap + 2, idx);
    heap[0x1e] = 0;
    heap[0x16af] = 0;
    func_ov007_0204cac0();
    heap[1] = (int)func_0201ef9c(
        (int)(((((unsigned)heap[0] + 0x8000) & 0xfffffc) << 7) | 0x80000000), 0xe);
    func_02024c94(heap + 5, (int *)heap[1], heap[0x16af], heap[0x16af], heap[0x16af]);
    GFXi_EnqueueCommand(0x11, 0x2000, *(int *)(heap[7] + 0xc), *(int *)(heap[7] + 8));
    func_02024ae0(1, heap[6], 0, *(int *)(heap[6] + 0x10));
    {
        int iVar9 = *(int *)(heap[5] + 8);
        func_02024b04(1, heap[5], 0, iVar9);

        fr.l24[0] = ((((unsigned)heap[0] + 0x8000) & 0xfffffc) << 7) | 0x80000001;
        fr.l24[1] = 1;
        fr.l24[2] = 0;
        fr.l24[3] = 0;
        func_02032388(heap + 0x41f, fr.l24);
        heap[0x16ad] = WM_EndKeySharing_0x02032444(heap + 0x41f, 0, 0);

        fr.box[0] = 0x80000;
        fr.box[1] = 0xbc000;
        func_0203257c(heap + 0x41f, heap[0x16ad], fr.box);
        func_0203281c(heap + 0x41f, heap[0x16ad], 0);
        func_0202f7fc(heap + 9, &data_ov007_0204d3f8);

        {
            unsigned short flag = 0;
            fr.blk[0] = flag;
            if (heap[0x16af] == 0) {
                flag = 0xc;
            }
            fr.blk[1] = flag;
        }
        fr.blk[2] = 0x20;
        fr.blk[3] = 9;
        fr.blk[4] = 1;
        fr.blk[5] = 0;
        fr.blk[6] = 0;
        fr.blk[7] = 0;
        func_0202f834(heap + 0xc, 2, heap + 9, fr.blk);
        GX_LoadBGPltt(&data_ov007_0204d3ac, 0, 6);
        heap[8] = 0;
    }
    return (void *)func_ov007_0204cf18;
}
