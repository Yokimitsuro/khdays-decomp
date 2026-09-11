extern void func_02014dc4(int *ptr, int arg);

/* Per-track anim object bound during a blend. func_0202accc sets +4 to
   FX32_ONE (0x1000) and +0 to 0 on this same kind of object ("speed"/"frame"
   there), but here +4 is also driven through a 0..0x1000 ramp while the
   blend is in progress, so its job here is not solidly established. */
typedef struct {
    int frame;
    int field_04;
} AnmTrack;

/* Partial view of the blend-controller object driving a track crossfade.
   Only the fields this function touches are named; gap sizes are exact,
   their contents are unknown. */
typedef struct {
    unsigned short flags; /* +0x00: bit 2 cleared once the blend finishes */
    short field_02;       /* +0x02 */
    char pad_04[0xc - 0x4];
    AnmTrack *outTrack;   /* +0x0c: track fading out */
    char pad_10[0xca - 0x10];
    short field_ca;       /* +0xca: >=0 while a blend is active, -1 when idle */
    char pad_cc[0xd4 - 0xcc];
    AnmTrack *inTrack;    /* +0xd4: track fading in, reaches full speed */
    int elapsed;          /* +0xd8: accumulated blend time */
    int duration;         /* +0xdc: total blend duration */
} BlendState;

void func_0202a75c(BlendState *this_) {
    int diff = this_->elapsed - this_->duration;
    this_->elapsed = diff;
    if (diff < 0) {
        diff = 0;
    }
    short flag = this_->field_ca;
    AnmTrack *out = this_->outTrack;
    AnmTrack *in = this_->inTrack;
    int inv = 0x1000 - diff;
    if (flag >= 0) {
        out->field_04 = diff;
        in->field_04 = inv;
    }
    if (diff > this_->duration) {
        return;
    }
    func_02014dc4((int *)((char *)this_ + 0x20), (int)out);
    in->field_04 = 0x1000;
    this_->outTrack = in;
    this_->inTrack = 0;
    this_->field_02 = this_->field_ca;
    this_->field_ca = -1;
    this_->flags &= ~4;
}
