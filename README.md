# lua-tointeger


[![test](https://github.com/mah0x211/lua-tointeger/actions/workflows/test.yml/badge.svg)](https://github.com/mah0x211/lua-tointeger/actions/workflows/test.yml)
[![codecov](https://codecov.io/gh/mah0x211/lua-tointeger/branch/master/graph/badge.svg)](https://codecov.io/gh/mah0x211/lua-tointeger)

string to integer conversion module.


## Installation

```
luarocks install tointeger
```


## Usage


```lua
local tointeger = require('tointeger')

print( tointeger('123') == 123 )
print( tointeger('-123') == -123 )
```
