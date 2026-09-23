/* Sink tick of the ov252 actor: the +0x64 timer accumulates the frame rate. Once the +8 track
 * sinks to the actor's -(+0x80) depth (once, +0x88) a splash fires at the +0x560 part's point at
 * height 0x1c0: reaction 0x148/0xa, knock-backs in place with modes 9 and 0x32, and +0x584
 * clears. While above four times that depth the +0xc velocity follows the +0x574 partner's +0x2c
 * vector turned by the +0x54 angle and, once the +4 item's +0xad byte clears, pose 0x17 and the
 * partner motion 0x16 play. Deeper, the last shown one of the +0x4f4 shapes (+0x93) is hidden,
 * +0x88 becomes 2, the counters and velocity reset, the +0x60 high byte loses bit 0, the actor is
 * placed 3.0 below the origin (020c5c54) and the node moves on to 020d0f14. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { unsigned f : 8; } B8;
struct Hw60 { u16 lo : 8; u16 hi : 8; };
struct Shapes4e8 { char pad[0x4e8]; int shape[7]; };

extern void func_ov107_020c5af8(int owner, int id, int mode, void *at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern void func_ov252_020cdafc(Vec3 *out, int angle, void *base);
extern void func_ov107_020c5c54(int actor, Vec3 *at);
extern void func_0203c634(int *node, int slot, void *cb);
extern void func_ov107_020c9264(int actor, int pose, int loop);
extern void func_ov107_020c9ee8(int part, int motion, int mode);
extern void func_ov252_020d0f14(void);
extern const Vec3 data_02041dc8;

void func_ov252_020d0cc0(int *node)
{
    int *state = (int *)node[1];
    Vec3 pos;
    Vec3 spawn;
    Vec3 v;
    u8 i;

    state[0x19] += *(int *)(node[0] + 0x2c);
    if (*(int *)(state[2] + 4) <= -*(int *)(*state + 0x80) && *((u8 *)state + 0x88) == 0) {
        pos = *(Vec3 *)(*(int *)(*state + 0x560) + 0x14);
        pos.y = 0x1c0;
        func_ov107_020c5af8(*state, 0x148, 0xa, &pos);
        func_ov107_020c0b90(*state, 9, pos, 0);
        func_ov107_020c0b90(*state, 0x32, pos, 0);
        *(int *)(*state + 0x584) = 0;
        *((u8 *)state + 0x88) = 1;
    }
    if (*(int *)(state[2] + 4) > -*(int *)(*state + 0x80) * 4) {
        func_ov252_020cdafc(&v, state[0x15], (void *)(*(int *)(*state + 0x574) + 0x2c));
        *(Vec3 *)(state + 3) = v;
    } else {
        {
            Vec3 below = { 0, -0x30000, 0 };

            spawn = below;
        }
        for (i = 3; i >= 0; i--) {
            if (((B8 *)(((struct Shapes4e8 *)*state)->shape[i + 3] + 8))->f & 1) {
                *((u8 *)state + 0x93) = i;
                break;
            }
        }
        ((B8 *)(((struct Shapes4e8 *)*state)->shape[i + 3] + 8))->f &= ~1;
        *((u8 *)state + 0x88) = 2;
        state[0x27] = 0;
        *((u8 *)state + 0x86) = 0;
        state[0x19] = 0;
        *(Vec3 *)(state + 3) = data_02041dc8;
        ((struct Hw60 *)(*state + 0x60))->hi &= ~1;
        func_ov107_020c5c54(*state, &spawn);
        func_0203c634(node, *(signed char *)((char *)node + 0x20), func_ov252_020d0f14);
        return;
    }
    if (*(u8 *)(state[1] + 0xad) != 0) {
        return;
    }
    func_ov107_020c9264(*state, 0x17, 0);
    func_ov107_020c9ee8(*(int *)(*state + 0x574), 0x16, 0);
}
