#pragma once

#pragma comment(linker, "/nodefaultlib:msvcrt.lib")
#if defined(_DEBUG)
	#pragma comment(linker, "/nodefaultlib:libcmt.lib")
#else
	#pragma comment(linker, "/nodefaultlib:libcmtd.lib")
#endif

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "shlwapi.lib")

#define STRICT
#define _WIN32_DCOM
#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <Windows.h>
#include <crtdbg.h>
#include <time.h>
#include <emmintrin.h> // 'SSE2'
#include <Shlwapi.h> // 'PathFileExists'

#define UNUSED(var) (void)(var)
#define EXPORT _declspec(dllexport)
#define EXPORT_CPP extern "C" _declspec(dllexport)

#if defined(_DEBUG)
	#define ASSERT(cond) _ASSERTE((cond))
	#define STATIC_ASSERT(cond) static_assert((cond), "Static assertion failed.")
#else
	#define ASSERT(cond)
	#define STATIC_ASSERT(cond)
#endif

#if _MSC_VER >= 1900
	#define VS2015
#endif

typedef unsigned char Bool;
typedef wchar_t Char;
typedef unsigned char U8;
typedef unsigned short U16;
typedef unsigned int U32;
typedef unsigned long long U64;
typedef signed char S8;
typedef signed short S16;
typedef signed int S32;
typedef signed long long S64;
typedef __m128i S128;

static const Bool False = 0;
static const Bool True = 1;

typedef struct SClass
{
	U64 RefCnt;
	void* ClassTable;
} SClass;

static const S64 DefaultRefCntFunc = 0; // Just before exiting the function, this is incremented for 'GcInstance'.
static const S64 DefaultRefCntOpe = 1; // For 'GcInstance'.

static void* DummyPtr = (void*)1i64; // An invalid pointer used to point to non-NULL.

extern void* Heap;
extern S64* HeapCnt;
extern S64 AppCode;
extern const Char* AppName;
extern HINSTANCE Instance;

void* AllocMem(size_t size);
void FreeMem(void* ptr);
void ThrowImpl(U32 code, const Char* msg);
void* LoadFileAll(const Char* path, size_t* size, Bool occurExcpt);
void* OpenFileStream(const Char* path);
void CloseFileStream(void* handle);
size_t ReadFileStream(void* handle, size_t size, void* buf);
Bool SeekFileStream(void* handle, S64 offset, S64 origin);
S64 TellFileStream(void* handle);
Bool StrCmpIgnoreCase(const Char* a, const Char* b);
U8 SwapEndianU8(U8 n);
U16 SwapEndianU16(U16 n);
U32 SwapEndianU32(U32 n);
U64 SwapEndianU64(U64 n);
Bool IsPowerOf2(U64 n);
#if defined(DBG)
#define THROW(code, msg) ThrowImpl((code), (msg))
#else
#define THROW(code, msg) ThrowImpl((code), NULL)
#endif
