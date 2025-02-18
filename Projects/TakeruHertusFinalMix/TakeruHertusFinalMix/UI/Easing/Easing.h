#pragma once
#include <cmath>
#include <limits>
#include <algorithm>

/*==================================================================*/
//以下参照サイト
//[https://qiita.com/HnniTns/items/9e3799d3b414dccbbd7d]
//題名：イージング関数一覧【C++】
/*==================================================================*/

struct Easing
{
private:
	/*0.～*/
	static constexpr float pai = static_cast<float>(3.141592653589793f);
	static constexpr float _0 = static_cast<float>(0);
	static constexpr float _0_5 = static_cast<float>(0.5f);
	static constexpr float _0_75 = static_cast<float>(0.75f);
	static constexpr float _0_9375 = static_cast<float>(0.9375f);
	static constexpr float _0_984375 = static_cast<float>(0.984375f);

	/*1.～*/
	static constexpr float _1 = static_cast<float>(1);
	static constexpr float _1_5 = static_cast<float>(1.5f);
	static constexpr float _1_525 = static_cast<float>(1.525f);
	

	/*2.～*/
	static constexpr float _2 = static_cast<float>(2);
	static constexpr float _2_25 = static_cast<float>(2.25f);
	static constexpr float _2_5 = static_cast<float>(2.5f);
	static constexpr float _2_625 = static_cast<float>(2.625f);
	static constexpr float _2_75 = static_cast<float>(2.75f);


	static constexpr float _7_5625 = static_cast<float>(7.5625);

	static constexpr float _10 = static_cast<float>(10);

	static constexpr float _180 = static_cast<float>(180);

	static constexpr float _90 = static_cast<float>(90);

	float ToRadian(const float _angle)
	{
		return static_cast<float>(_angle * pai / _180);
	}

public:
	float InQuad(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		return _max * _time * _time + _min;
	}

	float OutQuad(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		return -_max * _time * (_time - _2) + _min;
	}

	float InOutQuad(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		if (_time / _2 < _1) return _max / _2 * _time * _time + _min;

		--_time;

		return -_max * (_time * (_time - _2) - _1) + _min;
	}

	float InCubic(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		return _max * _time * _time * _time + _min;
	}

	float OutCubic(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time = _time / _totalTime - _1;

		return _max * (_time * _time * _time + _1) + _min;
	}

	float InOutCubic(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		if (_time / _2 < _1) return _max / _2 * _time * _time * _time + _min;

		_time -= _2;

		return _max / _2 * (_time * _time * _time + _2) + _min;
	}

	float InQuart(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		return _max * _time * _time * _time * _time + _min;
	}

	float OutQuart(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time = _time / _totalTime - _1;

		return -_max * (_time * _time * _time * _time - _1) + _min;
	}

	float InOutQuart(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		if (_time / _2 < _1) return _max / _2 * _time * _time * _time * _time + _min;

		_time -= _2;

		return -_max / _2 * (_time * _time * _time * _time - _2) + _min;
	}


	float InQuint(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		return _max * _time * _time * _time * _time * _time + _min;
	}

	float OutQuint(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time = _time / _totalTime - _1;

		return _max * (_time * _time * _time * _time * _time + _1) + _min;
	}

	float InOutQuint(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		if (_time / _2 < _1) return _max / _2 * _time * _time * _time * _time * _time + _min;
	}

	float InSine(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;

		return -_max * std::cos(_time * ToRadian(_90) / _totalTime) + _max + _min;
	}

	float OutSine(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;

		return _max * std::sin(_time * ToRadian(_90) / _totalTime) + _min;
	}

	float InOutSine(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;

		return -_max / _2 * (std::cos(_time * pai / _totalTime) - 1) + _min;
	}

	float InCirc(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;
		_time = (std::max)((std::min)(_time, _1), -_1);

		return -_max * (std::sqrt(_1 - _time * _time) - _1) + _min;
	}

	float OutCirc(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= (_totalTime - _1);
		_time = (std::max)((std::min)(_time, _1), -_1);//キャスト

		return _max * std::sqrt(_1 - _time * _time) + _min;
	}

	float InOutCirc(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;
		_time = (std::max)((std::min)(_time, _1), -_1);//キャスト

		if (_time / _2 < _1) return -_max / _2 * (std::sqrt(_1 - _time * _time) - _1) + _min;

		_time -= _2;

		return _max / _2 * (std::sqrt(_1 - _time * _time) + _1) + _min;
	}

	float InBack(float _time, float _totalTime, float _back, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;
		 
		return _max * _time * _time * ((_back + _1) * _time - _back) + _min;
	}

	float OutBack(float _time, float _totalTime, float _back, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time = _time / _totalTime - _1;

		return _max * (_time * _time * ((_back + _1) * _time * _back) + _1) + _min;
	}

	float InOutBack(float _time, float _totalTime, float _back, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_back *= _1_525;

		if (_time / _2 < _1) return _max * (_time * _time * ((_back + _1) * _time - _back)) + _min;

		_time -= _2;

		return _max / _2 * (_time * _time * ((_back + _1) * _time + _back) + _2) + _min;
	}

	float OutBounce(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		_max -= _min;
		_time /= _totalTime;

		if (_time < _1 / _2_75) return _max * (_7_5625 * _time * _time) * _min;

		else if (_time < _2 / _2_75)
		{
			_time -= _1_5 / _2_75;

			return _max * (_7_5625 * _time * _time + _0_75) + _min;
		}
		else if (_time < _2_5 / _2_75)
		{
			_time -= _2_25 / _2_75;

			return _max * (_7_5625 * _time * _time + _0_9375) + _min;
		}
		else
		{
			_time -= _2_625 / _2_75;

			return _max * (_7_5625 * _time * _time + _0_984375) + _min;
		}
	}

	float InBounce(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		return _max - OutBounce(_totalTime - _time, _totalTime, _max - _min, _0) + _min;
	}

	float InOutBounce(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		if (_time < _totalTime / _2)
		{
			return InBounce(_time * _2, _totalTime, _max - _min, _max) * _0_5 + _min;
		}
		else
		{
			return OutBounce(_time * _2 - _totalTime, _totalTime, _max - _min, _0) * _0_5 + _min + (_max - _min) * _0_5;
		}

	}

	float Linear(float _time, float _totalTime, float _max = _1, float _min = _0)
	{
		return (_max - _min) * _time / _totalTime + _min;
	}

};