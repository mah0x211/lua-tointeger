require('luacov')
local testcase = require('testcase')
local assert = require('assert')
local tointeger = require('tointeger')

function testcase.tointeger_parses_decimal()
    assert.equal(tointeger('42'), 42)
    assert.equal(tointeger('0'), 0)
    assert.equal(tointeger('-1'), -1)
end

function testcase.tointeger_returns_nil_for_hexadecimal()
    assert.is_nil(tointeger('0x10'))
end

function testcase.tointeger_returns_nil_for_non_integer()
    assert.is_nil(tointeger('abc'))
    assert.is_nil(tointeger(''))
end

function testcase.tointeger_returns_nil_for_float_string()
    assert.is_nil(tointeger('1.5'))
end
