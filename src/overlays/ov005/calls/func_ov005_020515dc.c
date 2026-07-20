/* Scene entry: publish a 0x14-byte context, build its two objects, and pick the
 * opening transition.
 *
 * NNSi_FndGetCurrentRootHeap is genuinely called TWICE and the first result is
 * discarded -- that is what the ROM does, not a transcription slip.
 *
 * The tail is a three-way choice, not two: with data_ov005_0205b85c.nOption64
 * set it always runs func_020336a4(0x14); otherwise func_02030670 gets to veto,
 * and only if that returns 0 does func_020335ec(0x1e) run. */
typedef struct {
    void *pObjectA;         /* +0x00 */
    void *pObjectB;         /* +0x04 */
    int nMode;              /* +0x08 */
    char pad0c[8];
} Ov005SceneContext;        /* 0x14, measured off the MI_CpuFill8 */

typedef struct {
    char pad00[0x5c];
    unsigned char bMode;    /* +0x5c */
    char pad5d[7];
    int nOption64;          /* +0x64 */
} Ov005Config;

extern void *NNSi_FndGetCurrentRootHeap(void);
extern void MI_CpuFill8(void *dst, unsigned char value, unsigned int size);
extern void func_ov005_02051560(void);
extern void func_02034150(int a, int b);
extern void func_ov005_02057c48(void);
extern void *func_02023930(const void *res, int a);
extern int func_020336a4(int a);
extern int func_02030670(void);
extern void func_020335ec(int a);
extern void func_ov005_02051724(void);

extern Ov005SceneContext *data_ov005_0205b808;
extern Ov005Config data_ov005_0205b85c;
extern char data_ov005_0205b590[];
extern char data_ov005_0205b4f0[];

void *func_ov005_020515dc(int mode) {
    NNSi_FndGetCurrentRootHeap();
    data_ov005_0205b808 = NNSi_FndGetCurrentRootHeap();
    MI_CpuFill8(data_ov005_0205b808, 0, 0x14);
    data_ov005_0205b808->nMode = mode;
    func_ov005_02051560();
    func_02034150(0x15, 0xe);
    func_02034150(0x1a, 0xe);
    func_02034150(0x19, 0xe);
    func_ov005_02057c48();
    data_ov005_0205b808->pObjectB = func_02023930(data_ov005_0205b590, 0);
    data_ov005_0205b808->pObjectA = func_02023930(data_ov005_0205b4f0, 0);
    if (data_ov005_0205b85c.nOption64 != 0) {
        func_020336a4(0x14);
    } else if (func_02030670() == 0) {
        func_020335ec(0x1e);
    }
    return (void *)&func_ov005_02051724;
}
