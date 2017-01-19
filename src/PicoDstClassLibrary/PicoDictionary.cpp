// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME srcdIPicoDstClassLibrarydIPicoDictionary

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
#include "StPicoBTOWHit.h"
#include "StPicoBTofHit.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoEmcPidTraits.h"
#include "StPicoEmcTrigger.h"
#include "StPicoEvent.h"
#include "StPicoMtdHit.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoMtdTrigger.h"
#include "StPicoTrack.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_StPicoBTOWHit(void *p = 0);
   static void *newArray_StPicoBTOWHit(Long_t size, void *p);
   static void delete_StPicoBTOWHit(void *p);
   static void deleteArray_StPicoBTOWHit(void *p);
   static void destruct_StPicoBTOWHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBTOWHit*)
   {
      ::StPicoBTOWHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBTOWHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBTOWHit", ::StPicoBTOWHit::Class_Version(), "StPicoBTOWHit.h", 6,
                  typeid(::StPicoBTOWHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBTOWHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBTOWHit) );
      instance.SetNew(&new_StPicoBTOWHit);
      instance.SetNewArray(&newArray_StPicoBTOWHit);
      instance.SetDelete(&delete_StPicoBTOWHit);
      instance.SetDeleteArray(&deleteArray_StPicoBTOWHit);
      instance.SetDestructor(&destruct_StPicoBTOWHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBTOWHit*)
   {
      return GenerateInitInstanceLocal((::StPicoBTOWHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoBTOWHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBTofHit(void *p = 0);
   static void *newArray_StPicoBTofHit(Long_t size, void *p);
   static void delete_StPicoBTofHit(void *p);
   static void deleteArray_StPicoBTofHit(void *p);
   static void destruct_StPicoBTofHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBTofHit*)
   {
      ::StPicoBTofHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBTofHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBTofHit", ::StPicoBTofHit::Class_Version(), "StPicoBTofHit.h", 6,
                  typeid(::StPicoBTofHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBTofHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBTofHit) );
      instance.SetNew(&new_StPicoBTofHit);
      instance.SetNewArray(&newArray_StPicoBTofHit);
      instance.SetDelete(&delete_StPicoBTofHit);
      instance.SetDeleteArray(&deleteArray_StPicoBTofHit);
      instance.SetDestructor(&destruct_StPicoBTofHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBTofHit*)
   {
      return GenerateInitInstanceLocal((::StPicoBTofHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoBTofHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoBTofPidTraits(void *p = 0);
   static void *newArray_StPicoBTofPidTraits(Long_t size, void *p);
   static void delete_StPicoBTofPidTraits(void *p);
   static void deleteArray_StPicoBTofPidTraits(void *p);
   static void destruct_StPicoBTofPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoBTofPidTraits*)
   {
      ::StPicoBTofPidTraits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoBTofPidTraits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoBTofPidTraits", ::StPicoBTofPidTraits::Class_Version(), "StPicoBTofPidTraits.h", 8,
                  typeid(::StPicoBTofPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoBTofPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoBTofPidTraits) );
      instance.SetNew(&new_StPicoBTofPidTraits);
      instance.SetNewArray(&newArray_StPicoBTofPidTraits);
      instance.SetDelete(&delete_StPicoBTofPidTraits);
      instance.SetDeleteArray(&deleteArray_StPicoBTofPidTraits);
      instance.SetDestructor(&destruct_StPicoBTofPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoBTofPidTraits*)
   {
      return GenerateInitInstanceLocal((::StPicoBTofPidTraits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoEmcPidTraits(void *p = 0);
   static void *newArray_StPicoEmcPidTraits(Long_t size, void *p);
   static void delete_StPicoEmcPidTraits(void *p);
   static void deleteArray_StPicoEmcPidTraits(void *p);
   static void destruct_StPicoEmcPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoEmcPidTraits*)
   {
      ::StPicoEmcPidTraits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoEmcPidTraits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoEmcPidTraits", ::StPicoEmcPidTraits::Class_Version(), "StPicoEmcPidTraits.h", 6,
                  typeid(::StPicoEmcPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoEmcPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoEmcPidTraits) );
      instance.SetNew(&new_StPicoEmcPidTraits);
      instance.SetNewArray(&newArray_StPicoEmcPidTraits);
      instance.SetDelete(&delete_StPicoEmcPidTraits);
      instance.SetDeleteArray(&deleteArray_StPicoEmcPidTraits);
      instance.SetDestructor(&destruct_StPicoEmcPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoEmcPidTraits*)
   {
      return GenerateInitInstanceLocal((::StPicoEmcPidTraits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoEmcPidTraits*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoEmcTrigger(void *p = 0);
   static void *newArray_StPicoEmcTrigger(Long_t size, void *p);
   static void delete_StPicoEmcTrigger(void *p);
   static void deleteArray_StPicoEmcTrigger(void *p);
   static void destruct_StPicoEmcTrigger(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoEmcTrigger*)
   {
      ::StPicoEmcTrigger *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoEmcTrigger >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoEmcTrigger", ::StPicoEmcTrigger::Class_Version(), "StPicoEmcTrigger.h", 6,
                  typeid(::StPicoEmcTrigger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoEmcTrigger::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoEmcTrigger) );
      instance.SetNew(&new_StPicoEmcTrigger);
      instance.SetNewArray(&newArray_StPicoEmcTrigger);
      instance.SetDelete(&delete_StPicoEmcTrigger);
      instance.SetDeleteArray(&deleteArray_StPicoEmcTrigger);
      instance.SetDestructor(&destruct_StPicoEmcTrigger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoEmcTrigger*)
   {
      return GenerateInitInstanceLocal((::StPicoEmcTrigger*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoEvent(void *p = 0);
   static void *newArray_StPicoEvent(Long_t size, void *p);
   static void delete_StPicoEvent(void *p);
   static void deleteArray_StPicoEvent(void *p);
   static void destruct_StPicoEvent(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoEvent*)
   {
      ::StPicoEvent *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoEvent >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoEvent", ::StPicoEvent::Class_Version(), "StPicoEvent.h", 11,
                  typeid(::StPicoEvent), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoEvent::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoEvent) );
      instance.SetNew(&new_StPicoEvent);
      instance.SetNewArray(&newArray_StPicoEvent);
      instance.SetDelete(&delete_StPicoEvent);
      instance.SetDeleteArray(&deleteArray_StPicoEvent);
      instance.SetDestructor(&destruct_StPicoEvent);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoEvent*)
   {
      return GenerateInitInstanceLocal((::StPicoEvent*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoEvent*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMtdHit(void *p = 0);
   static void *newArray_StPicoMtdHit(Long_t size, void *p);
   static void delete_StPicoMtdHit(void *p);
   static void deleteArray_StPicoMtdHit(void *p);
   static void destruct_StPicoMtdHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMtdHit*)
   {
      ::StPicoMtdHit *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMtdHit >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMtdHit", ::StPicoMtdHit::Class_Version(), "StPicoMtdHit.h", 8,
                  typeid(::StPicoMtdHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMtdHit::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMtdHit) );
      instance.SetNew(&new_StPicoMtdHit);
      instance.SetNewArray(&newArray_StPicoMtdHit);
      instance.SetDelete(&delete_StPicoMtdHit);
      instance.SetDeleteArray(&deleteArray_StPicoMtdHit);
      instance.SetDestructor(&destruct_StPicoMtdHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMtdHit*)
   {
      return GenerateInitInstanceLocal((::StPicoMtdHit*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoMtdHit*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMtdPidTraits(void *p = 0);
   static void *newArray_StPicoMtdPidTraits(Long_t size, void *p);
   static void delete_StPicoMtdPidTraits(void *p);
   static void deleteArray_StPicoMtdPidTraits(void *p);
   static void destruct_StPicoMtdPidTraits(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMtdPidTraits*)
   {
      ::StPicoMtdPidTraits *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMtdPidTraits >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMtdPidTraits", ::StPicoMtdPidTraits::Class_Version(), "StPicoMtdPidTraits.h", 6,
                  typeid(::StPicoMtdPidTraits), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMtdPidTraits::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMtdPidTraits) );
      instance.SetNew(&new_StPicoMtdPidTraits);
      instance.SetNewArray(&newArray_StPicoMtdPidTraits);
      instance.SetDelete(&delete_StPicoMtdPidTraits);
      instance.SetDeleteArray(&deleteArray_StPicoMtdPidTraits);
      instance.SetDestructor(&destruct_StPicoMtdPidTraits);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMtdPidTraits*)
   {
      return GenerateInitInstanceLocal((::StPicoMtdPidTraits*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoMtdTrigger(void *p = 0);
   static void *newArray_StPicoMtdTrigger(Long_t size, void *p);
   static void delete_StPicoMtdTrigger(void *p);
   static void deleteArray_StPicoMtdTrigger(void *p);
   static void destruct_StPicoMtdTrigger(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoMtdTrigger*)
   {
      ::StPicoMtdTrigger *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoMtdTrigger >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoMtdTrigger", ::StPicoMtdTrigger::Class_Version(), "StPicoMtdTrigger.h", 6,
                  typeid(::StPicoMtdTrigger), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoMtdTrigger::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoMtdTrigger) );
      instance.SetNew(&new_StPicoMtdTrigger);
      instance.SetNewArray(&newArray_StPicoMtdTrigger);
      instance.SetDelete(&delete_StPicoMtdTrigger);
      instance.SetDeleteArray(&deleteArray_StPicoMtdTrigger);
      instance.SetDestructor(&destruct_StPicoMtdTrigger);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoMtdTrigger*)
   {
      return GenerateInitInstanceLocal((::StPicoMtdTrigger*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_StPicoTrack(void *p = 0);
   static void *newArray_StPicoTrack(Long_t size, void *p);
   static void delete_StPicoTrack(void *p);
   static void deleteArray_StPicoTrack(void *p);
   static void destruct_StPicoTrack(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::StPicoTrack*)
   {
      ::StPicoTrack *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::StPicoTrack >(0);
      static ::ROOT::TGenericClassInfo 
         instance("StPicoTrack", ::StPicoTrack::Class_Version(), "StPicoTrack.h", 14,
                  typeid(::StPicoTrack), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::StPicoTrack::Dictionary, isa_proxy, 4,
                  sizeof(::StPicoTrack) );
      instance.SetNew(&new_StPicoTrack);
      instance.SetNewArray(&newArray_StPicoTrack);
      instance.SetDelete(&delete_StPicoTrack);
      instance.SetDeleteArray(&deleteArray_StPicoTrack);
      instance.SetDestructor(&destruct_StPicoTrack);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::StPicoTrack*)
   {
      return GenerateInitInstanceLocal((::StPicoTrack*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::StPicoTrack*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr StPicoBTOWHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBTOWHit::Class_Name()
{
   return "StPicoBTOWHit";
}

//______________________________________________________________________________
const char *StPicoBTOWHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTOWHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBTOWHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTOWHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBTOWHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTOWHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBTOWHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTOWHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBTofHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBTofHit::Class_Name()
{
   return "StPicoBTofHit";
}

//______________________________________________________________________________
const char *StPicoBTofHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBTofHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBTofHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBTofHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoBTofPidTraits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoBTofPidTraits::Class_Name()
{
   return "StPicoBTofPidTraits";
}

//______________________________________________________________________________
const char *StPicoBTofPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoBTofPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoBTofPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoBTofPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoBTofPidTraits*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoEmcPidTraits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoEmcPidTraits::Class_Name()
{
   return "StPicoEmcPidTraits";
}

//______________________________________________________________________________
const char *StPicoEmcPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcPidTraits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoEmcPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcPidTraits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoEmcPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcPidTraits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoEmcPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcPidTraits*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoEmcTrigger::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoEmcTrigger::Class_Name()
{
   return "StPicoEmcTrigger";
}

//______________________________________________________________________________
const char *StPicoEmcTrigger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoEmcTrigger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoEmcTrigger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoEmcTrigger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEmcTrigger*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoEvent::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoEvent::Class_Name()
{
   return "StPicoEvent";
}

//______________________________________________________________________________
const char *StPicoEvent::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoEvent::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoEvent::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoEvent::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoEvent*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMtdHit::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMtdHit::Class_Name()
{
   return "StPicoMtdHit";
}

//______________________________________________________________________________
const char *StPicoMtdHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMtdHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMtdHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMtdHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdHit*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMtdPidTraits::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMtdPidTraits::Class_Name()
{
   return "StPicoMtdPidTraits";
}

//______________________________________________________________________________
const char *StPicoMtdPidTraits::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMtdPidTraits::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMtdPidTraits::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMtdPidTraits::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdPidTraits*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoMtdTrigger::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoMtdTrigger::Class_Name()
{
   return "StPicoMtdTrigger";
}

//______________________________________________________________________________
const char *StPicoMtdTrigger::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoMtdTrigger::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoMtdTrigger::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoMtdTrigger::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoMtdTrigger*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr StPicoTrack::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *StPicoTrack::Class_Name()
{
   return "StPicoTrack";
}

//______________________________________________________________________________
const char *StPicoTrack::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int StPicoTrack::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *StPicoTrack::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *StPicoTrack::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::StPicoTrack*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void StPicoBTOWHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBTOWHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBTOWHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBTOWHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBTOWHit(void *p) {
      return  p ? new(p) ::StPicoBTOWHit : new ::StPicoBTOWHit;
   }
   static void *newArray_StPicoBTOWHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBTOWHit[nElements] : new ::StPicoBTOWHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBTOWHit(void *p) {
      delete ((::StPicoBTOWHit*)p);
   }
   static void deleteArray_StPicoBTOWHit(void *p) {
      delete [] ((::StPicoBTOWHit*)p);
   }
   static void destruct_StPicoBTOWHit(void *p) {
      typedef ::StPicoBTOWHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBTOWHit

//______________________________________________________________________________
void StPicoBTofHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBTofHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBTofHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBTofHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBTofHit(void *p) {
      return  p ? new(p) ::StPicoBTofHit : new ::StPicoBTofHit;
   }
   static void *newArray_StPicoBTofHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBTofHit[nElements] : new ::StPicoBTofHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBTofHit(void *p) {
      delete ((::StPicoBTofHit*)p);
   }
   static void deleteArray_StPicoBTofHit(void *p) {
      delete [] ((::StPicoBTofHit*)p);
   }
   static void destruct_StPicoBTofHit(void *p) {
      typedef ::StPicoBTofHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBTofHit

//______________________________________________________________________________
void StPicoBTofPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoBTofPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoBTofPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoBTofPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoBTofPidTraits(void *p) {
      return  p ? new(p) ::StPicoBTofPidTraits : new ::StPicoBTofPidTraits;
   }
   static void *newArray_StPicoBTofPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoBTofPidTraits[nElements] : new ::StPicoBTofPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoBTofPidTraits(void *p) {
      delete ((::StPicoBTofPidTraits*)p);
   }
   static void deleteArray_StPicoBTofPidTraits(void *p) {
      delete [] ((::StPicoBTofPidTraits*)p);
   }
   static void destruct_StPicoBTofPidTraits(void *p) {
      typedef ::StPicoBTofPidTraits current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoBTofPidTraits

//______________________________________________________________________________
void StPicoEmcPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoEmcPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoEmcPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoEmcPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoEmcPidTraits(void *p) {
      return  p ? new(p) ::StPicoEmcPidTraits : new ::StPicoEmcPidTraits;
   }
   static void *newArray_StPicoEmcPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoEmcPidTraits[nElements] : new ::StPicoEmcPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoEmcPidTraits(void *p) {
      delete ((::StPicoEmcPidTraits*)p);
   }
   static void deleteArray_StPicoEmcPidTraits(void *p) {
      delete [] ((::StPicoEmcPidTraits*)p);
   }
   static void destruct_StPicoEmcPidTraits(void *p) {
      typedef ::StPicoEmcPidTraits current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoEmcPidTraits

//______________________________________________________________________________
void StPicoEmcTrigger::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoEmcTrigger.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoEmcTrigger::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoEmcTrigger::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoEmcTrigger(void *p) {
      return  p ? new(p) ::StPicoEmcTrigger : new ::StPicoEmcTrigger;
   }
   static void *newArray_StPicoEmcTrigger(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoEmcTrigger[nElements] : new ::StPicoEmcTrigger[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoEmcTrigger(void *p) {
      delete ((::StPicoEmcTrigger*)p);
   }
   static void deleteArray_StPicoEmcTrigger(void *p) {
      delete [] ((::StPicoEmcTrigger*)p);
   }
   static void destruct_StPicoEmcTrigger(void *p) {
      typedef ::StPicoEmcTrigger current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoEmcTrigger

//______________________________________________________________________________
void StPicoEvent::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoEvent.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoEvent::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoEvent::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoEvent(void *p) {
      return  p ? new(p) ::StPicoEvent : new ::StPicoEvent;
   }
   static void *newArray_StPicoEvent(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoEvent[nElements] : new ::StPicoEvent[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoEvent(void *p) {
      delete ((::StPicoEvent*)p);
   }
   static void deleteArray_StPicoEvent(void *p) {
      delete [] ((::StPicoEvent*)p);
   }
   static void destruct_StPicoEvent(void *p) {
      typedef ::StPicoEvent current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoEvent

//______________________________________________________________________________
void StPicoMtdHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMtdHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMtdHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMtdHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMtdHit(void *p) {
      return  p ? new(p) ::StPicoMtdHit : new ::StPicoMtdHit;
   }
   static void *newArray_StPicoMtdHit(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMtdHit[nElements] : new ::StPicoMtdHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMtdHit(void *p) {
      delete ((::StPicoMtdHit*)p);
   }
   static void deleteArray_StPicoMtdHit(void *p) {
      delete [] ((::StPicoMtdHit*)p);
   }
   static void destruct_StPicoMtdHit(void *p) {
      typedef ::StPicoMtdHit current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMtdHit

//______________________________________________________________________________
void StPicoMtdPidTraits::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMtdPidTraits.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMtdPidTraits::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMtdPidTraits::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMtdPidTraits(void *p) {
      return  p ? new(p) ::StPicoMtdPidTraits : new ::StPicoMtdPidTraits;
   }
   static void *newArray_StPicoMtdPidTraits(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMtdPidTraits[nElements] : new ::StPicoMtdPidTraits[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMtdPidTraits(void *p) {
      delete ((::StPicoMtdPidTraits*)p);
   }
   static void deleteArray_StPicoMtdPidTraits(void *p) {
      delete [] ((::StPicoMtdPidTraits*)p);
   }
   static void destruct_StPicoMtdPidTraits(void *p) {
      typedef ::StPicoMtdPidTraits current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMtdPidTraits

//______________________________________________________________________________
void StPicoMtdTrigger::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoMtdTrigger.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoMtdTrigger::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoMtdTrigger::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoMtdTrigger(void *p) {
      return  p ? new(p) ::StPicoMtdTrigger : new ::StPicoMtdTrigger;
   }
   static void *newArray_StPicoMtdTrigger(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoMtdTrigger[nElements] : new ::StPicoMtdTrigger[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoMtdTrigger(void *p) {
      delete ((::StPicoMtdTrigger*)p);
   }
   static void deleteArray_StPicoMtdTrigger(void *p) {
      delete [] ((::StPicoMtdTrigger*)p);
   }
   static void destruct_StPicoMtdTrigger(void *p) {
      typedef ::StPicoMtdTrigger current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoMtdTrigger

//______________________________________________________________________________
void StPicoTrack::Streamer(TBuffer &R__b)
{
   // Stream an object of class StPicoTrack.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(StPicoTrack::Class(),this);
   } else {
      R__b.WriteClassBuffer(StPicoTrack::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_StPicoTrack(void *p) {
      return  p ? new(p) ::StPicoTrack : new ::StPicoTrack;
   }
   static void *newArray_StPicoTrack(Long_t nElements, void *p) {
      return p ? new(p) ::StPicoTrack[nElements] : new ::StPicoTrack[nElements];
   }
   // Wrapper around operator delete
   static void delete_StPicoTrack(void *p) {
      delete ((::StPicoTrack*)p);
   }
   static void deleteArray_StPicoTrack(void *p) {
      delete [] ((::StPicoTrack*)p);
   }
   static void destruct_StPicoTrack(void *p) {
      typedef ::StPicoTrack current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::StPicoTrack

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = 0);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 457,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const vector<unsigned int>*)0x0); R__UseDummy(_R__UNIQUE_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal((const vector<unsigned int>*)0x0)->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new((::ROOT::Internal::TOperatorNewHelper*)p) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete ((vector<unsigned int>*)p);
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] ((vector<unsigned int>*)p);
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace {
  void TriggerDictionaryInitialization_PicoDictionary_Impl() {
    static const char* headers[] = {
"StPicoBTOWHit.h",
"StPicoBTofHit.h",
"StPicoBTofPidTraits.h",
"StPicoEmcPidTraits.h",
"StPicoEmcTrigger.h",
"StPicoEvent.h",
"StPicoMtdHit.h",
"StPicoMtdPidTraits.h",
"StPicoMtdTrigger.h",
"StPicoTrack.h",
0
    };
    static const char* includePaths[] = {
"/home/jdb12/work/muonAna/include/CandidateMakers",
"/home/jdb12/work/muonAna/include/Cocktail",
"/home/jdb12/work/muonAna/include/Corrections",
"/home/jdb12/work/muonAna/include/DataAdapters",
"/home/jdb12/work/muonAna/include/EventPlane",
"/home/jdb12/work/muonAna/include/Exporters",
"/home/jdb12/work/muonAna/include/Filters",
"/home/jdb12/work/muonAna/include/HistoMakers",
"/home/jdb12/work/muonAna/include/LinkDef",
"/home/jdb12/work/muonAna/include/PicoDstClassLibrary",
"/home/jdb12/work/muonAna/include/Plotters",
"/home/jdb12/work/muonAna/include/ProductionUtils",
"/home/jdb12/work/muonAna/include/QA",
"/home/jdb12/work/muonAna/include/Skimmers",
"/home/jdb12/work/muonAna/include/StRefMultCorr",
"/home/jdb12/work/muonAna/include/StarClassLibrary",
"/home/jdb12/work/muonAna/include/TaskUtils",
"/home/jdb12/work/muonAna/include/TreeData",
"/home/jdb12/work/muonAna/include/TreeIO",
"/home/jdb12/work/muonAna/include/TreeMakers",
"/home/jdb12/work/muonAna/include/UnitTests",
"/home/jdb12/work/muonAna/include/vendor",
"/home/jdb12/work/muonAna/include/",
"/Volumes/data1/star1/jdb12/vendor/root-6.06.02/include",
"/home/jdb12/work/muonAna/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "PicoDictionary dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$StPicoBTOWHit.h")))  StPicoBTOWHit;
class __attribute__((annotate("$clingAutoload$StPicoBTofHit.h")))  StPicoBTofHit;
class __attribute__((annotate("$clingAutoload$StPicoBTofPidTraits.h")))  StPicoBTofPidTraits;
class __attribute__((annotate("$clingAutoload$StPicoEmcPidTraits.h")))  StPicoEmcPidTraits;
class __attribute__((annotate("$clingAutoload$StPicoEmcTrigger.h")))  StPicoEmcTrigger;
class __attribute__((annotate("$clingAutoload$StPicoEvent.h")))  StPicoEvent;
class __attribute__((annotate("$clingAutoload$StPicoMtdHit.h")))  StPicoMtdHit;
class __attribute__((annotate("$clingAutoload$StPicoMtdPidTraits.h")))  StPicoMtdPidTraits;
class __attribute__((annotate("$clingAutoload$StPicoMtdTrigger.h")))  StPicoMtdTrigger;
class __attribute__((annotate("$clingAutoload$StPicoTrack.h")))  StPicoTrack;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "PicoDictionary dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "StPicoBTOWHit.h"
#include "StPicoBTofHit.h"
#include "StPicoBTofPidTraits.h"
#include "StPicoEmcPidTraits.h"
#include "StPicoEmcTrigger.h"
#include "StPicoEvent.h"
#include "StPicoMtdHit.h"
#include "StPicoMtdPidTraits.h"
#include "StPicoMtdTrigger.h"
#include "StPicoTrack.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"StPicoBTOWHit", payloadCode, "@",
"StPicoBTofHit", payloadCode, "@",
"StPicoBTofPidTraits", payloadCode, "@",
"StPicoEmcPidTraits", payloadCode, "@",
"StPicoEmcTrigger", payloadCode, "@",
"StPicoEvent", payloadCode, "@",
"StPicoMtdHit", payloadCode, "@",
"StPicoMtdPidTraits", payloadCode, "@",
"StPicoMtdTrigger", payloadCode, "@",
"StPicoTrack", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("PicoDictionary",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_PicoDictionary_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_PicoDictionary_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_PicoDictionary() {
  TriggerDictionaryInitialization_PicoDictionary_Impl();
}
