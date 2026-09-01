typedef signed char s8;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u16 id;
    u8 flags2;
    u8 flags3;
    s8 icon;
    s8 sprite;
    u8 field6;
    u8 pad7;
} MissionMenuRow;

typedef struct {
    int row;
    int column;
} MissionGridPosition;

typedef struct {
    void *sceneObject;
    u16 inputHeader[13];
} MissionMenuContext;

extern MissionMenuRow data_ov006_020561d0;
extern u32 data_ov006_020563f8[6];
extern int data_ov006_02056410[2][12];
extern MissionGridPosition data_ov006_02056470[6];
extern u16 data_0204c18c;
extern MissionMenuContext *data_ov006_02056660;
extern u16 data_0204c190;

extern u16 func_ov006_0204f3ac(void);
extern int func_ov006_0204fffc(int selection);
extern int func_ov006_02055970(u32 selection);
extern u16 func_020362fc(u16 *value);
extern int func_ov006_02050034(int selection, MissionMenuRow *members);
extern u32 func_ov006_0204fbb4(void);

int func_ov006_02051b34(
    MissionMenuRow *members,
    int *resolvedSelectionOut,
    int unusedR2,
    int unusedR3)
{
    u8 occupiedSelections[4];
    u16 directionInput;
    u16 cursorEntry;
    int resolvedSelection;
    u32 i;
    int gridRow;
    int gridColumn;
    u8 selectionIndex;
    u8 scanColumn;
    u8 occupiedCount;
    int action;
    int candidateSelection;
    int targetRow;
    u32 *selectionIds;
    MissionGridPosition *gridPositions;

    cursorEntry = func_ov006_0204f3ac();
    selectionIds = data_ov006_020563f8;
    gridPositions = data_ov006_02056470;
    gridRow = 0;
    occupiedSelections[0] = data_ov006_020561d0.flags3;
    occupiedSelections[1] = ((u8 *)&data_ov006_020561d0)[4];
    occupiedSelections[2] = ((u8 *)&data_ov006_020561d0)[5];
    gridColumn = 0;
    i = 0;
    selectionIndex = cursorEntry & 0xff;
    action = -1;

    do {
        resolvedSelection = func_ov006_0204fffc(selectionIds[i]);
        if (resolvedSelection != 0) {
            resolvedSelection =
                func_ov006_02055970(selectionIds[i] & 0xffff);
            data_ov006_02056410[
                gridPositions[resolvedSelection].row][
                gridPositions[resolvedSelection].column] =
                    selectionIds[i];
        }
        i = (i + 1) & 0xff;
    } while (i < 6);

    if (members[selectionIndex].flags3 == 0) {
        directionInput = data_0204c18c;
        if ((directionInput & 0x40) != 0) {
            directionInput = func_020362fc(data_ov006_02056660->inputHeader);
            if ((directionInput & 0x40) != 0) {
                action = 0;
            }
        } else if ((directionInput & 0x80) != 0) {
            directionInput = func_020362fc(data_ov006_02056660->inputHeader);
            if ((directionInput & 0x80) != 0) {
                action = 1;
            }
        } else if ((directionInput & 0x10) != 0) {
            directionInput = func_020362fc(data_ov006_02056660->inputHeader);
            if ((directionInput & 0x10) != 0) {
                action = 2;
            }
        } else if ((directionInput & 0x20) != 0) {
            directionInput = func_020362fc(data_ov006_02056660->inputHeader);
            if ((directionInput & 0x20) != 0) {
                action = 3;
            }
        }
    }

    if ((data_0204c190 & 2) != 0) {
        action = 5;
    }
    if ((data_0204c190 & 1) != 0) {
        action = 4;
    }

    if (members[selectionIndex].icon < 0) {
        members[selectionIndex].icon = 0;
    }
    if (members[selectionIndex].icon >= 19) {
        members[selectionIndex].icon = 18;
    }

    i = 0;
    do {
        scanColumn = 0;
        do {
            if (members[selectionIndex].icon ==
                data_ov006_02056410[i][scanColumn]) {
                gridColumn = (s8)scanColumn;
                gridRow = (s8)i;
            }
            scanColumn = (scanColumn + 1) & 0xff;
        } while (scanColumn < 12);
        i = (i + 1) & 0xff;
    } while (i < 2);

    i = 0xffffffff;
    if (action == -1) {
        return 0;
    }

    switch (action) {
    case 0:
    case 1:
        if (gridRow == 0) {
            i = 1;
        } else {
            i = 0;
        }
        targetRow = gridRow;
        gridRow = (s8)i;
        candidateSelection =
            func_ov006_02050034(
                (s8)data_ov006_02056410[gridRow][gridColumn],
                members);
        if (candidateSelection == 0) {
            i = gridRow % 2;
            if (i == 0 && gridColumn + 1 < 12 &&
                func_ov006_02050034(
                    (s8)data_ov006_02056410[gridRow][gridColumn + 1],
                    members) != 0) {
                gridColumn = (s8)(gridColumn + 1);
            } else if (i == 1 && gridColumn - 1 > 0 &&
                       func_ov006_02050034(
                           (s8)data_ov006_02056410[gridRow][gridColumn - 1],
                           members) != 0) {
                gridColumn = (s8)(gridColumn - 1);
            } else {
                gridRow = (s8)targetRow;
            }
        }
        break;

    case 2:
    case 3: {
        int *gridRowData;
        s8 occupied0;
        s8 occupied1;
        s8 occupied2;

        i = 0;
        occupiedCount = 0;
        do {
            if (occupiedCount != selectionIndex &&
                members[occupiedCount].flags2 != 0) {
                occupiedSelections[i] = members[occupiedCount].icon;
                i = (i + 1) & 0xff;
            }
            occupiedCount = (occupiedCount + 1) & 0xff;
        } while (occupiedCount < 4);

        gridRowData = data_ov006_02056410[gridRow];
        occupied0 = (s8)occupiedSelections[0];
        occupied1 = (s8)occupiedSelections[1];
        occupied2 = (s8)occupiedSelections[2];
        targetRow = 0;
        do {
            if (action == 2) {
                gridColumn = (s8)(gridColumn + 1);
            }
            if (action == 3) {
                gridColumn = (s8)(gridColumn - 1);
            }
            if (gridColumn > 11) {
                gridColumn = 0;
            }
            if (gridColumn < 0) {
                gridColumn = 11;
            }
            candidateSelection = gridRowData[gridColumn];
        } while ((candidateSelection < 0 ||
                  occupied0 == candidateSelection ||
                  occupied1 == candidateSelection ||
                  occupied2 == candidateSelection) &&
                 (u32)(targetRow = (targetRow + 1) & 0xff) < 12);
        break;
    }

    default:
        break;
    }

    members[selectionIndex].icon =
        (s8)data_ov006_02056410[gridRow][gridColumn];

    resolvedSelection =
        func_ov006_0204fffc((s8)members[selectionIndex].icon);
    if (resolvedSelection != 0 && action == 4) {
        members[selectionIndex].flags3 = 1;
    }

    if (func_ov006_0204fbb4() == 0 &&
        members[selectionIndex].flags3 != 0 &&
        action == 5) {
        members[selectionIndex].flags3 = 0;
    }

    *resolvedSelectionOut =
        func_ov006_0204fffc((s8)members[selectionIndex].icon);
    return 1;
}
