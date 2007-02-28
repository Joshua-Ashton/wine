/*
 * Copyright 2005 James Hawkins
 * Copyright 2007 Jacek Caban for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef HHCTRL_H
#define HHCTRL_H

#include <stdarg.h>

#define COBJMACROS

#include "windef.h"
#include "winbase.h"
#include "winuser.h"
#include "winnls.h"
#include "htmlhelp.h"
#include "ole2.h"
#include "exdisp.h"
#include "mshtmhst.h"

#ifdef INIT_GUID
#include "initguid.h"
#endif

#include "wine/itss.h"
#include "wine/unicode.h"

#define WB_GOBACK     0
#define WB_GOFORWARD  1
#define WB_GOHOME     2
#define WB_SEARCH     3
#define WB_REFRESH    4
#define WB_STOP       5

typedef struct CHMInfo
{
    IITStorage *pITStorage;
    IStorage *pStorage;
    LPCWSTR szFile;

    IStream *strings_stream;
    char **strings;
    DWORD strings_size;
} CHMInfo;


typedef struct {
    IOleClientSite *client_site;
    IWebBrowser2 *web_browser;
    IOleObject *wb_object;

    HH_WINTYPEW WinType;
    CHMInfo *pCHMInfo;
    HWND hwndTabCtrl;
    HWND hwndSizeBar;
    HFONT hFont;
} HHInfo;

BOOL InitWebBrowser(HHInfo*,HWND);
void ReleaseWebBrowser(HHInfo*);
void ResizeWebBrowser(HHInfo*,DWORD,DWORD);
void DoPageAction(HHInfo*,DWORD);

CHMInfo *OpenCHM(LPCWSTR szFile);
BOOL LoadWinTypeFromCHM(CHMInfo *pCHMInfo, HH_WINTYPEW *pHHWinType);
CHMInfo *CloseCHM(CHMInfo *pCHMInfo);

HHInfo *CreateHelpViewer(LPCWSTR);
void ReleaseHelpViewer(HHInfo*);
BOOL NavigateToChm(HHInfo*,LPCWSTR,LPCWSTR);

/* memory allocation functions */

static inline void *hhctrl_alloc(size_t len)
{
    return HeapAlloc(GetProcessHeap(), 0, len);
}

static inline void *hhctrl_alloc_zero(size_t len)
{
    return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, len);
}

static inline void *hhctrl_realloc(void *mem, size_t len)
{
    return HeapReAlloc(GetProcessHeap(), 0, mem, len);
}

static inline void *hhctrl_realloc_zero(void *mem, size_t len)
{
    return HeapReAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, mem, len);
}

static inline BOOL hhctrl_free(void *mem)
{
    return HeapFree(GetProcessHeap(), 0, mem);
}

static inline LPWSTR strdupW(LPCWSTR str)
{
    LPWSTR ret;
    int size;

    if(!str)
        return NULL;

    size = (strlenW(str)+1)*sizeof(WCHAR);
    ret = hhctrl_alloc(size);
    memcpy(ret, str, size);

    return ret;
}

static inline LPWSTR strdupAtoW(LPCSTR str)
{
    LPWSTR ret;
    DWORD len;

    if(!str)
        return NULL;

    len = MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0);
    ret = hhctrl_alloc(len*sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, str, -1, ret, len);

    return ret;
}

extern HINSTANCE hhctrl_hinstance;
extern BOOL hh_process;

#endif
