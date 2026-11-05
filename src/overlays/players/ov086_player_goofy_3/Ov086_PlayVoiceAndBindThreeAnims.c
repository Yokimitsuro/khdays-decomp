/* Plays the attack voice (the variant depends on the attack kind), binds tracks 0-2 of the effect
 * for that variant, rewound, and activates it. */

extern int Ov022_PlayEntityVoice(int self, int nSeqArc, int nSeq);
extern void BindAnimTrack(int a, int b, int c, short d);
extern void Anim_SetFrameWrapped(int a, int b, int c);

void Ov086_PlayVoiceAndBindThreeAnims(int self, int *node) {
    int sit = 0;
    int idx = 0;
    if (node[0] != 0) {
        sit = 1;
        idx = 2;
    }
    *(int *)((char *)node + 0x370) = Ov022_PlayEntityVoice(self, 0xd5, sit);
    BindAnimTrack((int)node + 0xc, 0, node[0x45], idx);
    BindAnimTrack((int)node + 0xc, 2, node[0x45], idx);
    BindAnimTrack((int)node + 0xc, 1, node[0x45], idx);
    Anim_SetFrameWrapped((int)node + 0xc, 0, 0);
    Anim_SetFrameWrapped((int)node + 0xc, 2, 0);
    Anim_SetFrameWrapped((int)node + 0xc, 1, 0);
    node[2] = 1;
    *(int *)((char *)node + 0x118) = 0;
}
