/* Spawns the ov032 enemy's two attachment effects (and its byte-identical twins): for each of
 * the overlay's two 64-bit capability masks that the actor's +0x464 flags carry, the +0x2c2c
 * extra class is asked for a slot at the origin (a negative answer ends the pass), bound to the
 * matching +0x528 matrix, released from any source and the actor's +0x7a6 cue fired with mode
 * 7 (modes 0x25/0x27/0x2a), 5 (0x26/0x28/0x29) or 2. */
struct Vec3 { int x, y, z; };
struct Masks { long long m[2]; };

struct Ov032Actor {
    char pad000[0x464];
    long long nFlags464;
    char pad46c[0x528 - 0x46c];
    char aMatrix528[2][0x30];
    char pad588[0x6bc - 0x588];
    int nMode6bc;
    char pad6c0[0x7a6 - 0x6c0];
    short nCue7a6;
    char pad7a8[0x2c2c - 0x7a8];
    int pExtra2c2c;
};

extern int func_ov022_020893f4(int object, const struct Vec3 *at, int mode);
extern void func_ov022_0208954c(int object, int result, void *source);
extern void func_ov022_020894cc(int object, int result, int a);
extern void func_ov022_020a4490(struct Ov032Actor *self, int cue, int mode);
extern const struct Vec3 data_02041dc8;
extern const struct Masks data_ov032_020b5700;

void func_ov032_020b4034(struct Ov032Actor *self)
{
    struct Masks masks;
    int i;
    int r;
    int mode;

    masks = data_ov032_020b5700;
    for (i = 0; i < 2; i++) {
        if ((self->nFlags464 & masks.m[i]) != 0) {
            r = func_ov022_020893f4(self->pExtra2c2c, &data_02041dc8, 0);
            if (r < 0) {
                return;
            }
            func_ov022_0208954c(self->pExtra2c2c, r, self->aMatrix528[i]);
            func_ov022_020894cc(self->pExtra2c2c, r, 0);
            switch (self->nMode6bc) {
            case 0x26:
            case 0x28:
            case 0x29:
                mode = 5;
                break;
            case 0x25:
            case 0x27:
            case 0x2a:
                mode = 7;
                break;
            default:
                mode = 2;
                break;
            }
            func_ov022_020a4490(self, self->nCue7a6, mode);
        }
    }
}
