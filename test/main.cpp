#include <gtest/gtest.h>
#include <statistics.h>
#include "units.h"
#include <deque>
#include <type_traits>

using namespace units::time;
using namespace units::literals;

namespace 
{

	std::deque<units::time::second_t> measurements
	{
		18_s, 8_s, 14_s, 6_s, 11_s, 17_s, 12_s, 7_s, 6_s,
		10_s, 9_s, 8_s, 12_s, 15_s, 9_s, 9_s, 3_s, 1_s,
		6_s, 7_s, 14_s, 20_s, 19_s
	};

	Statistics<second_t> stats(measurements.begin(), measurements.end());

	// The fixture for testing class Cache
	class StatisticsTest : public ::testing::Test 
	{

	};

	TEST_F(StatisticsTest, traits)
	{
		EXPECT_TRUE(std::is_constructible_v<Statistics<second_t>>);
		EXPECT_TRUE(std::is_default_constructible_v<Statistics<second_t>>);
		EXPECT_TRUE(std::is_trivially_copy_constructible_v<Statistics<second_t>>);
		EXPECT_TRUE(std::is_trivially_copy_assignable_v<Statistics<second_t>>);
		EXPECT_TRUE(std::is_trivially_move_constructible_v<Statistics<second_t>>);
		EXPECT_TRUE(std::is_trivially_move_assignable_v<Statistics<second_t>>);
		EXPECT_TRUE((std::is_assignable_v<Statistics<second_t>, Statistics<second_t>>));
	}

	TEST_F(StatisticsTest, default_construtor)
	{
		Statistics<size_t> s;
		EXPECT_EQ(s.count(), 0);
		EXPECT_EQ(s.min(), std::numeric_limits<size_t>::max());
		EXPECT_EQ(s.max(), std::numeric_limits<size_t>::min());
		EXPECT_EQ(s.mean(), 0);
		EXPECT_EQ(s.sum(), 0);
		EXPECT_EQ(s.sumOfSquares(), 0);
	}

	TEST_F(StatisticsTest, measurement_construtor)
	{
		Statistics<int> s(2);
		EXPECT_EQ(s.count(), 1);
		EXPECT_EQ(s.min(), 2);
		EXPECT_EQ(s.max(), 2);
		EXPECT_EQ(s.mean(), 2);
		EXPECT_EQ(s.sum(), 2);
		EXPECT_EQ(s.sumOfSquares(), 4);
	}

	TEST_F(StatisticsTest, initializer_list_construtor)
	{
		Statistics<int> s({ 1, 2, 3 });
		EXPECT_EQ(s.sum(), 6);
		EXPECT_EQ(s.count(), 3);
	}

	TEST_F(StatisticsTest, input_iterator_construtor)
	{
		Statistics<size_t> s1 = { 1, 2, 3 };
		std::vector<size_t> v = { 1,2,3 };
		Statistics<size_t> s2(v.begin(), v.end());
		EXPECT_TRUE(s1 == s2);
	}

	TEST_F(StatisticsTest, clear)
	{
		Statistics<int> s(2);
		EXPECT_EQ(s.count(), 1);
		EXPECT_EQ(s.min(), 2);
		EXPECT_EQ(s.max(), 2);
		EXPECT_EQ(s.mean(), 2);
		EXPECT_EQ(s.sum(), 2);
		EXPECT_EQ(s.sumOfSquares(), 4);

		s.clear();
		EXPECT_EQ(s.count(), 0);
		EXPECT_EQ(s.min(), std::numeric_limits<int>::max());
		EXPECT_EQ(s.max(), std::numeric_limits<int>::lowest());
		EXPECT_EQ(s.mean(), 0);
		EXPECT_EQ(s.sum(), 0);
		EXPECT_EQ(s.sumOfSquares(), 0);
	}

	TEST_F(StatisticsTest, count)
	{
		EXPECT_EQ(stats.count(), 23);
	}

	TEST_F(StatisticsTest, insert)
	{
		Statistics<second_t> s(measurements.begin(), measurements.end());
		EXPECT_EQ(s.count(), 23);
		EXPECT_EQ(s.mean(), 10.478260869565217_s);
		EXPECT_EQ(s.min(), 1_s);
		EXPECT_EQ(s.max(), 20_s);
		EXPECT_EQ(s.sum(), 241_s);
		EXPECT_EQ(s.sumOfSquares(), (3087_s * 1_s));
		EXPECT_EQ(s.variance(), (24.423440453686197_s * 1_s));
		EXPECT_EQ(s.standardDeviation(), 4.9420077350896765_s);

		s.insert(4_s);
		EXPECT_EQ(s.count(), 24);
		EXPECT_EQ(s.mean(), 10.208333333333333_s);
		EXPECT_EQ(s.min(), 1_s);
		EXPECT_EQ(s.max(), 20_s);
		EXPECT_EQ(s.sum(), 245_s);
		EXPECT_EQ(s.sumOfSquares(), (3103_s * 1_s));
		EXPECT_EQ(s.variance(), (25.0815972222222_s * 1_s));
		EXPECT_EQ(s.standardDeviation(), 5.0081530749590915_s);
	}

