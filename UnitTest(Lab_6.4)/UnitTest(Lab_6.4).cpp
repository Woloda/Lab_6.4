#include "pch.h"
#include "CppUnitTest.h"

#include "../Lab_6.4/main.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab64
{
	TEST_CLASS(UnitTestLab64)
	{
	public:
		
		TEST_METHOD(Test_Elem_or_Cherga)
		{
			Cherga<Elem> a;

			a.Enqueue(15);
			a.Enqueue(84);
			a.Enqueue(56);
			a.Enqueue(13);

			Assert::AreEqual(a.Dequeue(), 15);
		}
	};
}
