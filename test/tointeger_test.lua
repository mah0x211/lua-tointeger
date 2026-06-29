require('luacov')
local testcase = require('testcase')
local assert = require('assert')
local tointeger = require('tointeger')

function testcase.parses_decimal_string()
    assert.equal(tointeger('42'), 42)
    assert.equal(tointeger('0'), 0)
    assert.equal(tointeger('-1'), -1)
    assert.equal(tointeger('+100'), 100)
end

function testcase.returns_nil_for_non_decimal_string()
    assert.is_nil(tointeger('0x10'))
    assert.is_nil(tointeger('abc'))
    assert.is_nil(tointeger(''))
    assert.is_nil(tointeger('1.5'))
end

function testcase.accepts_integer_number_directly()
    assert.equal(tointeger(42), 42)
    assert.equal(tointeger(0), 0)
    assert.equal(tointeger(-1), -1)
end

function testcase.returns_nil_for_float_number()
    assert.is_nil(tointeger(1.5))
    assert.is_nil(tointeger(3.14))
end

function testcase.accepts_whole_float_number()
    assert.equal(tointeger(42.0), 42)
    assert.equal(tointeger(-1.0), -1)
end

function testcase.returns_nil_for_non_numeric_type()
    assert.is_nil(tointeger(true))
    assert.is_nil(tointeger(nil))
    assert.is_nil(tointeger({}))
end
