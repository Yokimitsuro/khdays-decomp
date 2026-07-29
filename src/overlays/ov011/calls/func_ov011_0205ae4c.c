/* func_ov011_0205ae4c -- Ov011 initial state: wait for the intro movie, then bring up
 * the title. Polls the MobiClip stream (stream.poll, interface +0x14) every frame and
 * returns 0 to stay until it reports finished. On finish it stops the stream (+0x8),
 * fades both engines out, frees the movie resource, dispatches handler 0x20e9 and stores
 * the ARM7 thread/lid bit into scene-flags bit0. If an argument was passed and that bit
 * is set it kicks func_02033fec(0,0x1e) and hands back state func_ov011_0205ae14;
 * otherwise it opens the title container, builds two message handles, brings up both
 * panes, sets game mode 0, blends both BLDCNT registers down, fades back in and hands
 * back state func_ov011_0205cb18, clearing the busy bit first.
 *
 * Scene flags at +0x23ac0 are a bitfield: bit0 threadAvail, bit1 busy, bit2 lidClosed.
 * The signed 1-bit field is what makes bit0 read back with lsl#31/asr#31.
 */
typedef signed char   s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int  u32;
typedef void (*Ov011StateFn)(void);

typedef struct Ov011StreamInterface {
    void (*initialize)(void);
    void (*open)(const void *params);
    void (*close)(void);
    void (*start)(void);
    void (*unk10)(void);
    int  (*poll)(void);
} Ov011StreamInterface;

typedef struct Ov011SceneFlags {
    int bThreadAvail : 1;
    int bBusy        : 1;
    int bLidClosed   : 1;
    int reserved     : 29;
} Ov011SceneFlags;

typedef struct Ov011Scene {
    u8    pad_0000[0xc];
    void *pMsgResource;
    u8    pad_0010[0x23a9c - 0x10];
    int   handle1;
    u8    pad_23aa0[0x23aa8 - 0x23aa0];
    int   handle2;
    u8    pad_23aac[0x23ac0 - 0x23aac];
    Ov011SceneFlags flags;
    int   nArg;
    u8    pad_23ac8[0x2cf54 - 0x23ac8];
    void *pResource;
    Ov011StreamInterface stream;
    u8    pad_2cf70[0x2cf84 - 0x2cf70];
} Ov011Scene;

typedef struct Ov011Globals {
    int         nCursor;
    Ov011Scene *pScene;
} Ov011Globals;

extern Ov011Globals data_ov011_0205e960;
extern const u8 data_ov011_0205e8f8[];
extern const u8 data_ov011_0205e904[];
extern const u8 data_ov011_0205e91c[];

extern void func_0201e374(int brightness);
extern void func_0201e3cc(int brightness);
extern void func_02024fd4(void *resource);
extern void func_020235bc(int handlerId);
extern int  OS_IsThreadAvailable_0x02083358(void);
extern void func_02033fec(int a, int b);
extern void *func_02024ee8(const void *descriptor, int mode);
extern int  func_0201ebdc(const void *data, int id);
extern void func_ov011_0205d324(void);
extern long long func_ov011_0205d7bc(void);
extern void func_0201ef58(long long value);
extern void func_ov011_0205d6a0(void);
extern long long func_ov011_0205dac8(void);
extern void func_ov011_0205db90(long long value);
extern void func_02023c30(int mode);
extern void G2x_SetBlendBrightness_(u16 *reg, int a, int b);
extern void func_ov011_0205bddc(void);
extern void func_ov011_0205ae14(void);
extern void func_ov011_0205cb18(void);

Ov011StateFn func_ov011_0205ae4c(void)
{
    if (data_ov011_0205e960.pScene->stream.poll() == 0) {
        return 0;
    }
    data_ov011_0205e960.pScene->stream.close();
    func_0201e374(-0x10);
    func_0201e3cc(-0x10);
    func_02024fd4(data_ov011_0205e960.pScene->pResource);
    func_020235bc(0x20e9);
    data_ov011_0205e960.pScene->flags.bThreadAvail = OS_IsThreadAvailable_0x02083358();
    if (data_ov011_0205e960.pScene->nArg != 0 &&
        data_ov011_0205e960.pScene->flags.bThreadAvail) {
        func_02033fec(0, 0x1e);
        return (Ov011StateFn)func_ov011_0205ae14;
    }
    data_ov011_0205e960.pScene->pMsgResource = func_02024ee8(data_ov011_0205e8f8, 0xe);
    data_ov011_0205e960.pScene->handle1 = func_0201ebdc(data_ov011_0205e904, 0xe);
    data_ov011_0205e960.pScene->handle2 = func_0201ebdc(data_ov011_0205e91c, 0xe);
    func_ov011_0205d324();
    func_0201ef58(func_ov011_0205d7bc());
    func_ov011_0205d6a0();
    func_ov011_0205db90(func_ov011_0205dac8());
    func_02023c30(0);
    G2x_SetBlendBrightness_((u16 *)0x04000050, 4, -0x10);
    G2x_SetBlendBrightness_((u16 *)0x04001050, 4, -0x10);
    func_0201e374(0);
    func_0201e3cc(0);
    func_ov011_0205bddc();
    data_ov011_0205e960.pScene->flags.bBusy = 0;
    return (Ov011StateFn)func_ov011_0205cb18;
}
