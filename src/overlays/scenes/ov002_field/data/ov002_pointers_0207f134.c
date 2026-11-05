/* ov002 .data pointer tables, 0x0207f134-0x0207f404.
 *
 * 1 table, all zero in the ROM image because every entry is a relocation;
 * a zero word is a null entry.
 */

typedef void (*Ov_Fn)(void);

extern void Ov002_ScriptCmd_EnterPhase(void);
extern void Ov002_ScriptCmd_DispatchStateEnter(void);
extern void Ov002_ScriptCmd_SetSessionActive(void);
extern void Ov002_ScriptPostLinkMessage(void);
extern void Ov002_ScriptOpSetFlagInverted(void);
extern void Ov002_ScriptQueueTextItem(void);
extern void Ov002_ScriptAwardAndShow(void);
extern void Ov002_SubmitRequestBlockKind1(void);
extern void Ov002_ScriptSubmitPathTask(void);
extern void Ov002_ScriptSubmitTaskNode(void);
extern void Ov002_ScriptCmd_AdvanceRosterSetup(void);
extern void Ov002_ScriptCmd_WaitRosterSetup(void);
extern void Ov002_ScriptPlaceSlot(void);
extern void Ov002_ScriptMoveSlot(void);
extern void Ov002_ScriptCmd_CreateFieldContext(void);
extern void Ov002_ScriptCmd_RecreateObjectSlot(void);
extern void Ov002_ScriptOpInvokeWithFlag(void);
extern void Ov002_StartFieldEffect(void);
extern void Ov002_IsRequestForUs(void);
extern void Ov002_ScriptCmd_SnapshotPausedObject(void);
extern void Ov002_ScriptCmd_SkipIntOperand(void);
extern void Ov002_ScriptCmd_SetWorldByte8D68(void);
extern void Ov002_ScriptOpScaleAndPublish(void);
extern void Ov002_ScriptCmd_LoadWorldLinkResources(void);
extern void Ov002_ScriptCmd_LoadPeerIntoSlot(void);
extern void Ov002_ScriptCmd_SetSessionIdle(void);
extern void Ov002_ScriptCmd_ThreeOperandStub(void);
extern void Ov002_ScriptCmd_RestorePanel(void);
extern void Ov002_ScriptCmd_LoadObjectRecords(void);
extern void Ov002_ScriptCreateSpawner(void);
extern void Ov002_SubmitRequestBlockKind4(void);
extern void Ov002_ResolveFourDescriptors(void);
extern void Ov002_ScriptCmd_InitObjectTables(void);
extern void Ov002_ScriptBuildBindingPayload(void);
extern void Ov002_ScriptOpInvokeSlot0(void);
extern void Ov002_ScriptDriveFourOperands(void);
extern void Ov002_ScriptCmd_SetGlobalFlagOnce(void);
extern void Ov002_ScriptCmd_SetWorldByte8C9C(void);
extern void Ov002_SubmitRequestBlock(void);
extern void Ov002_ConstReturn1(void);
extern void Ov002_ConstReturn1_2(void);
extern void Ov002_ScriptCmd_AppendPendingId(void);
extern void Ov002_ScriptCmd_BuildKeyEntryTable(void);
extern void Ov002_ScriptCmd_UpdateSlotLookup(void);
extern void Ov002_ScriptCmd_CreateActorFromMarker(void);
extern void Ov002_ScriptCmd_BuildSceneIdTable(void);
extern void Ov002_ScriptCmd_SkipIntOperand_2(void);
extern void Ov002_BuildEntryList(void);
extern void Ov002_ScriptCmd_SetWorldSlotPair(void);
extern void Ov002_ScriptCmdAimRosterSlots(void);
extern void Ov002_CmdSetRowValues(void);
extern void Ov002_ScriptCmd_AddMissionMember(void);
extern void Ov002_ScriptCmd_ArmPartyReset(void);
extern void Ov002_ScriptDriveWithModeHalfword(void);
extern void Ov002_ScriptOpDispatchHalfWord(void);
extern void Ov002_ScriptCmd_SetWorldFlagByte(void);
extern void Ov002_ApplyRequestBlock(void);
extern void Ov002_FinishRequest(void);
extern void Ov002_ScriptCmd_WaitPanelPose(void);
extern void Ov002_ScriptOpenChoicePanel(void);
extern void Ov002_ConfirmMission(void);
extern void Ov002_IsActivePanelIdle(void);
extern void Ov002_ScriptCmd_SetWorldByte8BAD(void);
extern void Ov002_ScriptCmd_UpdateRatePanelIfFlag(void);
extern void Ov002_ScriptCmd_PostCrawlScoreLine(void);
extern void Ov002_ScriptCmd_SetPendingText(void);
extern void Ov002_ScriptCmd_SetEventParams(void);
extern void Ov002_ScriptCmd_EditSessionClock(void);
extern void Ov002_ScriptCmd_SetWorldHalf8D5C(void);
extern void Ov002_ScriptCmd_ThreeMixedOperands(void);
extern void Ov002_ScriptOpApplyValueA(void);
extern void Ov002_ScriptCmd_SetGlobalByte1F(void);
extern void Ov002_CmdApplyOperandList(void);
extern void Ov002_ScriptCmd_WaitCaptionSequence(void);
extern void Ov002_ScriptWalkPath(void);
extern void Ov002_ScriptCmd_SpawnStateSpot(void);
extern void Ov002_ConstReturn1_3(void);
extern void Ov002_ScriptCmd_SweepSharedMarker(void);
extern void Ov002_ScriptOpApplyValueB(void);
extern void Ov002_ScriptCmd_ResetTracks(void);
extern void Ov002_ScriptCmd_SetLinkMode(void);
extern void Ov002_ScriptSpawnAtPoint(void);

