//----------------------------------------------------------------------------------------------------------------------
//
//	STATISTICS
//
//----------------------------------------------------------------------------------------------------------------------
//
// The MIT License (MIT)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software
// and associated documentation files (the "Software"), to deal in the Software without
// restriction, including without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or
// substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
// BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//
//----------------------------------------------------------------------------------------------------------------------
//
// Copyright (c) 2018 Nic Holthaus
//
//----------------------------------------------------------------------------------------------------------------------
//
// ATTRIBUTION:
//
//
//----------------------------------------------------------------------------------------------------------------------
//
/// @file	statistics.h
/// @brief	A class to measure various statistics of a population. All operations (except iterator
///			insert), are O(1), and the Statistics class uses a minimal, fixed amount of memory (i.e.
///			it does NOT keep a list of all members of its population);
//
//----------------------------------------------------------------------------------------------------------------------

#pragma once
#ifndef statistics_h__
#	define statistics_h__

//------------------------------
//	INCLUDES
//------------------------------

#	include <algorithm>
#	include <initializer_list>
#	include <limits>
#	include <utility>

//----------------------------------------------------------------------------------------------------------------------
//	CLASS STATISTICS
//----------------------------------------------------------------------------------------------------------------------
///	@brief		Keeps a simple average of a series of measurements
///	@details
//----------------------------------------------------------------------------------------------------------------------
template<class T>
class Statistics
{
public:
	//----------------------------
	//  TYPES
	//----------------------------

	using T2 = decltype(T{} * T{});

public:
	//----------------------------
	//  CONSTRUCTORS
	//----------------------------

	inline Statistics();
	inline explicit Statistics(T measurement);
	inline Statistics(std::initializer_list<T> init);
	template<class InputIt>
	inline explicit Statistics(InputIt first, InputIt last);

	//----------------------------
	//  INSERTERS
	//----------------------------

	inline Statistics& insert(const T& measurement) noexcept;
	template<class InputIt>
	inline Statistics& insert(const InputIt& first, const InputIt& last) noexcept;
	inline Statistics& operator+=(const T& measurement) noexcept;
	inline Statistics& operator+=(const Statistics& rhs) noexcept;

	//----------------------------
	//  CLEAR
	//----------------------------

	inline void clear() noexcept;

	//----------------------------
	//  ACCESSORS
	//----------------------------

	[[nodiscard]] inline size_t count() const noexcept;
	[[nodiscard]] inline T      latest() const noexcept;
	[[nodiscard]] inline T      mean() const noexcept;
	[[nodiscard]] inline T      min() const noexcept;
	[[nodiscard]] inline T      max() const noexcept;
	[[nodiscard]] inline T      sum() const noexcept;
	[[nodiscard]] inline T2     sumOfSquares() const noexcept;
	[[nodiscard]] inline auto   variance() const noexcept;
	[[nodiscard]] inline T      standardDeviation() const noexcept;

	//----------------------------
	//      FRIEND OPERATORS
	//----------------------------

	template<class U>
	friend Statistics<U> operator+(const Statistics<U>& lhs, const T& rhs) noexcept;
	template<class U>
	friend Statistics<U> operator+(const Statistics<U>& lhs, const Statistics<U>& rhs) noexcept;
	template<class U>
	friend bool operator==(const Statistics<U>& lhs, const Statistics<U>& rhs) noexcept;
	template<class U>
	friend bool operator!=(const Statistics<U>& lhs, const Statistics<U>& rhs) noexcept;
	template<class U>
	friend bool operator<(const Statistics<U>& lhs, const Statistics<U>& rhs) noexcept;
	template<class U>
	friend bool operator<=(const Statistics<U>& lhs, const Statistics<U>& rhs) noexcept;
	template<class U>
	friend bool operator>(const Statistics<U>& lhs, const Statistics<U>& rhs) noexcept;
	template<class U>
	friend bool operator>=(const Statistics<U>& lhs, const Statistics<U>& rhs) noexcept;

private:
	//----------------------------
	//  PRIVATE MEMBERS
	//----------------------------

	size_t m_count{};
	T      m_latest;
	T      m_max;
	T      m_min;
	T      m_sum;
	T2     m_sumOfSquares;
};

