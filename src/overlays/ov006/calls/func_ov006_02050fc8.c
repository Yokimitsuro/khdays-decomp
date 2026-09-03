/* func_ov006_02050fc8 -- per-frame update of the Mission Mode member menu screen, ov006.
 *
 * Reads the cursor entry and the pad state, then bails out to the video-scene state
 * function when the menu has been confirmed or the cursor is 0xff, clearing the
 * context's parameters-ready flag on the way out.
 *
 * Otherwise it refreshes the four member rows from the mission tables, resolves the
 * selection for the cursor row, and -- while the sub-state is 5 and an entry is live --
 * runs the member-selection input pass over a saved copy of the cursor row, restoring
 * the row afterwards so only the arm-cursor request survives.
 *
 * It then decides whether the "all members ready" slot is shown: every visible row must
 * carry its ready flag, the ready count must equal the polled key count, and no two
 * visible rows may share a member id.
 *
 * After committing the title mode, model pose, slot visibility and cursor selection, the
 * sub-states 4-6 redraw the text layers: the prompt line, the resolved and cursor name
 * lines, the two label columns, the four per-slot labels and the footer prompt.
 *
 * Finally the local rows are written back to the shared context and the next state
 * function is returned (0 to stay, or the menu-state entry point after a confirm). */
typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* One mission-menu row. Eight bytes, so the ROM indexes it with `lsl #3`.
 * The same layout backs the twin loop in ov008; the offsets are what the
 * disassembly pins, the names what the uses show.
 */
typedef struct {
    u16 id;          /* +0x00  entry id                                    */
    u8 slotUsed;     /* +0x02  row occupied; gates the cues and the counter */
    u8 readyFlag;    /* +0x03  member is ready; the 0x2e / 0x2f cue pair    */
    s8 memberId;     /* +0x04  loaded signed, compared as u8 against the ctx */
    s8 sprite;       /* +0x05  not read by this function                   */
    u8 value6;       /* +0x06  not read here; named to match the Ghidra type */
    u8 pad_7;        /* +0x07  padding to the 8-byte stride                */
} MissionMenuRow;

typedef struct {
    void *sceneObject;
    u16 inputHeader[13];
    u8 pad_1e[2];
    int sessionReady;
    int parametersReady;
    int singleRowMode;
    int menuState;
    u8 optionMask;
    u8 messageStateFlag;
    u16 messageId;
    u16 messageTimer;
    u8 pad_36[2];
    u8 selection[8];   /* Ov006MissionMenuSelectionState in the Ghidra model */
    MissionMenuRow rows[4];
    u8 resource[0x0d];
    u8 rowDataReady;
} MissionMenuContext;

extern MissionMenuContext *data_ov006_02056660;
extern u16 data_0204c190;
extern u8 data_ov006_020561d0[];

