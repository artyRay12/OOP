#include <iostream>
#include <map>
#include <string>
#include "htmlEncoder.h"
using namespace std;

int main()
{
	string html = ReadString(cin);

	string htmlEncoded = HtmlEncode(html);

	cout << htmlEncoded << endl;
	return 0;
}
        
 


