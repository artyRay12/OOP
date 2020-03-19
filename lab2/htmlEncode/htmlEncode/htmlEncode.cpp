#include <iostream>
#include <cstring>
#include <iostream>
#include <map>
#include <stdio.h>
#include <string.h>
#include <string>
#include "htmlEncoder.h"
using namespace std;




int main()
{
	string html;

	while (cin >> html)
	{
		HtmlEncode(html);
		cout << html << endl;
	}

	return 0;
}
        
 


