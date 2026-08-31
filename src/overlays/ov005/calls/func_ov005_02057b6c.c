/* Count newly reached reward thresholds and return the last valid threshold. */
typedef unsigned char u8;
typedef struct MsgDbRecordHeader { short nSlot,nDbId; int nField04,nField08; } MsgDbRecordHeader;
typedef struct MsgDbRewardThresholdRecord { MsgDbRecordHeader header; int threshold; } MsgDbRewardThresholdRecord;
typedef struct Ov005Config { char unknown00[0x34]; int rewardBases[3]; int rewardTotals[3]; unsigned int rewardScales[3]; } Ov005Config;
extern Ov005Config data_ov005_0205b85c;
extern int func_ov005_02057b40(int,int);
extern int func_02034150(unsigned int,int);
extern int func_020342e8(MsgDbRewardThresholdRecord **,int,unsigned int,int);
extern int func_020343cc(MsgDbRewardThresholdRecord **);
extern int func_02034258(int);
u8 func_ov005_02057b6c(int *outMaximum) {
    u8 index;
    u8 previousCount;
    u8 newCount;
    int previousTotal=data_ov005_0205b85c.rewardTotals[2];
    int newTotal=data_ov005_0205b85c.rewardTotals[2]+func_ov005_02057b40(data_ov005_0205b85c.rewardBases[2],data_ov005_0205b85c.rewardScales[2]);
    int maximum;
    previousCount=0;
    newCount=0;
    func_02034150(28,14);
    maximum=0;
    for(index=0;index<100;index++) {
        MsgDbRewardThresholdRecord *record=0;
        int threshold;
        func_020342e8(&record,28,index,14);
        threshold=record->threshold;
        if(threshold<0) {func_020343cc(&record);break;}
        if(threshold<=previousTotal)previousCount++;
        if(threshold<=newTotal)newCount++;
        maximum=threshold;
        func_020343cc(&record);
    }
    func_02034258(28);
    *outMaximum=maximum;
    return newCount-previousCount;
}
