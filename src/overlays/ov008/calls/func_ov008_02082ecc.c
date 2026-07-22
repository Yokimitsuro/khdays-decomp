/* func_ov008_02082ecc -- create and place a mission cell object, ov008.
 * Instantiates a cell in slot `slot` from resource `res` (WM_EndKeySharing_0x02032444),
 * makes it visible (func_0203281c), commits it (func_020326cc), sets frame 0 (func_02032710)
 * and applies the transform passed by value via func_0203257c. Returns the new object.
 *
 * Parked as a "frame-layout tie": the ROM homes all four arguments with `push {r0,r1,r2,r3}`
 * and passes `&xform` INTO that block (`add r2,sp,#0x1c`), while a plain 4-argument function
 * has to copy the transform to a stack slot of its own first. The push of r0-r3 is not a frame
 * choice, it is the VARIADIC prologue -- declare the function `...` and the block exists for
 * free, so `&xform` is the block slot and the copy disappears. `push {r0,r1,r2,r3}` at the top
 * of a function is always that tell. */
extern int  WM_EndKeySharing_0x02032444(int *mgr, unsigned int res, int slot);
extern void func_0203281c(int mgr, int obj, int a);
extern void func_020326cc(int mgr, int obj);
extern void func_02032710(int mgr, int obj, int a);
extern void func_0203257c(int mgr, int obj, int *xform);

int func_ov008_02082ecc(int *mgr, unsigned int res, int slot, int xform, ...) {
    int obj = WM_EndKeySharing_0x02032444(mgr, res, slot);
    func_0203281c((int)mgr, obj, 1);
    func_020326cc((int)mgr, obj);
    func_02032710((int)mgr, obj, 0);
    func_0203257c((int)mgr, obj, &xform);
    return obj;
}
