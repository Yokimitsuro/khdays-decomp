/* Draw pre-pass of the ov235 enemy: the +0x39c part's first item and the +0x3a0 part take the
 * +0x3ac rig's pose, the +0x3a4 part the +0x3b0 rig's pose (+0x10 <- +4). Outside sub-state 0xc the
 * pending +0x44 and +0x54 effects of the +0x3bc block are finished. The base pre-pass runs. */
typedef struct { int w[11]; } Srt;
struct Part { char pad[0x10]; Srt pose; };
struct Rig { int pad; Srt srt; };

extern void func_0203c650(int list, int handle);
extern void func_ov107_020c7ca4(char *self);

void func_ov235_020cc8b8(char *self)
{
    (**(struct Part ***)(self + 0x39c))->pose = (*(struct Rig **)(self + 0x3ac))->srt;
    (*(struct Part **)(self + 0x3a0))->pose = (*(struct Rig **)(self + 0x3ac))->srt;
    (*(struct Part **)(self + 0x3a4))->pose = (*(struct Rig **)(self + 0x3b0))->srt;
    if (*(signed char *)(self + 0x100 + 0xc6) != 0xc) {
        if (*(int *)(*(int *)(self + 0x3bc) + 0x44) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3bc) + 0x44));
            *(int *)(*(int *)(self + 0x3bc) + 0x44) = 0;
        }
        if (*(int *)(*(int *)(self + 0x3bc) + 0x54) != 0) {
            func_0203c650(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3bc) + 0x54));
            *(int *)(*(int *)(self + 0x3bc) + 0x54) = 0;
        }
    }
    func_ov107_020c7ca4(self);
}
