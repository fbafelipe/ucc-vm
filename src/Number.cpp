#include "Number.h"

#include <cassert>
#include <cstdlib>
#include <cstring>

bool Number::isInteger(Type t) {
	return t == INT;
}

bool Number::isFloat(Type t) {
	return t == FLOAT;
}

Number::Number() : type(INT) {
	memset(&value, 0, sizeof(Value));
}

Number::Number(Type t) : type(t) {
	memset(&value, 0, sizeof(Value));
}

Number::Number(Type t, Value v) : type(t), value(v) {}

Number::Number(Type t, long long int v) : type(t) {
	memset(&value, 0, sizeof(Value));
	value.intValue = v;
}

Number::Number(Type t, double v) : type(t) {
	memset(&value, 0, sizeof(Value));
	value.floatValue = v;
}

Number::Number(bool b) : type(INT) {
	memset(&value, 0, sizeof(Value));
	value.intValue = b ? 1 : 0;
}

Number::~Number() {}

Number::Type Number::getType() const {
	return type;
}

Number Number::castTo(Type t) const {
	if (isInteger() ^ isInteger(t)) {
		if (isInteger(t)) return Number(t, (long long int)value.floatValue);
		else return Number(t, (double)value.intValue);
	}
	
	if (isInteger()) return Number(t, value.intValue);
	return Number(t, value.floatValue);
}

bool Number::isInteger() const {
	return isInteger(type);
}

bool Number::isFloat() const {
	return isFloat(type);
}

long long int Number::intValue() const {
	if (isInteger()) return value.intValue;
	return (long long int)value.floatValue;
}

double Number::floatValue() const {
	if (isFloat()) return value.floatValue;
	return (long double)value.intValue;
}

bool Number::boolValue() const {
	return intValue();
}

Number Number::operator+(const Number & other) const {
	Type t = getCastType(type, other.type);
	if (isInteger() && other.isInteger()) return Number(t, value.intValue + other.value.intValue);
	return Number(t, value.floatValue + other.value.floatValue);
}

Number Number::operator-(const Number & other) const {
	Type t = getCastType(type, other.type);
	if (isInteger() && other.isInteger()) return Number(t, value.intValue - other.value.intValue);
	return Number(t, value.floatValue - other.value.floatValue);
}

Number Number::operator*(const Number & other) const {
	Type t = getCastType(type, other.type);
	if (isInteger() && other.isInteger()) return Number(t, value.intValue * other.value.intValue);
	return Number(t, value.floatValue * other.value.floatValue);
}

Number Number::operator/(const Number & other) const {
	Type t = getCastType(type, other.type);
	if (isInteger() && other.isInteger()) return Number(t, value.intValue / other.value.intValue);
	return Number(t, value.floatValue / other.value.floatValue);
}

Number Number::operator%(const Number & other) const {
	Type t = getCastType(type, other.type);
	if (isInteger() && other.isInteger()) return Number(t, value.intValue % other.value.intValue);
	abort();
}

Number Number::operator&(const Number & other) const {
	Type t = getCastType(type, other.type);
	if (!isInteger() || !other.isInteger()) abort();
	return Number(t, value.intValue & other.value.intValue);
}

Number Number::operator|(const Number & other) const {
	Type t = getCastType(type, other.type);
	if (!isInteger() || !other.isInteger()) abort();
	return Number(t, value.intValue | other.value.intValue);
}

Number Number::operator^(const Number & other) const {
	Type t = getCastType(type, other.type);
	assert(isInteger() && other.isInteger());
	return Number(t, value.intValue ^ other.value.intValue);
}

Number Number::operator<<(int shifts) const {
	assert(isInteger());
	return Number(type, value.intValue << shifts);
}

Number Number::operator>>(int shifts) const {
	assert(!isFloat());
	return Number(type, value.intValue >> shifts);
}

Number Number::operator+() const {
	if (isInteger()) return Number(type, +value.intValue);
	return Number(type, +value.floatValue);
}

Number Number::operator-() const {
	if (isInteger()) return Number(type, -value.intValue);
	return Number(type, -value.floatValue);
}

Number Number::operator~() const {
	assert(!isFloat());
	return Number(type, ~value.intValue);
}

Number Number::operator!() const {
	if (isInteger()) return Number(INT, (long long int)!value.intValue);
	return Number(INT, (long long int)!value.floatValue);
}

Number & Number::operator=(const Number & other) {
	type = other.type;
	value = other.value;
	return *this;
}

Number & Number::operator+=(const Number & other) {
	return *this = *this + other;
}

Number & Number::operator-=(const Number & other) {
	return *this = *this - other;
}

Number & Number::operator*=(const Number & other) {
	return *this = *this * other;
}

Number & Number::operator/=(const Number & other) {
	return *this = *this / other;
}

Number & Number::operator%=(const Number & other) {
	return *this = *this % other;
}

Number & Number::operator&=(const Number & other) {
	return *this = *this & other;
}

Number & Number::operator|=(const Number & other) {
	return *this = *this | other;
}

Number & Number::operator^=(const Number & other) {
	return *this = *this ^ other;
}

Number & Number::operator<<=(int shifts) {
	return *this = *this << shifts;
}

Number & Number::operator>>=(int shifts) {
	return *this = *this >> shifts;
}

bool Number::operator==(const Number & other) const {
	if (isInteger() && isInteger()) return value.intValue == other.value.intValue;
	return floatValue() == other.floatValue();
}

bool Number::operator!=(const Number & other) const {
	if (isInteger() && isInteger()) return value.intValue != other.value.intValue;
	return floatValue() != other.floatValue();
}

bool Number::operator<(const Number & other) const {
	if (isInteger() && isInteger()) return value.intValue < other.value.intValue;
	return floatValue() < other.floatValue();
}

bool Number::operator>(const Number & other) const {
	if (isInteger() && isInteger()) return value.intValue > other.value.intValue;
	return floatValue() > other.floatValue();
}

bool Number::operator<=(const Number & other) const {
	if (isInteger() && isInteger()) return value.intValue <= other.value.intValue;
	return floatValue() <= other.floatValue();
}

bool Number::operator>=(const Number & other) const {
	if (isInteger() && isInteger()) return value.intValue >= other.value.intValue;
	return floatValue() >= other.floatValue();
}

Number::Type Number::getCastType(Type a, Type b) const {
	if (a > b) return a;
	return b;
}

Number::TypeMap Number::createTypeMap() {
	TypeMap typeMap;
	
	typeMap["float"] = FLOAT;
	typeMap["int"] = INT;
	
	return typeMap;
}

Number::TypeMap Number::typeMap = createTypeMap();
