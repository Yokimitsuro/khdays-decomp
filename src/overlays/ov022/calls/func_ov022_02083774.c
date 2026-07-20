/* Scene teardown: commit the open document and hand back the next scene step, or
 * null if func_ov002_0206b600(-1) says there is nothing to commit.
 *
 * data_0204c240 bit 2 (the same boot-mode gate ov002 reads) selects between one
 * commit for the whole document (index -1) and one commit per connected peer.
 *
 * The main path lives INSIDE the guard so that its `return 0` shares the tail
 * block the ROM branches to at +0xbc; written as an early `return 0` mwcc emits a
 * second epilogue instead. */
typedef struct {
    char pad00[0x30];
    int nHandle;               /* +0x30 */
} Ov022Session;

extern Ov022Session *data_ov022_020b2e60;
extern unsigned char data_0204c240;

extern void func_ov022_02083c08(int a);
extern int func_ov002_0206b600(int index);
extern int func_ov002_02072808(int handle);
extern void func_ov002_02072820(int handle, void *out);
extern int func_ov022_020882f8(void);
extern int func_01fffe14(void);
extern void func_ov002_0206b4bc(int index, int a, int *out, int d, void *buf, int f);
extern void func_ov002_0206d69c(void);
extern void func_ov002_0206ba78(int a, int b);
extern void func_020340d0(int a);
extern void func_ov022_02082bf4(void);

void *func_ov022_02083774(void) {
    int out[3];
    int buf[4];
    int a;
    int i;

    func_ov022_02083c08(0);
    if (func_ov002_0206b600(-1) == 1) {
        out[0] = 0;
        out[1] = 0;
        out[2] = 0;
        a = func_ov002_02072808(data_ov022_020b2e60->nHandle);
        func_ov002_02072820(data_ov022_020b2e60->nHandle, buf);
        if ((data_0204c240 & 4) == 0) {
            for (i = 0; i < func_ov022_020882f8(); i++) {
                if (i != func_01fffe14()) {
                    func_ov002_0206b600(i);
                }
            }
            for (i = 0; i < func_ov022_020882f8(); i++) {
                func_ov002_0206b4bc(i, a, out, 0, buf, 0);
            }
            func_ov002_0206d69c();
        } else {
            func_ov002_0206b4bc(-1, a, out, 0, buf, 0);
        }
        func_ov002_0206ba78(0, -1);
        data_ov022_020b2e60->nHandle = 0;
        func_020340d0(0);
        return (void *)&func_ov022_02082bf4;
    }
    return 0;
}
