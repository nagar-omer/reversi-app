/*****************************************************************************
 * Student Name:    Oved Nagar                                               *
 * Id:              302824875                                                *
 * Student Name:    Orly Paknahad                                            *
 * Id:              315444646                                                *
 * Exercise name:   Ex3                                                      *
 ****************************************************************************/




#include "gtest/gtest.h"
#include "../include/Player.h"

TEST(Player_construct, constructor){
    Player user = Player("nick");
    Player pc = Player("pc", true);

    EXPECT_EQ(user.nick(), "nick");
    EXPECT_EQ(user.getLoss(), 0);
    EXPECT_EQ(user.getWins(), 0);
    EXPECT_EQ(user.isComputer(), false);

    EXPECT_EQ(pc.nick(), "pc");
    EXPECT_EQ(pc.getLoss(), 0);
    EXPECT_EQ(pc.getWins(), 0);
    EXPECT_EQ(pc.isComputer(), true);
}

TEST(Player_operators, check_operators){
    Player user = Player("nick");
    Player pc = Player("pc", true);

    --user;
    ++user;
    EXPECT_EQ(user.getLoss(), 1);
    EXPECT_EQ(user.getWins(), 1);

    --pc;
    --pc;
    ++pc;
    EXPECT_EQ(pc.getLoss(), 2);
    EXPECT_EQ(pc.getWins(), 1);

}