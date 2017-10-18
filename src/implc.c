/*
 *  Copyright (C) 2017 Masatoshi Teruya
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to
 *  deal in the Software without restriction, including without limitation the
 *  rights to use, copy, modify, merge, publish, distribute, sublicense,
 *  and/or sell copies of the Software, and to permit persons to whom the
 *  Software is furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 *  DEALINGS IN THE SOFTWARE.
 *
 *  src/implc.c
 *  lua-rfcvalid
 *  Created by Masatoshi Teruya on 17/10/06.
 *
 */

#include <ctype.h>
#include <stdint.h>
// lua
#include <lua.h>
#include <lauxlib.h>


static int tointeger_lua( lua_State *L )
{
    size_t len = 0;
    uint8_t *str = (uint8_t*)luaL_checklstring( L, 1, &len );

    lua_pushnil( L );
    if( len )
    {
        size_t i = 0;

#define str2int(v) do {                                     \
    if( !isdigit( str[i] ) ){                               \
        return 1;                                           \
    }                                                       \
    /* dec = dec * 10 + ( ascii_digit - '0' ) */            \
    (v) = ( (v) << 3 ) + ( (v) << 1 ) + ( str[i] - '0' );   \
}while( ++i < len )

        switch( *str )
        {
            case '-': {
                int64_t dec = 0;

                i++;
                str2int( dec );
                lua_pushinteger( L, -dec );
                return 1;
            }

            case '+':
                i++;
            default: {
                uint64_t dec = 0;

                str2int( dec );
                lua_pushinteger( L, dec );
                return 1;
            }
        }

#undef str2num
    }

    return 1;
}


LUALIB_API int luaopen_tointeger_implc( lua_State *L )
{
    lua_createtable( L, 0, 2 );
    lua_pushstring( L, "tointeger" );
    lua_pushcfunction( L, tointeger_lua );
    lua_rawset( L, -3 );

#if defined(LUA_LJDIR)
    // set LUAJIT flag
    lua_pushstring( L, "LUAJIT" );
    lua_pushboolean( L, 1 );
    lua_rawset( L, -3 );
#endif

    return 1;
}


