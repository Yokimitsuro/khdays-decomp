extern void func_ov027_0208346c(int obj);
extern void func_ov002_02050e64(void);
extern void func_ov002_0205126c(int arg);
extern char data_ov027_02084360[];
/* Run the per-frame update, flush, then forward the active entry (*(table+4)+0x588) to the HUD. */
void func_ov027_0208344c(int obj) {
    func_ov027_0208346c(obj);
    func_ov002_02050e64();
    func_ov002_0205126c(*(int *)(data_ov027_02084360 + 4) + 0x588);
}
