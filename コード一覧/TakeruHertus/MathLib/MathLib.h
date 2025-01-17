#pragma once

template <typename T>
T Clamp(T _value, T _minValue, T _maxValue)
{
	if (_value < _minValue) return _minValue;
	if (_value > _maxValue) return _maxValue;
	return _value;
}


