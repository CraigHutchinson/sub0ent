#include "TestTypes.h"

#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

template<> std::wstring Microsoft::VisualStudio::CppUnitTestFramework::ToString<Human>(const Human& inputValue)
{
	return L"human";
}



namespace Enti {
namespace Test 
{
} //END: Test
} //END: Enti