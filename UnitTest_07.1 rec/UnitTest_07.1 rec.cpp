#include "pch.h"
#include "CppUnitTest.h"

// 1. Захист від повторного оголошення main()
#define UNIT_TESTING

// 2. Підключаємо файл рекурсивного способу
#include "../PR_07.1 rec.cpp" 

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab71Rec
{
	TEST_CLASS(UnitTestLab71Rec)
	{
	public:

		TEST_METHOD(TestMethod_CalcRows_Recursion)
		{
			// Arrange (Підготовка даних)
			const int rowCount = 3;
			const int colCount = 3;

			int** a = new int* [rowCount];
			for (int i = 0; i < rowCount; i++)
				a[i] = new int[colCount];

			// Тестова матриця 3х3:
			// Рядок 0: 12 (підходить: >=0 і %3==0), -6 (від'ємне - ні), 3 (підходить)
			// Рядок 1:  0 (підходить: >=0 і %3==0),  5 (не ділиться на 3), 9 (підходить)
			// Рядок 2: -21 (від'ємне - ні),        7 (ні),              4 (ні)
			a[0][0] = 12;  a[0][1] = -6; a[0][2] = 3;
			a[1][0] = 0;   a[1][1] = 5;  a[1][2] = 9;
			a[2][0] = -21; a[2][1] = 7;  a[2][2] = 4;

			int S = 0;
			int k = 0;

			// Act (Виклик рекурсивної функції CalcRows)
			CalcRows(a, rowCount, colCount, 0, S, k);

			// Assert (Перевірка результатів)
			// Очікувані елементи: 12, 3, 0, 9
			// Сума S = 12 + 3 + 0 + 9 = 24
			// Кількість k = 4
			Assert::AreEqual(24, S, L"Сума S обчислена некоректно!");
			Assert::AreEqual(4, k, L"Кількість k обчислена некоректно!");

			// Перевіряємо заміну нулями
			Assert::AreEqual(0, a[0][0]);
			Assert::AreEqual(-6, a[0][1]); // від'ємне, не змінювалося
			Assert::AreEqual(0, a[0][2]);
			Assert::AreEqual(0, a[1][0]);
			Assert::AreEqual(5, a[1][1]);  // не ділиться на 3, не змінювалося
			Assert::AreEqual(0, a[1][2]);

			// Cleanup (Звільнення пам'яті)
			for (int i = 0; i < rowCount; i++)
				delete[] a[i];
			delete[] a;
		}
	};
}