extern void FS_UnloadOverlayImage_0x020362ec(void *image);
extern int func_02033b78(int bank, int sound);  /* PlaySound */
extern u16 func_ov006_0204f3ac(void);  /* Ov006_MissionGetCursorEntry */
extern int func_ov006_0204fa58(void);  /* Ov006_GetMissionMenuSelection */
extern int func_ov006_0204fa88(void);  /* Ov006_MissionPollKeys */
extern int func_ov006_0204fb50(void);
extern void func_ov006_0204fb68(int memberId);  /* Ov006_SetPendingInput */
extern void func_ov006_0204fbd0(int row, MissionMenuRow *out);  /* Ov006_GetMissionRowInfo */
extern int func_ov006_0204fc78(void);  /* Ov006_MissionIsEntryActive */
extern void func_ov006_0204fcd8(u16 *row);  /* Ov006_MissionArmCursorRequest */
extern void func_ov006_0204fef4(void);  /* Ov006_BlankScreensAndTeardownText */
extern void func_ov006_0204ff34(int selection);  /* Ov006_MissionApplyParameterRow */
extern int func_ov006_0204fffc(int memberId);  /* Ov006_ResolveMissionSelection */
extern int func_ov006_02050090(void);  /* Ov006_CanConfirmMissionMenu */
extern void func_ov006_02051878(void);
extern void func_ov006_02051884(void);  /* Ov006_MissionInitVideoScene */
extern int func_ov006_02051b34(MissionMenuRow *rows, int *resolvedSelectionOut);  /* Ov006_UpdateMissionMemberSelectionInput */
extern int func_ov006_02055924(void);
extern int func_ov006_02055950(void);
extern int func_ov006_02055998(int slot, int flag);  /* Ov006_SetTitleWord */
extern int func_ov006_02055a54(u32 state, int animate, int completion);  /* Ov006_RequestMenuState */
extern void func_ov006_02055b0c(int selection);
extern int func_ov006_02055b30(u32 mode);
extern int func_ov006_02055b70(int slot, u16 value, int visible);
extern int func_ov006_02055c38(int pose);  /* Ov002_BeginTextCrawl */
extern void func_ov006_02055e04(int visible);  /* Ov006_MissionSetSlotVisible */
extern void func_ov006_02056030(void);  /* Ov006_ResetTextLayers */
extern void *func_ov006_0204d58c(void *resource, int index);  /* GetVarRecordByIndex */
extern void func_ov006_0205606c(void *text, int x, int y, u8 style, int layer,  /* Ov006_MissionDrawTextRunFwd */
                            int align, int visible);
extern void func_ov006_02056098(void);  /* Ov006_FlushTextLayers */

