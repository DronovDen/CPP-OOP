#pragma once
#include "gtest/gtest.h"
#include "RNA.hpp"
#include <crtdbg.h>

TEST(RNA_methods, ConstructorWithCapacity)
{
    RNA rna(1000000);
    for (size_t i = 0; i < 1000000; i++)
    {
        rna[i] = C;
    }
    for (size_t i = 0; i < 1000000; i++)
    {
        EXPECT_EQ(C, rna[i]);
    }
}

TEST(RNA_methods, ConstructorWithNucl)
{
    RNA rna(C, 1000000);
    for (size_t i = 0; i < 1000000; i++)
    {
        EXPECT_EQ(C, rna[i]);
    }
}

TEST(RNA_methods, EmptyConstructor)
{
    RNA rna;
    ASSERT_EQ(0, rna.get_nucles_number());
    ASSERT_EQ(0, rna.get_uints_number());
}

TEST(RNA_methods, CopyConstructor)
{
    RNA rna1(T, 100);
    ASSERT_EQ(100, rna1.get_nucles_number());
    RNA rna2(rna1);
    ASSERT_EQ(100, rna2.get_nucles_number());
    for (size_t i = 0; i < 100; i++)
    {
        EXPECT_EQ(T, rna2[i]);
    }
}

TEST(RNA_methods, PushBack)
{
    RNA rna(G, 1);
    for (size_t i = 0; i < 10; i++)
    {
        rna.push_back(G);
    }
    ASSERT_EQ(11, rna.get_nucles_number());
    for (size_t i = 0; i < 11; i++)
    {
        EXPECT_EQ(G, rna[i]);
    }
}

TEST(RNA_methods, PopBack)
{
    RNA rna(G, 100);
    ASSERT_EQ(G, rna.pop_back());
    ASSERT_EQ(99, rna.get_nucles_number());
}

TEST(RNA_methods, Trim)
{
    RNA rna(T, 100);
    rna.trim(22);
    ASSERT_EQ(22, rna.get_nucles_number());
}

TEST(RNA_methods, Split)
{
    RNA_set set;
    RNA rna(T, 200);
    rna[177] = A;
    set = rna.split(177);
    ASSERT_EQ(177, set.first->get_nucles_number());
    ASSERT_EQ(23, set.second->get_nucles_number());
    ASSERT_EQ((*set.first)[0], rna[0]);
    ASSERT_EQ((*set.second)[0], rna[177]);
}

TEST(RNA_methods, IsComplementary)
{
    RNA rna1(A, 500);
    RNA rna2(A, 499);
    RNA rna3(T, 500);
    ASSERT_EQ(true, rna1.is_complementary(rna3));
    ASSERT_EQ(false, rna1.is_complementary(rna2));
    ASSERT_EQ(false, rna2.is_complementary(rna3));
}

TEST(RNA_methods, Cardinality)
{
    RNA rna(T, 100);
    rna[4] = A;
    rna[20] = C;
    rna[57] = C;
    ASSERT_EQ(97, rna.cardinality(T));
    ASSERT_EQ(1, rna.cardinality(A));
    ASSERT_EQ(2, rna.cardinality(C));
}

TEST(RNA_methods, MapCardinality)
{
    RNA rna(T, 100);
    rna[4] = A;
    rna[20] = C;
    rna[57] = C;
    std::unordered_map<Nucl, int, std::hash<int>> map = rna.cardinality();
    ASSERT_EQ(97, map[T]);
    ASSERT_EQ(1, map[A]);
    ASSERT_EQ(2, map[C]);
}

TEST(RNA_operators, GetByIdx)
{
    RNA rna(T, 100);
    for (size_t i = 0; i < 100; i++)
    {
        EXPECT_EQ(T, rna[i]);
    }
}

TEST(RNA_operators, Assignment)
{
    RNA rna1(A, 100);
    RNA rna2(G, 80);
    rna2 = rna1;
    ASSERT_EQ(100, rna2.get_nucles_number());
    for (size_t i = 0; i < 100; i++)
    {
        ASSERT_EQ(A, rna2[i]);
    }
}

TEST(RNA_operators, IsEqual) //!!!!!!!!!!!!
{
    RNA rna1(A, 100);
    RNA rna2(T, 100);
    RNA rna3(A, 101);
    RNA rna4(A, 100);
    EXPECT_EQ(true, rna1 == rna4);
    EXPECT_EQ(false, rna1 == rna2);
    EXPECT_EQ(false, rna1 == rna3);
}

TEST(RNA_operators, IsNotEqual) //!!!!!!!!!!!!!!!
{
    RNA rna1(A, 100);
    RNA rna2(T, 100);
    RNA rna3(A, 101);
    RNA rna4(A, 100);
    EXPECT_EQ(false, rna1 != rna4);
    EXPECT_EQ(true, rna1 != rna2);
    EXPECT_EQ(true, rna1 != rna3);
}

TEST(RNA_operators, NOT)
{
    RNA rna(C, 100);
    RNA rna1 = !rna;
    ASSERT_EQ(100, rna1.get_nucles_number());
    for (size_t i = 0; i < 100; i++)
    {
        EXPECT_EQ(G, rna1[i]);
    }
}

TEST(RNA_operators, Addition)
{
    RNA rna1(A, 100);
    RNA rna2(T, 50);
    EXPECT_EQ(150, (rna1 + rna2).get_nucles_number());
    EXPECT_EQ(A, (rna1 + rna2)[99]);
    EXPECT_EQ(T, (rna1 + rna2)[101]);
}

TEST(Memory, MemoryLeak)
{
    _CrtMemState stady1 = {0};
    _CrtMemState stady2 = {0};

    RNA rna(T, 1);
    _CrtMemCheckpoint(&stady1);

    for (size_t i = 0; i < 1000000; i++)
    {
        rna.push_back(Nucl(i % 4));
    }
    rna.trim(100);

    _CrtMemCheckpoint(&stady2);

    _CrtMemState result = {0};
    EXPECT_FALSE(_CrtMemDifference(&result, &stady1, &stady2));
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    std::system("Pause");
    return 0;
}