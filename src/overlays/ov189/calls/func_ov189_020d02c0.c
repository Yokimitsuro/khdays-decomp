/* Release the attachments the actor's state no longer needs, then publish the pose.
 *
 * Largest variant of the Ov*_ReleaseByState shape: three separate handles (+0x3d4, +0x3e4,
 * +0x3c4), a six-value state whitelist {0, 1, 3, 5, 0xa} requesting state 5, and the usual
 * pair of pose publications.
 *
 * One oddity, faithfully reproduced: in the state-9 branch the actor's flag byte is written
 * into a ONE-BIT bitfield at bit 1 of (+0x3e0)->+0x5c, masked with 0xa.  0xa is even, so the
 * assigned bit is always zero and the field is unconditionally cleared -- the ROM's
 * `and #0xa ; lsl #0x1f ; lsr #30` says so plainly.  It looks like the author meant
 * `!= 0`; either way the C has to say what the ROM does, so the mask stays.
 */
typedef struct { int w[11]; } Pose;
struct Bit1 { unsigned pad0 : 1, b1 : 1; };

extern void func_0203c650(int owner, int handle);
extern void func_ov107_020cb100(int attachment);
extern void func_ov107_020c7ca4(char *actor);

void func_ov189_020d02c0(char *actor) {
    int state;

    if (*(signed char *)(actor + 0x1c6) != 6 && *(int *)(actor + 0x3d4) != 0) {
        func_0203c650(*(int *)(actor + 0x3c), *(int *)(actor + 0x3d4));
        *(int *)(actor + 0x3d4) = 0;
    }

    if (*(signed char *)(actor + 0x1c6) != 9) {
        if (*(int *)(actor + 0x3e4) != 0) {
            func_0203c650(*(int *)(actor + 0x3c), *(int *)(actor + 0x3e4));
            *(int *)(actor + 0x3e4) = 0;
        }
        if (*(int *)(actor + 0x3c4) != 0) {
            func_ov107_020cb100(*(int *)(actor + 0x3c4));
            *(int *)(actor + 0x3c4) = 0;
        }
    } else if (*(int *)(actor + 0x3e4) != 0) {
        ((struct Bit1 *)(*(int *)(actor + 0x3e0) + 0x5c))->b1 =
            *(unsigned char *)(actor + 0x1c4) & 0xa;
    }

    if ((*(unsigned char *)(actor + 0x1c4) & 0xa) != 0) {
        state = *(signed char *)(actor + 0x1c6);
        if (state != 0 && state != 1 && state != 3 && state != 5 && state != 0xa) {
            *(signed char *)(actor + 0x1c7) = 5;
            if (*(int *)(actor + 0x3e4) != 0) {
                func_0203c650(*(int *)(actor + 0x3c), *(int *)(actor + 0x3e4));
                *(int *)(actor + 0x3e4) = 0;
            }
        }
    }

    *(Pose *)(*(char **)(actor + 0x38c) + 0x10) = *(Pose *)(*(char **)(actor + 0x390) + 4);
    *(Pose *)(**(char ***)(actor + 0x388) + 0x10) = *(Pose *)(*(char **)(actor + 0x38c) + 0x10);

    func_ov107_020c7ca4(actor);
}
