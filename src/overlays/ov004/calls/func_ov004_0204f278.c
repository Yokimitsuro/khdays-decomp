/* func_ov004_0204f278 -- open the logo confirm dialog, ov004 (byte-identical twin of an ov000 helper). Resets the input
 * (func_02030788), builds the prompt box (func_020353e0) and shows it anchored to the
 * save work buffer (data_0204be18 + 0xee0) via func_ov004_0204f2b4. */
extern void func_02030788(void);
extern void func_020353e0(int, int, int, int);
extern void func_ov004_0204f2b4(int, void *anchor);
extern char *data_0204be18;
void func_ov004_0204f278(int arg) {
    func_02030788();
    func_020353e0(0, 0, arg, 0);
    func_ov004_0204f2b4(0, data_0204be18 + 0xee0);
}
