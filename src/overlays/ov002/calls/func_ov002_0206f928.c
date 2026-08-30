/* Ov002_DispatchSessionPacket: channel 7 receive callback. */
typedef struct VecFx32 { int x, y, z; } VecFx32;
typedef struct Ov002ForwardPacketFlags {
    unsigned char nKind : 2;
    unsigned char nIndex : 6;
} Ov002ForwardPacketFlags;
typedef struct Ov002PeerReadyPacketFlags {
    unsigned char nSlot : 3;
    unsigned char bReady : 1;
    unsigned char nReserved : 4;
} Ov002PeerReadyPacketFlags;
typedef struct Ov002SessionPacketHeader {
    unsigned char nOp, nArg1, nArg2, nArg3;
    int nValue;
} Ov002SessionPacketHeader;
typedef struct Ov002ForwardRecordPacket {
    unsigned char nOp;
    Ov002ForwardPacketFlags flags;
    unsigned char nOwner;
    signed char nRecordKey;
    unsigned char nParam, pad005[3];
    VecFx32 vPosition;
} Ov002ForwardRecordPacket;
typedef struct Ov002SpotSpawnPacket {
    unsigned char nOp, nArg2, nKind, nArg1;
    VecFx32 vPosition;
} Ov002SpotSpawnPacket;
typedef struct Ov002PeerReadyPacket {
    unsigned char nOp;
    Ov002PeerReadyPacketFlags flags;
} Ov002PeerReadyPacket;
typedef union Ov002SessionPacket {
    Ov002SessionPacketHeader header;
    Ov002ForwardRecordPacket forward;
    Ov002SpotSpawnPacket spot;
    Ov002PeerReadyPacket ready;
} Ov002SessionPacket;
extern void func_ov002_0206ef68(int nId);
extern void func_ov002_0206eec4(void *pPacket);
extern void func_ov002_0207220c(int nSlot, int nDay);
extern void func_ov002_0206c7bc(void *pPacket);
extern void func_ov002_0206f788(int nKind, int nDelta);
extern void func_ov002_0206c1ac(void *pPacket);
extern void func_ov002_0206c230(void *pPacket);
extern void func_ov002_0206c764(void *pPacket);
extern void func_ov002_02072dd0(int nSlot, int nIndex);
extern void func_ov002_02072e1c(int nSlot);
extern void func_ov002_02072d7c(int nValue);
extern void func_ov002_02072db0(int nBit);
extern void func_ov002_0206d1b4(int nOwner, int nKey, int nIndex, VecFx32 *pPos, signed char nKind, unsigned char nParam);
extern void *func_ov002_020779dc(int nKind, int nArg1, int nArg2, VecFx32 *pPos, int nMode);
extern void func_ov002_0206e354(void *pPacket);
extern void func_ov002_0206dfd8(unsigned int nSlot, int bReady);
extern void func_ov002_0206e44c(void *pPacket);
extern void func_ov002_0206be18(void *pPacket, unsigned int nPayloadBytes);
extern void func_ov002_0206c144(void *pPacket);
extern void func_ov002_0206c834(void *pPacket);
extern void func_ov002_0206e7e0(int nEvent, int nPeer);

void func_ov002_0206f928(Ov002SessionPacket *pPacket, unsigned int nPayloadBytes)
{
    switch (pPacket->header.nOp) {
    case 0: break;
    case 1: func_ov002_0206ef68(pPacket->header.nValue); break;
    case 2:
    case 3:
    case 4: func_ov002_0206eec4(pPacket); break;
    case 5: func_ov002_0207220c(pPacket->header.nArg1, pPacket->header.nArg2); break;
    case 6: func_ov002_0206c7bc(pPacket); break;
    case 7: func_ov002_0206f788(pPacket->header.nArg1, pPacket->header.nValue); break;
    case 8: func_ov002_0206c1ac(pPacket); break;
    case 9: func_ov002_0206c230(pPacket); break;
    case 18: func_ov002_0206c764(pPacket); break;
    case 12: func_ov002_02072dd0(pPacket->header.nArg1, pPacket->header.nArg2); break;
    case 13: func_ov002_02072e1c(pPacket->header.nArg1); break;
    case 14: func_ov002_02072d7c(pPacket->header.nArg1); break;
    case 15: func_ov002_02072db0(pPacket->header.nArg1); break;
    case 16:
        func_ov002_0206d1b4(pPacket->forward.nOwner, pPacket->forward.nRecordKey,
            pPacket->forward.flags.nIndex, &pPacket->forward.vPosition,
            (signed char)pPacket->forward.flags.nKind, pPacket->forward.nParam);
        break;
    case 17:
        func_ov002_020779dc(pPacket->spot.nKind, pPacket->spot.nArg1,
            pPacket->spot.nArg2, &pPacket->spot.vPosition, 3);
        break;
    case 20:
    case 21: func_ov002_0206e354(pPacket); break;
    case 22:
        func_ov002_0206dfd8(pPacket->ready.flags.nSlot, (signed char)pPacket->ready.flags.bReady);
        break;
    case 23:
    case 24: func_ov002_0206e44c(pPacket); break;
    case 10: func_ov002_0206be18(pPacket, nPayloadBytes); break;
    case 11: func_ov002_0206c144(pPacket); break;
    case 19: func_ov002_0206c834(pPacket); break;
    case 25: func_ov002_0206e7e0(25, pPacket->header.nArg1); break;
    case 26: func_ov002_0206e7e0(26, 255); break;
    }
}
