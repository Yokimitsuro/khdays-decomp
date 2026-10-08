/* Ov024_MobiClip_InstallStreamSourceVtbl -- MobiClip: install the stream-source handler table into `obj`.
 * Five entry points plus the fields they use, all cleared: +0x10 is the only gap in the
 * pointer block (no handler for that slot), and +0x18/+0x1c/+0x28 are the per-instance state
 * the handlers own. */
extern void Ov024_MobiClip_RestoreDisplay(void);
extern void Ov024_MobiClip_CreatePlayerTask(void);
extern void Ov024_MobiClip_DestroyPlayerTask(void);
extern void Ov024_StreamSourceStart(void);
extern void Ov024_StreamSourceIsReady(void);

void Ov024_MobiClip_InstallStreamSourceVtbl(int *obj) {
    obj[0] = (int)Ov024_MobiClip_RestoreDisplay;
    obj[1] = (int)Ov024_MobiClip_CreatePlayerTask;
    obj[2] = (int)Ov024_MobiClip_DestroyPlayerTask;
    obj[3] = (int)Ov024_StreamSourceStart;
    obj[4] = 0;
    obj[5] = (int)Ov024_StreamSourceIsReady;
    obj[6] = 0;
    obj[7] = 0;
    obj[10] = 0;
}
