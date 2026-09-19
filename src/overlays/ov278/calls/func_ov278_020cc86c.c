/* Message handler: a "spawned" message (kind 5) with slot byte 0 starts the +0x3b0 sub-item
 * mapped by data_ov278_020d6230[cmd[4]] (kind 0x17, weight 1.0, payload at cmd+5); slot 1
 * spawns the first sub-item at the actor's +0x74 position (y = 0x100) from an identity
 * transform and pushes pose 1; slots 2 / 3 start the +0x30 / +0x38 sub-items; slot 4 stores
 * the 020d5f34 result at +0x44; slot 5 starts effect 0x166 (kind 0xf) on the +0x39c item's
 * transform into +0x3c4. The base handler always runs. */
typedef unsigned char u8;
typedef struct { int x, y, z; } VecFx32;
typedef struct { int w[11]; } Srt;
struct Ov278SlotMap { u8 b[4]; };

extern int func_ov107_020c08cc(int list, int parent, int kind, int a, int scale, u8 *payload);
extern void func_0203c960(Srt *srt);
extern void func_0203ca30(Srt *srt, const VecFx32 *t);
extern int func_ov107_020c0794(int owner, int slot, int kind, int a4, const Srt *srt);
extern void func_ov107_020c0b14(char *self, int a2);
extern int func_ov278_020d5ee8();
extern int func_ov107_020cb040(char *self, int id, int a3, int a4, int xform);
extern void func_ov107_020c7500(char *self, u8 *cmd, void *arg3);
extern const struct Ov278SlotMap data_ov278_020d6230;

void func_ov278_020cc86c(char *self, u8 *cmd, void *arg3)
{
    Srt srt;
    VecFx32 pos;
    struct Ov278SlotMap map;

    if (cmd[2] == 5) {
        switch (cmd[3]) {
        case 0:
            map = data_ov278_020d6230;
            *(int *)(*(int *)(self + 0x3b0) + map.b[cmd[4]] * 8 + 4) =
                func_ov107_020c08cc(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3b0) + map.b[cmd[4]] * 8),
                                    0x17, 0, 0x1000, cmd + 5);
            break;
        case 1:
            func_0203c960(&srt);
            pos = *(VecFx32 *)(self + 0x74);
            pos.y = 0x100;
            func_0203ca30(&srt, &pos);
            *(int *)(*(int *)(self + 0x3b0) + 4) =
                func_ov107_020c0794(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3b0)), 0x17, 0, &srt);
            func_ov107_020c0b14(self, 1);
            break;
        case 2:
            *(int *)(*(int *)(self + 0x3b0) + 0x34) =
                func_ov107_020c08cc(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3b0) + 0x30), 0x17, 0, 0x1000, cmd + 5);
            break;
        case 3:
            *(int *)(*(int *)(self + 0x3b0) + 0x3c) =
                func_ov107_020c08cc(*(int *)(self + 0x3c), *(int *)(*(int *)(self + 0x3b0) + 0x38), 0x17, 0, 0x1000, cmd + 5);
            break;
        case 4:
            *(int *)(*(int *)(self + 0x3b0) + 0x44) = func_ov278_020d5ee8();
            break;
        case 5:
            *(int *)(self + 0x3c4) = func_ov107_020cb040(self, 0x166, 0xf, 1, *(int *)(self + 0x39c) + 4);
            break;
        }
    }
    func_ov107_020c7500(self, cmd, arg3);
}
