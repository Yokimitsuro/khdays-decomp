extern void SND_SetTrackPan(int playerNo, int trackMask, int pan);
struct S { unsigned char *volatile p; };

void func_0201a1a0(struct S *s, int track_mask, int pan) {
    if (s->p) {
        SND_SetTrackPan(s->p[0x3c], track_mask, pan);
    }
}
