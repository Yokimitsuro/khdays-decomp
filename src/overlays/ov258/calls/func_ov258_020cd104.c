/* Attack hit test of the ov258 actor: the targets touching `sphere` (else `box`, else `capsule`,
 * else `cylinder`) are tried in turn; unless `once` already marked them in the +0x52 low nibble each
 * gets the push (kind 1 adds a 1.0 / 6.0 lift; the lift is capped at 3.0) through 020ca918. The first
 * target hit is marked, plays hit sound 0x10 of the +0x58 bank for kinds 1 / 4, spawns effect
 * `effect` + 6 at its +0x190 point and returns 1; 0 when nothing is hit. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef struct { int x, y, z; } Vec3;
typedef struct { u8 lo : 4; u8 hi : 4; } NibblePair;

extern int func_ov107_020c8eb8(int owner, void *sphere, int *hits);
extern int func_ov107_020c8df0(int owner, void *box, int *hits);
extern int func_ov107_020c8f44(int owner, void *capsule, int *hits);
extern int func_ov107_020c8fd0(int owner, void *cylinder, int *hits);
extern int func_ov107_020ca918(int hit, int owner, int item, u8 kind, Vec3 *push, int z);
extern void func_ov107_020c5af8(int actor, int bank, int variant, int at);
extern void func_ov107_020c0b90(int owner, int mode, Vec3 at, int flag);

int func_ov258_020cd104(int *node, void *sphere, void *box, void *capsule, void *cylinder, Vec3 *push, int once, u16 effect, int kind)
{
    int *state = (int *)node[1];
    int hits[4];
    long n;
    long i;
    u8 bit;

    if (sphere != 0) {
        n = func_ov107_020c8eb8(*state, sphere, hits);
    } else if (box != 0) {
        n = func_ov107_020c8df0(*state, box, hits);
    } else if (capsule != 0) {
        n = func_ov107_020c8f44(*state, capsule, hits);
    } else {
        n = func_ov107_020c8fd0(*state, cylinder, hits);
    }
    if (n != 0) {
        for (i = 0; i < n; i++) {
            bit = 1 << *(u16 *)(hits[i] + 2);
            if (once != 0 && (bit & ((NibblePair *)((u8 *)state + 0x52))->lo)) {
                continue;
            }
            if (kind == 1) {
                push->y += 0x1000;
                push->z += 0x6000;
            }
            if (push->y > 0x3000) {
                push->y = 0x3000;
            }
            if (func_ov107_020ca918(hits[i], *state, *state, kind, push, 0) == 0) {
                continue;
            }
            if (once != 0) {
                ((NibblePair *)((u8 *)state + 0x52))->lo |= bit;
            }
            if (kind == 1 || kind == 4) {
                func_ov107_020c5af8(*state, *(short *)(state + 0x16), 0x10, hits[i] + 0x190);
            }
            func_ov107_020c0b90(*state, effect + 6, *(Vec3 *)(hits[i] + 0x190), 0);
            return 1;
        }
    }
    return 0;
}
