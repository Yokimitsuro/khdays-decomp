typedef struct Ov002Vec3 { int x, y, z; } Ov002Vec3;
typedef struct Ov002SessionMarker {
    Ov002Vec3 place;
    int nOwner;
    int nKind;
    char szName[0x30];
} Ov002SessionMarker;
typedef struct Ov002SessionBlock {
    int nSessionToken;
    Ov002SessionMarker *pMarkers;
} Ov002SessionBlock;
typedef struct Ov002SessionActorFlags {
    unsigned long long qwFlags;
    unsigned char pad008[0x45c];
    unsigned int dwStateFlags;
} Ov002SessionActorFlags;

extern char *data_ov002_0207fa00;
extern unsigned short func_01fffe14(void);
extern char *func_0201f924(char *pDest, const char *pSource);
extern int func_ov002_0207285c(int nDestination);
extern int func_ov002_02072770(int nCode, int *pSlot, int *pDestination);
extern int func_ov022_020882f8(void);
extern Ov002SessionActorFlags *func_01fffde0(int nPlayer);
extern void func_ov002_02072874(const char *pName, int nSlot,
    Ov002Vec3 *pPlace, int *pExtra, int nPlayer);

/* Refresh marker destinations and optional named placements after a code change. */
void func_ov002_0206d69c(void)
{
    char *pRoot = data_ov002_0207fa00;
    Ov002SessionBlock *pSession = (Ov002SessionBlock *)(pRoot + 0x8bcc);
    int nLocalPlayer = func_01fffe14();
    Ov002SessionMarker *pMarker = &pSession->pMarkers[nLocalPlayer];
    char *pMarkerName = 0;
    int nOldDestination = pMarker->nKind;
    int nSlot;
    int nNewDestination;
    char szMarkerName[16];
    int i;
    int bHasName;
    Ov002SessionActorFlags *pActor;

    if (nOldDestination != -1) {
        if (pMarker->szName[0]) {
            pMarkerName = pMarker->szName;
            func_0201f924(szMarkerName, pMarkerName);
        }
        nSlot = func_ov002_0207285c(nOldDestination);
        if (nSlot == -1 && func_ov002_02072770(pRoot[0x8d79], &nSlot, &nNewDestination)
            && nOldDestination != nNewDestination) {
            pSession->pMarkers[nLocalPlayer].nKind = nNewDestination;
            nSlot = func_ov002_0207285c(nNewDestination);
            if (nSlot != -1) {
                for (i = 0; i < func_ov022_020882f8(); i++) {
                    pActor = func_01fffde0(i);
                    bHasName = pMarkerName != 0;
                    if (i == nLocalPlayer || (pActor->qwFlags & 0x10000ULL) != 0) {
                        if (bHasName) {
                            func_ov002_02072874(szMarkerName, nSlot,
                                &pSession->pMarkers[i].place,
                                &pSession->pMarkers[i].nOwner, i);
                            pSession->pMarkers[i].szName[0] = 0;
                        }
                        pSession->pMarkers[i].nKind = nNewDestination;
                    }
                }
            }
        }
    }
}
