/* Shut the link down: close the two key-sharing handles at +0x14, tear the four
 * subsystems down, release the frame slot and clear both root words.
 *
 * The handle loop counts UNSIGNED (blo), and the handle array is walked rather
 * than indexed. */
extern void func_ov022_020831dc(void *ctx);
extern void WM_EndKeySharing_0x02023ad0(int handle);
extern void func_ov002_02076568(void);
extern void func_ov002_02077e68(void);
extern void func_0202c4b0(void);
extern void func_ov002_02071ae0(void);
extern void func_020340d0(int slot);

typedef struct {
    int reserved;
    char *pCtx;     /* +4 */
} Ov022LinkRoot;

extern Ov022LinkRoot data_ov022_020b2e60;

void func_ov022_02082bb0(void) {
    unsigned int i;
    char *ctx = data_ov022_020b2e60.pCtx;
    char *handle = *(char **)(ctx + 0x20);

    func_ov022_020831dc(ctx);

    for (i = 0; i < 2; i++) {
        if (*(int *)(handle + 0x14) != 0) {
            WM_EndKeySharing_0x02023ad0(*(int *)(handle + 0x14));
        }
        handle += 4;
    }

    func_ov002_02076568();
    func_ov002_02077e68();
    func_0202c4b0();
    func_ov002_02071ae0();
    func_020340d0(0);

    data_ov022_020b2e60.pCtx = 0;
    data_ov022_020b2e60.reserved = 0;
}
