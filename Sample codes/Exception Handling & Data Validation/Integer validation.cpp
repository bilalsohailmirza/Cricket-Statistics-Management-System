#include <iostream>
#include <sstream>
using namespace std;

//int get_int(int min, int max ,std::string prompt)
//{
//	int ret_integer;
//	std::string str_number;
//
//	while(true) {
//
//		std::cout << prompt;
//		std::getline(std::cin, str_number); //get string input
//		std::stringstream convert(str_number); //turns the string into a stream
//
//		//checks for complete conversion to integer and checks for minimum value
//		if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= min && <=max) 
//		{
//		return ret_integer;
//		}
//
//		std::cin.clear(); //just in case an error occurs with cin (eof(), etc)
//		std::cerr << "Input must be >= " << min << ". Please try again.\n";
//	}
//}

int main()
{
//	const int min_score=1; //example
//	std::cout << "Enter your 3 test scores and I will average them.\n";
//
//	int score1=get_int(min_score,"\nPlease enter test score #1: ");
//	int score2=get_int(min_score,"\nPlease enter test score #2: ");
//	int score3=get_int(min_score,"\nPlease enter test score #3: ");
//
//	the rest of your code

int num; //variable to store the number entered by the user.

//Prompt the user to enter an integer.
cout << "Enter an integer: ";
cin >> num;

//While the input entered is not an integer, prompt the user to enter an integer.
while(!cin)
{
    cout << "That was no integer! Please enter an integer: ";
    cin.clear();
    cin.ignore(100,'\n');
    cin >> num;
}

//Print the integer entered by the user to the screen.
cout << "The integer entered is " << num << endl;

	return 0;
}