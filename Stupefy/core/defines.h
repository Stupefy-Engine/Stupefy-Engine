/****************************************************************************/
/*  defines.h                                                               */
/****************************************************************************/
/*                          This file is a part of:                         */
/*                              STUPEFY ENGINE                              */
/*                                                                          */
/****************************************************************************/
/*  Copyright[2020] Harshit Bargujar                                        */
/*                                                                          */
/*  Licensed under the Apache License, Version 2.0 (the "License");         */
/*  you may not use this file except in compliance with the License.        */
/*  You may obtain a copy of the License at                                 */
/*                                                                          */
/*  http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                          */
/*  Unless required by applicable law or agreed to in writing, software     */
/*  distributed under the License is distributed on an "AS IS" BASIS,       */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*/
/*  See the License for the specific language governing permissions and     */
/*  limitations under the License.                                          */
/****************************************************************************/


#pragma once

#if _WIN32 || _WIN64
	#define PLATFORM_WINDOWS
#else
#if __linux__
	#define PLATFORM_LINUX
#elif __APPLE__
	#define PLATFORM_MAC
#else
	#error "Unable to determine platform!"
#endif
#endif

#ifdef PLATFORM_WINDOWS
#define FORCEINLINE __forceinline
#define FORCENOINLINE _declspec(noinline)
/*#ifdef STUPEFY_BUILD_LIB
#define STUPEFY_API __declspec(dllexport)
#else
#define STUPEFY_API __declspec(dllimport)
#endif
#elif PLATFORM_LINUX || PLATFORM_MAC
#define FORCEINLINE inline*/
#endif

#define ASSERTIONS_ENABLED
#ifdef ASSERTIONS_ENABLED
#include <iostream>

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugbreak();
#else
#define debugBreak() __asm { int 3 }
#endif

#define ASSERT(expr) \
{ \
    if( expr ) \
    { \
    } \
    else \
    { \
        reportAssertionFailure(#expr, "", __FILE__, __LINE__); \
        debugBreak(); \
    } \
}

#define ASSERT_MSG(expr,message) \
{ \
    if( expr ) \
    { \
    } \
    else \
    { \
        reportAssertionFailure(#expr,message, __FILE__, __LINE__); \
        debugBreak(); \
    } \
}

#ifdef _DEBUG
#define ASSERT_DEBUG(expr) \
{ \
    if( expr ) \
    { \
    } \
    else \
    { \
        reportAssertionFailure(#expr, __FILE__, __LINE__); \
        debugBreak(); \
    } \
}
#else
    #define ASSERT_DEBUG(expr)
#endif

FORCEINLINE void reportAssertionFailure(const char* expression, const char* message, const char* file, int line)
{
	std::cerr << "Assertion Failure: " << expression << ", message: " << "', in file: " << file << ", line: " << line << "\n";
}

#else
#define ASSERT(expr)
#define ASSERT_MSG(expr,message)
#define ASSERT_DEBUG(expr)

#endif