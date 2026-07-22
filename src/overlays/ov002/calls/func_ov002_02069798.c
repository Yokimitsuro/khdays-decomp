/* Snap the master brightness to a saturated value and push it to both engines.
 * The stored level survives only when it is already fully dark (-16) or fully
 * bright (+16); anything in between is forced to fully dark. func_0201e1d0 then
 * commits the change. */
extern int func_0201e428(void);
extern void func_0201e374(int ev);
extern void func_0201e3cc(int ev);
extern void func_0201e1d0(void);

void func_ov002_02069798(void) {
    int ev = func_0201e428();

    if (ev != -0x10 && ev != 0x10) {
        ev = -0x10;
    }
    func_0201e374(ev);
    func_0201e3cc(ev);
    func_0201e1d0();
}
