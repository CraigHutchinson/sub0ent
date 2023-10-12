#include "TestTypes.hpp"

#include "CppUnitTest.hpp"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Human>(const Human& inputValue)
{
	return L"human";
}



namespace Sub0Ent {
namespace Test 
{
} //END: Test
} //END: Sub0Ent