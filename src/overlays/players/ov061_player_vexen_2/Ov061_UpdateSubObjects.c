/* Per-frame update of the ov042 enemy's two sub-objects (x4: ov042/061/081/098), the ov031
 * shape: (the node animation's frame is polled but unused,) each sub-object is fed the frame
 * delta and stepped; if either is idle, the local player raises bit 0x10000 of both attack-flag
 * words. The ready states 0x2f / 0x30 ring cue 0xc7 (variants 2 / 3) exactly at progress 0xf000
 * / 0x1b000, then the common actor step runs. */
extern int Anim_GetFrame(unsigned short *p, unsigned int idx);                  /* Anim_GetFrame */
extern int Ov022_GetGlobal34(void);
extern void Ov022_ForwardToNodeHandler(int a, int b);
extern void Ov022_InvokeCallback24IfBit0(int a);
extern int Ov022_AreStreamsIdle(int a);
extern int Session_GetLocalPlayerIndex(void);                                                /* Session_GetLocalPlayerIndex */
extern void Ov022_PlayEntityVoice(char *self, int nSeqArc, int nSeq);
extern void func_ov022_020ad588(char *self);

void Ov061_UpdateSubObjects(char *self)
{
    int v;

    Anim_GetFrame((unsigned short *)(*(char **)(self + 0x20) + 4), 0);
    v = Ov022_GetGlobal34();
    Ov022_ForwardToNodeHandler(*(int *)(self + 0x2000 + 0x644), v);
    v = Ov022_GetGlobal34();
    Ov022_ForwardToNodeHandler(*(int *)(self + 0x2000 + 0x644) + 0x30, v);
    Ov022_InvokeCallback24IfBit0(*(int *)(self + 0x2000 + 0x644));
    Ov022_InvokeCallback24IfBit0(*(int *)(self + 0x2000 + 0x644) + 0x30);
    if (Ov022_AreStreamsIdle(*(int *)(self + 0x2000 + 0x644)) == 0 ||
        Ov022_AreStreamsIdle(*(int *)(self + 0x2000 + 0x644) + 0x30) == 0) {
        if (Session_GetLocalPlayerIndex() == 0) {
            *(unsigned long long *)(self + 0x464) |= 0x10000;
        }
        if (Session_GetLocalPlayerIndex() == 0) {
            *(unsigned long long *)(self + 0x46c) |= 0x10000;
        }
    }
    switch (*(int *)(self + 0x6bc)) {
    case 0x2f:
        if (*(int *)(self + 0x7b0) == 0xf000) {
            Ov022_PlayEntityVoice(self, 0xc7, 2);
        }
        break;
    case 0x30:
        if (*(int *)(self + 0x7b0) == 0x1b000) {
            Ov022_PlayEntityVoice(self, 0xc7, 3);
        }
        break;
    }
    func_ov022_020ad588(self);
}
