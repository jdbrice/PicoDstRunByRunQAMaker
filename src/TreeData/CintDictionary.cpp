// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdITreeDatadICintDictionary

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
#include "CandidateEvent.h"
#include "CandidateTrack.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_CandidateEvent(void *p = 0);
   static void *newArray_CandidateEvent(Long_t size, void *p);
   static void delete_CandidateEvent(void *p);
   static void deleteArray_CandidateEvent(void *p);
   static void destruct_CandidateEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CandidateEvent*)
   {
      ::CandidateEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CandidateEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CandidateEvent", ::CandidateEvent::Class_Version(), "CandidateEvent.h", 6,
                  typeid(::CandidateEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CandidateEvent::Dictionary, isa_proxy, 4,
                  sizeof(::CandidateEvent) );
      instance.SetNew(&new_CandidateEvent);
      instance.SetNewArray(&newArray_CandidateEvent);
      instance.SetDelete(&delete_CandidateEvent);
      instance.SetDeleteArray(&deleteArray_CandidateEvent);
      instance.SetDestructor(&destruct_CandidateEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CandidateEvent*)
   {
      return GenerateInitInstanceLocal((::CandidateEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CandidateEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CandidateTrack(void *p = 0);
   static void *newArray_CandidateTrack(Long_t size, void *p);
   static void delete_CandidateTrack(void *p);
   static void deleteArray_CandidateTrack(void *p);
   static void destruct_CandidateTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CandidateTrack*)
   {
      ::CandidateTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CandidateTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CandidateTrack", ::CandidateTrack::Class_Version(), "CandidateTrack.h", 6,
                  typeid(::CandidateTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CandidateTrack::Dictionary, isa_proxy, 4,
                  sizeof(::CandidateTrack) );
      instance.SetNew(&new_CandidateTrack);
      instance.SetNewArray(&newArray_CandidateTrack);
      instance.SetDelete(&delete_CandidateTrack);
      instance.SetDeleteArray(&deleteArray_CandidateTrack);
      instance.SetDestructor(&destruct_CandidateTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CandidateTrack*)
   {
      return GenerateInitInstanceLocal((::CandidateTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CandidateTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
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
atomic_TClass_ptr CandidateTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CandidateTrack::Class_Name()
{
   return "CandidateTrack";
}

//______________________________________________________________________________
const char *CandidateTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CandidateTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CandidateTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CandidateTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void CandidateEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class CandidateEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CandidateEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(CandidateEvent::Class(),this);
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
} // end of namespace ROOT for class ::CandidateEvent

//______________________________________________________________________________
void CandidateTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class CandidateTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CandidateTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(CandidateTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CandidateTrack(void *p) {
      return  p ? new(p) ::CandidateTrack : new ::CandidateTrack;
   }
   static void *newArray_CandidateTrack(Long_t nElements, void *p) {
      return p ? new(p) ::CandidateTrack[nElements] : new ::CandidateTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_CandidateTrack(void *p) {
      delete ((::CandidateTrack*)p);
   }
   static void deleteArray_CandidateTrack(void *p) {
      delete [] ((::CandidateTrack*)p);
   }
   static void destruct_CandidateTrack(void *p) {
      typedef ::CandidateTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CandidateTrack

namespace {
  void TriggerDictionaryInitialization_CintDictionary_Impl() {
    static const char* headers[] = {
"CandidateEvent.h",
"CandidateTrack.h",
0
    };
    static const char* includePaths[] = {
"/Users/jdb/bnl/local/work/muonAna/include/DataAdapters",
"/Users/jdb/bnl/local/work/muonAna/include/EventPlane",
"/Users/jdb/bnl/local/work/muonAna/include/ProductionUtils",
"/Users/jdb/bnl/local/work/muonAna/include/QA",
"/Users/jdb/bnl/local/work/muonAna/include/Skimmers",
"/Users/jdb/bnl/local/work/muonAna/include/StRefMultCorr",
"/Users/jdb/bnl/local/work/muonAna/include/TreeData",
"/Users/jdb/bnl/vendor/root-6.06.02/include",
"/Users/jdb/bnl/local/work/muonAna/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "CintDictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$CandidateEvent.h")))  CandidateEvent;
class __attribute__((annotate("$clingAutoload$CandidateTrack.h")))  CandidateTrack;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "CintDictionary dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "CandidateEvent.h"
#include "CandidateTrack.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"CandidateEvent", payloadCode, "@",
"CandidateTrack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("CintDictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_CintDictionary_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_CintDictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_CintDictionary() {
  TriggerDictionaryInitialization_CintDictionary_Impl();
}
