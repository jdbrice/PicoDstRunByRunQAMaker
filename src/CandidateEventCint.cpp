// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME CandidateEventCint

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "../include/Skimmers/CandidateEvent.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_CandidateEvent(void *p = 0);
   static void *newArray_CandidateEvent(Long_t size, void *p);
   static void delete_CandidateEvent(void *p);
   static void deleteArray_CandidateEvent(void *p);
   static void destruct_CandidateEvent(void *p);
   static void streamer_CandidateEvent(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CandidateEvent*)
   {
      ::CandidateEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CandidateEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CandidateEvent", ::CandidateEvent::Class_Version(), "../include/Skimmers/CandidateEvent.h", 6,
                  typeid(::CandidateEvent), DefineBehavior(ptr, ptr),
                  &::CandidateEvent::Dictionary, isa_proxy, 16,
                  sizeof(::CandidateEvent) );
      instance.SetNew(&new_CandidateEvent);
      instance.SetNewArray(&newArray_CandidateEvent);
      instance.SetDelete(&delete_CandidateEvent);
      instance.SetDeleteArray(&deleteArray_CandidateEvent);
      instance.SetDestructor(&destruct_CandidateEvent);
      instance.SetStreamerFunc(&streamer_CandidateEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CandidateEvent*)
   {
      return GenerateInitInstanceLocal((::CandidateEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CandidateEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr CandidateEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CandidateEvent::Class_Name()
{
   return "CandidateEvent";
}

//______________________________________________________________________________
const char *CandidateEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CandidateEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CandidateEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CandidateEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void CandidateEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class CandidateEvent.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      TObject::Streamer(R__b);
      R__b >> runId;
      R__b >> eventId;
      R__b >> bin16;
      R__b.CheckByteCount(R__s, R__c, CandidateEvent::IsA());
   } else {
      R__c = R__b.WriteVersion(CandidateEvent::IsA(), kTRUE);
      TObject::Streamer(R__b);
      R__b << runId;
      R__b << eventId;
      R__b << bin16;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CandidateEvent(void *p) {
      return  p ? new(p) ::CandidateEvent : new ::CandidateEvent;
   }
   static void *newArray_CandidateEvent(Long_t nElements, void *p) {
      return p ? new(p) ::CandidateEvent[nElements] : new ::CandidateEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_CandidateEvent(void *p) {
      delete ((::CandidateEvent*)p);
   }
   static void deleteArray_CandidateEvent(void *p) {
      delete [] ((::CandidateEvent*)p);
   }
   static void destruct_CandidateEvent(void *p) {
      typedef ::CandidateEvent current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_CandidateEvent(TBuffer &buf, void *obj) {
      ((::CandidateEvent*)obj)->::CandidateEvent::Streamer(buf);
   }
} // end of namespace ROOT for class ::CandidateEvent

namespace {
  void TriggerDictionaryInitialization_CandidateEventCint_Impl() {
    static const char* headers[] = {
"../include/Skimmers/CandidateEvent.h",
0
    };
    static const char* includePaths[] = {
"/Users/danielbrandenburg/bnl/vendor/root-6.04.00/include",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/src/",
0
    };
    static const char* fwdDeclCode = 
R"DICTFWDDCLS(
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$../include/Skimmers/CandidateEvent.h")))  CandidateEvent;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../include/Skimmers/CandidateEvent.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"CandidateEvent", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("CandidateEventCint",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_CandidateEventCint_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_CandidateEventCint_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_CandidateEventCint() {
  TriggerDictionaryInitialization_CandidateEventCint_Impl();
}
