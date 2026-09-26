/* Swing tick of the ov258 shockwave: a +0x17a contact spawns effect 7 at the +8 point. While the +0xc
 * clock lies between +0x14 and +0x18 the owner rig's +0x78 segment (reach +1.5) sweeps: every target
 * not yet in the +0x10 mask whose +0x1c4 handler accepts a 0x28-byte hit packet (kind 1 | shield /
 * guard / flinch bits from its +0x28c record, push away 1.0 up / 4.0 out capped at 3.0, the record's
 * damage, reaction and hitstop, or a random reaction from data_ov258_020d1844 other than the last
 * +0x1d with hitstop 0x5a for the base record) gets the owner's effect 6 and the actor's reaction 0xd
 * (0x180 or 0x17b by the owner's +0x460 flag) and is marked. The clock then runs up at the frame
 * rate; past +0x18 the next move is 1.
 * Codegen: the +0x390 owner is read through the OwnerOf accessor (the plain dereference swaps the
 * owner and record-index registers). */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { int w[7]; int radius; } Segment;
typedef struct { short mode[5]; } Short5;
typedef struct { u8 b0 : 1; } Bit0;

struct HitPacket40 {
    int flags;
    Vec3 push;
    int damage;
    int reaction;
    u8 hitstop;
    int owner;
    int w[2];
};

extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);
extern int func_ov107_020c8f44(int owner, void *capsule, int *hits);
extern void VEC_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern int func_01ff8d18(const Vec3 *v, Vec3 *out);
extern int func_02023eb4(int bound);
extern void func_ov107_020c5af8(int actor, short bank, int variant, int at);
extern void func_0203c634(int *node, int slot, void *cb);
extern const Short5 data_ov258_020d1844;

struct B6 { u8 b0 : 1, b1 : 1, b2 : 1, b3 : 1, b4 : 1, b5 : 1, b6 : 1, b7 : 1; };

struct AtkEntry { u8 kind, flags, reaction, hitstop; u16 damage; };
struct AtkOwner { char pad[0x1a0]; int *pSlots; char pad1a4[0x28c - 0x1a4]; struct AtkEntry atk[4]; };
/* The actor's +0x390 owner (the hit source's parent). */
static inline int OwnerOf(int actor)
{
    return *(int *)(actor + 0x390);
}

void func_ov258_020d02f8(int *node)
{
    int *state = (int *)node[1];

    if (((Bit0 *)(*state + 0x17a))->b0) {
        func_ov107_020c0b90(*state, 7, *(Vec3 *)state[2], 0);
    }
    if (state[3] >= state[5] && state[3] < state[6]) {
        Segment seg;
        int hits[4];
        struct HitPacket40 packet = {0};
        long i;
        long n;
        int bit;

        seg = *(Segment *)(*(int *)(*state + 0x388) + 0x78);
        seg.radius += 0x1800;
        n = func_ov107_020c8f44(OwnerOf(*state), &seg, hits);
        i = 0;
        if (n > 0) {
            do {
                Vec3 push;
                short modes[5];
                u8 *rec;


                bit = 1 << *(u16 *)(hits[i] + 2);
                if (((unsigned long long)bit & *((u8 *)state + 0x10)) != 0) {
                    goto next;
                }
                if (*(int *)(hits[i] + 0x1c4) == 0) {
                    goto next;
                }
                VEC_Subtract((Vec3 *)(hits[i] + 0x74), (Vec3 *)(*state + 0x74), &push);
                func_01ff8d18(&push, &push);
                push.z += 0x4000;
                push.y += 0x1000;
                if (push.y > 0x3000) {
                    push.y = 0x3000;
                }
                packet.push = push;
                packet.damage = ((struct AtkOwner *)OwnerOf(*state))->atk[*((u8 *)state + 0x1c)].damage;
                packet.flags |= 1;
                packet.owner = OwnerOf(*state);
                rec = (u8 *)(OwnerOf(*state) + 0x28c + *((u8 *)state + 0x1c) * 6);
                *(Short5 *)modes = data_ov258_020d1844;
                if (!((struct B6 *)(*(int *)(OwnerOf(*state) + 0x1a0) + *((u8 *)state + 0x1c) * 4 + 6))->b6) {
                    packet.flags |= 8;
                }
                if (rec[1] & 1) {
                    packet.flags |= 0x20;
                }
                if (rec[1] & 2) {
                    packet.flags |= 0x40;
                }
                if (*((u8 *)state + 0x1c) != 0) {
                    packet.reaction = rec[2];
                    packet.hitstop = rec[3];
                } else {
                    u8 picked;

                    for (picked = 0; picked < 1;) {
                        signed char mode = modes[func_02023eb4(5)];

                        if (*((signed char *)state + 0x1d) != mode) {
                            packet.reaction = mode;
                            *((signed char *)state + 0x1d) = mode;
                            picked++;
                        }
                    }
                    packet.hitstop = 0x5a;
                }
                if ((*(int (**)(u16, struct HitPacket40 *))(hits[i] + 0x1c4))(*(u16 *)(hits[i] + 2), &packet) != 0) {
                    func_ov107_020c0b90(OwnerOf(*state), 6, *(Vec3 *)(hits[i] + 0x190), 0);
                    func_ov107_020c5af8(*state,
                                        *(int *)(OwnerOf(*state) + 0x460) != 0 ? 0x180 : 0x17b, 0xd, state[2]);
                    *((u8 *)state + 0x10) |= bit;
                }
next:
                ;
            } while (++i < n);
        }
    }
    state[3] += *(int *)(node[0] + 0x2c);
    if (state[3] <= state[6]) {
        return;
    }
    *(signed char *)(*state + 0x1c7) = 1;
    func_0203c634(node, *(signed char *)((char *)node + 0x20), 0);
}
