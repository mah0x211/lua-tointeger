# lua-tointeger


[![test](https://github.com/mah0x211/lua-tointeger/actions/workflows/test.yml/badge.svg)](https://github.com/mah0x211/lua-tointeger/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/mah0x211/lua-tointeger/branch/master/graph/badge.svg)](https://codecov.io/gh/mah0x211/lua-tointeger)

string to integer conversion module.


## Installation

```
luarocks install tointeger
```


## API


### iv = tointeger( v )

converts `v` to an integer and returns it.  If `v` is not convertible to an integer, returns `nil`.

The conversion follows the same rules as Lua 5.4 `math.tointeger`:

| input type | result |
|---|---|
| integer | the integer itself |
| float with no fractional part | the truncated integer |
| float with a fractional part | `nil` |
| numeric string convertible to an integer | the parsed integer |
| numeric string convertible to a non-integer float | `nil` |
| any other type | `nil` |

**Parameters**

- `v:any`: value to convert.

**Returns**

- `iv:integer|nil`: the resulting integer, or `nil` if `v` is not convertible.


**Example**

```lua
local tointeger = require('tointeger')

-- strings are parsed and converted
print(tointeger('123'))    -- 123
print(tointeger('-456'))   -- -456
print(tointeger('1.5'))    -- nil (fractional part)

-- numbers are checked for a fractional part
print(tointeger(42))       -- 42
print(tointeger(42.0))     -- 42
print(tointeger(3.14))     -- nil (fractional part)

-- non-numeric values return nil
print(tointeger('abc'))    -- nil
print(tointeger(true))     -- nil
```
