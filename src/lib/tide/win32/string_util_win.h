/**
* This file has been modified from its orginal sources.
*
* Copyright (c) 2012 Software in the Public Interest Inc (SPI)
* Copyright (c) 2012 David Pratt
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
***
* Copyright (c) 2008-2012 Appcelerator Inc.
* 
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
**/

#ifndef BASE_STRING_UTIL_WIN_H_
#define BASE_STRING_UTIL_WIN_H_

#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>

namespace base {

inline int strcasecmp(const char* s1, const char* s2) {
    return _stricmp(s1, s2);
}

inline int strncasecmp(const char* s1, const char* s2, size_t count) {
    return _strnicmp(s1, s2, count);
}

inline int vsnprintf(char* buffer, size_t size,
    const char* format, va_list arguments) {
    int length = vsnprintf_s(buffer, size, size - 1, format, arguments);
    if (length < 0)
        return _vscprintf(format, arguments);
    return length;
}

inline int vswprintf(wchar_t* buffer, size_t size,
    const wchar_t* format, va_list arguments) {
    //DCHECK(IsWprintfFormatPortable(format));

    int length = _vsnwprintf_s(buffer, size, size - 1, format, arguments);
    if (length < 0)
        return _vscwprintf(format, arguments);
    return length;
}

}  // namespace base

#endif  // BASE_STRING_UTIL_WIN_H_