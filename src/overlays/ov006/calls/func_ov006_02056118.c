/* func_ov006_02056118 -- title: per-frame watchdog on the boot/scene object.
 * Ticks the object held at data_ov006_02056668, and once it reports state 2 (finished) reads
 * the result (func_0200108c) and requests shutdown/reset with code -2. The global is re-read
 * after the tick because the tick may replace the object. */
extern void WM_EndKeySharing_0x02023ad0(int *p);
extern void func_0200108c(void);
extern void func_02003948(int code);
extern int  data_ov006_02056668;

#define OBJ (*(int **)&data_ov006_02056668)

void func_ov006_02056118(void) {
    WM_EndKeySharing_0x02023ad0(*(int **)OBJ);
    if (OBJ[1] != 2) {
        return;
    }
    func_0200108c();
    func_02003948(-2);
}
