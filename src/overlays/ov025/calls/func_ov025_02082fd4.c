/*
 * func_ov025_02082fd4 -- x3 (ov008/...). Enable or disable both half-screens together.
 * Context at data_02090f04[1]+0x9000. Each half is "on" only when `enable` is set and its own ready
 * flag (+0x9600 / +0x9604) is non-zero. Push that on/off state into the two command lists at +0x9500
 * and +0x954c (02055c08), publish their +0x20 halfwords (02055c40), and set control bits 1 and 0 of
 * the +0xa7c word for each surface (02054e4c / 02054e24; the second surface base is +0x4a80).
 *
 * All context reads use CTXV (volatile): the retail compiler re-loads data_02090f04[1] for every
 * access; mwcc 3.0/139 would cache it. The volatile forces the reload; behaviour is identical.
 */
extern void func_ov025_02089818(int cmdlist, int on);
extern void func_ov025_02089850(int cmdlist);
extern void func_ov025_02088af4(int surface, int on);
extern void func_ov025_02088acc(int surface, int on);
extern int data_ov025_020b5744[];

#define CTXV (*(volatile int *)((char *)data_ov025_020b5744 + 4))

void func_ov025_02082fd4(int enable) {
    int u1 = (enable != 0 && *(int *)(CTXV + 0x9600) != 0);
    int u2 = (enable != 0 && *(int *)(CTXV + 0x9604) != 0);

    func_ov025_02089818(CTXV + 0x9500, u1);
    func_ov025_02089818(CTXV + 0x954c, u2);
    func_ov025_02089850(CTXV + 0x9500);
    func_ov025_02089850(CTXV + 0x954c);
    func_ov025_02088af4(CTXV, u1);
    func_ov025_02088af4(CTXV + 0x4a80, u2);
    func_ov025_02088acc(CTXV, u1);
    func_ov025_02088acc(CTXV + 0x4a80, u2);
}
