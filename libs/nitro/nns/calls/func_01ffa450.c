typedef unsigned long u32;
typedef signed long s32;
typedef signed long fx32;
typedef signed long long s64;

typedef struct MtxFx44 {
    fx32 m[4][4];
} MtxFx44;

typedef struct NNSG3dProjectionState {
    u32 flags;
    unsigned char pad004[0x2c];
    fx32 scaleX;
    fx32 scaleY;
} NNSG3dProjectionState;

typedef struct NNSG3dProjectionPacket {
    u32 command;
    u32 projectionMode;
    MtxFx44 matrix;
    u32 positionVectorMode;
} NNSG3dProjectionPacket;

typedef void (*NNSG3dProjectionBuilder)(MtxFx44 *matrix,
                                        const NNSG3dProjectionState *state);

typedef struct NNSG3dProjectionBuilderTable {
    NNSG3dProjectionBuilder entries[8];
} NNSG3dProjectionBuilderTable;

#pragma opt_propagation off
static inline NNSG3dProjectionBuilder GetProjectionBuilder(u32 index)
{
    volatile NNSG3dProjectionBuilder *table =
        (volatile NNSG3dProjectionBuilder *)0x01ffa1f8;
    return table[index];
}

extern void func_01ff9f00(u32 op, const void *args, u32 numWords);

#define FX_MUL(a, b) ((fx32)(((s64)(a) * (b)) >> 12))

void func_01ffa450(const NNSG3dProjectionState *state)
{
    u32 packet[19];
    u32 *packetBase;
    u32 zero;
    u32 positionVectorMode;
    u32 projectionMode;
    NNSG3dProjectionBuilder builder;

    if (state->flags & 8) {
        projectionMode = 3;
        zero = 0;
        positionVectorMode = 2;
        packet[0] = 0x00101610;
    } else {
        projectionMode = 3;
        zero = 0;
        positionVectorMode = 2;
        packet[0] = 0x00101810;
    }

    packet[17] = 0x1000;
    packet[1] = projectionMode;
    packet[18] = positionVectorMode;
    packet[16] = zero;
    packet[13] = zero;
    packet[12] = zero;
    packet[11] = zero;
    packet[10] = zero;
    packet[9] = zero;
    packet[8] = zero;
    packet[4] = packet[5] = zero;

    zero = state->flags;
    zero &= 7;
    builder = GetProjectionBuilder(zero);
    builder((MtxFx44 *)&packet[2], state);

    if (state->scaleX != 0x1000) {
        packet[2] = FX_MUL(state->scaleX, (fx32)packet[2]);
        packet[3] = FX_MUL(state->scaleX, (fx32)packet[3]);
        packet[14] = FX_MUL(state->scaleX, (fx32)packet[14]);
    }

    if (state->scaleY != 0x1000) {
        packet[6] = FX_MUL(state->scaleY, (fx32)packet[6]);
        packet[7] = FX_MUL(state->scaleY, (fx32)packet[7]);
        packet[15] = FX_MUL(state->scaleY, (fx32)packet[15]);
    }

    packetBase = packet;
    func_01ff9f00(packet[0], packetBase + 1, 0x12);
}
