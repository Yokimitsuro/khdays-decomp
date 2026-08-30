/* Ov002_FindSharedPlayerExit: all players must overlap the same exit key.
 * Last matching item wins. Preserve the 64-bit flags test, direct bounds,
 * X/Y/Z calculation order, and bound-first comparisons for exact codegen.
 * Declarations k/i/j/context reproduce the original stack slot ordering. */
typedef struct VecFx32 { int x,y,z; } VecFx32;
typedef struct Ov002SessionActorFlags {
    unsigned long long qwFlags;
    char pad008[0x45c];
    unsigned int dwStateFlags;
} Ov002SessionActorFlags;
typedef struct Ov002PeerRow {
    unsigned char nKey;
    char pad001[5];
    short nRadius;
} Ov002PeerRow;
typedef struct Ov002LinkItem {
    signed char nKey;
    char pad001[3];
    int reserved04; /* Opaque word preceding the position; used as an anchor. */
    VecFx32 vPos;
} Ov002LinkItem;
typedef struct Ov002LinkCtx {
    char pad000[0xf];
    signed char aPlayerExitKeys[4];
    char pad013[0x1c];
    signed char slots[4];
    char pad033[0x49];
    Ov002LinkItem *aapItems[4][8];
    signed char aItemCount[4];
} Ov002LinkCtx;
extern Ov002LinkCtx *data_ov002_0207fa10;
extern int func_ov022_020882f8(void);
extern Ov002SessionActorFlags *func_01fffde0(int nPlayer);
extern VecFx32 *func_ov022_020881f8(int nPlayer);
extern int func_ov022_02088474(int nPlayer);
extern int func_ov022_020886d0(int nPlayer);
extern int func_ov022_020882e0(int nPlayer);
extern Ov002PeerRow *func_ov002_02071420(int nKey,int nRosterIndex);
extern int func_01ff8e94(const VecFx32 *pA,const VecFx32 *pB);

int func_ov002_02071230(void)
{
    int k,i,j;
    Ov002LinkCtx *pCtx=data_ov002_0207fa10;
    Ov002SessionActorFlags *pActor;
    VecFx32 *pPos;
    int nRoster;
    for(i=0;i<func_ov022_020882f8();i++) {
        pActor=func_01fffde0(i);
        pPos=func_ov022_020881f8(i);
        pCtx->aPlayerExitKeys[i]=-1;
        for(j=0;j<4;j++) {
            nRoster=data_ov002_0207fa10->slots[j];
            if(nRoster>=0 && j==func_ov022_02088474(i) &&
                (func_01fffde0(i)->dwStateFlags & 0x10000000)==0 &&
                func_ov022_020886d0(i)==0 && func_ov022_020882e0(i)>0 &&
                (pActor->qwFlags & 0x10000)==0) {
                for(k=0;k<pCtx->aItemCount[j];k++) {
                    int *pShape;
                    int nRadius;
                    int nXMin,nXMax,nZMin,nZMax,nYMax,nYMin;
                    pShape=&pCtx->aapItems[j][k]->reserved04;
                    nRadius=func_ov002_02071420(pCtx->aapItems[j][k]->nKey,nRoster)->nRadius;
                    nXMin=pShape[1]-nRadius;
                    nXMax=pShape[1]+nRadius;
                    nYMin=pShape[2]-nRadius;
                    nYMax=pShape[2]+nRadius;
                    nZMin=pShape[3]-nRadius;
                    nZMax=pShape[3]+nRadius;
                    if(nXMin<=pPos->x && nXMax>=pPos->x &&
                        nZMin<=pPos->z && nZMax>=pPos->z &&
                        nYMin<=pPos->y && nYMax>=pPos->y &&
                        func_01ff8e94(pPos,(VecFx32 *)(pShape+1))<=nRadius) {
                        pCtx->aPlayerExitKeys[i]=pCtx->aapItems[j][k]->nKey;
                    }
                }
            }
        }
    }
    if(pCtx->aPlayerExitKeys[0]>=0) {
        for(i=0;i<func_ov022_020882f8();i++) {
            if(pCtx->aPlayerExitKeys[0]!=pCtx->aPlayerExitKeys[i]) return -1;
        }
    }
    return pCtx->aPlayerExitKeys[0];
}