//======================================================================================================================
//      MEMBER FUNCTIONS
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: Constructor [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Default Constructor
//----------------------------------------------------------------------------------------------------------------------
template<class T>
Statistics<T>::Statistics()
    : m_count(T{0})
    , m_latest(T{0})
    , m_max(std::numeric_limits<T>::lowest())
    , m_min(std::numeric_limits<T>::max())
    , m_sum(T{0})
    , m_sumOfSquares(T2{0})
{
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: Constructor [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Constructor
/// @details	O(1) complexity
/// @param[in]	measurement	Initial measurement
//----------------------------------------------------------------------------------------------------------------------
template<class T>
Statistics<T>::Statistics(T measurement)
    : m_count(1)
    , m_latest(measurement)
    , m_max(measurement)
    , m_min(measurement)
    , m_sum(measurement)
    , m_sumOfSquares(measurement * measurement)
{
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: Initializer List Construtor [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Construct from initializer list
/// @details	O(N) complexity.
/// @param[in]	init	initializer list containing the population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
Statistics<T>::Statistics(std::initializer_list<T> init)
    : Statistics()
{
	for (const auto& measurement : init)
		*this += measurement;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: Range Construtor [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief     Constructor from input iterators
/// @details		O(N) complexity
/// @param[in] first    beginning of the measurement range
/// @param[in] last     end of the measurement range
//----------------------------------------------------------------------------------------------------------------------
template<class T>
template<class InputIt>
Statistics<T>::Statistics(InputIt first, InputIt last)
    : Statistics()
{
	for (InputIt itr = first; itr != last; ++itr)
		*this += *itr;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: clear [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Clears statistics
/// @details	O(1) complexity.
//----------------------------------------------------------------------------------------------------------------------
template<class T>
void Statistics<T>::clear() noexcept
{
	*this = std::move(Statistics());
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: count [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Measurement count.
/// @details	O(1) complexity.
/// @returns	The number of measurements taken
//----------------------------------------------------------------------------------------------------------------------
template<class T>
size_t Statistics<T>::count() const noexcept
{
	return m_count;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: insert [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Insert a measurement into the population
/// @details	O(1) complexity. Equivalent to `+=`.
/// @param[in]	measurement	Measurement to add to the population
/// @returns	Reference to `this`
//----------------------------------------------------------------------------------------------------------------------
template<class T>
Statistics<T>& Statistics<T>::insert(const T& measurement) noexcept
{
	*this += measurement;
	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: insert [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Insert measurements into the population
/// @details	O(N) complexity.
/// @param[in]	first	begin iterator
/// @param[in]	last	end iterator
/// @returns	Reference to `this`
//----------------------------------------------------------------------------------------------------------------------
template<class T>
template<class InputIt>
Statistics<T>& Statistics<T>::insert(const InputIt& first, const InputIt& last) noexcept
{
	for (InputIt itr = first; itr != last; ++itr)
		*this += *itr;

	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: latest [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief      Return the most recent measurement value added to the statistics.
/// @details    O(1) complexity.
/// @return     Most recent measurement value
//----------------------------------------------------------------------------------------------------------------------
template<class T>
T Statistics<T>::latest() const noexcept
{
	return m_latest;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: mean [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Value of the mean.
/// @details	O(1) complexity. Returns 0 if no measurements have been taken.
/// @returns	Current value of the average
//----------------------------------------------------------------------------------------------------------------------
template<class T>
T Statistics<T>::mean() const noexcept
{
	return m_sum / std::max<size_t>(m_count, 1);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: min [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Returns minimum sampled value.
/// @details		O(1) complexity.
//----------------------------------------------------------------------------------------------------------------------
template<class T>
T Statistics<T>::min() const noexcept
{
	return m_min;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: max [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Returns maximum sampled value.
/// @details	O(1) complexity.
//----------------------------------------------------------------------------------------------------------------------
template<class T>
T Statistics<T>::max() const noexcept
{
	return m_max;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: sum [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Sum of the samples
/// @details	O(1) complexity.
/// @returns	The sum of all sampled values
//----------------------------------------------------------------------------------------------------------------------
template<class T>
T Statistics<T>::sum() const noexcept
{
	return m_sum;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: sumOfSquares [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Returns the sum of squares of all measurements
/// @details	O(1) complexity.
/// @returns	The sum of squares of all measurements
//----------------------------------------------------------------------------------------------------------------------
template<class T>
typename Statistics<T>::T2 Statistics<T>::sumOfSquares() const noexcept
{
	return m_sumOfSquares;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: variance [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Calculates the variance of the population
/// @details	O(1) complexity.
/// @returns	variance
//----------------------------------------------------------------------------------------------------------------------
template<class T>
auto Statistics<T>::variance() const noexcept
{
	auto denom = std::max<size_t>(m_count, 1);
	return ((m_sumOfSquares / denom) - (m_sum / denom) * (m_sum / denom));
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: standardDeviation [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Calculates the standard deviation of the population
/// @details	O(1) complexity.
/// @returns	standard deviation
//----------------------------------------------------------------------------------------------------------------------
template<class T>
T Statistics<T>::standardDeviation() const noexcept
{
	return sqrt(variance());
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator+= [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Returns the average updated with the given measurement.
/// @details	O(1) complexity.
/// @param[in]	measurement	value to add to the average.
/// @returns	Reference to this.
//----------------------------------------------------------------------------------------------------------------------
template<class T>
Statistics<T>& Statistics<T>::operator+=(const T& measurement) noexcept
{
	m_latest = measurement;

	if (m_latest < m_min)
		m_min = m_latest;
	else if (m_latest > m_max)
		m_max = m_latest;

	m_sum += m_latest;
	m_sumOfSquares += m_latest * m_latest;

	++m_count;

	return *this;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator+= [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Returns the average updated with the given measurement.
/// @details	O(1) complexity.
/// @param[in]	measurement	value to add to the average.
/// @returns	Reference to this.
//----------------------------------------------------------------------------------------------------------------------
template<class T>
Statistics<T>& Statistics<T>::operator+=(const Statistics& rhs) noexcept
{
	m_count += rhs.m_count;
	m_latest = rhs.m_latest;
	m_max = std::max(m_max, rhs.m_max);
	m_min = std::min(m_min, rhs.m_min);
	m_sum += rhs.m_sum;
	m_sumOfSquares += rhs.m_sumOfSquares;

	return *this;
}

//======================================================================================================================
//      FRIEND FUNCTIONS
//======================================================================================================================

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator+ [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Adds a measurement to the population
/// @details	O(1) complexity.
/// @param[in]	population	population to add the measurement to
/// @param[in]	measurement measurement to add
/// @returns	The resulting population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline Statistics<T> operator+(const Statistics<T>& lhs, const T& rhs) noexcept
{
	Statistics<T> s;
	s += lhs;
	s += rhs;
	return s;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator+ [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Combine two populations
/// @details	O(1) complexity.
/// @param[in]	lhs	first population
/// @param[in]	rhs second population
/// @returns	The resulting population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline Statistics<T>& operator+(const Statistics<T>& lhs, const Statistics<T>& rhs) noexcept
{
	Statistics<T> s;
	s += lhs;
	s += rhs;
	return s;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator== [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Equality operator
/// @details	O(1) complexity.
/// @param[in]	lhs left hand population
/// @param[in]	rhs	right hand population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline bool operator==(const Statistics<T>& lhs, const Statistics<T>& rhs) noexcept
{
	if (lhs.m_count != rhs.m_count)
		return false;
	else if (lhs.m_latest != rhs.m_latest)
		return false;
	else if (lhs.m_min != rhs.m_min)
		return false;
	else if (lhs.m_max != rhs.m_max)
		return false;
	else if (lhs.m_sum != rhs.m_sum)
		return false;
	else
		return true;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator!= [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Inequality operator
/// @details	O(1) complexity.
/// @param[in]	lhs left hand population
/// @param[in]	rhs	right hand population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline bool operator!=(const Statistics<T>& lhs, const Statistics<T>& rhs) noexcept
{
	return !(lhs == rhs);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator< [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Less than operator
/// @details	O(1) complexity.
/// @param[in]	lhs left hand population
/// @param[in]	rhs	right hand population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline bool operator<(const Statistics<T>& lhs, const Statistics<T>& rhs) noexcept
{
	if (lhs.m_count < rhs.m_count)
		return true;
	else if (lhs.m_latest < rhs.m_latest)
		return true;
	else if (lhs.m_min < rhs.m_min)
		return true;
	else if (lhs.m_max < rhs.m_max)
		return true;
	else if (lhs.m_sum < rhs.m_sum)
		return true;
	else
		return false;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator<= [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Less than or equal to operator
/// @details	O(1) complexity.
/// @param[in]	lhs left hand population
/// @param[in]	rhs	right hand population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline bool operator<=(const Statistics<T>& lhs, const Statistics<T>& rhs) noexcept
{
	return !(rhs < lhs);
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator> [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Greater than operator
/// @details	O(1) complexity.
/// @param[in]	lhs left hand population
/// @param[in]	rhs	right hand population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline bool operator>(const Statistics<T>& lhs, const Statistics<T>& rhs) noexcept
{
	return rhs < lhs;
}

//----------------------------------------------------------------------------------------------------------------------
//      FUNCTION: operator>= [public]
//----------------------------------------------------------------------------------------------------------------------
/// @brief		Greater than or equal to operator
/// @details	O(1) complexity.
/// @param[in]	lhs left hand population
/// @param[in]	rhs	right hand population
//----------------------------------------------------------------------------------------------------------------------
template<class T>
inline bool operator>=(const Statistics<T>& lhs, const Statistics<T>& rhs) noexcept
{
	return !(lhs < rhs);
}

#endif    // average_h__