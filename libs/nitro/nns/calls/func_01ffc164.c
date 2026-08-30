/* NitroSystem G3D NODEDESC: joint animation and optional matrix restore/store. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef signed short s16;
typedef signed long s32;
typedef signed long fx32;

typedef struct VecFx32 { fx32 x, y, z; } VecFx32;
typedef struct MtxFx33 { fx32 aM[9]; } MtxFx33;
typedef struct NNSG3dJntAnmResult {
    u32 flag;
    VecFx32 scale;
    VecFx32 scaleEx0;
    VecFx32 scaleEx1;
    MtxFx33 rot;
    VecFx32 trans;
} NNSG3dJntAnmResult;
typedef struct NNSG3dResDictTreeNode {
    u8 refBit, idxLeft, idxRight, idxEntry;
} NNSG3dResDictTreeNode;
typedef struct NNSG3dResDict {
    u8 revision, numEntry;
    u16 sizeDictBlk, dummy, ofsEntry;
    NNSG3dResDictTreeNode node[1];
} NNSG3dResDict;
typedef struct NNSG3dResDictEntryHeader {
    u16 sizeUnit, ofsName;
    u8 data[4];
} NNSG3dResDictEntryHeader;
typedef struct NNSG3dResNodeInfo { NNSG3dResDict dict; } NNSG3dResNodeInfo;
typedef struct NNSG3dResDictNodeData { u32 offset; } NNSG3dResDictNodeData;
typedef struct NNSG3dResNodeData { u16 flag; s16 rot00; } NNSG3dResNodeData;
typedef struct NNSG3dAnmObj NNSG3dAnmObj;
typedef struct NNSG3dRenderObj {
    u32 flags;
    void *pResMdl;
    NNSG3dAnmObj *anmMat;
    u8 pad00c_010[4];
    NNSG3dAnmObj *anmJnt;
    u8 pad014_034[0x20];
    NNSG3dJntAnmResult *jntResults;
    u8 pad038_04c[0x14];
} NNSG3dRenderObj;
struct NNSG3dRenderState;
typedef void (*NNSG3dSbcCallback)(struct NNSG3dRenderState *);
typedef void (*NNSG3dFuncJntScale)(NNSG3dJntAnmResult *, const fx32 *, const u8 *, u32);
typedef void (*NNSG3dFuncJntSend)(NNSG3dJntAnmResult *);
typedef struct NNSG3dRenderState {
    u8 *pSbc;
    NNSG3dRenderObj *pRenderObj;
    u32 flags;
    NNSG3dSbcCallback sbcCallbacks[32];
    u8 callbackTimings[32];
    u8 commandAc, materialAd, nodeId, pad0af;
    u32 pad0b0;
    u32 jointWorkB4;
    u8 pad0b8_0d4[0x1c];
    NNSG3dResNodeInfo *pResNodeInfo;
    u8 pad0d8_0e8[0x10];
    NNSG3dFuncJntScale funcJntScale;
    NNSG3dFuncJntSend sendJnt;
    u8 pad0f0_12c[0x3c];
    NNSG3dJntAnmResult jntBuffer;
    u8 pad184_188[4];
} NNSG3dRenderState;

extern void func_01ffa764(u32 command, u32 argument);
extern int func_01ffb304(NNSG3dJntAnmResult *result,
                        const NNSG3dAnmObj *anmObj, u32 nodeId);
extern void MI_Zero36B(void *destination);
extern const u8 data_020420ac[][4];

static inline const NNSG3dResNodeData *GetNodeDataUnchecked(
    const NNSG3dResNodeInfo *info, u32 nodeId)
{
    const NNSG3dResDictEntryHeader *header =
        (const NNSG3dResDictEntryHeader *)((const u8 *)info + info->dict.ofsEntry);
    const NNSG3dResDictNodeData *entry =
        (const NNSG3dResDictNodeData *)(header->data + header->sizeUnit * nodeId);
    return (const NNSG3dResNodeData *)((const u8 *)info + entry->offset);
}

void func_01ffc164(NNSG3dRenderState *state, u32 option)
{
    u32 nodeId = state->pSbc[1];
    u32 commandSize = 4;
    u32 sourceIndex;
    NNSG3dRenderObj *renderObj;
    NNSG3dJntAnmResult *result;

    state->nodeId = (u8)nodeId;
    state->flags |= 0x10;
    if (state->flags & 0x400) {
        if (option == 0x40 || option == 0x60) {
            ++commandSize;
        }
        if (option == 0x20 || option == 0x60) {
            ++commandSize;
            if (!(state->flags & 0x100)) {
                func_01ffa764(0x14, state->pSbc[4]);
            }
        }
        state->pSbc += commandSize;
        return;
    }

    sourceIndex = 4;
    if (option == 0x40 || (sourceIndex = 5, option == 0x60)) {
        ++commandSize;
        if (!(state->flags & 0x100)) {
            func_01ffa764(0x14, state->pSbc[sourceIndex]);
        }
    }
    renderObj = state->pRenderObj;
    if (renderObj->jntResults != 0) {
        result = &renderObj->jntResults[nodeId];
        if (!(state->flags & 0x80)) {
            goto send_joint;
        }
    } else {
        result = &state->jntBuffer;
    }
    if (renderObj->anmJnt == 0 ||
        !func_01ffb304(result, renderObj->anmJnt, nodeId)) {
        const NNSG3dResNodeData *node = GetNodeDataUnchecked(state->pResNodeInfo, nodeId);
        u16 flags = node->flag;
        const u8 *payload = (const u8 *)node + sizeof(*node);
        result->flag = 6;
        if (!(flags & 1)) {
            const fx32 *translation = (const fx32 *)payload;
            result->trans.x = translation[0];
            result->trans.y = translation[1];
            result->trans.z = translation[2];
            payload += sizeof(VecFx32);
            result->flag &= ~4U;
        }
        if (!(flags & 2)) {
            if (flags & 8) {
                u32 pivot = (flags & 0xf0) >> 4;
                const u8 *permutation = data_020420ac[pivot];
                s32 second = ((const s16 *)payload)[1];
                s32 first = ((const s16 *)payload)[0];
                MI_Zero36B(&result->rot);
                result->rot.aM[pivot] = (flags & 0x100) ? -0x1000 : 0x1000;
                result->rot.aM[permutation[0]] = first;
                result->rot.aM[permutation[1]] = second;
                if (flags & 0x200) {
                    second = -second;
                }
                result->rot.aM[permutation[2]] = second;
                if (flags & 0x400) {
                    first = -first;
                }
                result->rot.aM[permutation[3]] = first;
                payload += 4;
            } else {
                const s16 *rotation = (const s16 *)payload;
                result->rot.aM[0] = node->rot00;
                result->rot.aM[1] = rotation[0];
                result->rot.aM[2] = rotation[1];
                result->rot.aM[3] = rotation[2];
                result->rot.aM[4] = rotation[3];
                result->rot.aM[5] = rotation[4];
                result->rot.aM[6] = rotation[5];
                result->rot.aM[7] = rotation[6];
                result->rot.aM[8] = rotation[7];
                payload += 16;
            }
            result->flag &= ~2U;
        }
        state->funcJntScale(result, (const fx32 *)payload, state->pSbc, flags);
    }
send_joint:
    if (!(state->flags & 0x100)) {
        state->sendJnt(result);
    }
    state->jointWorkB4 = 0;
    if (state->callbackTimings[6] == 3) {
        state->sbcCallbacks[6](state);
    }
    if (option == 0x20 || option == 0x60) {
        ++commandSize;
        if (!(state->flags & 0x100)) {
            func_01ffa764(0x13, state->pSbc[4]);
        }
    }
    state->pSbc += commandSize;
}
