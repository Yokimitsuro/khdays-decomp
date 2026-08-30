/* Swept sphere versus a polygon face: plane contact followed by finite-edge tests.
 * The wide address carrier and vertex declaration order preserve retail register
 * lifetimes. The carrier holds an ARM9 pointer, not a new game-object layout. */
typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned char u8;
typedef signed long long s64;
typedef struct VecFx32 { s32 x,y,z; } VecFx32;
typedef struct VecFx16 { s16 x,y,z; } VecFx16;
typedef struct CollisionPlane { VecFx16 normal; s16 pad06; s32 distance; } CollisionPlane;
typedef struct CollisionFace84 {
 s32 minX00,minZ04,maxX08,maxZ0c;
 u16 flags10,vertexCount12;
 CollisionPlane plane;
 CollisionPlane edges[4];
 VecFx32 vertices50[4];
 u8 pad80[4];
} CollisionFace84;
typedef struct CollCastState {
 u8 pad00[0x10];
 VecFx32 vRayStart,vDir;
 u8 pad28[0xc];
 s32 nBoundMaxA,nBoundMaxB,nBoundMinA,nBoundMinB;
 VecFx32 vUnitDir;
 s32 nDirLength;
 VecFx32 vRayEnd,vCandidateHit;
 s32 nCandidateT;
 CollisionPlane *pCachedPlane;
 s32 nRadius,nNearestHit;
} CollCastState;
extern void VEC_Add(const VecFx32*,const VecFx32*,VecFx32*);
extern s64 func_01ff8a14(s32,s32);
extern void func_01ffd0e8(s32,const VecFx32*,const VecFx32*,VecFx32*);
extern s32 VEC_DotProductFx16(const VecFx32*,const VecFx16*);
extern s32 func_01ffe460(const VecFx32*,const VecFx32*,const VecFx32*,VecFx32*);
extern s32 func_01ffe3c8(const VecFx32*,const VecFx32*,const VecFx32*,s32,VecFx32*);
extern s32 VEC_Mag(const VecFx32*);
#define DOT_XZ(v,n) ((s32)(((s64)(v).x*(n).x+(s64)(v).z*(n).z+0x800)>>12))
s32 func_01ffe4f4(CollisionFace84 *face,CollCastState *inputQuery)
{
 VecFx32 shiftedStart,shiftedEnd,entryPoint,exitPoint,edgePoint,sphereOffset;
 s64 queryAddress;
 CollCastState *query;
 s32 planeDistance;
 s32 startDistance;
 s32 endDistance;
 s32 denominator;
 s32 centerStartDistance;
 s32 centerEndDistance;
 s32 radius;
 s32 edgeIndex;
 s32 vertexCount;
 s32 dot;
 s32 nextIndex;
 CollisionPlane *edge;
 s32 edgeLimit;
 VecFx32 *vertex;
 VecFx32 *vertices;
 s32 fraction;
 queryAddress=(unsigned int)inputQuery;
 query=(CollCastState *)(unsigned int)queryAddress;
 if(query->nBoundMinA<face->minX00 || query->nBoundMinB<face->minZ04 ||
    query->nBoundMaxA>face->maxX08 || query->nBoundMaxB>face->maxZ0c) return -4096;
 radius=query->nRadius;
 shiftedStart.x=query->vRayStart.x-(s32)(((s64)radius*face->plane.normal.x)>>12);
 shiftedStart.z=query->vRayStart.z-(s32)(((s64)radius*face->plane.normal.z)>>12);
 shiftedStart.y=query->vRayStart.y;
 VEC_Add(&shiftedStart,&query->vDir,&shiftedEnd);
 planeDistance=face->plane.distance;
 startDistance=DOT_XZ(shiftedStart,face->plane.normal);
 endDistance=DOT_XZ(shiftedEnd,face->plane.normal);
 fraction=0;
 startDistance-=planeDistance;
 endDistance-=planeDistance;
 denominator=startDistance-endDistance;
 if(denominator<=4) return -4096;
 if(startDistance < -radius || endDistance>128) return -4096;
 centerStartDistance=startDistance+radius;
 centerEndDistance=endDistance+radius;
 if(startDistance<=0) {
  if(query->nNearestHit<=0) return -4096;
  entryPoint=shiftedStart;
 } else {
  if(startDistance >= (s32)(((s64)query->nNearestHit*denominator)>>27)) return -4096;
  if(endDistance>=0) { entryPoint=shiftedEnd; fraction=1<<27; }
  else {
   fraction=(s32)(func_01ff8a14(startDistance,denominator)>>5);
   func_01ffd0e8(fraction,&query->vDir,&shiftedStart,&entryPoint);
  }
 }
 if(centerEndDistance<=0) {
  if(centerEndDistance>=0) exitPoint=query->vRayEnd;
  else func_01ffd0e8((s32)(func_01ff8a14(centerStartDistance,centerStartDistance-centerEndDistance)>>5),&query->vDir,&query->vRayStart,&exitPoint);
 }
 vertexCount=face->vertexCount12;
 edge=face->edges;
 edgeIndex=0;
 if(edgeIndex<vertexCount) {
 vertex=vertices=face->vertices50;
 do {
  edgeLimit=edge->distance;
  dot=VEC_DotProductFx16(&entryPoint,&edge->normal);
  if(dot<edgeLimit) {
   edgeLimit-=radius;
   if(dot>=edgeLimit) {
    nextIndex=edgeIndex+1;
    if(nextIndex>=vertexCount) nextIndex=0;
    if(func_01ffe460(&entryPoint,vertex,&vertices[nextIndex],&edgePoint)>=0 &&
       func_01ffe3c8(&edgePoint,&query->vUnitDir,&query->vRayStart,query->nRadius,&sphereOffset)) {
     s32 hitFraction=(s32)(func_01ff8a14(VEC_Mag(&sphereOffset),query->nDirLength)>>5);
     if(hitFraction<query->nNearestHit) { query->nNearestHit=hitFraction; return hitFraction; }
    }
   }
   if(centerEndDistance>0 || VEC_DotProductFx16(&exitPoint,&edge->normal)<edgeLimit) return -4096;
  }
  edge++; vertex++; edgeIndex++;
 } while(edgeIndex<vertexCount);
 }
 query->nNearestHit=fraction;
 return fraction;
}
