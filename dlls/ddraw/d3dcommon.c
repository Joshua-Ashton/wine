/* Direct3D Common functions
 * Copyright (c) 1998 Lionel ULMER
 *
 * This file contains all common miscellaneous code that spans
 * different 'objects'
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "windef.h"
#include "objbase.h"
#include "ddraw.h"
#include "d3d.h"
#include "wine/debug.h"

#include "d3d_private.h"

WINE_DEFAULT_DEBUG_CHANNEL(ddraw);

const char *_get_renderstate(D3DRENDERSTATETYPE type) {
    static const char * const states[] = {
        "ERR",
	"D3DRENDERSTATE_TEXTUREHANDLE",
	"D3DRENDERSTATE_ANTIALIAS",
	"D3DRENDERSTATE_TEXTUREADDRESS",
	"D3DRENDERSTATE_TEXTUREPERSPECTIVE",
	"D3DRENDERSTATE_WRAPU",
	"D3DRENDERSTATE_WRAPV",
	"D3DRENDERSTATE_ZENABLE",
	"D3DRENDERSTATE_FILLMODE",
	"D3DRENDERSTATE_SHADEMODE",
	"D3DRENDERSTATE_LINEPATTERN",
	"D3DRENDERSTATE_MONOENABLE",
	"D3DRENDERSTATE_ROP2",
	"D3DRENDERSTATE_PLANEMASK",
	"D3DRENDERSTATE_ZWRITEENABLE",
	"D3DRENDERSTATE_ALPHATESTENABLE",
	"D3DRENDERSTATE_LASTPIXEL",
	"D3DRENDERSTATE_TEXTUREMAG",
	"D3DRENDERSTATE_TEXTUREMIN",
	"D3DRENDERSTATE_SRCBLEND",
	"D3DRENDERSTATE_DESTBLEND",
	"D3DRENDERSTATE_TEXTUREMAPBLEND",
	"D3DRENDERSTATE_CULLMODE",
	"D3DRENDERSTATE_ZFUNC",
	"D3DRENDERSTATE_ALPHAREF",
	"D3DRENDERSTATE_ALPHAFUNC",
	"D3DRENDERSTATE_DITHERENABLE",
	"D3DRENDERSTATE_ALPHABLENDENABLE",
	"D3DRENDERSTATE_FOGENABLE",
	"D3DRENDERSTATE_SPECULARENABLE",
	"D3DRENDERSTATE_ZVISIBLE",
	"D3DRENDERSTATE_SUBPIXEL",
	"D3DRENDERSTATE_SUBPIXELX",
	"D3DRENDERSTATE_STIPPLEDALPHA",
	"D3DRENDERSTATE_FOGCOLOR",
	"D3DRENDERSTATE_FOGTABLEMODE",
	"D3DRENDERSTATE_FOGTABLESTART",
	"D3DRENDERSTATE_FOGTABLEEND",
	"D3DRENDERSTATE_FOGTABLEDENSITY",
	"D3DRENDERSTATE_STIPPLEENABLE",
	"D3DRENDERSTATE_EDGEANTIALIAS",
	"D3DRENDERSTATE_COLORKEYENABLE",
	"ERR",
	"D3DRENDERSTATE_BORDERCOLOR",
	"D3DRENDERSTATE_TEXTUREADDRESSU",
	"D3DRENDERSTATE_TEXTUREADDRESSV",
	"D3DRENDERSTATE_MIPMAPLODBIAS",
	"D3DRENDERSTATE_ZBIAS",
	"D3DRENDERSTATE_RANGEFOGENABLE",
	"D3DRENDERSTATE_ANISOTROPY",
	"D3DRENDERSTATE_FLUSHBATCH",
	"D3DRENDERSTATE_TRANSLUCENTSORTINDEPENDENT",
	"D3DRENDERSTATE_STENCILENABLE",
	"D3DRENDERSTATE_STENCILFAIL",
	"D3DRENDERSTATE_STENCILZFAIL",
	"D3DRENDERSTATE_STENCILPASS",
	"D3DRENDERSTATE_STENCILFUNC",
	"D3DRENDERSTATE_STENCILREF",
	"D3DRENDERSTATE_STENCILMASK",
	"D3DRENDERSTATE_STENCILWRITEMASK",
	"D3DRENDERSTATE_TEXTUREFACTOR",
	"ERR",
	"ERR",
	"ERR",
	"D3DRENDERSTATE_STIPPLEPATTERN00",
	"D3DRENDERSTATE_STIPPLEPATTERN01",
	"D3DRENDERSTATE_STIPPLEPATTERN02",
	"D3DRENDERSTATE_STIPPLEPATTERN03",
	"D3DRENDERSTATE_STIPPLEPATTERN04",
	"D3DRENDERSTATE_STIPPLEPATTERN05",
	"D3DRENDERSTATE_STIPPLEPATTERN06",
	"D3DRENDERSTATE_STIPPLEPATTERN07",
	"D3DRENDERSTATE_STIPPLEPATTERN08",
	"D3DRENDERSTATE_STIPPLEPATTERN09",
	"D3DRENDERSTATE_STIPPLEPATTERN10",
	"D3DRENDERSTATE_STIPPLEPATTERN11",
	"D3DRENDERSTATE_STIPPLEPATTERN12",
	"D3DRENDERSTATE_STIPPLEPATTERN13",
	"D3DRENDERSTATE_STIPPLEPATTERN14",
	"D3DRENDERSTATE_STIPPLEPATTERN15",
	"D3DRENDERSTATE_STIPPLEPATTERN16",
	"D3DRENDERSTATE_STIPPLEPATTERN17",
	"D3DRENDERSTATE_STIPPLEPATTERN18",
	"D3DRENDERSTATE_STIPPLEPATTERN19",
	"D3DRENDERSTATE_STIPPLEPATTERN20",
	"D3DRENDERSTATE_STIPPLEPATTERN21",
	"D3DRENDERSTATE_STIPPLEPATTERN22",
	"D3DRENDERSTATE_STIPPLEPATTERN23",
	"D3DRENDERSTATE_STIPPLEPATTERN24",
	"D3DRENDERSTATE_STIPPLEPATTERN25",
	"D3DRENDERSTATE_STIPPLEPATTERN26",
	"D3DRENDERSTATE_STIPPLEPATTERN27",
	"D3DRENDERSTATE_STIPPLEPATTERN28",
	"D3DRENDERSTATE_STIPPLEPATTERN29",
	"D3DRENDERSTATE_STIPPLEPATTERN30",
	"D3DRENDERSTATE_STIPPLEPATTERN31"
    };
    static const char * const states_2[] = {
        "D3DRENDERSTATE_WRAP0",
	"D3DRENDERSTATE_WRAP1",
	"D3DRENDERSTATE_WRAP2",
	"D3DRENDERSTATE_WRAP3",
	"D3DRENDERSTATE_WRAP4",
	"D3DRENDERSTATE_WRAP5",
	"D3DRENDERSTATE_WRAP6",
	"D3DRENDERSTATE_WRAP7",
	"D3DRENDERSTATE_CLIPPING",
	"D3DRENDERSTATE_LIGHTING",
	"D3DRENDERSTATE_EXTENTS",
	"D3DRENDERSTATE_AMBIENT",
	"D3DRENDERSTATE_FOGVERTEXMODE",
	"D3DRENDERSTATE_COLORVERTEX",
	"D3DRENDERSTATE_LOCALVIEWER",
	"D3DRENDERSTATE_NORMALIZENORMALS",
	"D3DRENDERSTATE_COLORKEYBLENDENABLE",
	"D3DRENDERSTATE_DIFFUSEMATERIALSOURCE",
	"D3DRENDERSTATE_SPECULARMATERIALSOURCE",
	"D3DRENDERSTATE_AMBIENTMATERIALSOURCE",
	"D3DRENDERSTATE_EMISSIVEMATERIALSOURCE",
	"ERR",
	"ERR",
	"D3DRENDERSTATE_VERTEXBLEND",
	"D3DRENDERSTATE_CLIPPLANEENABLE",
    };
    if (type >= D3DRENDERSTATE_WRAP0) {
        type -= D3DRENDERSTATE_WRAP0;
	if (type >= (sizeof(states_2) / sizeof(states_2[0]))) return "ERR";
	return states_2[type];
    }
    if (type >= (sizeof(states) / sizeof(states[0]))) return "ERR";
    return states[type];
}
