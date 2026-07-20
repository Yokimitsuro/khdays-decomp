/* Load a background set from the archive owned by `page`: pull members 0, 1 and
 * 6 (palette, character data, screen map), push all three to the sub screen's
 * BG3, then close the archive and release the page. Finally raise the context's
 * pending event -- through the hook at +0x1a8 when one is installed, otherwise
 * func_ov002_020637d4 -- and park the context state at 2. */
extern int data_ov002_0207f9fc;

extern int func_ov002_02052aec(int page);
extern void func_02025464(int arc, int a);
extern int func_020255d4(int arc, int member, int a);
extern int func_02011a20(int block, void *out);
extern int func_02011988(int block, void *out);
extern int func_02011a6c(int block, void *out);
extern void GXS_LoadBGPltt(void *src, int offset, unsigned int size);
extern void GXS_LoadBG3Char_0x020079ac(void *src, int offset, unsigned int size);
extern void GXS_LoadBG3Scr_0x020076ac(void *src, int offset, unsigned int size);
extern void func_0202552c(int arc);
extern void func_ov002_02052af4(int page, int a);
extern void func_ov002_020637d4(int arg, int a);

void func_ov002_02067078(int page) {
    int *chr;
    int *scr;
    int *pltt;
    char *ctx = *(char **)&data_ov002_0207f9fc;
    int arc = func_ov002_02052aec(page);

    func_02025464(arc, 1);
    func_02011a20(func_020255d4(arc, 0, 0), &pltt);
    func_02011988(func_020255d4(arc, 1, 0), &chr);
    func_02011a6c(func_020255d4(arc, 6, 0), &scr);

    GXS_LoadBGPltt((void *)pltt[3], 0, pltt[2]);
    GXS_LoadBG3Char_0x020079ac((void *)chr[5], 0, chr[4]);
    GXS_LoadBG3Scr_0x020076ac((char *)scr + 0xc, 0, scr[2]);

    func_0202552c(arc);
    func_ov002_02052af4(page, 1);

    if (*(int *)(ctx + 0x24) != 0) {
        void (*hook)(int, int) = *(void (**)(int, int))(ctx + 0x1a8);

        if (hook == 0) {
            func_ov002_020637d4(0xffff0000, 0);
        } else {
            hook(0xffff0000, 0);
        }
        *(int *)(ctx + 0x28) = 2;
    }
}
