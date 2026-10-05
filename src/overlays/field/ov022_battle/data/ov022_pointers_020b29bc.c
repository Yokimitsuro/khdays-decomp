/* ov022 .data pointer tables, 0x020b29bc-0x020b2b1c.
 *
 * 7 tables, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

extern void Ov022_StepAimedPart(void);
extern void Ov022_StepHomingPart(void);
extern void Ov022_StepPartStrike(void);
extern void func_ov022_0208b1c8(void);
extern void Ov022_LaunchSlotPart(void);
extern void Ov022_TickEntrySubObjects(void);
extern void func_ov022_0208bb38(void);
extern void func_ov022_0208bb98(void);
extern void func_ov022_0208bbe4(void);
extern void Ov022_CreateSlotKind00(void);
extern void Ov022_CreateSlotKind01(void);
extern void Ov022_CreateSlotKind02(void);
extern void Ov022_LaunchSlotPartArc(void);
extern void Ov022_StepSlotPartsD(void);
extern void Ov022_CreateSlotKind03(void);
extern void Ov022_EnterReactionAlongFacing(void);
extern void Ov022_StepSlotPartsC(void);
extern void Ov022_CreateSlotKind05(void);
extern void Ov022_EnterReactionAtOffset(void);
extern void Ov022_StepSlotByState(void);
extern void func_ov022_0208cb9c(void);
extern void Ov022_CreateSlotKind04(void);
extern void Ov022_LaunchSlotPartTracked(void);
extern void Ov022_StepSlotPartsB(void);
extern void Ov022_CreateSlotKind09(void);
extern void Ov022_CreateSlotKind0a(void);
extern void Ov022_LaunchSlotPartFlat(void);
extern void Ov022_StepSlotParts(void);
extern void Ov022_CreateReactionSlot(void);
extern void Ov022_EnterReactionAtActor(void);
extern void Ov022_StepSlotBeats(void);
extern void Ov022_UpdateTracks23ByFlag(void);
extern void Ov022_CreateSlotKind06(void);
extern void Ov022_ArmSlotAtActor(void);
extern void Ov022_StepSlotPartsAndArm(void);
extern void Ov022_RestartEntryParts(void);
extern void Ov022_StepSpawnPart(void);
extern void Ov022_CreateSlotKind07(void);
extern void Ov022_EnterChainReaction(void);
extern void Ov022_CreateSlotKind08(void);
extern void Ov022_EnterGroundReaction(void);
extern void Ov022_StepSlotByPartState(void);
extern void Ov022_CreateSlotKind0c(void);
extern void Ov022_CreateSlotKind0d(void);
extern void Ov022_CreateSlotKind0e(void);
extern void Ov022_EnterBlockReaction(void);
extern void Ov022_StepChargeSlot(void);
extern void Ov022_UpdateTrack10ByFlag(void);
extern void func_ov022_0208fdf8(void);
extern void Ov022_StepReaction(void);
extern void func_ov022_02090070(void);
extern void Ov022_VeneerTo_Ov022_LaunchSlotPart(void);
extern void Ov022_VeneerTo_Ov022_EnterBlockReaction(void);

void *data_ov022_020b29bc[5] = {

    0,

    (void *)Ov022_StepAimedPart,

    (void *)Ov022_StepHomingPart,

    (void *)Ov022_StepPartStrike,

    (void *)func_ov022_0208b1c8,

};

void *data_ov022_020b29d0[5] = {

    0,

    0,

    (void *)Ov022_StepSpawnPart,

    (void *)Ov022_StepPartStrike,

    (void *)func_ov022_0208b1c8,

};

void *data_ov022_020b29e4[15] = {

    (void *)Ov022_CreateSlotKind00,

    (void *)Ov022_CreateSlotKind01,

    (void *)Ov022_CreateSlotKind02,

    (void *)Ov022_CreateSlotKind03,

    (void *)Ov022_CreateSlotKind04,

    (void *)Ov022_CreateSlotKind05,

    (void *)Ov022_CreateSlotKind06,

    (void *)Ov022_CreateSlotKind07,

    (void *)Ov022_CreateSlotKind08,

    (void *)Ov022_CreateSlotKind09,

    (void *)Ov022_CreateSlotKind0a,

    (void *)Ov022_CreateReactionSlot,

    (void *)Ov022_CreateSlotKind0c,

    (void *)Ov022_CreateSlotKind0d,

    (void *)Ov022_CreateSlotKind0e,

};

void *data_ov022_020b2a20[15] = {

    (void *)Ov022_LaunchSlotPart,

    (void *)Ov022_LaunchSlotPart,

    (void *)Ov022_LaunchSlotPartArc,

    (void *)Ov022_EnterReactionAlongFacing,

    (void *)Ov022_LaunchSlotPartTracked,

    (void *)Ov022_EnterReactionAtOffset,

    (void *)Ov022_ArmSlotAtActor,

    (void *)Ov022_EnterChainReaction,

    (void *)Ov022_EnterGroundReaction,

    &Ov022_VeneerTo_Ov022_LaunchSlotPart,

    (void *)Ov022_LaunchSlotPartFlat,

    (void *)Ov022_EnterReactionAtActor,

    (void *)Ov022_EnterBlockReaction,

    &Ov022_VeneerTo_Ov022_EnterBlockReaction,

    (void *)func_ov022_0208fdf8,

};

void *data_ov022_020b2a5c[15] = {

    (void *)Ov022_TickEntrySubObjects,

    (void *)Ov022_TickEntrySubObjects,

    (void *)Ov022_StepSlotPartsD,

    (void *)Ov022_StepSlotPartsC,

    (void *)Ov022_StepSlotPartsB,

    (void *)Ov022_StepSlotByState,

    (void *)Ov022_StepSlotPartsAndArm,

    (void *)Ov022_StepSlotPartsAndArm,

    (void *)Ov022_StepSlotByPartState,

    (void *)Ov022_TickEntrySubObjects,

    (void *)Ov022_StepSlotParts,

    (void *)Ov022_StepSlotBeats,

    (void *)Ov022_StepChargeSlot,

    (void *)Ov022_StepChargeSlot,

    (void *)Ov022_StepReaction,

};

void *data_ov022_020b2a98[15] = {

    (void *)func_ov022_0208bb38,

    (void *)func_ov022_0208bb38,

    (void *)func_ov022_0208bb38,

    (void *)func_ov022_0208bbe4,

    (void *)func_ov022_0208bbe4,

    (void *)func_ov022_0208cb9c,

    (void *)Ov022_RestartEntryParts,

    (void *)Ov022_RestartEntryParts,

    (void *)func_ov022_0208bb38,

    (void *)func_ov022_0208bb38,

    (void *)func_ov022_0208bbe4,

    (void *)Ov022_UpdateTracks23ByFlag,

    (void *)func_ov022_02090070,

    (void *)Ov022_UpdateTrack10ByFlag,

    (void *)func_ov022_02090070,

};

void *data_ov022_020b2ad4[18] = {

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    0,

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    (void *)func_ov022_0208bb98,

    0,

    0,

    0,

    0,

    0,

    0,

    0,

};
