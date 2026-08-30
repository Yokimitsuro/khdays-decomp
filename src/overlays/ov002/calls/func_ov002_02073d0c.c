/* Ov002_CreateActorFromMarker: initialize a marker actor and its record properties. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef struct VecFx32 {int x,y,z;} VecFx32;
typedef struct ActorFlags40 {int pad:1;int bActive:1;} ActorFlags40;
typedef struct Actor Actor;
struct Actor {
    char pad0[0xc];void (*pfnHandler0c)(Actor *,int);char pad10[0x30];
    ActorFlags40 flags40;char pad44[0x15b];u8 nMarkerBoost;char pad1a0[14];u16 wFlags1ae;
    char pad1b0[0x3c];void (*pSetHeight)(Actor *,int);void (*pActivate)(Actor *,int);
    char pad1f4[0x2c];int nMarkerValue;char pad224[0xd0];u32 nMarkerOverride;int nMarkerParam;
};
typedef struct Ov002MarkerRow {u8 bId,nKinds,nBoost,nProfile;s8 nHeightAdjustment,nParam;short nActorValue,nActorParam;char padA[6];} Ov002MarkerRow;
typedef struct Ov002RecordList {u8 nRowCount,nEntryCount;char pad2[2];Ov002MarkerRow *pRows;} Ov002RecordList;
typedef struct Ov002MarkerOverride {u32 nId,nValue;} Ov002MarkerOverride;
typedef struct Ov002ObjectContext {void *pOwnedTable;Ov002RecordList *pEntryList;char pad8[0x14];void *aSources[8];short aMarkerIds[4];char pad44[0x58];Ov002MarkerOverride aMarkerOverrides[5];} Ov002ObjectContext;
extern Ov002ObjectContext *data_ov002_0207fa14;
extern VecFx32 data_02041dc8;
extern void func_ov002_02072b58(void);
extern Actor *func_ov107_020c2ea8(int);
extern void func_ov107_020c5c54(Actor *,VecFx32 *);
extern void func_ov107_020c2b20(void *,Actor *);
extern int func_ov002_0206b84c(void);
extern int func_ov002_02072bcc(Ov002MarkerRow *);
extern void func_ov107_020c8958(Actor *,u32);
extern void *func_ov002_02072ba8(int);
extern void func_ov015_02081284(void *,Actor *);
void func_ov002_02073d0c(int nSourceIndex,int nRowIndex)
{
    Ov002ObjectContext *pCtx=data_ov002_0207fa14;
    Ov002MarkerRow *pRow=&pCtx->pEntryList->pRows[nRowIndex];
    Actor *pActor;
    int i;
    for(i=0;i<4;i++){
        if(pRow->bId==pCtx->aMarkerIds[i])break;
        if(pCtx->aMarkerIds[i]==-1){
            pCtx->aMarkerIds[i]=pRow->bId;
            switch(pRow->bId){
            case 0x46:pCtx->aMarkerIds[i+1]=0;break;
            case 0x62:pCtx->aMarkerIds[i+1]=0x56;break;
            case 0x47:pCtx->aMarkerIds[i+1]=4;break;
            case 0x4d:pCtx->aMarkerIds[i+1]=0x69;pCtx->aMarkerIds[i+2]=0x6a;break;
            case 0x21:pCtx->aMarkerIds[i+1]=2;break;
            case 0x53:case 0x54:case 0x68:case 0x71:case 0x72:func_ov002_02072b58();break;
            }
            break;
        }
    }
    pActor=func_ov107_020c2ea8(pRow->bId);
    pActor->wFlags1ae|=0x80;
    func_ov107_020c5c54(pActor,&data_02041dc8);
    func_ov107_020c2b20(pCtx->aSources[nSourceIndex],pActor);
    if(func_ov002_0206b84c()!=2000){
        int nHeight=func_ov002_02072bcc(pRow);
        if(pActor->pSetHeight)pActor->pSetHeight(pActor,nHeight);
        if(pRow->nParam>0 && pActor->pActivate)pActor->pActivate(pActor,pRow->nParam);
    }
    if(pRow->nBoost){
        int nBoost=pRow->nBoost+pActor->nMarkerBoost;
        pActor->nMarkerBoost=nBoost>255?255:nBoost<0?0:(u8)nBoost;
    }
    pActor->nMarkerValue=pRow->nActorValue;
    pActor->nMarkerParam=pRow->nActorParam;
    func_ov107_020c8958(pActor,pRow->nProfile);
    for(i=0;i<5;i++){
        if(pRow->bId==pCtx->aMarkerOverrides[i].nId){pActor->nMarkerOverride=pCtx->aMarkerOverrides[i].nValue;break;}
    }
    if(pRow->bId==0x55){
        void *pSibling=func_ov002_02072ba8(nSourceIndex);
        func_ov015_02081284(pSibling,pActor);
        if(pActor->flags40.bActive && pActor->pfnHandler0c)pActor->pfnHandler0c(pActor,0);
    }
}
