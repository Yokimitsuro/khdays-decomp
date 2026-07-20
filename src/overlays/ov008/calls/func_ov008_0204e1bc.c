/* Enters the ov008 result/continue screen: refresh panels, honor the session, seed the menu
 * context, and pick the next scene callback by whether a pending job is still running.
 *
 * Gets the local player's slot record (func_020315c0 of the session index), rebuilds two panels,
 * and if a session exists re-arms it. With a slot record, runs func_020352cc and pushes the record's
 * field +4. Then, if func_ov008_0207baf8 reports no pending job, clears the menu context's counters
 * (either just +0x172, or the +0x92..+0x9e block when func_ov008_0204ed3c is set) and returns the
 * "ready" callback; otherwise returns the "wait" callback.
 */

typedef void (*SceneCallback)(void);

extern unsigned short func_02030788(void);
extern int func_020315c0(unsigned int index);
extern void func_ov008_0204d7c0(void);
extern void func_ov008_0204d8bc(void);
extern int func_02030640(void);
extern void func_020307b8(int enable);
extern void func_020352cc(void);
extern void func_ov008_02053b18(int value, int b);
extern void func_ov008_0204d0cc(void);
extern int func_ov008_0207baf8(void);
extern int func_ov008_0204ed3c(void);
extern void func_ov008_0204e6f8(void);
extern int *data_ov008_02090f00;
extern void func_ov008_0204e274(void);

SceneCallback func_ov008_0204e1bc(void) {
    int record = func_020315c0((unsigned int)func_02030788());

    func_ov008_0204d7c0();
    func_ov008_0204d8bc();
    if (func_02030640()) {
        func_020307b8(1);
    }
    if (record != 0) {
        func_020352cc();
        func_ov008_02053b18(*(int *)(record + 4), 0);
    }
    func_ov008_0204d0cc();
    if (func_ov008_0207baf8() != 0) {
        return func_ov008_0204e6f8;
    }
    if (func_ov008_0204ed3c() != 0) {
        *(unsigned short *)((int)data_ov008_02090f00 + 0x92) = 0;
        *(unsigned short *)((int)data_ov008_02090f00 + 0x96) = 0;
        *(unsigned short *)((int)data_ov008_02090f00 + 0x9a) = 0;
        *(unsigned short *)((int)data_ov008_02090f00 + 0x9e) = 0;
    } else {
        *(unsigned short *)((int)data_ov008_02090f00 + 0x172) = 0;
    }
    return func_ov008_0204e274;
}
