/* Initialize the result-screen resource tracker and load archive member 3. */

#include "nitro/types.h"
#include "game/archive.h"

typedef int (*ResourceCallback)(int);
typedef struct Ov000ResourceTrackerConfig {u32 entryCapacity,nodeCapacity,auxiliaryCapacity;ResourceCallback entryCallback,nodeCallback;} Ov000ResourceTrackerConfig;
typedef struct Ov000ResourceTracker {char data[76];} Ov000ResourceTracker;
typedef struct Ov005ResultContext {u32 resultArchive;char pad4[4];Ov000ResourceTracker resourceTracker;} Ov005ResultContext;
extern Ov005ResultContext *data_ov005_0205b810;
extern int Ov005_ResultResourceEntryCallback(int);
extern int Ov005_ResultResourceNodeCallback(int);
extern void Ov005_Container_Init(Ov000ResourceTracker *,Ov000ResourceTrackerConfig *);
extern void Ov005_LoadAndInitResourceSections(Ov000ResourceTracker *,u32);
void Ov005_InitializeResultResourceTracker(void) {
    Ov000ResourceTrackerConfig config;
    Ov005ResultContext *context=data_ov005_0205b810;
    config.entryCapacity=57;
    config.nodeCapacity=1;
    config.auxiliaryCapacity=26;
    config.entryCallback=Ov005_ResultResourceEntryCallback;
    config.nodeCallback=Ov005_ResultResourceNodeCallback;
    Ov005_Container_Init(&context->resourceTracker,&config);
    Ov005_LoadAndInitResourceSections(&context->resourceTracker,ARCHIVE_HANDLE(data_ov005_0205b810->resultArchive, 3));
}
