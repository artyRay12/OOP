#include <iostream>
#include <map>
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
        
 


