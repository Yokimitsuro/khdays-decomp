/* Message handler (second rider form): a kind-0 message copies its +0x28 bit 0 into the actor's
 * +0x3d4 bit 0 and its +0x24 / +0x26 halfwords into the +0x3d0 / +0x3d2 rider counters. A
 * "spawned" message (kind 5) dispatches on its slot byte: 0 / 1 spawn the two +0x3cc sub-items
 * (kind 0x17) 0x600 below the +0x39c / +0x3a4 item's +0x20 position, posed like the actor's
 * +0xa0; 2 / 3 run the 020ce984 hook; 4 / 5 start the +0x10 / +0x18 sub-items at the +0x3bc /
 * +0x3b8 items' transforms. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } VecFx32;
typedef struct { int w[11]; } Srt;
struct Bits3d4 { unsigned int b0 : 1; };
struct Bits28 { u8 b0 : 1; };
struct Ov236SubSlot { int pItem; int pChild; };

extern void func_0203c960(Srt *srt);
extern void func_0203ca30(Srt *srt, const VecFx32 *t);
extern void func_0203c9d0(Srt *srt, void *pose);
extern int func_ov107_020c0794(int owner, int slot, int kind, int a4, const Srt *srt);
extern void func_ov278_020ce984(char *self);
extern int func_ov107_020c09a0(int list, int parent, int kind, void *at, int a, int b);
extern void func_ov107_020c7500(char *self, u8 *cmd, void *arg3);

void func_ov278_020ce4c8(char *self, u8 *cmd, void *arg3)
{
    Srt srt;
    VecFx32 pos;

    if (cmd[2] == 0) {
        ((struct Bits3d4 *)(self + 0x3d4))->b0 = ((struct Bits28 *)(cmd + 0x28))->b0;
        *(short *)(self + 0x300 + 0xd0) = *(short *)(cmd + 0x24);
        *(short *)(self + 0x300 + 0xd2) = *(short *)(cmd + 0x26);
    } else if (cmd[2] == 5) {
        switch (cmd[3]) {
        case 0:
            pos = *(VecFx32 *)(*(char **)(self + 0x39c) + 0x20);
            pos.y -= 0x600;
            func_0203c960(&srt);
            func_0203ca30(&srt, &pos);
            func_0203c9d0(&srt, self + 0xa0);
            (*(struct Ov236SubSlot **)(self + 0x3cc))[0].pChild =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Ov236SubSlot **)(self + 0x3cc))[0].pItem, 0x17, 0, &srt);
            (*(struct Ov236SubSlot **)(self + 0x3cc))[1].pChild =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Ov236SubSlot **)(self + 0x3cc))[1].pItem, 0x17, 0, &srt);
            break;
        case 1:
            pos = *(VecFx32 *)(*(char **)(self + 0x3a4) + 0x20);
            pos.y -= 0x600;
            func_0203c960(&srt);
            func_0203ca30(&srt, &pos);
            func_0203c9d0(&srt, self + 0xa0);
            (*(struct Ov236SubSlot **)(self + 0x3cc))[0].pChild =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Ov236SubSlot **)(self + 0x3cc))[0].pItem, 0x17, 0, &srt);
            (*(struct Ov236SubSlot **)(self + 0x3cc))[1].pChild =
                func_ov107_020c0794(*(int *)(self + 0x3c), (*(struct Ov236SubSlot **)(self + 0x3cc))[1].pItem, 0x17, 0, &srt);
            break;
        case 2:
        case 3:
            func_ov278_020ce984(self);
            break;
        case 4:
            (*(struct Ov236SubSlot **)(self + 0x3cc))[2].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov236SubSlot **)(self + 0x3cc))[2].pItem,
                                    0x17, *(char **)(self + 0x3bc) + 4, 0, 0);
            break;
        case 5:
            (*(struct Ov236SubSlot **)(self + 0x3cc))[3].pChild =
                func_ov107_020c09a0(*(int *)(self + 0x3c), (*(struct Ov236SubSlot **)(self + 0x3cc))[3].pItem,
                                    0x17, *(char **)(self + 0x3b8) + 4, 0, 0);
            break;
        }
    }
    func_ov107_020c7500(self, cmd, arg3);
}
