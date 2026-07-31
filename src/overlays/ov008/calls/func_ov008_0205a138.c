/*
 * Ov008_Menu_LoadSceneText - load the message/text container and character weapon
 * for a menu scene, called from Ov008_Menu_InitSceneObject.
 *
 * Builds the container name into a stack buffer from the per-scene parameter table
 * (SceneParam[sceneId].f0 feeds the OS_SPrintf format), opens it as message-database
 * unit 0xe and stores the handle at obj+0x1b4. For scene 0xe it re-opens from a fixed
 * name (data_ov008_02090288), freeing the first handle. Finally loads the character
 * weapon model into obj+0x4d4.
 *
 * Note: OS_SPrintf's 4th argument is param4 passed straight through from the caller
 * (r3 is never reloaded); Ov008_Menu_InitSceneObject leaves it undefined because the
 * format does not consume it. func_02024ee8 (Msg_OpenContainerAndReadHeader) takes only
 * (name, unit); Ghidra's extra r2/r3 args are leftover-register phantoms.
 */

typedef struct { int f0; unsigned char pad_04[0x30]; } SceneParam;

extern int  OS_SPrintf(void *buf, const char *fmt, ...);
extern void *func_02024ee8(void *name, int unit);
extern void func_02024fd4(void *handle);
extern void func_ov008_0208b890(void *dst, int sceneId, int slot);
extern SceneParam data_ov008_0208e9c4[];
extern char data_ov008_02090278[];
extern char data_ov008_02090288[];

void func_ov008_0205a138(int obj, int sceneId, int slot, int param4)
{
    char buf[128];
    int v;

    v = data_ov008_0208e9c4[sceneId].f0;
    OS_SPrintf(buf, data_ov008_02090278, v, param4);
    *(void **)(obj + 0x1b4) = func_02024ee8(buf, 0xe);
    if (sceneId == 0xe) {
        void *old = *(void **)(obj + 0x1b4);
        *(void **)(obj + 0x1b4) = func_02024ee8(data_ov008_02090288, 0xe);
        func_02024fd4(old);
    }
    func_ov008_0208b890((void *)(obj + 0x4d4), sceneId, slot);
}
