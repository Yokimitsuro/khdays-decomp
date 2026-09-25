/* func_020307b8 -- GameSession_SetSyncEnabled, MAIN. Bit 0 of the shared session's +0x2c
 * halfword gates the member synchronisation used by the mission menus (ov006/ov008): enabling
 * clears it, disabling raises it. */
typedef unsigned short u16;

typedef struct GameSession {
    char pad00[0x2c];
    u16 bSyncDisabled : 1;              /* +0x2c bit 0 */
} GameSession;

extern GameSession *data_0204c228;

void func_020307b8(int enable)
{
    GameSession *session = data_0204c228;

    session->bSyncDisabled = enable ? 0 : 1;
}
