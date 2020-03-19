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
	string html = ReadString(cin);

	HtmlEncode(html);

	cout << html << endl;
	return 0;
}
        
 


