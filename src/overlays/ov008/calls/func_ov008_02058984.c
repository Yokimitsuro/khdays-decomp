/* func_ov008_02058984 -- Ov008_InitPanel (128 B, 8 relocs).
 * Binds arg0 as the active menu panel (data_ov008_02090f1c) and copies a resource handle into
 * the caller's out-param. func_02030788() yields a token that func_020315c0() resolves to a
 * record; its field +4 is written to *arg1 and mirrored (as u16) into field +4 of the object
 * from func_ov008_0204ed20(). Then func_ov008_0205714c(0) runs, and when func_ov008_0204ed3c()
 * reports active it fires cue 0x200a (func_02023588) and func_ov008_0204ebbc(). Finally it
 * clears the panel's field 0x5c8 (= -1) and sets bit 0x100 in the u16 flags at 0x5c6.
 * (func_02030788's result must stay live into func_020315c0, which is why the panel-pointer
 * store lands between the two calls.) */
typedef unsigned short u16;

extern void *data_ov008_02090f1c;
extern int   func_02030788(void);
extern void *func_020315c0(unsigned int a);
extern void *func_ov008_0204ed20(void);
extern void  func_ov008_0205714c(int a);
extern int   func_ov008_0204ed3c(void);
extern void  func_02023588(int flag);
extern void  func_ov008_0204ebbc(void);

void func_ov008_02058984(void *arg0, int *arg1)
{
    int a = func_02030788();
    data_ov008_02090f1c = arg0;
    *arg1 = *(int *)((char *)func_020315c0((unsigned int)a) + 4);
    *(u16 *)((char *)func_ov008_0204ed20() + 4) = *arg1;
    func_ov008_0205714c(0);
    if (func_ov008_0204ed3c() != 0) {
        func_02023588(0x200a);
        func_ov008_0204ebbc();
    }
    *(int *)((char *)data_ov008_02090f1c + 0x5c8) = -1;
    *(u16 *)((char *)data_ov008_02090f1c + 0x5c6) |= 0x100;
}