	TEST_F(StatisticsTest, insert_range)
	{
		Statistics<second_t> s(measurements.begin(), measurements.end());
		EXPECT_EQ(s, stats);
	}

	TEST_F(StatisticsTest, latest)
	{
		EXPECT_EQ(stats.latest(), 19_s);
	}

	TEST_F(StatisticsTest, mean)
	{
		EXPECT_EQ(stats.mean(), 10.478260869565217_s);
	}

	TEST_F(StatisticsTest, min)
	{
		EXPECT_EQ(stats.min(), 1_s);
	}

	TEST_F(StatisticsTest, max)
	{
		EXPECT_EQ(stats.max(), 20_s);
	}

	TEST_F(StatisticsTest, sum)
	{
		EXPECT_EQ(stats.sum(), 241_s);
	}

	TEST_F(StatisticsTest, sum_of_squares)
	{
		auto expected = 3087_s * 1_s;
		EXPECT_EQ(stats.sumOfSquares(), expected);
	}

	TEST_F(StatisticsTest, variance)
	{
		auto expected = 24.423440453686197_s * 1_s;
		EXPECT_EQ(stats.variance(), expected);
	}

	TEST_F(StatisticsTest, standard_deviation)
	{
		EXPECT_EQ(stats.standardDeviation(), 4.9420077350896765_s);
	}

	TEST_F(StatisticsTest, operator_plus_equal_t)
	{
		Statistics<second_t> s(measurements.begin(), measurements.end());
		EXPECT_EQ(s.count(), 23);
		EXPECT_EQ(s.mean(), 10.478260869565217_s);
		EXPECT_EQ(s.min(), 1_s);
		EXPECT_EQ(s.max(), 20_s);
		EXPECT_EQ(s.sum(), 241_s);
		EXPECT_EQ(s.sumOfSquares(), (3087_s * 1_s));
		EXPECT_EQ(s.variance(), (24.423440453686197_s * 1_s));
		EXPECT_EQ(s.standardDeviation(), 4.9420077350896765_s);

		s += 4_s;
		EXPECT_EQ(s.count(), 24);
		EXPECT_EQ(s.mean(), 10.208333333333333_s);
		EXPECT_EQ(s.min(), 1_s);
		EXPECT_EQ(s.max(), 20_s);
		EXPECT_EQ(s.sum(), 245_s);
		EXPECT_EQ(s.sumOfSquares(), (3103_s * 1_s));
		EXPECT_EQ(s.variance(), (25.0815972222222_s * 1_s));
		EXPECT_EQ(s.standardDeviation(), 5.0081530749590915_s);
	}

	TEST_F(StatisticsTest, operator_plus_equal_statistics)
	{
		Statistics<double> s1{ 1, 2 };
		Statistics<double> s2{ 3, 4 };
		Statistics<double> s3{ 1, 2, 3, 4 };
		EXPECT_FALSE(s1 == s3);
		s1 += s2;
		EXPECT_TRUE(s1 == s3);
	}

	TEST_F(StatisticsTest, operator_equal)
	{
		Statistics<double> s1{ 1, 2 };
		Statistics<double> s2{ 1, 2 };
		Statistics<double> s3{ 3, 4 };
		EXPECT_TRUE(s1 == s2);
	}

	TEST_F(StatisticsTest, operator_not_equal)
	{
		Statistics<double> s1{ 1, 2 };
		Statistics<double> s2{ 3, 4 };
		Statistics<double> s3{ 1, 2, 3, 4 };
		EXPECT_TRUE(s1 != s3);
		s1 += s2;
		EXPECT_FALSE(s1 != s3);
	}

	TEST_F(StatisticsTest, operator_less)
	{
		Statistics<double> s1{ 1, 2 };
		Statistics<double> s2{ 3, 4 };
		EXPECT_TRUE(s1 < s2);
		EXPECT_FALSE(s2 < s1);
	}

	TEST_F(StatisticsTest, operator_less_equal)
	{
		Statistics<double> s1{ 1, 2 };
		Statistics<double> s2{ 1, 2 };
		Statistics<double> s3{ 3, 4 };
		EXPECT_TRUE(s1 <= s2);
		EXPECT_TRUE(s1 <= s3);
		EXPECT_FALSE(s2 < s1);
	}

	TEST_F(StatisticsTest, operator_greater)
	{
		Statistics<double> s1{ 1, 2 };
		Statistics<double> s2{ 3, 4 };
		EXPECT_FALSE(s1 > s2);
		EXPECT_TRUE(s2 > s1);
	}

	TEST_F(StatisticsTest, operator_greater_equal)
	{
		Statistics<double> s1{ 1, 2 };
		Statistics<double> s2{ 1, 2 };
		Statistics<double> s3{ 3, 4 };
		EXPECT_GE(s1, s2);
		EXPECT_LT(s1, s3);
		EXPECT_GE(s2, s1);
	}
}  // namespace

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
