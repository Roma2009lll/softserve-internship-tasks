#include "pch.h" 
#include <gmock/gmock.h>
#include "../soft_servetask2/AnyType.hpp"

template <typename T>
void CheckConstructorAndGetter(T test_value, AnyType::Datatype expected_type)
{
    AnyType obj(test_value);
    EXPECT_EQ(obj.GetType(), expected_type);
    EXPECT_EQ(obj.GetVal<T>(), test_value);
}

TEST(AnyTypeConstructorTests, ConstructorTest) 
{
    CheckConstructorAndGetter(10, AnyType::Datatype::INT);
    CheckConstructorAndGetter(3.14f, AnyType::Datatype::FLOAT);
    CheckConstructorAndGetter(14.4, AnyType::Datatype::DOUBLE);
    CheckConstructorAndGetter('Z', AnyType::Datatype::CHAR);
    CheckConstructorAndGetter(true, AnyType::Datatype::BOOL);
}

TEST(AnyTypeAssignmentTests, TypeTest)
{
    AnyType obj = 10;
    EXPECT_EQ(obj.ToInt(), 10);
    EXPECT_EQ(obj.GetType(), AnyType::Datatype::INT);
    obj = 14.4;
    EXPECT_EQ(obj.ToDouble(), 14.4);
    EXPECT_EQ(obj.GetType(), AnyType::Datatype::DOUBLE);
}

TEST(AnyTypeExceptionTests, ExceptionTest)
{
    AnyType obj = 10;
    EXPECT_THROW(obj.ToDouble(), std::runtime_error);
    EXPECT_THROW(obj.ToFloat(), std::runtime_error);
    EXPECT_THROW(obj.ToChar(), std::runtime_error);
    EXPECT_THROW(obj.ToBool(), std::runtime_error);
    EXPECT_NO_THROW(obj.ToInt());
}

TEST(AnyTypeMethodTests, SwapTest)
{
    AnyType obj1 = 10;
    EXPECT_EQ(obj1.ToInt(), 10);
    EXPECT_EQ(obj1.GetType(), AnyType::Datatype::INT);
    AnyType obj2 = 14.4;
    EXPECT_EQ(obj2.ToDouble(), 14.4);
    EXPECT_EQ(obj2.GetType(), AnyType::Datatype::DOUBLE);
    obj1.Swap(obj2);
    EXPECT_EQ(obj2.ToInt(), 10);
    EXPECT_EQ(obj2.GetType(), AnyType::Datatype::INT);
    EXPECT_EQ(obj1.ToDouble(), 14.4);
    EXPECT_EQ(obj1.GetType(), AnyType::Datatype::DOUBLE);
}

TEST(AnyTypeMethodTests, DestroyTest)
{
    AnyType obj = 10;
    obj.Destroy();
    EXPECT_EQ(obj.GetType(), AnyType::Datatype::EMPTY);
}

TEST(AnyTypeConstructorTests, DefaultConstructorTest) 
{
    AnyType obj;
    EXPECT_EQ(obj.GetType(), AnyType::Datatype::EMPTY);
    EXPECT_EQ(obj.GetTypeAsStirng(), "empty");
}

TEST(AnyTypeMethodTests, CopyTest) 
{
    AnyType obj1 = 10;
    AnyType obj2 = obj1;
    EXPECT_EQ(obj2.GetType(), AnyType::Datatype::INT);
    EXPECT_EQ(obj2.ToInt(), 10);
}

TEST(AnyTypeConstructorTests, MoveConstructorTest) 
{
    AnyType obj1 = 10;
    AnyType obj2 = std::move(obj1);
    EXPECT_EQ(obj2.GetType(), AnyType::Datatype::INT);
    EXPECT_EQ(obj2.ToInt(), 10);
}

TEST(AnyTypeAssignmentTests, MoveAssignmentTest) 
{
    AnyType obj1 = 10;
    AnyType obj2 = 20;
    obj2 = std::move(obj1);
    EXPECT_EQ(obj2.GetType(), AnyType::Datatype::INT);
    EXPECT_EQ(obj2.ToInt(), 10);
}