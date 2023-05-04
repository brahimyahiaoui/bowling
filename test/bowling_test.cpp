#include "gtest/gtest.h"
#include <bowling.h>


TEST(Bowling, MAX_SCORE)
{
    // Alice have 10 strikes + 2 bonus
    CBowler alice("Alice");
    alice.ComputeLastLaunch(10u); // 1
    alice.ComputeLastLaunch(10u); // 2
    alice.ComputeLastLaunch(10u); // 3
    alice.ComputeLastLaunch(10u); // 4
    alice.ComputeLastLaunch(10u); // 5
    alice.ComputeLastLaunch(10u); // 6
    alice.ComputeLastLaunch(10u); // 7
    alice.ComputeLastLaunch(10u); // 8
    alice.ComputeLastLaunch(10u); // 9
    alice.ComputeLastLaunch(10u); // 10
    alice.ComputeLastLaunch(10u); // 11
    alice.ComputeLastLaunch(10u); // 12

    // test
    ASSERT_TRUE(alice.GetLastResult() == "XXXXXXXXXXXX"); // 12xX
    ASSERT_EQ(alice.CalculateLastScore(), 300u); // Maximum score
}

TEST(Bowling, NINE_AND_MISS)
{
    // Bob 10 pairs of 9 and miss
    CBowler bob("Bob");
    bob.ComputeLastLaunch(9u); // 1
    bob.ComputeLastLaunch(0u); // 2
    bob.ComputeLastLaunch(9u); // 3
    bob.ComputeLastLaunch(0u); // 4
    bob.ComputeLastLaunch(9u); // 5
    bob.ComputeLastLaunch(0u); // 6
    bob.ComputeLastLaunch(9u); // 7
    bob.ComputeLastLaunch(0u); // 8
    bob.ComputeLastLaunch(9u); // 9
    bob.ComputeLastLaunch(0u); // 10
    bob.ComputeLastLaunch(9u); // 11
    bob.ComputeLastLaunch(0u); // 12
    bob.ComputeLastLaunch(9u); // 13
    bob.ComputeLastLaunch(0u); // 14
    bob.ComputeLastLaunch(9u); // 15
    bob.ComputeLastLaunch(0u); // 16
    bob.ComputeLastLaunch(9u); // 17
    bob.ComputeLastLaunch(0u); // 18
    bob.ComputeLastLaunch(9u); // 19
    bob.ComputeLastLaunch(0u); // 20

    // test
    ASSERT_TRUE(bob.GetLastResult() == "9-9-9-9-9-9-9-9-9-9-");
    ASSERT_EQ(bob.CalculateLastScore(), 90u);
}

TEST(Bowling, SPARES)
{
    // AI42 10 pairs of 5 and spare + bonus 5
    CBowler ai42("AI42");
    ai42.ComputeLastLaunch(5u); // 1
    ai42.ComputeLastLaunch(5u); // 2
    ai42.ComputeLastLaunch(5u); // 3
    ai42.ComputeLastLaunch(5u); // 4
    ai42.ComputeLastLaunch(5u); // 5
    ai42.ComputeLastLaunch(5u); // 6
    ai42.ComputeLastLaunch(5u); // 7
    ai42.ComputeLastLaunch(5u); // 8
    ai42.ComputeLastLaunch(5u); // 9
    ai42.ComputeLastLaunch(5u); // 10
    ai42.ComputeLastLaunch(5u); // 11
    ai42.ComputeLastLaunch(5u); // 12
    ai42.ComputeLastLaunch(5u); // 13
    ai42.ComputeLastLaunch(5u); // 14
    ai42.ComputeLastLaunch(5u); // 15
    ai42.ComputeLastLaunch(5u); // 16
    ai42.ComputeLastLaunch(5u); // 17
    ai42.ComputeLastLaunch(5u); // 18
    ai42.ComputeLastLaunch(5u); // 19
    ai42.ComputeLastLaunch(5u); // 20
    ai42.ComputeLastLaunch(5u); // 21

    // test
    ASSERT_TRUE(ai42.GetLastResult() == "5/5/5/5/5/5/5/5/5/5/5");
    ASSERT_EQ(ai42.CalculateLastScore(), 150u);
}

TEST(Bowling, TWO_BOWLERS)
{
    // Bob 10 pairs of 9 and miss
    CBowler alice("Alice"), bob("Bob");
    bob.ComputeLastLaunch(8u); //Frame 1 Bob
    bob.ComputeLastLaunch(0u); //Frame 1 Bob
    alice.ComputeLastLaunch(6u); //Frame 1 Alice
    alice.ComputeLastLaunch(4u); //Frame 1 Alice
    bob.ComputeLastLaunch(10u); //Frame 2 Bob
    alice.ComputeLastLaunch(4u); //Frame 2 Alice
    alice.ComputeLastLaunch(3u); //Frame 2 Alice
    bob.ComputeLastLaunch(0u); //Frame 3 Bob
    bob.ComputeLastLaunch(0u); //Frame 3 Bob
    alice.ComputeLastLaunch(10u); //Frame 3 Alice
    bob.ComputeLastLaunch(7u); //Frame 4 Bob
    bob.ComputeLastLaunch(1u); //Frame 4 Bob
    alice.ComputeLastLaunch(7u); //Frame 4 Alice
    alice.ComputeLastLaunch(3u); //Frame 4 Alice
    bob.ComputeLastLaunch(0u); //Frame 5 Bob
    bob.ComputeLastLaunch(3u); //Frame 5 Bob
    alice.ComputeLastLaunch(9u); //Frame 5 Alice
    alice.ComputeLastLaunch(1u); //Frame 5 Alice
    bob.ComputeLastLaunch(1u); //Frame 6 Bob
    bob.ComputeLastLaunch(3u); //Frame 6 Bob
    alice.ComputeLastLaunch(10u); //Frame 6 Alice
    bob.ComputeLastLaunch(0u); //Frame 7 Bob
    bob.ComputeLastLaunch(0u); //Frame 7 Bob
    alice.ComputeLastLaunch(8u); //Frame 7 Alice
    alice.ComputeLastLaunch(1u); //Frame 7 Alice
    bob.ComputeLastLaunch(3u); //Frame 8 Bob
    bob.ComputeLastLaunch(4u); //Frame 8 Bob
    alice.ComputeLastLaunch(2u); //Frame 8 Alice
    alice.ComputeLastLaunch(5u); //Frame 8 Alice
    bob.ComputeLastLaunch(1u); //Frame 9 Bob
    bob.ComputeLastLaunch(6u); //Frame 9 Bob
    alice.ComputeLastLaunch(8u); //Frame 9 Alice
    alice.ComputeLastLaunch(2u); //Frame 9 Alice
    bob.ComputeLastLaunch(10u); //Frame 10 Bob
    alice.ComputeLastLaunch(3u); //Frame 10 Alice
    alice.ComputeLastLaunch(6u); //Frame 10 Alice
    bob.ComputeLastLaunch(10u); //Frame 10 Bob
    bob.ComputeLastLaunch(5u); //Frame 10 Bob

    // test
    ASSERT_EQ(alice.GetLastResult(), "6/43X7/9/X81258/36"); //OK
    ASSERT_EQ(bob.GetLastResult(), "8-X--71-313--3416XX5"); //OK
    ASSERT_GT(alice.CalculateLastScore(), bob.CalculateLastScore());
}

int main(int argc, char ** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
