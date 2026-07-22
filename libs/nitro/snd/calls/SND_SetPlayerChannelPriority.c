/* Player parameter 4 = channel priority. */
extern void *SNDi_SetPlayerParam();

void *SND_SetPlayerChannelPriority(int player, int prio) {
    return SNDi_SetPlayerParam(player, 4, prio, 1);
}
