/* func_ov005_02050cb0 -- open the logo confirm dialog, ov005 (byte-identical twin of an ov000 helper). Resets the input
 * (func_02030788), builds the prompt box (func_020353e0) and shows it anchored to the
 * save work buffer (data_0204be18 + 0xee0) via func_ov005_02050cec. */
extern void func_02030788(void);
extern void func_020353e0(int, int, int, int);
extern void func_ov005_02050cec(int, void *anchor);
extern char *data_0204be18;
void func_ov005_02050cb0(int arg) {
    func_02030788();
    func_020353e0(0, 0, arg, 0);
    func_ov005_02050cec(0, data_0204be18 + 0xee0);
}
