extern int ScriptVm_ReadOperandInt(int ctx, void *arg);
extern char *ByteCode_ResolveOperand(int ctx, void *arg);
extern int ScriptVm_ResolveActorIndex(int ctx, int arg);
extern int func_020200b4(const char *s);
extern int strncmp(const char *a, const char *b, int n);
extern int OS_SNPrintf(char *dst, unsigned int len, const char *fmt, ...);
extern int OS_SPrintf(char *dst, const char *fmt, ...);
extern int Ov023_Window_OpenMessages(void *entity, char *path);
extern int Ov023_MakeDescriptorWord(void *entity, int anim);
extern int ResCache_Acquire(int a, void *b, int c);
extern void TailForwardTrackEntry_2(int id, int a, int b, int c);
extern void Ov023_ReleaseSubPanelResource(void *entity);
extern void Slot48_StoreAtCurrentIndex(int ctx, char *args);
extern char gOv023EvPath[];
extern char gOv023StrFmt[];
extern char gOv023EvPathFmt[];
extern char gOv023CoName[];
extern char gOv023MsSharedEffectPath[];
extern char gOv023MsPackPathFmt[];

/* Script command: builds the animation file path from the operand's short-hand name, loads it onto
 * the entity, and yields until it has finished playing. */
int Ov023_Cmd_PlayEntityAnimByName(int ctx, char *args) {
    int entity = ScriptVm_ReadOperandInt(ctx, args);
    char *name = ByteCode_ResolveOperand(ctx, args + 8);
    int id = ScriptVm_ResolveActorIndex(ctx, entity);
    char group[0x20];
    char path[0x40];
    char prefix[0x10];
    int anim;
    int loop;
    if (strncmp(name, gOv023EvPath, 3) == 0) {
        OS_SNPrintf(prefix, 3, gOv023StrFmt, name + 3);
        OS_SPrintf(path, gOv023EvPathFmt, prefix);
        anim = func_020200b4(name + 6);
    } else {
        OS_SNPrintf(group, 3, gOv023StrFmt, name);
        if (strncmp(name, gOv023CoName, 2) == 0) {
            OS_SPrintf(path, gOv023MsSharedEffectPath);
        } else {
            OS_SPrintf(path, gOv023MsPackPathFmt, group);
        }
        anim = func_020200b4(name + 3);
    }
    Ov023_Window_OpenMessages(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64, path);
    if (ResCache_Acquire(Ov023_MakeDescriptorWord(
                          *(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64, anim),
                      *(char **)(ctx + 0x128) + 0x28, 0) != 0) {
        if (ScriptVm_ReadOperandInt(ctx, args + 0x10) != 0) {
            loop = 1;
        } else {
            loop = 0;
        }
        TailForwardTrackEntry_2((unsigned short)id, *(int *)(*(char **)(ctx + 0x128) + 0x28), 0, 0);
        if (loop != 0) {
            Ov023_ReleaseSubPanelResource(*(char **)(*(char **)(ctx + 0x128) + 0x440) + id * 0x1a64);
        }
        if (id == 0) {
            *(int *)(args + 0x1c) = ~0x62;
        } else {
            *(int *)(args + 0x1c) = -id;
        }
    } else {
        *(int *)(args + 0x1c) = id;
    }
    Slot48_StoreAtCurrentIndex(ctx, args);
    return 0;
}
