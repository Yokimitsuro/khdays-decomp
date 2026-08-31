/* Assemble result-screen values, records, ranks and reward factors. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;
typedef struct PlayerItemLimit { u16 itemId; short limit; } PlayerItemLimit;
typedef struct Ov002ResultTally {u16 wId;short nCount;} Ov002ResultTally;
typedef struct Ov002DayClock {u8 nModeFlags,nArmedKind;u16 nMinutes,nMinutesElapsed;u8 missionMask,pad7;} Ov002DayClock;
typedef struct Ov002MissionResult {
    u16 wPanelTotal; signed char bRequestId; char pad3; short nRequestParam; char pad6[2];
    int nValue,nDuration,nScaled,nRaw;u64 nStampTicks;
    u8 bFlags,pad21,nMemberMask,rewardMultiplier;
    short aMemberValues[4];Ov002ResultTally aTally[18];
} Ov002MissionResult;
typedef struct Ov002PanelThresholds {char unknown00[14];u16 nMetric;u32 aThresh[3];} Ov002PanelThresholds;
typedef struct Ov002SessionBoard {char unknown00[0x4d];u8 nLocalRankGroup;} Ov002SessionBoard;
typedef struct Ov005Config {
    u16 sceneId,missionIndex;u16 *resultTitle;signed char requestId;char pad9;u16 resultLabelIndex,rewardMode;char pade[2];
    int resultRank,specialQuantity;u32 rankThresholds[4];int missionResultValue,updateMissionRecord,missionTargetValue;
    int rewardBases[3],rewardTotals[3];u32 rewardScales[3];int maximumRewardTotal;u8 bMode,pad5d[3];
    PlayerItemLimit *itemQuantities;int nOption64;u8 rewardMultiplier,specialItemMask;short specialQuantities[4];
} Ov005Config;
typedef struct Ov005MissionListConfig {char *path;int option,recordKind;} Ov005MissionListConfig;
typedef struct Ov005MissionListManager {char opaque[36];} Ov005MissionListManager;
typedef struct Ov005MissionListEntry {
    u16 sceneId,missionIndex,labelIndex;char unknown06[18];u32 modeMask;char unknown1c[32];u16 *title;
} Ov005MissionListEntry;
typedef struct Ov005MissionAward {short missionIndex,quantity;} Ov005MissionAward;
typedef struct GameState {char unknown00[4];int rewardTotal04,rewardTotal08,rewardTotal0c;char unknown10[0x197c];u32 missionResultRecords[200];} GameState;
typedef struct MsgDbRecordHeader {short nSlot,nDbId;int nField04,nField08;} MsgDbRecordHeader;
typedef struct RewardRecord {MsgDbRecordHeader header;int recordId,missionId;u32 scaleReward0c,scaleReward04,scaleReward08,items[5],weightedTables[5];} RewardRecord;
extern Ov002DayClock data_0204c240;
extern u16 data_0204c23c;
extern Ov002MissionResult data_0204c32c;
extern Ov002PanelThresholds data_0204c254;
extern Ov002SessionBoard data_0204c300;
extern GameState *data_0204be18;
extern Ov005Config data_ov005_0205b85c;
extern const Ov005MissionListConfig data_ov005_0205b3b0;
extern Ov005MissionListManager data_ov005_0205b814,data_ov005_0205b838;
extern u16 data_ov005_0205b75c[];
extern const Ov005MissionAward data_ov005_0205b620[];
extern void func_ov005_0204ec90(Ov005MissionListManager *,Ov005MissionListConfig *);
extern Ov005MissionListEntry *func_ov005_0204ed20(Ov005MissionListManager *,Ov005MissionListEntry *);
extern Ov005MissionListEntry *func_ov005_0204ed5c(Ov005MissionListManager *,int);
extern void MIi_CpuCopy16(const void *,void *,u32);
extern u64 func_02020368(u64,u64);
extern u32 func_020235d0(u32,u32);
extern int func_020342e8(RewardRecord **,int,u32,int);
extern int func_020343cc(RewardRecord **);
extern u8 func_ov005_02057b6c(int *);
void func_ov005_02057c48(void) {
    Ov005MissionListEntry *sceneEntry;
    Ov005Config *config=&data_ov005_0205b85c;
    Ov002MissionResult *result;
    Ov002PanelThresholds *thresholds;
    Ov005MissionListEntry *missionEntry;
    int index;
    u8 flags=data_0204c240.nModeFlags;
    u16 missionIndex=data_0204c23c;
    Ov005MissionListConfig listConfig;
    config->sceneId=data_0204c240.nMinutes;
    listConfig=data_ov005_0205b3b0;
    config->missionIndex=missionIndex;
    missionEntry=0;
    result=&data_0204c32c;
    thresholds=&data_0204c254;
    if(flags==0) {
        switch((int)config->sceneId) {
        case 5:config->missionIndex=4;break;
        case 6:config->missionIndex=5;break;
        case 4:config->missionIndex=6;break;
        case 108:config->missionIndex=37;break;
        case 111:config->missionIndex=74;break;
        case 1300:config->missionIndex=91;break;
        case 114:config->missionIndex=92;break;
        case 1301:config->missionIndex=93;break;
        default:if(config->sceneId>=1 && config->sceneId<=6)config->missionIndex=config->sceneId;break;
        }
    }
    if(data_0204c240.nModeFlags&2) {
        listConfig.recordKind=6;
        func_ov005_0204ec90(&data_ov005_0205b814,&listConfig);
        missionEntry=func_ov005_0204ed20(&data_ov005_0205b814,0);
        while(missionEntry) {
            if(missionEntry->missionIndex==config->missionIndex && (missionEntry->modeMask&data_0204c240.missionMask))break;
            missionEntry=func_ov005_0204ed20(&data_ov005_0205b814,missionEntry);
        }
    }
    listConfig.recordKind=5;
    func_ov005_0204ec90(&data_ov005_0205b838,&listConfig);
    sceneEntry=func_ov005_0204ed5c(&data_ov005_0205b838,data_0204c240.nMinutes);
    config->itemQuantities=(PlayerItemLimit *)result->aTally;
    config->nOption64=(result->bFlags&1)!=0;
    config->specialItemMask=result->nMemberMask;
    MIi_CpuCopy16(result->aMemberValues,config->specialQuantities,8);
    config->rewardMultiplier=(data_0204c240.nModeFlags&2)?1:result->rewardMultiplier;
    if(sceneEntry) {config->resultTitle=sceneEntry->title;config->resultLabelIndex=sceneEntry->labelIndex;}
    else if(missionEntry && missionEntry->title) {config->resultTitle=missionEntry->title;config->resultLabelIndex=missionEntry->labelIndex;}
    else {config->resultTitle=data_ov005_0205b75c;config->resultLabelIndex=0;}
    config->requestId=result->bRequestId;
    if(data_0204c240.nModeFlags&4)config->rewardMode=8;
    else config->rewardMode=(data_0204c240.nModeFlags&2)?thresholds->nMetric:255;
    config->missionTargetValue=result->nValue;
    if(config->rewardMode==255) {
        config->rankThresholds[0]=result->nValue;
        config->rankThresholds[1]=result->nRequestParam;
        config->rankThresholds[2]=result->nRequestParam;
    } else {
        config->rankThresholds[0]=thresholds->aThresh[0];
        config->rankThresholds[1]=thresholds->aThresh[1];
        config->rankThresholds[2]=thresholds->aThresh[2];
    }
    switch((int)config->rewardMode) {
    case 2:case 4:case 5:case 6:case 7:case 8:case 255:config->missionResultValue=result->nDuration;break;
    case 0:config->missionResultValue=func_02020368(result->nStampTicks<<6,0x82ea);break;
    case 1:config->missionResultValue=(short)result->wPanelTotal;break;
    case 3:config->missionResultValue=result->nRaw;break;
    }
    config->resultRank=-1;
    config->updateMissionRecord=0;
    if(!config->nOption64) {
        switch((int)config->rewardMode) {
        case 1:case 2:case 3:case 255:
            for(index=0;index<4;index++) {
                if(config->rankThresholds[index]<=(u32)config->missionResultValue) {config->resultRank=index;break;}
            }
            if(config->rewardMode!=255 && (data_0204be18->missionResultRecords[config->missionIndex]==-1 || data_0204be18->missionResultRecords[config->missionIndex]<(u32)config->missionResultValue))config->updateMissionRecord=1;
            break;
        case 8:
            if((data_0204c240.nModeFlags&12)==4)config->resultRank=data_0204c300.nLocalRankGroup;
            else config->resultRank=0;
            break;
        case 0:
            for(index=0;index<4;index++) {
                if(config->rankThresholds[index]>=(u32)config->missionResultValue/10) {config->resultRank=index;break;}
            }
            if(data_0204be18->missionResultRecords[config->missionIndex]==-1 || data_0204be18->missionResultRecords[config->missionIndex]>(u32)config->missionResultValue)config->updateMissionRecord=1;
            break;
        default:
            for(index=0;index<4;index++) {
                if(config->rankThresholds[index]>=(u32)config->missionResultValue) {config->resultRank=index;break;}
            }
            if(data_0204be18->missionResultRecords[config->missionIndex]==-1 || data_0204be18->missionResultRecords[config->missionIndex]>(u32)config->missionResultValue)config->updateMissionRecord=1;
            break;
        }
    }
    config->specialQuantity=0;
    if(!config->nOption64) {
        if(config->rewardMode==8) {
            if(config->resultRank==0) {
                config->specialQuantity=1;
                if(func_020235d0(config->missionIndex*3+0x2ca4,3)<4) {
                    const Ov005MissionAward *award=data_ov005_0205b620;
                    while(award->missionIndex>=0) {
                        if(award->missionIndex==config->missionIndex) {config->specialQuantity=award->quantity;break;}
                        award++;
                    }
                }
            }
        } else if(config->resultRank>=0 && config->resultRank<=2 && func_020235d0(config->missionIndex*3+0x2a4c,3)<(u32)(3-config->resultRank)) {
            config->specialQuantity=3-config->resultRank-func_020235d0(config->missionIndex*3+0x2a4c,3);
        }
    }
    config->rewardBases[0]=(short)result->wPanelTotal;
    config->rewardBases[1]=result->nRaw;
    config->rewardBases[2]=result->nScaled;
    config->rewardTotals[0]=data_0204be18->rewardTotal0c;
    config->rewardTotals[1]=data_0204be18->rewardTotal08;
    config->rewardTotals[2]=data_0204be18->rewardTotal04;
    for(index=0;index<103;index++) {
        RewardRecord *record=0;
        func_020342e8(&record,25,index,14);
        if(record && record->missionId==config->sceneId) {
            config->rewardScales[0]=record->scaleReward0c;
            config->rewardScales[1]=record->scaleReward08;
            config->rewardScales[2]=record->scaleReward04;
            func_020343cc(&record);
            break;
        }
        func_020343cc(&record);
    }
    for(index=0;index<3;index++)if(config->rewardScales[index]==0)config->rewardScales[index]=0x1000;
    config->bMode=func_ov005_02057b6c(&config->maximumRewardTotal);
    if((u32)(config->rewardTotals[2]+config->rewardBases[2])>(u32)config->maximumRewardTotal)config->rewardBases[2]=config->maximumRewardTotal-config->rewardTotals[2];
}
