#include <iostream>
#include "InfiniteInt.h"

using namespace std;

main()
{
int a = 125,
b = 975;
InfiniteInt n1;
InfiniteInt n2(a);

cout << "Converted 125 (int) to " << n2 << " InfiniteInt" << endl;

n1 = n2 + InfiniteInt(b);
cout << n2 << " + 975 (int) = " << n1 << endl;

cin >> n2;
cout << "Input " << n2 << endl;

InfiniteInt n3 = 64;
cout << "Converted 64 (int) to " << n3 << " InfiniteInt" << endl;

InfiniteInt sum = n1 + n3;
InfiniteInt difference = n1 - n3;
InfiniteInt product = n1 * n3;
cout << n1 << " + " << n3 << " = " << sum;
cout << n1 << " - " << n3 << " = " << difference;
cout << n1 << " * " << n3 << " = " << product;

cout << product << " has " << product.numDigits() << " digits" << endl;
}
