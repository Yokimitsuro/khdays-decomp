extern void func_020300f8(char *p);
extern void func_ov002_02053cd4(int id);
extern int func_ov002_020575d0(void);
extern void func_ov002_020633d8(void);
extern char *data_ov002_0207f62c;

/* Per-frame tick of the options page: closes the open sub-window if there is one, then hands the
 * frame to the page body while the page is still active. */
void func_ov002_02063398(void) {
    char *page = (&data_ov002_0207f62c)[1];
    if (*(int *)(page + 0x90) != 0) {
        func_020300f8(page + 0xfc);
        func_ov002_02053cd4(0x1a);
    }
    if (func_ov002_020575d0() == 0) {
        return;
    }
    func_ov002_020633d8();
}
