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
 *  src/tointeger.c
 *  lua-tointeger
 *  Created by Masatoshi Teruya on 17/10/06.
 *
 */

// lua
#include <lauxlib.h>

// system
#include <ctype.h>
#include <stdint.h>

static int tointeger_lua(lua_State *L)
{
    switch (lua_type(L, 1)) {
    /* number: avoid string round-trip entirely */
    case LUA_TNUMBER:
#if LUA_VERSION_NUM >= 503
        /* Lua 5.3+: integer subtype — return as-is */
        if (lua_isinteger(L, 1)) {
            lua_pushvalue(L, 1);
            return 1;
        }
#endif
        /* float subtype: accept only when fractional part is zero */
        {
            lua_Number n   = lua_tonumber(L, 1);
            lua_Integer iv = (lua_Integer)n;
            if ((lua_Number)iv == n) {
                lua_pushinteger(L, iv);
            } else {
                lua_pushnil(L);
            }
            return 1;
        }

    /* string: parse decimal integer manually */
    case LUA_TSTRING: {
        size_t len         = 0;
        const uint8_t *str = (const uint8_t *)lua_tolstring(L, 1, &len);
        size_t i           = 0;

        if (!len) {
            lua_pushnil(L);
            return 1;
        }

        switch (*str) {
        case '-': {
            int64_t dec = 0;
            i++;
            do {
                if (!isdigit(str[i])) {
                    lua_pushnil(L);
                    return 1;
                }
                dec = (dec << 3) + (dec << 1) + (str[i] - '0');
            } while (++i < len);
            lua_pushinteger(L, -dec);
            return 1;
        }
        case '+':
            i++;
            /* fall through */
        default: {
            uint64_t dec = 0;
            do {
                if (!isdigit(str[i])) {
                    lua_pushnil(L);
                    return 1;
                }
                dec = (dec << 3) + (dec << 1) + (str[i] - '0');
            } while (++i < len);
            lua_pushinteger(L, dec);
            return 1;
        }
        }
    }

    default:
        lua_pushnil(L);
        return 1;
    }
}

LUALIB_API int luaopen_tointeger(lua_State *L)
{
    lua_pushcfunction(L, tointeger_lua);
    return 1;
}
