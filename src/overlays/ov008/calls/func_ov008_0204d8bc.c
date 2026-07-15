/* func_ov008_0204d8bc -- load the menu UI container and build its root cell, ov008.
 * Runs once (guarded by heap[0x608]): clears the two OBJ palettes, loads the UI archive
 * (data_ov008_0208ffb4 = "UI/mlt/res.p2") via func_02024ee8, then registers the root cell
 * in the object manager (heap+0x60c) from a {resAddr, 2, 0, 0} descriptor (func_02032388),
 * creates it (WM_EndKeySharing_0x02032444 slot 5 -> heap[0x5044]), sets frame 0 and scale
 * 1.0, and enables sub-BG mode 1. */
extern char *data_ov008_02090f00;
extern char  data_ov008_0208ffb4[];
extern void *func_02024ee8(void *desc, int mode);
extern void  func_0201e3cc(int);
extern void  func_02032388(void *mgr, int *desc);
extern void *WM_EndKeySharing_0x02032444(void *mgr, int slot, int);
extern void  func_020325ec(void *mgr, void *obj, int);
extern void  func_020326cc(void *mgr, void *obj);
extern void  func_0203257c(void *mgr, void *obj, int *scale);

void func_ov008_0204d8bc(void) {
    if (*(int *)(data_ov008_02090f00 + 0x608) != 0) {
        return;
    }
    *(unsigned short *)0x05000000 = 0;
    *(unsigned short *)0x05000400 = 0;
    *(void **)(data_ov008_02090f00 + 0x608) = func_02024ee8(data_ov008_0208ffb4, 0xe);
    func_0201e3cc(0);
    {
        int desc[4];
        desc[0] = ((*(int *)(data_ov008_02090f00 + 0x608) + 0x8000 & 0xfffffc) << 7) | 0x80000001;
        desc[1] = 2;
        desc[2] = 0;
        desc[3] = 0;
        func_02032388(data_ov008_02090f00 + 0x60c, desc);
    }
    *(void **)(data_ov008_02090f00 + 0x5044) =
        WM_EndKeySharing_0x02032444(data_ov008_02090f00 + 0x60c, 5, 0);
    {
        int scale[2];
        scale[0] = 0x8000;
        scale[1] = 0x8000;
        func_020325ec(data_ov008_02090f00 + 0x60c, *(void **)(data_ov008_02090f00 + 0x5044), 0);
        func_020326cc(data_ov008_02090f00 + 0x60c, *(void **)(data_ov008_02090f00 + 0x5044));
        func_0203257c(data_ov008_02090f00 + 0x60c, *(void **)(data_ov008_02090f00 + 0x5044), scale);
    }
    *(volatile unsigned int *)0x04001000 = (*(volatile unsigned int *)0x04001000 & ~0x1f00) | 0x1000;
}
