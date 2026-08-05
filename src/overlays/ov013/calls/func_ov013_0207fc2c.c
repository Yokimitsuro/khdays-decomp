typedef unsigned char u8;

typedef struct {
    int value;
    char padding04[8];
    unsigned short *type;
} Ov013Entry;

typedef struct {
    char padding00;
    u8 count;
    char padding02[2];
    Ov013Entry **entries;
} Ov013EntryGroup;

typedef struct {
    char padding00[0xb0];
    int scaleX;
    int scaleY;
    int scaleZ;
} Ov013SpawnedSlot;

typedef struct {
    char padding00[0x464];
    unsigned long long flags464;
    char padding46c[0x20];
    char spawnData[0x230];
    int currentGroup;
    Ov013EntryGroup *groups[60];
    int valueLimit;
    char padding7b4[0x14];
    int subsystem;
    char padding7cc[4];
    u8 processedMask;
    u8 previousGroup;
} Ov013Context;

extern int func_ov022_020893f4(int subsystem, void *spawnData, int zero);
extern Ov013SpawnedSlot *func_ov022_0208963c(int subsystem, int index);

static inline int HasEntries(int count) {
    return count > 0;
}

void func_ov013_0207fc2c(Ov013Context *ctx) {
    Ov013EntryGroup *group;
    int i;

    if (ctx->currentGroup < 0) {
        return;
    }

    if (ctx->previousGroup != ctx->currentGroup
        || (ctx->flags464 & 0x80000000ULL) != 0) {
        ctx->processedMask = 0;
    }

    group = ctx->groups[ctx->currentGroup];
    if (group == 0) {
        return;
    }
    ctx->previousGroup = ctx->currentGroup;

    i = 0;
    if (!HasEntries(group->count)) {
        return;
    }
    do {
        Ov013Entry *entry = group->entries[i];
        unsigned short type = *entry->type;

        if ((type == 15 || type == 2 || type == 28)
            && entry->value <= ctx->valueLimit
            && (ctx->processedMask & (1 << i)) == 0) {
            int index;
            ctx->processedMask |= 1 << i;
            index = func_ov022_020893f4(ctx->subsystem, ctx->spawnData, 0);
            if (index >= 0) {
                Ov013SpawnedSlot *slot = func_ov022_0208963c(ctx->subsystem, index);
                slot->scaleX = slot->scaleY = slot->scaleZ = 0x1000;
            }
        }
        i++;
    } while (i < group->count);
}

