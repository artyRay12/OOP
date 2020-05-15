#include <iostream>
#include "CVector3D.h"

int main()
{
	CVector3D v1(1,1,1);
	CVector3D v2(2, 2, 2);
	std::cout << CrossProduct(v1, v2);
	
}