Ov_Fn data_ov002_0207f134[180] = {

    Ov002_ScriptCmd_EnterPhase,

    0,

    Ov002_ScriptCmd_DispatchStateEnter,

    0,

    Ov002_ScriptCmd_SetSessionActive,

    0,

    Ov002_ScriptPostLinkMessage,

    0,

    Ov002_ScriptOpSetFlagInverted,

    0,

    Ov002_ScriptQueueTextItem,

    0,

    Ov002_ScriptAwardAndShow,

    0,

    Ov002_SubmitRequestBlockKind1,

    0,

    Ov002_ScriptSubmitPathTask,

    0,

    Ov002_ScriptSubmitTaskNode,

    0,

    Ov002_ScriptCmd_AdvanceRosterSetup,

    Ov002_ScriptCmd_WaitRosterSetup,

    Ov002_ScriptPlaceSlot,

    0,

    Ov002_ScriptMoveSlot,

    0,

    Ov002_ScriptCmd_CreateFieldContext,

    0,

    Ov002_ScriptCmd_RecreateObjectSlot,

    0,

    Ov002_ScriptOpInvokeWithFlag,

    0,

    Ov002_StartFieldEffect,

    0,

    Ov002_IsRequestForUs,

    0,

    0,

    0,

    0,

    0,

    Ov002_ScriptCmd_SnapshotPausedObject,

    0,

    Ov002_ScriptCmd_SkipIntOperand,

    0,

    0,

    0,

    Ov002_ScriptCmd_SetWorldByte8D68,

    0,

    0,

    0,

    Ov002_ScriptCmd_LoadWorldLinkResources,

    0,

    Ov002_ScriptCmd_LoadPeerIntoSlot,

    0,

    Ov002_ScriptCmd_SetSessionIdle,

    0,

    Ov002_ScriptCmd_ThreeOperandStub,

    0,

    Ov002_ScriptCmd_RestorePanel,

    0,

    0,

    0,

    Ov002_ScriptCmd_LoadObjectRecords,

    0,

    Ov002_ScriptCreateSpawner,

    0,

    Ov002_SubmitRequestBlockKind4,

    0,

    Ov002_ResolveFourDescriptors,

    0,

    0,

    0,

    Ov002_ScriptCmd_InitObjectTables,

    0,

    Ov002_ScriptBuildBindingPayload,

    0,

    Ov002_ScriptOpInvokeSlot0,

    0,

    Ov002_ScriptDriveFourOperands,

    0,

    Ov002_ScriptCmd_SetGlobalFlagOnce,

    0,

    Ov002_ScriptCmd_SetWorldByte8C9C,

    0,

    Ov002_SubmitRequestBlock,

    0,

    Ov002_ConstReturn1,

    0,

    Ov002_ConstReturn1_2,

    0,

    Ov002_ScriptCmd_AppendPendingId,

    0,

    Ov002_ScriptCmd_BuildKeyEntryTable,

    0,

    0,

    0,

    Ov002_ScriptCmd_UpdateSlotLookup,

    0,

    Ov002_ScriptCmd_CreateActorFromMarker,

    0,

    Ov002_ScriptCmd_BuildSceneIdTable,

    0,

    Ov002_ScriptCmd_SkipIntOperand_2,

    0,

    Ov002_BuildEntryList,

    0,

    Ov002_ScriptCmd_SetWorldSlotPair,

    0,

    Ov002_ScriptCmdAimRosterSlots,

    0,

    Ov002_CmdSetRowValues,

    0,

    Ov002_ScriptCmd_AddMissionMember,

    0,

    Ov002_ScriptCmd_ArmPartyReset,

    0,

    Ov002_ScriptDriveWithModeHalfword,

    0,

    Ov002_ScriptOpDispatchHalfWord,

    0,

    0,

    0,

    Ov002_ScriptCmd_SetWorldFlagByte,

    0,

    Ov002_ApplyRequestBlock,

    0,

    Ov002_FinishRequest,

    Ov002_ScriptCmd_WaitPanelPose,

    Ov002_ScriptOpenChoicePanel,

    Ov002_ConfirmMission,

    Ov002_IsActivePanelIdle,

    0,

    Ov002_ScriptCmd_SetWorldByte8BAD,

    0,

    Ov002_ScriptOpScaleAndPublish,

    0,

    Ov002_ScriptCmd_UpdateRatePanelIfFlag,

    0,

    Ov002_ScriptCmd_PostCrawlScoreLine,

    0,

    0,

    0,

    0,

    0,

    Ov002_ScriptCmd_SetPendingText,

    0,

    Ov002_ScriptCmd_SetEventParams,

    0,

    Ov002_ScriptCmd_EditSessionClock,

    0,

    Ov002_ScriptCmd_SetWorldHalf8D5C,

    0,

    Ov002_ScriptCmd_ThreeMixedOperands,

    0,

    Ov002_ScriptOpApplyValueA,

    0,

    Ov002_ScriptCmd_SetGlobalByte1F,

    0,

    Ov002_CmdApplyOperandList,

    Ov002_ScriptCmd_WaitCaptionSequence,

    0,

    0,

    0,

    0,

    Ov002_ScriptWalkPath,

    0,

    Ov002_ScriptCmd_SpawnStateSpot,

    0,

    Ov002_ConstReturn1_3,

    0,

    Ov002_ScriptCmd_SweepSharedMarker,

    0,

    Ov002_ScriptOpApplyValueB,

    0,

    Ov002_ScriptCmd_ResetTracks,

    0,

    Ov002_ScriptCmd_SetLinkMode,

    0,

    Ov002_ScriptSpawnAtPoint,

    0,

};