void *func_ov006_02050fc8(void)
{
    MissionMenuRow rows[4];
    int resolvedSelection;
    MissionMenuRow saved;
    u8 labels[8];
    MissionMenuRow probeC;
    MissionMenuRow probeD;
    MissionMenuRow probe;
    MissionMenuRow probeB;
    MissionMenuRow probeA;
    void *result;
    int canConfirm;
    u32 cursorEntry;
    u32 pollKeys;
    u32 messageId;
    u32 allSame;
    int slotVisible;
    u8 i;
    u8 j;
    u8 count;
    u8 visibleSlot;
    int unique;
    int x;
    int y;
    int stateCode;
    int paramSel;
    void *record;
    u8 *labelsHi;
    MissionMenuRow *rowPtr;

    result = 0;
    cursorEntry = func_ov006_0204f3ac();
    pollKeys = (u32)func_ov006_0204fa88();
    allSame = 0;
    slotVisible = 0;
    resolvedSelection = 0;
    FS_UnloadOverlayImage_0x020362ec(data_ov006_02056660->inputHeader);

    if (func_ov006_02050090() != 0 || cursorEntry == 0xff) {
        func_ov006_0204fef4();
        data_ov006_02056660->rowDataReady = 0;
        return (void *)func_ov006_02051884;
    }

    i = 0;
    do {
        func_ov006_0204fbd0(i, &rows[i]);
        i++;
    } while (i < 4);

    canConfirm = func_ov006_02050090();
    resolvedSelection = func_ov006_0204fffc(rows[cursorEntry].memberId);
    if (func_ov006_02055924() != 0 && canConfirm == 0 &&
        func_ov006_02055950() == 5 && func_ov006_0204fc78() != 0) {
        saved = rows[cursorEntry];
        if (func_ov006_02051b34(rows, &resolvedSelection) != 0) {
            rows[cursorEntry].id++;
        }
        func_ov006_0204fcd8((u16 *)&rows[cursorEntry]);
        rows[cursorEntry] = saved;
    }

    if (func_ov006_02055924() != 0 &&
        data_ov006_02056660->sessionReady != 0) {
        count = 0;
        i = 0;
        do {
            func_ov006_0204fbd0(i, &probe);
            if (probe.slotUsed != 0) {
                if (probe.readyFlag == 0) {
                    allSame = 0;
                    goto have_flag;
                }
                count++;
            }
            i++;
        } while (i < 4);
        if (count != (u32)func_ov006_0204fa88()) {
            allSame = 0;
        } else {
            allSame = 1;
        }

have_flag:
        if (allSame != 0) {
            if (data_ov006_02056660->singleRowMode != 0) {
                unique = 1;
            } else {
                i = 0;
                do {
                    j = (u8)(i + 1);
                    while (j < 4) {
                        func_ov006_0204fbd0(i, &probeA);
                        func_ov006_0204fbd0(j, &probeB);
                        if (probeA.slotUsed != 0 && probeB.slotUsed != 0 &&
                            probeA.memberId == probeB.memberId) {
                            unique = 0;
                            goto have_unique;
                        }
                        j++;
                    }
                    i++;
                } while (i < 4);
                unique = 1;
            }
have_unique:
            if (unique != 0) {
                slotVisible = 1;
                if ((data_0204c190 & 8) != 0) {
                    func_ov006_0204fb68(rows[0].memberId);
                }
            }
        }
    }

    func_ov006_02055b30(pollKeys);
    func_ov006_02055c38(rows[cursorEntry].memberId);
    func_ov006_02055e04(slotVisible);
    func_ov006_02055b0c(func_ov006_0204fa58());

    if (func_ov006_02055950() == 5 &&
        (data_ov006_02056660->parametersReady == 0 ||
         rows[cursorEntry].memberId !=
             data_ov006_02056660->rows[cursorEntry].memberId)) {
        if (resolvedSelection != 0) {
            paramSel = rows[cursorEntry].memberId;
        } else {
            paramSel = 0x13;
        }
        func_ov006_0204ff34(paramSel);
    }

    /* Push the four rows to the on-screen slots and play the change cues.
     *
     * visibleSlot counts only rows that are in use, so the display packs the live
     * rows upwards while i still walks the fixed four-entry table. Each row reports
     * its occupancy first, then its member and ready state.
     *
     * The cues compare against the shared context, i.e. the state as of the previous
     * frame, so they fire once on the frame a value actually changes: cue 0 when the
     * cursor row's member changes, 0x2e when a row becomes ready and 0x2f when it
     * stops being ready. Rows that are not in use stay silent.
     */
    visibleSlot = 0;
    i = 0;
    do {
        func_ov006_02055998(visibleSlot, rows[i].slotUsed);
        rowPtr = &rows[i];
        func_ov006_02055b70(visibleSlot, rowPtr->memberId, rowPtr->readyFlag);
        if (rows[i].slotUsed != 0) {
            if (i == cursorEntry &&
                (u8)rows[i].memberId != (u8)data_ov006_02056660->rows[i].memberId) {
                func_02033b78(0, 0);
            }
            if (rows[i].readyFlag != data_ov006_02056660->rows[i].readyFlag) {
                if (rows[i].readyFlag != 0) {
                    func_02033b78(0, 0x2e);
                } else {
                    func_02033b78(0, 0x2f);
                }
            }
        }
        if (rows[i].slotUsed != 0) {
            visibleSlot++;
        }
        i++;
    } while (i < 4);

    if (func_ov006_0204fb50() == 3) {
        func_02033b78(0, 1);
        func_ov006_02055a54(7, 1, 0);
        result = (void *)func_ov006_02051878;
    }

    stateCode = func_ov006_02055950();
    if (!(stateCode != 4 && stateCode != 5 && stateCode != 6)) {
        labels[3] = data_ov006_020561d0[6];
        labels[4] = data_ov006_020561d0[7];
        labels[5] = data_ov006_020561d0[8];
        labels[6] = data_ov006_020561d0[9];
        labels[0] = data_ov006_020561d0[0];
        labels[1] = data_ov006_020561d0[1];
        labels[2] = data_ov006_020561d0[2];
        func_ov006_02056030();

        if (data_ov006_02056660->sessionReady != 0) {
            func_ov006_0204fbd0((int)cursorEntry, &probeC);
            if (probeC.readyFlag == 0 || rows[cursorEntry].readyFlag == 0) {
                messageId = 0x33;
            } else if (allSame == 0) {
                messageId = 0x34;
            } else {
                messageId = 0x37;
            }
        } else if (rows[cursorEntry].readyFlag == 0) {
            data_ov006_02056660->messageId = 0x35;
            data_ov006_02056660->messageTimer = 0;
            messageId = 0x33;
        } else {
            data_ov006_02056660->messageTimer++;
            if (data_ov006_02056660->messageTimer > 0x3c) {
                data_ov006_02056660->messageTimer = 0;
                if (data_ov006_02056660->messageId == 0x34) {
                    data_ov006_02056660->messageId = 0x35;
                } else {
                    data_ov006_02056660->messageId = 0x34;
                }
            }
            messageId = (u32)(data_ov006_02056660->messageId & 0xff);
        }

        record = func_ov006_0204d58c(data_ov006_02056660->resource, (int)messageId);
        func_ov006_0205606c(record, 0xfa, 2, 1, 1, 1, 1);

        if (resolvedSelection != 0) {
            record = func_ov006_0204d58c(data_ov006_02056660->resource,
                                     rows[func_ov006_0204f3ac()].memberId + 0xb);
        } else {
            record = func_ov006_0204d58c(data_ov006_02056660->resource, 0x1e);
        }
        func_ov006_0205606c(record, 0x26, 0x1c, 1, 1, 2, 1);

        record = func_ov006_0204d58c(data_ov006_02056660->resource,
                                 rows[func_ov006_0204f3ac()].memberId + 0x1f);
        func_ov006_0205606c(record, 0x80, 0x1c, 1, 1, 2, 1);

        i = 0;
        labelsHi = &labels[3];
        do {
            record = func_ov006_0204d58c(data_ov006_02056660->resource,
                                     labelsHi[i]);
            func_ov006_0205606c(record, 0x87, i * 0x10 + 0x38, 1, 1, 1, 1);
            i++;
        } while (i < 4);

        i = 0;
        do {
            record = func_ov006_0204d58c(data_ov006_02056660->resource,
                                     labels[i]);
            func_ov006_0205606c(record, 0xe4, i * 0x10 + 0x38, 1, 1, 1, 1);
            i++;
        } while (i < 3);

        i = 0;
        do {
            switch (i) {
            case 0:
                x = 0x44;
                y = 0x9a;
                break;
            case 1:
                x = 0xc4;
                y = 0x9a;
                break;
            case 2:
                x = 0x44;
                y = 0xb0;
                break;
            case 3:
                x = 0xc4;
                y = 0xb0;
                break;
            default:
                x = 0;
                y = 0;
                break;
            }
            if (rows[i].slotUsed != 0 || i == func_ov006_0204f3ac()) {
                if (func_ov006_0204fffc(rows[i].memberId) != 0) {
                    record = func_ov006_0204d58c(
                        data_ov006_02056660->resource,
                        rows[i].memberId + 0xb);
                } else {
                    record = func_ov006_0204d58c(
                        data_ov006_02056660->resource, 0x1e);
                }
                func_ov006_0205606c(record, x, y, 1, 1, 2, 1);
            }
            i++;
        } while (i < 4);

        if (data_ov006_02056660->sessionReady != 0) {
            func_ov006_0204fbd0((int)cursorEntry, &probeD);
            if (probeD.readyFlag == 0 || rows[cursorEntry].readyFlag == 0) {
                messageId = 0x38;
            } else if (allSame == 0) {
                messageId = 0x39;
            } else {
                messageId = 0x3a;
            }
        } else if (rows[cursorEntry].readyFlag == 0) {
            messageId = 0x38;
        } else {
            messageId = 0x39;
        }

        record = func_ov006_0204d58c(data_ov006_02056660->resource, (int)messageId);
        func_ov006_0205606c(record, 0xa, 0xb4, 1, 1, 0, 0);
        func_ov006_02056098();
    }

    i = 0;
    do {
        data_ov006_02056660->rows[i] = rows[i];
        i++;
    } while (i < 4);

    return result;
}
