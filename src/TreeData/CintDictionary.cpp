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
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"

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
   static void *new_CandidateEventPlane(void *p = 0);
   static void *newArray_CandidateEventPlane(Long_t size, void *p);
   static void delete_CandidateEventPlane(void *p);
   static void deleteArray_CandidateEventPlane(void *p);
   static void destruct_CandidateEventPlane(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CandidateEventPlane*)
   {
      ::CandidateEventPlane *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CandidateEventPlane >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CandidateEventPlane", ::CandidateEventPlane::Class_Version(), "CandidateEventPlane.h", 6,
                  typeid(::CandidateEventPlane), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CandidateEventPlane::Dictionary, isa_proxy, 4,
                  sizeof(::CandidateEventPlane) );
      instance.SetNew(&new_CandidateEventPlane);
      instance.SetNewArray(&newArray_CandidateEventPlane);
      instance.SetDelete(&delete_CandidateEventPlane);
      instance.SetDeleteArray(&deleteArray_CandidateEventPlane);
      instance.SetDestructor(&destruct_CandidateEventPlane);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CandidateEventPlane*)
   {
      return GenerateInitInstanceLocal((::CandidateEventPlane*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CandidateEventPlane*)0x0); R__UseDummy(_R__UNIQUE_(Init));
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

namespace ROOT {
   static void *new_CandidateTrackBTofPidTraits(void *p = 0);
   static void *newArray_CandidateTrackBTofPidTraits(Long_t size, void *p);
   static void delete_CandidateTrackBTofPidTraits(void *p);
   static void deleteArray_CandidateTrackBTofPidTraits(void *p);
   static void destruct_CandidateTrackBTofPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CandidateTrackBTofPidTraits*)
   {
      ::CandidateTrackBTofPidTraits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CandidateTrackBTofPidTraits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CandidateTrackBTofPidTraits", ::CandidateTrackBTofPidTraits::Class_Version(), "CandidateTrackBTofPidTraits.h", 6,
                  typeid(::CandidateTrackBTofPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CandidateTrackBTofPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::CandidateTrackBTofPidTraits) );
      instance.SetNew(&new_CandidateTrackBTofPidTraits);
      instance.SetNewArray(&newArray_CandidateTrackBTofPidTraits);
      instance.SetDelete(&delete_CandidateTrackBTofPidTraits);
      instance.SetDeleteArray(&deleteArray_CandidateTrackBTofPidTraits);
      instance.SetDestructor(&destruct_CandidateTrackBTofPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CandidateTrackBTofPidTraits*)
   {
      return GenerateInitInstanceLocal((::CandidateTrackBTofPidTraits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CandidateTrackBTofPidTraits*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CandidateTrackMtdPidTraits(void *p = 0);
   static void *newArray_CandidateTrackMtdPidTraits(Long_t size, void *p);
   static void delete_CandidateTrackMtdPidTraits(void *p);
   static void deleteArray_CandidateTrackMtdPidTraits(void *p);
   static void destruct_CandidateTrackMtdPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CandidateTrackMtdPidTraits*)
   {
      ::CandidateTrackMtdPidTraits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CandidateTrackMtdPidTraits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CandidateTrackMtdPidTraits", ::CandidateTrackMtdPidTraits::Class_Version(), "CandidateTrackMtdPidTraits.h", 6,
                  typeid(::CandidateTrackMtdPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CandidateTrackMtdPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::CandidateTrackMtdPidTraits) );
      instance.SetNew(&new_CandidateTrackMtdPidTraits);
      instance.SetNewArray(&newArray_CandidateTrackMtdPidTraits);
      instance.SetDelete(&delete_CandidateTrackMtdPidTraits);
      instance.SetDeleteArray(&deleteArray_CandidateTrackMtdPidTraits);
      instance.SetDestructor(&destruct_CandidateTrackMtdPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CandidateTrackMtdPidTraits*)
   {
      return GenerateInitInstanceLocal((::CandidateTrackMtdPidTraits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::CandidateTrackMtdPidTraits*)0x0); R__UseDummy(_R__UNIQUE_(Init));
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
atomic_TClass_ptr CandidateEventPlane::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CandidateEventPlane::Class_Name()
{
   return "CandidateEventPlane";
}

//______________________________________________________________________________
const char *CandidateEventPlane::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateEventPlane*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CandidateEventPlane::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateEventPlane*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CandidateEventPlane::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateEventPlane*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CandidateEventPlane::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateEventPlane*)0x0)->GetClass(); }
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
atomic_TClass_ptr CandidateTrackBTofPidTraits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CandidateTrackBTofPidTraits::Class_Name()
{
   return "CandidateTrackBTofPidTraits";
}

//______________________________________________________________________________
const char *CandidateTrackBTofPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackBTofPidTraits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CandidateTrackBTofPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackBTofPidTraits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CandidateTrackBTofPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackBTofPidTraits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CandidateTrackBTofPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackBTofPidTraits*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CandidateTrackMtdPidTraits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CandidateTrackMtdPidTraits::Class_Name()
{
   return "CandidateTrackMtdPidTraits";
}

//______________________________________________________________________________
const char *CandidateTrackMtdPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackMtdPidTraits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CandidateTrackMtdPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackMtdPidTraits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CandidateTrackMtdPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackMtdPidTraits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CandidateTrackMtdPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CandidateTrackMtdPidTraits*)0x0)->GetClass(); }
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
void CandidateEventPlane::Streamer(TBuffer &R__b)
{
   // Stream an object of class CandidateEventPlane.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CandidateEventPlane::Class(),this);
   } else {
      R__b.WriteClassBuffer(CandidateEventPlane::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CandidateEventPlane(void *p) {
      return  p ? new(p) ::CandidateEventPlane : new ::CandidateEventPlane;
   }
   static void *newArray_CandidateEventPlane(Long_t nElements, void *p) {
      return p ? new(p) ::CandidateEventPlane[nElements] : new ::CandidateEventPlane[nElements];
   }
   // Wrapper around operator delete
   static void delete_CandidateEventPlane(void *p) {
      delete ((::CandidateEventPlane*)p);
   }
   static void deleteArray_CandidateEventPlane(void *p) {
      delete [] ((::CandidateEventPlane*)p);
   }
   static void destruct_CandidateEventPlane(void *p) {
      typedef ::CandidateEventPlane current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CandidateEventPlane

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

//______________________________________________________________________________
void CandidateTrackBTofPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class CandidateTrackBTofPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CandidateTrackBTofPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(CandidateTrackBTofPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CandidateTrackBTofPidTraits(void *p) {
      return  p ? new(p) ::CandidateTrackBTofPidTraits : new ::CandidateTrackBTofPidTraits;
   }
   static void *newArray_CandidateTrackBTofPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::CandidateTrackBTofPidTraits[nElements] : new ::CandidateTrackBTofPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_CandidateTrackBTofPidTraits(void *p) {
      delete ((::CandidateTrackBTofPidTraits*)p);
   }
   static void deleteArray_CandidateTrackBTofPidTraits(void *p) {
      delete [] ((::CandidateTrackBTofPidTraits*)p);
   }
   static void destruct_CandidateTrackBTofPidTraits(void *p) {
      typedef ::CandidateTrackBTofPidTraits current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CandidateTrackBTofPidTraits

//______________________________________________________________________________
void CandidateTrackMtdPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class CandidateTrackMtdPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CandidateTrackMtdPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(CandidateTrackMtdPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CandidateTrackMtdPidTraits(void *p) {
      return  p ? new(p) ::CandidateTrackMtdPidTraits : new ::CandidateTrackMtdPidTraits;
   }
   static void *newArray_CandidateTrackMtdPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::CandidateTrackMtdPidTraits[nElements] : new ::CandidateTrackMtdPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_CandidateTrackMtdPidTraits(void *p) {
      delete ((::CandidateTrackMtdPidTraits*)p);
   }
   static void deleteArray_CandidateTrackMtdPidTraits(void *p) {
      delete [] ((::CandidateTrackMtdPidTraits*)p);
   }
   static void destruct_CandidateTrackMtdPidTraits(void *p) {
      typedef ::CandidateTrackMtdPidTraits current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CandidateTrackMtdPidTraits

namespace {
  void TriggerDictionaryInitialization_CintDictionary_Impl() {
    static const char* headers[] = {
"CandidateEvent.h",
"CandidateEventPlane.h",
"CandidateTrack.h",
"CandidateTrackBTofPidTraits.h",
"CandidateTrackMtdPidTraits.h",
0
    };
    static const char* includePaths[] = {
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/include/DataAdapters",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/include/EventPlane",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/include/ProductionUtils",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/include/QA",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/include/Skimmers",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/include/StRefMultCorr",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/include/TreeData",
"/Users/danielbrandenburg/bnl/vendor/root-6.06.04/include",
"/Users/danielbrandenburg/bnl/local/work/PicoDst/muonAna/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "CintDictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$CandidateEvent.h")))  CandidateEvent;
class __attribute__((annotate("$clingAutoload$CandidateEventPlane.h")))  CandidateEventPlane;
class __attribute__((annotate("$clingAutoload$CandidateTrack.h")))  CandidateTrack;
class __attribute__((annotate("$clingAutoload$CandidateTrackBTofPidTraits.h")))  CandidateTrackBTofPidTraits;
class __attribute__((annotate("$clingAutoload$CandidateTrackMtdPidTraits.h")))  CandidateTrackMtdPidTraits;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "CintDictionary dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "CandidateEvent.h"
#include "CandidateEventPlane.h"
#include "CandidateTrack.h"
#include "CandidateTrackBTofPidTraits.h"
#include "CandidateTrackMtdPidTraits.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"CandidateEvent", payloadCode, "@",
"CandidateEventPlane", payloadCode, "@",
"CandidateTrack", payloadCode, "@",
"CandidateTrackBTofPidTraits", payloadCode, "@",
"CandidateTrackMtdPidTraits", payloadCode, "@",
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
