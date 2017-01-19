#include "CandidatePair.h"
#include "TriggerPatchMapper.h"

int CandidatePair::d1bl() { return TriggerPatchMapper::backleg(d1_mMtdHitChan); }
int CandidatePair::d2bl() { return TriggerPatchMapper::backleg(d2_mMtdHitChan); }
int CandidatePair::d1es() { return TriggerPatchMapper::etaStrip(d1_mMtdHitChan); }
int CandidatePair::d2es() { return TriggerPatchMapper::etaStrip(d2_mMtdHitChan); }
int CandidatePair::d1tp() { return TriggerPatchMapper::findTriggerPatch(d1_mMtdHitChan); }
int CandidatePair::d2tp() { return TriggerPatchMapper::findTriggerPatch(d2_mMtdHitChan); }