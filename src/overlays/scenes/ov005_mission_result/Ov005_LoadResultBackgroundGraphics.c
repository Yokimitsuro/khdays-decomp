/* Ov005_LoadResultBackgroundGraphics: upload the result-screen BG resources.
 * Pack the archive ADDRESS into a subfile handle; do not dereference its header.
 * Reuse the decoded character/palette layouts, then free only the temporary files.
 * The explicit unsigned mode predicate preserves the original boolean sequence.
 * ARM: 476 bytes, 17 relocations, byte-exact.
 */

#include "nitro/types.h"
#include "game/engine.h"
#include "game/archive.h"

typedef struct Ov002PageChars {char header[16];int nCharSize;void *pCharData;} Ov002PageChars;
typedef struct BgPlttSrc {int nFormat,n_pad;u32 dwSize;void *pData;} BgPlttSrc;
typedef struct SpriteResSet {void *pScreen;Ov002PageChars *pChar;BgPlttSrc *pPalette;} SpriteResSet;
typedef struct Ov005Config {u16 sceneId;char unknown02[8];u16 resultLabelIndex;} Ov005Config;
typedef struct Ov005ResultContext {u32 *resultArchive;} Ov005ResultContext;
extern Ov005Config data_ov005_0205b85c;
extern Ov005ResultContext *data_ov005_0205b810;
extern char gOv005UiSrsltUbPath[];
extern void *Archive_LoadFile(const char *,int);
extern void GXS_LoadBGPltt(const void *,u32,u32);
extern void GXS_LoadBG0Char(const void *,u32,u32);
extern void GXS_LoadBG1Char(const void *,u32,u32);
extern void GXS_LoadBG3Char(const void *,u32,u32);
extern int GetResourceSubBlock_CHAR2(void *,Ov002PageChars **);
extern void NNSi_FndFreeFromDefaultHeap(void *);
void Ov005_LoadResultBackgroundGraphics(void) {
    SpriteResSet resources;
    Ov002PageChars *extraCharacters;
    Ov005Config *config=&data_ov005_0205b85c;
    void *archive;
    int characterIndex;
    archive=Archive_LoadFile((const char *)ARCHIVE_HANDLE(data_ov005_0205b810->resultArchive, 0),14);
    Res_LoadSpriteSet(&resources,archive,-1,5,1);
    GXS_LoadBGPltt(resources.pPalette->pData,0,resources.pPalette->dwSize);
    GXS_LoadBG1Char(resources.pChar->pCharData,0,resources.pChar->nCharSize);
    Res_LoadSpriteSet(&resources,archive,-1,6,-1);
    GXS_LoadBG3Char(resources.pChar->pCharData,0,resources.pChar->nCharSize);
    switch(config->sceneId) {
    case 0x547:characterIndex=19;break;
    case 0x548:characterIndex=20;break;
    case 0x514:case 0x515:characterIndex=22;break;
    case 0x54a:
    default:characterIndex=config->resultLabelIndex+7;break;
    }
    Res_LoadSpriteSet(&resources,archive,-1,characterIndex,-1);
    GXS_LoadBG0Char(resources.pChar->pCharData,0,resources.pChar->nCharSize);
    if((unsigned int)(GetLanguage()==1)==0) {
        void *extra=Archive_LoadFile(gOv005UiSrsltUbPath,14);
        GetResourceSubBlock_CHAR2(extra,&extraCharacters);
        GXS_LoadBG1Char(extraCharacters->pCharData,0x3000,extraCharacters->nCharSize);
        if(extra!=0)NNSi_FndFreeFromDefaultHeap(extra);
    }
    if(archive!=0)NNSi_FndFreeFromDefaultHeap(archive);
}
