/* func_ov000_020588ec -- open the logo confirm dialog, ov000. Resets the input
 * (func_02030788), builds the prompt box (func_020353e0) and shows it anchored to the
 * save work buffer (data_0204be18 + 0xee0) via func_ov000_02058928. */
extern void func_02030788(void);
extern void func_020353e0(int, int, int, int);
extern void func_ov000_02058928(int, void *anchor);
extern char *data_0204be18;
void func_ov000_020588ec(int arg) {
    func_02030788();
    func_020353e0(0, 0, arg, 0);
    func_ov000_02058928(0, data_0204be18 + 0xee0);
}
