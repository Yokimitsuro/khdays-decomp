/* Plays the attack voice (the variant depends on the attack kind) and binds the effect's tracks 0
 * and 2 for that variant, rewound. */

extern void Ov022_PlayEntityVoice(int self, int nSeqArc, int nSeq);
extern void BindAnimTrack(int a, int b, int c, short d);
extern void Anim_SetFrameWrapped(int a, int b, int c);
extern int data_ov059_020b7320;

void Ov059_PlayVoiceAndBindAnims(int self, int obj) {
    int idx = 0;
    if (*(int *)(*(int *)&data_ov059_020b7320 + 0x2000 + 0xc50) != 0) {
        idx = 1;
        Ov022_PlayEntityVoice(self, 0xce, 2);
    } else {
        Ov022_PlayEntityVoice(self, 0xce, 3);
    }
    *(int *)(obj + 0x124) = 1;
    BindAnimTrack(obj + 0x128, 0, obj + 0x208, idx);
    BindAnimTrack(obj + 0x128, 2, obj + 0x208, idx);
    Anim_SetFrameWrapped(obj + 0x128, 0, 0);
    Anim_SetFrameWrapped(obj + 0x128, 2, 0);
}
