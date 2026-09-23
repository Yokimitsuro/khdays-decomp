/* Draw pre-pass of the ov255 enemy (+0xc): the collision shapes follow their parts -- the first
 * +0x394 shape and the +0x398 shape take the +0x3a8 part's pose, the +0x39c shape the +0x3ac
 * part's and the +0x3a0 shape the +0x3b0 part's -- before the common draw handler runs. */
typedef struct { int w[11]; } Srt;
struct Part { char pad[0x10]; Srt pose; };
struct Rig { int pad; Srt srt; };

extern void func_ov107_020c7ca4(char *self);

void func_ov255_020cc9c4(char *self)
{
    (**(struct Part ***)(self + 0x394))->pose = (*(struct Rig **)(self + 0x3a8))->srt;
    (*(struct Part **)(self + 0x398))->pose = (*(struct Rig **)(self + 0x3a8))->srt;
    (*(struct Part **)(self + 0x39c))->pose = (*(struct Rig **)(self + 0x3ac))->srt;
    (*(struct Part **)(self + 0x3a0))->pose = (*(struct Rig **)(self + 0x3b0))->srt;
    func_ov107_020c7ca4(self);
}
