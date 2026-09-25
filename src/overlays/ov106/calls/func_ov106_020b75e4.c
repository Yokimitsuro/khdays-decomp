#pragma thumb on
/* Load the ov106 scene's font and caption: the player name is fetched, the data_ov106_020b8ac4 resource
 * loads (mode 0xf) and the +0x8e50 caption is drawn from it into +0x8594 (colour from the +0x8e52
 * number), the resource is released, the data_ov106_020b8b20 handle is stored in +0x8e40 and sound
 * 0x323 plays. Returns the next state (020b7918). */
typedef struct { char s[12]; } ResName;

extern char *data_ov106_020b8b60;
extern const ResName data_ov106_020b8ac4;
extern char data_ov106_020b8b20[];
extern void func_ov002_0206d834(int index, char *out);
extern void *func_02024ee8(const void *descriptor, int mode);
extern int func_020200b4(char *pszNumber);
extern void func_02020c7c(void *stream, int id, void *path, void *work);
extern void func_02024fd4(void *resource);
extern int func_02023930(void *ptr, int arg);
extern void func_0203355c(int id);
extern void func_ov106_020b7918(void);

void *func_ov106_020b75e4(void)
{
    char path[0x20];
    char name[0x80];
    void *res;
    char *scene;

    func_ov002_0206d834(0, name);
    res = path;     /* one local serves as the request buffer, then as the loaded resource */
    *(ResName *)res = data_ov106_020b8ac4;
    res = func_02024ee8(path, 0xf);
    scene = data_ov106_020b8b60;
    func_02020c7c(data_ov106_020b8b60,
                  ((((int)res + 0x8000) & 0xfffffc) << 7) | 0x80000000 | (func_020200b4(scene + 0x8e52) & 0x1ff),
                  scene + 0x8e50, scene + 0x8594);
    func_02024fd4(res);
    *(int *)(data_ov106_020b8b60 + 0x8e40) = func_02023930(data_ov106_020b8b20, 0);
    func_0203355c(0x323);
    return func_ov106_020b7918;
}
