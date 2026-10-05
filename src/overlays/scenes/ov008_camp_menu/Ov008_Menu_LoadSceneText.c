/*
 * Ov008_Menu_LoadSceneText - load the message/text container and character weapon
 * for a menu scene, called from Ov008_Menu_InitSceneObject.
 *
 * Builds the container name into a stack buffer from the per-scene parameter table
 * (SceneParam[sceneId].f0 feeds the OS_SPrintf format), opens it as message-database
 * unit 0xe and stores the handle at obj+0x1b4. For scene 0xe it re-opens from a fixed
 * name (gOv008RoxasWPath), freeing the first handle. Finally loads the character
 * weapon model into obj+0x4d4.
 *
 * Note: OS_SPrintf's 4th argument is param4 passed straight through from the caller
 * (r3 is never reloaded); Ov008_Menu_InitSceneObject leaves it undefined because the
 * format does not consume it. Msg_OpenContainerAndReadHeader (Msg_OpenContainerAndReadHeader) takes only
 * (name, unit); Ghidra's extra r2/r3 args are leftover-register phantoms.
 */

#include "game/engine.h"

typedef struct { int f0; unsigned char pad_04[0x30]; } SceneParam;

extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern void *Msg_OpenContainerAndReadHeader(void *name, int unit);
extern void Ov008_LoadCharacterWeapon(void *dst, int sceneId, int slot);
extern SceneParam data_ov008_0208e9c4[];
extern char gOv008BaChWPathFmt[];
extern char gOv008RoxasWPath[];

void Ov008_Menu_LoadSceneText(int obj, int sceneId, int slot, int param4)
{
    char buf[128];
    int v;

    v = data_ov008_0208e9c4[sceneId].f0;
    OS_SPrintf(buf, gOv008BaChWPathFmt, v, param4);
    *(void **)(obj + 0x1b4) = Msg_OpenContainerAndReadHeader(buf, 0xe);
    if (sceneId == 0xe) {
        void *old = *(void **)(obj + 0x1b4);
        *(void **)(obj + 0x1b4) = Msg_OpenContainerAndReadHeader(gOv008RoxasWPath, 0xe);
        ZeroHalfThenFree(old);
    }
    Ov008_LoadCharacterWeapon((void *)(obj + 0x4d4), sceneId, slot);
}
