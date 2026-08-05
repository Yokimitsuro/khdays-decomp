typedef struct {
    int x;
    int y;
    int z;
} Vec3;

struct ReactionModes {
    unsigned char flagged[2];
    unsigned char normal[2];
};

struct HitFlags {
    unsigned int low : 16;
    unsigned int kind : 16;
};

struct HitDescriptor {
    unsigned int flags;
    Vec3 direction;
    char pad10[0x18];
    int damage;
};

struct ReactionNode {
    unsigned char *actor;
    char pad04[4];
    int source;
    int reactionContext;
    char pad10[0x0c];
    Vec3 direction;
    char pad28[0x1c];
    unsigned char facing;
};

extern const struct ReactionModes data_ov147_020ce8a0;
extern int func_ov107_020c89e8(int owner, struct HitDescriptor *hit);
extern void func_ov107_020c5af8(int owner, int reactionId,
                                unsigned char mode, int context);

int func_ov147_020cc800(int owner, int source, struct HitDescriptor *hit)
{
    struct ReactionModes modes;
    struct ReactionNode *node = *(struct ReactionNode **)(owner + 0x214);
    int damage;
    int delta;
    int remaining;
    struct HitFlags *flags;

    modes.normal[0] = data_ov147_020ce8a0.normal[0];
    modes.normal[1] = data_ov147_020ce8a0.normal[1];
    modes.flagged[0] = data_ov147_020ce8a0.flagged[0];
    modes.flagged[1] = data_ov147_020ce8a0.flagged[1];

    if (*(short *)(owner + 0x21a) <= 0) {
        return 0;
    }

    node->direction = hit->direction;
    damage = func_ov107_020c89e8(owner, hit);
    hit->damage = damage;

    delta = *(short *)(owner + 0x21a) - damage;
    if (delta < 0) {
        remaining = 0;
    } else {
        remaining = *(short *)(owner + 0x218);
        if (delta <= remaining) {
            remaining = delta;
        }
    }
    *(short *)(owner + 0x21a) = (short)remaining;
    node->source = source;

    if (hit->damage > 0) {
        flags = (struct HitFlags *)hit;
        if ((flags->low & 8) == 0 || (flags->low & 0x80) == 0 ||
            flags->kind != 0x80) {
            if ((flags->low & 0x22) != 0) {
                func_ov107_020c5af8(owner, 0x126,
                                    modes.flagged[node->facing],
                                    node->reactionContext);
            } else {
                func_ov107_020c5af8(owner, 0x126,
                                    modes.normal[node->facing],
                                    node->reactionContext);
            }
            node->facing ^= 1;
        }
    }

    if (*(short *)(owner + 0x21a) == 0) {
        node->actor[0x1c7] = 3;
    } else if (((unsigned short)hit->flags & 0x8000) != 0) {
        node->actor[0x1c7] = 6;
    }

    return 1;
}




