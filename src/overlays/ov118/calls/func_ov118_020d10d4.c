/* Publish the landing: copy the pending anchor into the live slot and ask the placement helper
 * where the object ends up. If it reports a spot, send the canned 4-byte event to the object's
 * notify hook, latch the returned height and go to action 7. If it does not, wait unless the
 * ready bit at +0x17a is set, in which case clear the counter, drop 0x06 from the hw60 high byte
 * and continue in the next step.
 *
 * Matched byte-exact 2026-07-23, first compile. The event pair is copied HIGH halfword first
 * through a pointer bound to the destination -- a struct assignment reads the low one first and
 * four instructions come out different.
 *
 * One of four byte-identical siblings. */
typedef struct { int x, y, z; } VecFx32;
typedef struct { unsigned short a, b; } Ev;

extern Ev data_ov118_020d1868[];
extern int func_ov107_020c8eb8(int obj, void *a, void *out);
extern void func_0203c634(void *node, int idx, void *cb);
extern void func_ov118_020d11d4(void);

struct hw60 { unsigned short lo : 8, hi : 8; };
struct Bit0 { unsigned char b0 : 1; };

void func_ov118_020d10d4(int *node) {
    int *state = (int *)node[1];
    int out[4];
    Ev ev;
    void (*cb)(int, Ev *, int);

    *(VecFx32 *)(state + 0xb) = *(VecFx32 *)(state + 0x19);
    if (func_ov107_020c8eb8(state[0], (void *)(state[0] + 0x74), out) != 0) {
        Ev *pe = &ev;
        pe->b = data_ov118_020d1868[2].b;
        pe->a = data_ov118_020d1868[2].a;
        cb = *(void (**)(int, Ev *, int))(state[0] + 0x24);
        if (cb != 0) {
            cb(state[0], pe, 4);
        }
        state[0x1d] = out[0];
        *(char *)(state[0] + 0x1c7) = 7;
        func_0203c634(node, *(signed char *)((int)node + 0x20), 0);
        return;
    }
    if (((struct Bit0 *)(state[0] + 0x17a))->b0 == 0) {
        return;
    }
    state[0xe] = 0;
    ((struct hw60 *)(state[0] + 0x60))->hi &= ~6;
    func_0203c634(node, *(signed char *)((int)node + 0x20), func_ov118_020d11d4);
}
