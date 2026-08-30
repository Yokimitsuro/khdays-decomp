/* Ov002_CreatePlacedPiece: claim, position and register a destructible piece. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef struct Ov002Vec3 {int x,y,z;} Ov002Vec3;
typedef struct Ov002PlaceParams {int nKind,nParamB,nParamA,nParamC,nAngle;} Ov002PlaceParams;
typedef struct Ov002PiecePlacementBytes {s8 bPlaceKind,bSlotKind;} Ov002PiecePlacementBytes;
typedef union Ov002PiecePlacementParamB {short nParamB;Ov002PiecePlacementBytes fields;} Ov002PiecePlacementParamB;
typedef struct Ov002PieceClass {char pad0[0x68];short nRequestA;char pad6a[10];s8 bKind,bVariant;short nParamA;Ov002PiecePlacementParamB placeParamB;short nParamC;} Ov002PieceClass;
typedef void *Ov002StateFn(void *);
typedef struct Ov002PieceElement {
    char pad0[0xc];Ov002StateFn *pfnPhase;u8 bBucket,pad11;u16 wFlags,wRequestId;u8 bRequestSlot,bStateDirty;
    short nAngle;char pad1a[2];Ov002Vec3 vPlace;int nNodeFlags;char aBodyNode[12];int nBuildFlags;u16 wAnimFlags;
    char pad3e[0x7a];short nHomeAngle;char padba[0xf6];int aClock[1];short nDropScale;u8 bDropsOn:1,nReplays:7;u8 nAnimCounter;
} Ov002PieceElement;
extern Ov002PieceElement *func_ov002_02076a38(Ov002PieceClass *,int);
extern int func_ov002_0207c4c0(void *,void *,Ov002PlaceParams *,int,int,int,int,int,int,int);
extern void func_ov002_0207c53c(Ov002Vec3 *,Ov002Vec3 *,Ov002PlaceParams *);
extern void func_0202b450(void *,Ov002Vec3 *);
extern Ov002StateFn func_ov002_02077078;
extern void func_ov002_02076480(int,Ov002PieceElement *);
extern int func_ov002_02076968(int,int);
Ov002PieceElement *func_ov002_02077394(Ov002PieceClass *pClass,u16 nEntry,int nBucket,Ov002Vec3 *pPosition,short nAngle,short nDropScale,u16 nRequestId,u8 nRequestSlot)
{
    Ov002PlaceParams placement;
    Ov002Vec3 vPlaced;
    Ov002PieceElement *pPiece=func_ov002_02076a38(pClass,nEntry);
    int nPlaceAngle=nAngle;
    func_ov002_0207c4c0(pPiece,pPiece->aBodyNode,&placement,nEntry,pClass->bKind,pClass->nParamA,pClass->placeParamB.nParamB,pClass->nParamC,nPlaceAngle,1);
    func_ov002_0207c53c(&vPlaced,pPosition,&placement);
    func_0202b450(&pPiece->nBuildFlags,pPosition);
    if(!(pPiece->nBuildFlags&0x20)){pPiece->nHomeAngle=nPlaceAngle;pPiece->wAnimFlags|=0x20;}
    pPiece->nAngle=nAngle;
    pPiece->vPlace=vPlaced;
    pPiece->nNodeFlags=0;
    pPiece->aClock[0]=0;
    pPiece->nDropScale=nDropScale;
    pPiece->bDropsOn=0;
    pPiece->nAnimCounter=0;
    pPiece->nReplays=0;
    pPiece->bBucket=nBucket;
    pPiece->pfnPhase=func_ov002_02077078;
    pPiece->wFlags|=8;
    pPiece->wFlags|=0x40;
    pPiece->wRequestId=nRequestId;
    pPiece->bRequestSlot=nRequestSlot;
    pPiece->bStateDirty=0;
    func_ov002_02076480(nBucket,pPiece);
    if(pClass->nRequestA==0x2b)func_ov002_02076968(nBucket,2);
    else func_ov002_02076968(nBucket,1);
    return pPiece;
}
