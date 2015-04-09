#include <gtest/gtest.h>

#include "duck_typing/object.hpp"

TEST(object_tests, lambda_without_arguemnt_can_be_called)
{
    bool called = false;

    object obj;

    obj["method"] = [&called] ()
    {
        called = true;
    };

    EXPECT_FALSE(called);

    obj["method"]();

    EXPECT_TRUE(called);
}

TEST(object_tests, lambda_with_one_arguemnt_can_be_called)
{
    bool called = false;
    int arg1 = 1;

    object obj;

    obj["method"] = [&] (int i)
    {
        called = true;
        arg1 = i;
    };

    EXPECT_FALSE(called);

    (obj / "method")(2);

    EXPECT_TRUE(called);
    EXPECT_EQ(2, arg1);
}

TEST(object_tests, called_non_existing_method)
{
    object obj;

    EXPECT_ANY_THROW((obj / "non_existing")());
}

TEST(object_tests, called_with_wrong_arguments)
{
    object obj;

    obj / "method" = [] {};

    EXPECT_ANY_THROW((obj / "method")(5));
}
