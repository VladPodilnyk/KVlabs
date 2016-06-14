#include "cArray.h"

int main() {
	int i, n;
	cArray *test = new cArray;
	cArray *test2 = new cArray;
	cArray test3;
	test3.SetSize(5);

	printf("Size: %i\n", test->GetSize());
	printf("Count: %i\n", test->GetCount());
	printf("The highest index: %i\n", test->GetUpperBound());

	test->SetSize(3);
	printf("%s\n", "--------------------------------------");
	printf("Size: %i\n", test->GetSize());
	printf("Count: %i\n", test->GetCount());
	printf("The highest index: %i\n", test->GetUpperBound());
	printf("%s\n", "--------------------------------------");

	test->SetAt(10, 0);
	test->SetAt(11, 1);
	test->SetAt(12, 2);
	test->SetAt(13, 3);

	printf("Size: %i\n", test->GetSize());
	printf("Count: %i\n", test->GetCount());
	printf("The highest index: %i\n", test->GetUpperBound());
	printf("%s\n", "--------------------------------------");

	test->Add(13);
	printf("Size: %i\n", test->GetSize());
	printf("Count: %i\n", test->GetCount());
	printf("The highest index: %i\n", test->GetUpperBound());

	test->FreeExtra();
	printf("%s\n", "--------------------------------------");
	printf("Size: %i\n", test->GetSize());
	printf("Count: %i\n", test->GetCount());
	printf("The highest index: %i\n", test->GetUpperBound());
	n = test2->GetUpperBound();
	for (i = 0; i <= n; i++)
		printf("%i\n", test->GetAt(i));

	printf("%s\n", "--------------------------------------");
	test2->Copy(test);
	n = test2->GetUpperBound();
	for (i = 0; i <= n; i++)
		printf("%i\n", test2->GetAt(i));
	

	printf("%s\n", "--------------------------------------");
	test->Append(test2);
	printf("Size: %i\n", test->GetSize());
	printf("Count: %i\n", test->GetCount());
	printf("The highest index: %i\n", test->GetUpperBound());
	n = test->GetUpperBound();
	for (i = 0; i <= n; i++)
		printf("%i\n", test->GetAt(i));

	printf("%s\n", "--------------------------------------");
	n = test2->GetUpperBound();
	for (int i = 0; i <= n; i++) {
		test2->SetAt(i,i);
		printf("%i\n", test2->GetAt(i));
	}

	test->Copy(test2);
	printf("%s\n", "--------------------------------------");
	n = test->GetUpperBound();
	for (i = 0; i <= n; i++)
		printf("%i\n", test->GetAt(i));

	test->InsertAt(20, 2);
	test->RemoveAt(20);
	test->RemoveAt(0);
	printf("%s\n", "--------------------------------------");
	n = test->GetUpperBound();
	for (i = 0; i <= n; i++)
		printf("%i\n", test->GetAt(i));

	printf("%s\n", "--------------------------------------");
	n = test3.GetUpperBound();
	for (i = 0; i < 5; i++) {
		test3[i] = i + 1;
		printf("%i\n", test3[i]);
	}
	return 0;
}