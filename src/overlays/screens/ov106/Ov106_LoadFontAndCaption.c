#pragma thumb on
/* Load the ov106 scene's font and caption: the player name is fetched, the gOv106EvEvDpPath resource
 * loads (mode 0xf) and the +0x8e50 caption is drawn from it into +0x8594 (colour from the +0x8e52
 * number), the resource is released, the data_ov106_020b8b20 handle is stored in +0x8e40 and sound
 * 0x323 plays. Returns the next state (020b7918). */
typedef struct { char s[12]; } ResName;

extern char *data_ov106_020b8b60;
extern const ResName gOv106EvEvDpPath;
extern char data_ov106_020b8b20[];
extern void Ov002_FormatEventScriptName(int index, char *out);
extern void *Msg_OpenContainerAndReadHeader(const void *descriptor, int mode);
extern int func_020200b4(char *pszNumber);
extern void Stream_DecodeIntoStagingBuffer(void *stream, int id, void *path, void *work);
extern void ZeroHalfThenFree(void *resource);
extern int InstantiateClass(void *ptr, int arg);
extern void Res_RequestIdPair(int id);
extern void Ov106_MainState(void);

void *Ov106_LoadFontAndCaption(void)
{
    char path[0x20];
    char name[0x80];
    void *res;
    char *scene;

    Ov002_FormatEventScriptName(0, name);
    res = path;     /* one local serves as the request buffer, then as the loaded resource */
    *(ResName *)res = gOv106EvEvDpPath;
    res = Msg_OpenContainerAndReadHeader(path, 0xf);
    scene = data_ov106_020b8b60;
    Stream_DecodeIntoStagingBuffer(data_ov106_020b8b60,
                  ((((int)res + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (func_020200b4(scene + 0x8e52) & 0x1ff),
                  scene + 0x8e50, scene + 0x8594);
    ZeroHalfThenFree(res);
    *(int *)(data_ov106_020b8b60 + 0x8e40) = InstantiateClass(data_ov106_020b8b20, 0);
    Res_RequestIdPair(0x323);
    return Ov106_MainState;
}
