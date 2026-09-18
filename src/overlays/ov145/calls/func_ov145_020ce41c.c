/* Message handler of the ov144 enemy (and its byte-identical twin). A sub-state message (kind
 * 0) mirrors the sub-state into bit 1 of the +0x388 part's +0x5c flags (clear for sub-states
 * 4/6/7): sub-states 0/7 hide the +0x38c part (bit 1) and reset the +0x3f0 mode; otherwise, with
 * a +0x25 phase below 3, the +0x38c part is shown and a changed +0x26 mode toggles its sub-items
 * 0/1 (on for mode 0) and refreshes it, the mode being remembered at +0x3f0. A "spawned" message
 * (kind 5) unpacks the 24-bit position into a fresh transform scaled by 2.0 and, for payload 0,
 * attaches the +0x3f8 model of that slot (kind 0x17) under the +0x3c owner into +0x3fc. The base
 * handler always runs.
 *
 * MATCH NOTE: the sub-state set {4, 6, 7} is tested as the ROM does, a bit mask over the
 * sub-state minus 4 in unsigned-byte arithmetic; `||` chains and switches lower to compare
 * chains, range checks or jump tables instead. */
typedef unsigned char u8;
typedef struct { int w[11]; } SrtTransform;
typedef struct { int x, y, z; } Vec3;
struct Flags5c { unsigned int b0 : 1, bShow : 1; };

extern void func_0203b9fc(int part, int slot, short on, int c);
extern void func_0203c7ac(int part, int a);
extern void func_0203c960(SrtTransform *transform);
extern void func_0203ca30(SrtTransform *transform, const Vec3 *translation);
extern void func_0203ca9c(SrtTransform *transform, int scale);
extern int func_ov107_020c0794(int model, int parent, int kind, int zero, SrtTransform *transform);
extern void func_ov107_020c7500(int owner, u8 *msg, int arg);

void func_ov145_020ce41c(int owner, u8 *msg, int arg)
{
    SrtTransform transform;
    Vec3 translation;
    union {
        int words[3];
        u8 bytes[12];
    } packed;
    signed char sub;
    u8 mode;
    int on;
    int part;

    if (msg[2] == 0) {
        sub = *(signed char *)(msg + 0x24);
        mode = msg[0x26];
        on = 1;
        if ((u8)((u8)sub + 0xfc) <= 3 && ((1 << (u8)((u8)sub + 0xfc)) & 0xd) != 0) {
            on = 0;
        }
        ((struct Flags5c *)(*(int *)(owner + 0x388) + 0x5c))->bShow = on;
        if (sub == 0 || sub == 7) {
            *(unsigned int *)(*(int *)(owner + 0x38c) + 0x5c) |= 2;
            *(int *)(owner + 0x3f0) = 0;
        } else {
            part = *(signed char *)(msg + 0x25) < 3 ? *(int *)(owner + 0x38c) : 0;
            if (part != 0) {
                *(unsigned int *)(part + 0x5c) &= ~2;
                if (*(int *)(owner + 0x3f0) != mode) {
                    func_0203b9fc(part, 0, mode == 0, 0);
                    func_0203b9fc(part, 1, mode == 0, 0);
                    func_0203c7ac(part, 0);
                }
            }
            *(int *)(owner + 0x3f0) = mode;
        }
    } else if (msg[2] == 5) {
        packed.bytes[3] = msg[5];
        packed.bytes[2] = msg[6];
        packed.bytes[1] = msg[7];
        translation.x = packed.words[0] >> 8;
        packed.bytes[7] = msg[8];
        packed.bytes[6] = msg[9];
        packed.bytes[5] = msg[0xa];
        translation.y = packed.words[1] >> 8;
        packed.bytes[11] = msg[0xb];
        packed.bytes[10] = msg[0xc];
        packed.bytes[9] = msg[0xd];
        translation.z = packed.words[2] >> 8;
        func_0203c960(&transform);
        func_0203ca30(&transform, &translation);
        func_0203ca9c(&transform, 0x2000);
        if (msg[3] == 0) {
            *(int *)(owner + msg[3] * 8 + 0x3fc) =
                func_ov107_020c0794(*(int *)(owner + 0x3c), *(int *)(owner + msg[3] * 8 + 0x3f8), 0x17, 2, &transform);
        }
    }
    func_ov107_020c7500(owner, msg, arg);
}
