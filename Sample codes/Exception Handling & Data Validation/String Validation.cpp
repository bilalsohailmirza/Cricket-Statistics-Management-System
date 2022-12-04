#include<iostream>
#include<cctype>
#include<algorithm>
//using namespace std;



bool isValidString( std::string name )
{
   return ( all_of( name.begin(), name.end(),[] ( char c ) { return ( std::isalpha( c ) ); } ) );
}

int main()
{
	std::string random;
	
	std::cout<<"Enter a string: ";
	std::cin>>random;
	
	if(!isValidString(random))
	{
		std::cout<<"Invalid Input! ";
	}
	else 
	std::cout<<"Right input! ";
	return 0;
}