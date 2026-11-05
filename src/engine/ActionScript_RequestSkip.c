/* Asks a running action script to skip to its end: sets +0x588 of the script's state.
 * Game_RunActionScript unwinds to the target it kept when +0x584 and +0x588 are both set. Callers:
 * the pause menu's Skip (Ov023_RequestEventSkip, the event's state at the scene root + 0x4b88),
 * the opening (ov012) and the movie player (ov024), whose scripts are group 3 of the script
 * machine's tables. */

void ActionScript_RequestSkip(int pScript)
{
    *(int *)(pScript + 0x588) = 1;
}
