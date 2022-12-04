#include <iostream>
#include<cstdio>
#include<iomanip>
#include<windows.h>
#include <thread>
#include <chrono>
#include "sqlite3.h"
#include<cctype>
#include<algorithm>
#include<conio.h>

using namespace std;

void connection();
void readData();

sqlite3 *db;
sqlite3_stmt *stmt;
int result;
string query;

void connection()
{
    if(sqlite3_open("Project.db", &db) == SQLITE_OK)
    {
        cout<<"Database has Been Connected Successfully. \n";
    }
    else
    {
      cout<<"Database did not connected successfully. \n";
    }
}
bool adminLogin(string username, string pass)
{
    string query1 = "SELECT id FROM AdminInformation WHERE username = ";
    string query2 = " AND password = ";
    string apos = "'";
    string semicol = ";";
    string Query = query1 + apos + username + apos + query2 + apos + pass + apos + semicol;

    result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

    if((result = sqlite3_step(stmt) == SQLITE_ROW))
    {
       return true;
    }
    else
    {
        return false;
    }

}

bool isValidTableName(string tableName)
{
    int result;

    string query = "SELECT name FROM sqlite_master WHERE type='table' AND name = ";
    string apos = "'";
    string semicolon = ";";
    string Query = query + apos + tableName + apos + semicolon;

   result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

//   sqlite3_step(stmt);
//   sqlite3_finalize(stmt);

   if(result != SQLITE_OK)
    {
        cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;

    }

   else
    {
        return 1;
    }


}

bool isValidString( std::string name )  // to validate if any string input has any numbers in it
{
    string temp = name;

    name.erase(remove(name.begin(), name.end(), ' '), name.end());

   return ( all_of( name.begin(), name.end(),[] ( char c ) { return ( std::isalpha( c ) ); } ) );
}

int validateInteger(int min, int max, std::string prompt)
{
	int ret_integer;
	std::string str_number;

	while(true) {

		std::cout << prompt;
		std::getline(std::cin, str_number); //get string input
		std::stringstream convert(str_number); //turns the string into a stream

		//checks for complete conversion to integer and checks for minimum value
		if(convert >> ret_integer && !(convert >> str_number) && ret_integer >= min )
		{
		return ret_integer;
		}

		std::cin.clear(); //just in case an error occurs with cin (eof(), etc)
		std::cerr << "Input must be an integer. Please try again.\n";
	}
}
class PlayerRankings
{
    protected:

    string Name, Country;
    int Ranking,Rating;

    public:

    void updateData(string tableName)       // for updating record
    {
//        int rating,ranking;
//        string country,name;

        readData(tableName);

        cout<<"\n\nEnter the rank you want to update: ";
        cin>>Ranking;
        fflush(stdin);
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the rank you want to update: ";
            fflush(stdin);
            cin>>Ranking;
        }

        cout<<"Enter the name of player: ";
        getline(cin,Name);
        while(!isValidString(Name))
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter the name of player: ";

            fflush(stdin);
            getline(cin,Name);
            fflush(stdin);
        }


        cout<<"Enter the Country of the Player: ";
        getline(cin,Country);
        while(!isValidString(Country))
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter the Country of the Player: ";

            fflush(stdin);
            getline(cin,Country);
            fflush(stdin);
        }

        cout<<"Enter Player's Rating ";
        cin>>Rating;
        fflush(stdin);
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the rank you want to update: ";
            cin>>Rating;
            fflush(stdin);
        }

        string semiColon= ";";
        string R = to_string(Ranking);

        string query1 = "UPDATE ";
        string query2 = " SET Name = ?, Country = ?, Rating = ? WHERE Rank = ";

        string Query = query1 + tableName + query2 + R + semiColon;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

//        sqlite3_bind_int(stmt, 1, ranking);
        sqlite3_bind_text(stmt, 1, Name.c_str(), Name.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, Country.c_str(), Country.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, Rating);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result != SQLITE_OK )
        {
            cout<<"\nQuery execution failed: "<<sqlite3_errmsg(db)<<"\n";
        }
        else
        {
            cout<<"\nData Updated Successfully! \n";
        }

    }

void readData(string tableName)
{


    string query = "SELECT * FROM ";
    string Query = query + tableName;
    result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
        }

        else
        {
            for(int i=0; i<70; i++)
                cout<<"-";
            cout<<endl<< right<< setw(5)<< "RANK"
            << setw(20)<< "NAME"
            << setw(20)<<"COUNTRY "
            <<setw(20)<<"RATING\n";
            for(int i=0; i<70; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout << setw(4)<< sqlite3_column_int(stmt, 0);
             cout<< setw(25) << sqlite3_column_text(stmt, 1);
             cout << setw(13)<< sqlite3_column_text(stmt, 2);
             cout<< setw(20) << sqlite3_column_int(stmt, 3);
             cout<<"\n";
            }
        }


    }

    void insertData(string tableName)
    {

//        int rating,ranking;
//        string country,name;

//        readData(tableName);

//        cout<<"Enter the rank you want to Insert : ";
//        cin>>ranking;
//        fflush(stdin);
//        while(!cin)
//        {
//            cout<<"Wrong Input! Try again \n";
//            cout<<"\nEnter the rank you want to update: ";
//            fflush(stdin);
//            cin>>Ranking;
//        }

        cout<<"\n\nEnter the name of player: ";
        getline(cin,Name);
        while(!isValidString(Name))
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the Country: ";

            fflush(stdin);
            getline(cin,Name);
            fflush(stdin);
        }

        cout<<"Enter the Country of the Player: ";
        cin>>Country;
        while(!isValidString(Country))
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the Country: ";

            fflush(stdin);
            getline(cin,Country);
            fflush(stdin);
        }

        cout<<"Enter Player's Rating ";
        cin>>Rating;
        fflush(stdin);
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the rank you want to update: ";
            cin>>Rating;
            fflush(stdin);
        }

        string semiColon= ";";
        string R = to_string(Ranking);

        string query1 = "UPDATE ";
        string query2 = " SET Name = ?, Country = ?, Rating = ? WHERE Rank = ";

        string Query = query1 + tableName + query2 + R + semiColon;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

//        sqlite3_bind_int(stmt, 1, ranking);
        sqlite3_bind_text(stmt, 1, Name.c_str(), Name.length(), SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, Country.c_str(), Country.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 3, Rating);

        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result != SQLITE_OK )
        {
            cout<<"Query execution failed: "<<sqlite3_errmsg(db)<<"\n";
        }
        else
        {
            cout<<"Data Updated Successfully! \n";
        }

    }
    void deleteData(string tableName)
    {
        readData(tableName);

        cout<<"\n\nEnter the rank you want to delete: ";
        cin>>Ranking;
        fflush(stdin);
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the rank you want to update: ";
            cin>>Ranking;
            fflush(stdin);
        }

        query = "DELETE FROM testBatsmen WHERE Rank = ";
        string R = to_string(Ranking);
        string semicolon = ";";
        string Query = query + R + semicolon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, Ranking);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result == SQLITE_OK)
        {
            cout<<"Record Deleted Successfully!\n";
        }
        else
        {
            cout<<"Query could not be Executed.\nError: "<<sqlite3_errmsg(db)<<endl;
        }

    }
};

class TeamRankings
{
    string Country;
    int Ranking,Matches,Points,Rating;

    public:

    void readData(string tableName)
    {


    string query = "SELECT * FROM ";
    string Query = query + tableName;
    result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
        }

        else
        {
            for(int i=0; i<90; i++)
                cout<<"-";
            cout<<endl<< right<< setw(5)<< "RANK"
            << setw(20)<< "COUNTRY "
            << setw(20)<<"MATCHES "
            <<setw(20)<<"POINTS "
            <<setw(20)<<"RATING\n";;
            for(int i=0; i<90; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout << setw(4)<< sqlite3_column_int(stmt, 0);
             cout<< setw(25) << sqlite3_column_text(stmt, 1);
             cout << setw(13)<< sqlite3_column_int(stmt, 2);
             cout<< setw(20) << sqlite3_column_int(stmt, 3);
             cout<< setw(20) << sqlite3_column_int(stmt, 4);
             cout<<"\n";
            }
        }


    }

    void updateData(string tableName)
    {
        TeamRankings::readData(tableName);

//        int ranking,matches,rating,points;
//        string country;

        cout<<"\n\nEnter the rank you want to update: ";
        cin>>Ranking;
        fflush(stdin);
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the rank you want to update: ";
            fflush(stdin);
            cin>>Ranking;
        }
        cout<<"Enter the Country : ";
        getline(cin,Country);
        while(!isValidString(Country))
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the Country: ";

            fflush(stdin);
            getline(cin,Country);
            fflush(stdin);
        }

        cout<<"Enter the number of Matches: ";
        cin>>Matches;
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter the number of Matches: ";
            fflush(stdin);
            cin>>Matches;
            fflush(stdin);
        }


        cout<<"Enter Team's Points: ";
        cin>>Points;
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter Team's Points: ";
            fflush(stdin);
            cin>>Points;
            fflush(stdin);
        }
        cout<<"Enter Team's Rating ";
        cin>>Rating;
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter Team's Rating ";
            fflush(stdin);
            cin>>Rating;
            fflush(stdin);
        }

        string semiColon= ";";
        string R = to_string(Ranking);

        string query1 = "UPDATE ";
        string query2 = " SET Country = ?, Matches = ?, Points = ?, Rating = ? WHERE Rank = ";

        string Query = query1 + tableName + query2 + R + semiColon;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

//        sqlite3_bind_int(stmt, 1, ranking);
        sqlite3_bind_text(stmt, 1, Country.c_str(), Country.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, Matches);
        sqlite3_bind_int(stmt, 3, Points);
         sqlite3_bind_int(stmt, 4, Rating);


        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result != SQLITE_OK )
        {
            cout<<"Query execution failed: "<<sqlite3_errmsg(db)<<"\n";
        }
        else
        {
            cout<<"Data Updated Successfully! \n";
        }

    }

    void insertData(string tableName)   // insertData() function here
    {
        TeamRankings::readData(tableName);
//        cout<<"\n\nEnter the rank you want to update: ";
//        cin>>Ranking;
//        fflush(stdin);
//        while(!cin)
//        {
//            cout<<"Wrong Input! Try again \n";
//            cout<<"\nEnter the rank you want to update: ";
//            fflush(stdin);
//            cin>>Ranking;
//        }
        cout<<"\n\nEnter the Country of the team: ";
        getline(cin,Country);
        while(!isValidString(Country))
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the Country: ";

            fflush(stdin);
            getline(cin,Country);
            fflush(stdin);
        }

        cout<<"Enter the number of Matches: ";
        cin>>Matches;
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter the number of Matches: ";
            fflush(stdin);
            cin>>Matches;
            fflush(stdin);
        }


        cout<<"Enter Team's Points: ";
        cin>>Points;
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter Team's Points: ";
            fflush(stdin);
            cin>>Points;
            fflush(stdin);
        }
        cout<<"Enter Team's Rating ";
        cin>>Rating;
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"Enter Team's Rating ";
            fflush(stdin);
            cin>>Rating;
            fflush(stdin);
        }

        string R = to_string(Ranking);

        string query1 = "INSERT INTO ";
        string query2 = "(Country , Matches , Points , Rating) VALUES (?, ?, ?, ?);";
        string semiColon= ";";

        string Query = query1 + tableName + query2;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

//        sqlite3_bind_int(stmt, 1, ranking);
        sqlite3_bind_text(stmt, 1, Country.c_str(), Country.length(), SQLITE_TRANSIENT);
        sqlite3_bind_int(stmt, 2, Matches);
        sqlite3_bind_int(stmt, 3, Points);
         sqlite3_bind_int(stmt, 4, Rating);


        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result != SQLITE_OK )
        {
            cout<<"Query execution failed: "<<sqlite3_errmsg(db)<<"\n";
        }
        else
        {
            cout<<"Data Inserted Successfully! \n";
        }
    }

    void deleteData(string tableName)
    {
        TeamRankings::readData(tableName);

        cout<<"\n\nEnter the rank you want to delete: ";
        cin>>Ranking;
        fflush(stdin);
        while(!cin)
        {
            cout<<"Wrong Input! \n";
            cout<<"\nEnter the rank you want to delete: ";
            cin>>Ranking;
            fflush(stdin);
        }

        string query = "DELETE FROM ";
        string query2 = " WHERE Rank = ";

        string R = to_string(Ranking);
        string semicolon = ";";
        string Query = query + tableName + query2 + R + semicolon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
        sqlite3_bind_int(stmt, 1, Ranking);
        sqlite3_step(stmt);
        sqlite3_finalize(stmt);

        if(result == SQLITE_OK)
        {
            cout<<"Record Deleted Successfully!\n";
        }
        else
        {
            cout<<"Query could not be Executed.\nError: "<<sqlite3_errmsg(db)<<endl;
        }


    }

};

void adminChoices()
{   int choice;


    system("cls");
    cout<<"\nWhat you want to do? \n1. View Records\n2. Update Records\n3. Insert Records\n4. Delete Records\n\n ";
    cin>>choice;

}

int main()
{
    char ch;
    int choice,operationChoice;
    int c_ranking_stats,c_team_player_rank,c_operation;
    int user;
    string username,password,table;

    connection();
    this_thread::sleep_for(std::chrono::milliseconds(2000));
    system("cls");

//    TestBatsman testBatsman;
//    TestBowler testBowler;
//    TestAllRounder testAllRounder;
    PlayerRankings player;
    TeamRankings team;

//    for(int i=1;i<90;i++)
//    {
//     cout<<"-";
//     this_thread::sleep_for(std::chrono::milliseconds(30));
//    }
//    cout<<"\n\t\t\t\t";
//    string title = "BUB CRICKET STATISTICS SYSTEM\n";
//    for(int i=0;i<30;i++)
//    {
//        this_thread::sleep_for(std::chrono::milliseconds(30));
//        cout<<title[i];
//    }
//    for(int i=1;i<90;i++)
//    {
//     cout<<"-";
//     this_thread::sleep_for(std::chrono::milliseconds(30));
//    }

    do
    {

        cout<<"\n\nAre you a user or Admin? \n\n";
        cout<<"1. Admin\n2. User \n\n ";
        cin>>choice;
        while(!cin)
        {
            cout<<"\nInvalid input! Only enter the given numeric options. Try Again\n ";
            cin.clear();
            fflush(stdin);
            cin>>choice;
        }
        switch(choice)
        {
           do
           {
                case 1:

                    cout<<"\nUsername: ";
                    cin>>username;
                    fflush(stdin);
                    cout<<"Password: ";
                    cin>>password;
                    fflush(stdin);
//                    while(!cin)
//                    {
//                        cout<<"\nUsername does not contain numeric values! Try agian\n";
//                        cin.clear();
////                        cin.ignore(100, ' ');
//                        cin>>username;
//                        fflush(stdin);
//                    }
//                        cout<<"Password: ";
//                        cin>>password;
//                        fflush(stdin);
//                    while(!cin)
//                    {
//                        cout<<"\nPassword does not contain numeric values! Try agian\n";
//                        cin.clear();
////                        cin.ignore(100,' ');
//                        cin>>password;
//                        fflush(stdin);
//                    }
                    while(true)
                    {

                     if(!adminLogin(username, password))
                        {
                            while(true)
                            {
                                cout<<"\nInvalid Username or Password. Try again\n";
                                Sleep(2000);
                                cout<<"\nUsername: ";
                                cin>>username;
                                fflush(stdin);
                                while(!cin)
                                {
                                    cout<<"\nInvalid Username! Try agian\n";
                                    cin.clear();
//                                    cin.ignore(100,' ');
                                    cin>>username;
                                    fflush(stdin);
                                }
                                    cout<<"Password: ";
                                    cin>>password;
                                    fflush(stdin);
                                while(!cin)
                                {
                                    cout<<"\nInvalid Username! Try agian\n";
                                    cin.clear();
//                                    cin.ignore(100, ' ');
                                    cin>>password;
                                    fflush(stdin);
                                }
                                    break;
                                }

                            }

                        else
                        {
                            cout<<"Logging in ... ";
                            Sleep(2000);
                            break;
                        }


               }
                break;
           }while(choice!=1);
        }

        if(username=="admin")
        {
            break;
        }
        else if(choice==2)
        {
            user=1;
            break;
        }
        else
        {
            system("cls");
            continue;
        }

    }while(choice!= 1 || choice!=2);


    if(username=="admin")   // admin control section starts from here
    {
        do
        {
            system("cls");
        cout<<"\n\nWhat do you want to access: \n\n";
        cout<<"1. Rankings\n2. Statistics\n\n ";
        cin>>choice;    // choice between ranking and statistics
        fflush(stdin);
        while(!cin)
        {
            cout<<"\nWrong input! Try Again\n ";
            cin.clear();
            system("cls");
            cout<<"\n\nWhat do you want to access: \n\n";
            cout<<"1. Rankings\n2. Statistics\n\n ";
            cin>>choice;

            fflush(stdin);
        }

            switch(choice)  // choice between player rankings and team rankings
            {
//
                while(true)
                {

                    case 1:



                        system("cls");

                        cout<<"\nEnter your choice: ";
                        cout<<"\n1. Team Rankings\n2. Player Rankings\n\n ";
                        cin>>choice;
                        while(!cin)
                        {
                            fflush(stdin);
                            cout<<"\nWrong input! Try Again\n ";
                            cin.clear();
//                            cin.ignore(100,'\n');
                            cin>>choice;
                            fflush(stdin);
                        }
                            switch(choice)  // choice of operation to be performed
                            {
                                while(true)
                                {

                                        case 1:

                                        cout<<"\nEnter your choice: ";
                                        cout<<"\n1. View Records\n2. Update Records\n3.Insert Records\n4. Delete Records \n\n ";
                                        cin>>operationChoice;
                                        fflush(stdin);
                                        while(!cin)
                                        {
                                            cout<<"\nWrong input! Try Again\n ";
                                            cin.clear();
                //                            cin.ignore(100,'\n');
                                            cin>>operationChoice;
                                            fflush(stdin);
                                        }


                                    switch(operationChoice)  // choice of cricket format
                                    {

                                         while(true)
                                        {
                                            case 1:     // view records

                                           cout<<"VIEWING RECORDS: \n\n";
                                           cout<<"Select a Format: \n1. Test\n2. ODI\n3. T20 \n\n ";
                                           cin>>choice;
                                           fflush(stdin);

                                        while(!cin)
                                        {
                                            cout<<"\nWrong input! Try Again:  ";
                                            cin.clear();
                //                            cin.ignore(100,'\n');
                                            cin>>choice;
                                            fflush(stdin);
                                        }

                                           switch(choice)
                                           {
                                                case 1:

                                                    team.readData("testTeams");
                                                    break;

                                                case 2:
                                                    team.readData("odiTeams");
                                                    break;

                                                case 3:
                                                    team.readData("t20Teams");
                                                    break;

                                                default:
                                                    cout<<"Wrong Input! ";
                                                    Sleep(1000);
                                                    continue;

                                           }


                                            cout<<"\nDo you want to see more records or wanna go back? (y/n)\n\n ";
                                                cin>>ch;
                                                while(!cin)
                                                {
                                                cout<<"Try Again! \n";
                                                fflush(stdin);

                                                }
                                                if(ch=='y'||ch=='Y')
                                                {
                                                system("pause");
                                                system("cls");
                                                continue;
                                                }
                                                else
                                                {
                                                    system("cls");
                                                    break;
                                                }
                                            if(ch=='n' || ch=='N')
                                            {
                                                break;
                                            }
                                        }
                                            if(ch=='n' || ch=='N')
                                                break;  // breaking while loop as well as inner switch



                                            if(ch=='n' || ch=='N')
                                                break;      // breaking switch of operation

                                        case 2:     // for updating records

                                               cout<<"UPDATING RECORDS: \n\n";
                                               cout<<"Select a Format: \n1. Test\n2. ODI\n3. T20 \n\n ";
                                               cin>>choice;
                                               fflush(stdin);

                                            while(!cin)
                                            {
                                                cout<<"\nWrong input! Try Again:  ";
                                                cin.clear();
                    //                            cin.ignore(100,'\n');
                                                cin>>choice;
                                                fflush(stdin);
                                            }


                                             switch(choice)
                                             {
                                                case 1:

                                                    team.updateData("testTeams");
                                                    break;

                                                case 2:
                                                    team.updateData("odiTeams");
                                                    break;

                                                case 3:
                                                    team.updateData("t20Teams");
                                                    break;

                                                default:
                                                    cout<<"Wrong Input! ";
                                                    Sleep(1000);
                                                    continue;

                                                }


                                            cout<<"\nDo you want to update more records or wanna go back? (y/n)\n\n ";
                                                cin>>ch;
                                                while(!cin)
                                                {
                                                cout<<"Try Again! \n";
                                                cin>>ch;
                                                fflush(stdin);

                                                }
                                                if(ch=='y'||ch=='Y')
                                                {
                                                system("pause");
                                                system("cls");
                                                continue;
                                                }
                                                else
                                                {
                                                    system("cls");
                                                    break;
                                                }
                                            if(ch=='n' || ch=='N')
                                            {
                                                break;  // break switch of operations
                                            }

                                        case 3:     // for inserting records

                                            cout<<"\nINSERTING RECORDS: \n\n";
                                            cout<<"Select a Format: \n1. Test\n2. ODI\n3. T20 \n\n ";
                                            cin>>choice;
                                            fflush(stdin);
                                            while(!cin)
                                        {
                                            cout<<"\nWrong input! Try Again:  ";
                                            cin.clear();
                //                            cin.ignore(100,'\n');
                                            cin>>choice;
                                            fflush(stdin);
                                        }
                                        switch(choice)
                                           {
                                                case 1:

                                                    team.insertData("testTeams");
                                                    break;

                                                case 2:
                                                    team.insertData("odiTeams");
                                                    break;

                                                case 3:
                                                    team.insertData("t20Teams");
                                                    break;

                                                default:
                                                    cout<<"Wrong Input! ";
                                                    Sleep(1000);
                                                    continue;

                                           }
                                           cout<<"\nDo you want to update more records or wanna go back? (y/n)\n\n ";
                                                cin>>ch;
                                                while(!cin)
                                                {
                                                cout<<"Try Again! \n";
                                                cin>>ch;
                                                fflush(stdin);

                                                }
                                                if(ch=='y'||ch=='Y')
                                                {
                                                system("pause");
                                                system("cls");
                                                continue;
                                                }
                                                else
                                                {
                                                    system("cls");
                                                    break;
                                                }
                                            if(ch=='n' || ch=='N')
                                            {
                                                break;  // break switch of operations
                                            }

                                            case 4:     // for deleting records

                                            cout<<"\nDLETING RECORDS: \n\n";
                                            cout<<"Select a Format: \n1. Test\n2. ODI\n3. T20 \n\n ";
                                            cin>>choice;
                                            fflush(stdin);
                                            while(!cin)
                                        {
                                            cout<<"\nWrong input! Try Again:  ";
                                            cin.clear();
                //                            cin.ignore(100,'\n');
                                            cin>>choice;
                                            fflush(stdin);
                                        }
                                        switch(choice)
                                           {
                                                case 1:

                                                    team.deleteData("testTeams");
                                                    break;

                                                case 2:
                                                    team.deleteData("odiTeams");
                                                    break;

                                                case 3:
                                                    team.deleteData("t20Teams");
                                                    break;

                                                default:
                                                    cout<<"Wrong Input! ";
                                                    Sleep(1000);
                                                    continue;

                                           }
                                           cout<<"\nDo you want to delete more records or wanna go back? (y/n)\n\n ";
                                                cin>>ch;
                                                while(!cin)
                                                {
                                                cout<<"Try Again! \n";
                                                cin>>ch;
                                                fflush(stdin);

                                                }
                                                if(ch=='y'||ch=='Y')
                                                {
                                                system("pause");
                                                system("cls");
                                                continue;
                                                }
                                                else
                                                {
                                                    system("cls");
                                                    break;
                                                }
                                            if(ch=='n' || ch=='N')
                                            {
                                                break;  // break switch of operations
                                            }
                                        }       // here switch of operations ends

                                            if(ch=='n' || ch=='N')
                                                break;  // breaking while loop of admin operations
                                        }

                                        if(ch=='n' || ch=='N')
                                                break;  // break to go out of selection of admin operations


                                    case 2:     // for player rankings

                                        cout<<"What operation you want to perform? \n\n";
                                        cout<<"1. View Records\n2. Update Records\n3. Insert Records\n4. Delete Records\n\n";
                                        cin>>operationChoice;

                                            switch(operationChoice)
                                            {
                                                case 1:		// for viewing records
                                                    while(true)
                                                    {

                                                       cout<<"Enter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);
                                                       if(!isValidTableName(table))
                                                        {
                                                             break;  //continue;
                                                        }
                                                       else
                                                        {
                                                          player.readData(table);
                                                          cout<<"\n\nIf you want to view any more records ";
                                                          system("pause");
                                                          cout<<"\n\n";
                                                        }
                                                     }

                                                case 2:		// for updating records

//                                                    while(true)
//                                                    {
                                                        cout<<"Enter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);
                                                        while(!isValidTableName(table))
                                                        {
//                                                            if(isValidTableName(table))
//                                                        {
//                                                        }
                                                            cout<<"Wrong Table Name! \n";
                                                            cout<<"Enter Table Name: ";
                                                            fflush(stdin);
                                                            getline(cin,table);
                                                            fflush(stdin);
//                                                            continue;
                                                        }
//                                                       else
//                                                        {
                                                          player.updateData(table);
                                                          cout<<"\n\nIf you want to view any more records ";
                                                          system("pause");
                                                          cout<<"\n\n";
                                                            break;  //continue;
//                                                        }
//                                                    }

                                                case 3:

                                                    while(true)
                                                    {
                                                        cout<<"Enter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);
                                                       if(!isValidTableName(table))
                                                        {
                                                             break;  //continue;
                                                        }
                                                       else
                                                        {
                                                          player.insertData(table);
                                                          cout<<"\n\nIf you want to view any more records ";
                                                          system("pause");
                                                          cout<<"\n\n";
                                                        }
                                                    }

                                                 case 4:

                                                    while(true)
                                                    {
                                                        cout<<"Enter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);
                                                       if(!isValidTableName(table))
                                                        {
                                                             break;  //continue;
                                                        }
                                                       else
                                                        {
                                                          player.deleteData(table);
                                                          cout<<"\n\nIf you want to view any more records ";
                                                          system("pause");
                                                          cout<<"\n\n";
                                                        }
                                                    }

                                            }

                                   }

//
//                                        cout<<"Do you want to go back ? (y/n)";
//                                        cin>>ch;
//                                        if(ch!='y' || ch!='Y' ||ch!='n' || ch!='N')
//                                        {
//                                            while(!cin)
//                                            {
//                                             cout<<"Do you want to go back ? (y/n)";
//                                             cin>>ch;
//                                            }
//                                        }
//
//                                        if(ch=='y' || ch=='Y')
//                                            break; // break to go out of the loop of team rankings or player rankings
//                                        else
//                                        continue;

//                                        break;    // break to go out of the case 1 of switch case for choice of team or player rankings
                                       // while loop of team / player rankings

                                        if(ch=='n' || ch=='N')
                                            break;
                                }
                                        break;

//                                    if(ch=='y'||ch=='Y')
//                                    {
//                                        break;  // breaking the switch (choice) for team rankings or player rankings
//                                    }



//                                do
//                                {
                            }   // if(choice == 1) ending here

//                                cout<<"\nSelect a Category: \n\n";
//                                //test categories
//                                cout<<"1. Test Batsmen\n2. Test Bowlers\n3. Test Allrounders\n";
//                                cout<<"4. All Time Test Batsmen\n5. All Time Test Bowlers\n6. All Time Test AllRounders\n";
//                                //ODI categories
//                                cout<<"7. ODI Batsmen\n8. ODI Bowlers\n9. ODI AllRounders\n";
//                                cout<<"10. All TIme ODI Batsmen\n11. All Time ODI Bowlers\n12. All TIme ODI AllRounders\n";
//                                //T20 categories
//                                cout<<"13. T20 Batsmen\n14. T20 Bowlers\n15. T20 AllRounders\n";
//                                cout<<"16. All Time T20 Batsmen\n17. All Time T20 Bowlers\n18. All Time T20 AllRounders\n ";
//
//                                cin>>choice;
//                                    while(!cin) //validating whether input is integer or not
//                                    {
//                                        cout<<"\nWrong input! Try Again\n ";
//                                        cin.clear();
//                                        cin.ignore(100,'\n');
//                                        cin>>choice;
//                                    }
//                                        switch(choice)
//                                        {
//                                            case 1:
//                                            {   system("cls");
//                                                player.readData("testBatsman");
//                                                break;
//                                            }
//                                            case 2:
//                                            {   system("cls");
//                                                player.readData("testBowler");
//                                                break;
//                                            }
//                                            case 3:
//                                            {   system("cls");
//                                                player.readData("testAllRounder");
//                                                break;
//                                            }
//                                            case 4:
//                                            {   system("cls");
//                                                player.readData("allTimeTestBat");
//                                                break;
//                                            }
//                                            case 5:
//                                            {   system("cls");
//                                                player.readData("allTimeTestBowl");
//                                                break;
//                                            }
//                                            case 6:
//                                            {   system("cls");
//                                                player.readData("allTimeTestAll");
//                                                break;
//                                            }
//                                            case 7:
//                                            {   system("cls");
//                                                player.readData("odiBatsman");
//                                                break;
//                                            }
//                                            case 8:
//                                            {   system("cls");
//                                                player.readData("odiBowler");
//                                                break;
//                                            }
//                                            case 9:
//                                            {   system("cls");
//                                                player.readData("odiAllRounder");
//                                                break;
//                                            }
//                                            case 10:
//                                            {   system("cls");
//                                                player.readData("allTimeOdiBat");
//                                                break;
//                                            }
//                                            case 11:
//                                            {   system("cls");
//                                                player.readData("allTimeOdiBowl");
//                                                break;
//                                            }
//                                            case 12:
//                                            {   system("cls");
//                                                player.readData("allTimeOdiAll");
//                                                break;
//                                            }
//                                            case 13:
//                                            {   system("cls");
//                                                player.readData("t20Batsman");
//                                                break;
//                                            }
//                                            case 14:
//                                            {   system("cls");
//                                                player.readData("t20Bowler");
//                                                break;
//                                            }
//                                            case 15:
//                                            {   system("cls");
//                                                player.readData("t20AllRounder");
//                                                break;
//                                            }
//                                            case 16:
//                                            {   system("cls");
//                                                player.readData("t20AllTimeBat");
//                                                break;
//                                            }
//                                            case 17:
//                                            {   system("cls");
//                                                player.readData("t20AllTimeBowl");
//                                                break;
//                                            }
//                                            case 18:
//                                            {   system("cls");
//                                                player.readData("t20AllTimeAll");
//                                                break;
//                                            }
//                                            default:
//                                             {
//                                                cout<<"Wrong Input! Try Again";
//                                                Sleep(2000);
//                                                system("cls");
//                                                continue;
//                                             }
//
//                                        }
//                                    cout<<"\nDo you want to see more Rankings or you wanna do back? (y/n)\n\n ";
//                                    cin>>ch;
//                                    while(!cin)
//                                    {
//                                    cout<<"Try Again! \n";
//                                    fflush(stdin);
//
//                                    }
//                                    if(ch=='y'||ch=='Y')
//                                    {
//                                    system("pause");
//                                    system("cls");
//                                    }
//                                    else
//                                    {
//                                        system("cls");
//                                        break;
//                                    }
//
//
//                                if(ch=='n' || ch=='N')
//                                    {
//                                        break;
//                                    }
//                            }while(true);
//
//                         }

    //                case 2:  // for player rankings
//                        default:
//                        cout<<"Wrong Input! \n";
//                        continue;

                  }while(choice!=1 || choice!= 2);

//                }

////
//        }while(choice!=1 || choice!= 2);

          }     // if (username == admin) ending here







    else if(user==1)    // user control section starts from here
    {
        do
        {
        cout<<"\n\nWhat do you want to look up: \n\n";
        cout<<"1. Rankings\n2. Statistics\n\n ";
        cin>>choice;
        fflush(stdin);
        while(!cin)
        {
            cout<<"\nWrong input! Try Again\n ";
            cin.clear();
//            cin.ignore(100,'\n');
            cin>>choice;
            fflush(stdin);
        }

            switch(choice)
            {
                case 1:
                {
                   do
                   {
                    system("cls");

                    cout<<"\nEnter your choice: ";
                    cout<<"\n1. Team Rankings\n2. Player Rankings\n\n ";
                    cin>>choice;
                    fflush(stdin);
                    while(!cin)
                    {
                        cout<<"\nWrong input! Try Again\n ";
                        cin.clear();
//                      cin.ignore(100,'\n');
                        cin>>choice;
                        fflush(stdin);
                    }

                switch(choice)
                {   while(true)
                    {
                        case 1:
                        {
                            cout<<"Select a Format: \n1. Test\n2. ODI\n3. T20 \n\n ";
                            cin>>choice;
                            fflush(stdin);
                            while(!cin)
                            {
                                cout<<"\nWrong input! Try Again:  ";
                                cin.clear();
    //                            cin.ignore(100,'\n');
                                cin>>choice;
                                fflush(stdin);
                            }
                            switch(choice)
                            {
                                case 1:
                                team.readData("testTeams");
                                break;

                                case 2:
                                team.readData("odiTeams");
                                break;

                                case 3:
                                team.readData("t20Teams");
                                break;

                            }

                        }
                            cout<<"\nDo you want to see more Rankings or wanna go back? (y/n)\n\n ";
                            cin>>ch;
                            while(!cin)
                            {
                                cout<<"Try Again! \n";
                                fflush(stdin);

                            }
                            if(ch=='y'||ch=='Y')
                            {
                                system("pause");
                                system("cls");
                                continue;
                            }
                            else
                            {
                                system("cls");
                                break;
                            }
                        }
                            if(ch=='n' || ch=='N')
                            {
                                break;
                            }
                        case 2:
                        {
                            do
                            {

                            cout<<"\nSelect a Category: \n\n";
                            //test categories
                            cout<<"1. Test Batsmen\n2. Test Bowlers\n3. Test Allrounders\n";
                            cout<<"4. All Time Test Batsmen\n5. All Time Test Bowlers\n6. All Time Test AllRounders\n";
                            //ODI categories
                            cout<<"7. ODI Batsmen\n8. ODI Bowlers\n9. ODI AllRounders\n";
                            cout<<"10. All TIme ODI Batsmen\n11. All Time ODI Bowlers\n12. All TIme ODI AllRounders\n";
                            //T20 categories
                            cout<<"13. T20 Batsmen\n14. T20 Bowlers\n15. T20 AllRounders\n";
                            cout<<"16. All Time T20 Batsmen\n17. All Time T20 Bowlers\n18. All Time T20 AllRounders\n ";

                            cin>>choice;
                                while(!cin) //validating whether input is integer or not
                                {
                                    cout<<"\nWrong input! Try Again\n ";
                                    cin.clear();
                                    cin.ignore(100,'\n');
                                    cin>>choice;
                                }
                                    switch(choice)
                                    {
                                        case 1:
                                        {   system("cls");
                                            player.readData("testBatsman");
                                            break;
                                        }
                                        case 2:
                                        {   system("cls");
                                            player.readData("testBowler");
                                            break;
                                        }
                                        case 3:
                                        {   system("cls");
                                            player.readData("testAllRounder");
                                            break;
                                        }
                                        case 4:
                                        {   system("cls");
                                            player.readData("allTimeTestBat");
                                            break;
                                        }
                                        case 5:
                                        {   system("cls");
                                            player.readData("allTimeTestBowl");
                                            break;
                                        }
                                        case 6:
                                        {   system("cls");
                                            player.readData("allTimeTestAll");
                                            break;
                                        }
                                        case 7:
                                        {   system("cls");
                                            player.readData("odiBatsman");
                                            break;
                                        }
                                        case 8:
                                        {   system("cls");
                                            player.readData("odiBowler");
                                            break;
                                        }
                                        case 9:
                                        {   system("cls");
                                            player.readData("odiAllRounder");
                                            break;
                                        }
                                        case 10:
                                        {   system("cls");
                                            player.readData("allTimeOdiBat");
                                            break;
                                        }
                                        case 11:
                                        {   system("cls");
                                            player.readData("allTimeOdiBowl");
                                            break;
                                        }
                                        case 12:
                                        {   system("cls");
                                            player.readData("allTimeOdiAll");
                                            break;
                                        }
                                        case 13:
                                        {   system("cls");
                                            player.readData("t20Batsman");
                                            break;
                                        }
                                        case 14:
                                        {   system("cls");
                                            player.readData("t20Bowler");
                                            break;
                                        }
                                        case 15:
                                        {   system("cls");
                                            player.readData("t20AllRounder");
                                            break;
                                        }
                                        case 16:
                                        {   system("cls");
                                            player.readData("t20AllTimeBat");
                                            break;
                                        }
                                        case 17:
                                        {   system("cls");
                                            player.readData("t20AllTimeBowl");
                                            break;
                                        }
                                        case 18:
                                        {   system("cls");
                                            player.readData("t20AllTimeAll");
                                            break;
                                        }
                                        default:
                                         {
                                            cout<<"Wrong Input! Try Again";
                                            Sleep(2000);
                                            system("cls");
                                            continue;
                                         }

                                    }
                                cout<<"\nDo you want to see more Rankings or you wanna do back? (y/n)\n\n ";
                                cin>>ch;
                                while(!cin)
                                {
                                cout<<"Try Again! \n";
                                fflush(stdin);

                                }
                                if(ch=='y'||ch=='Y')
                                {
                                system("pause");
                                system("cls");
                                }
                                else
                                {
                                    system("cls");
                                    break;
                                }


                            if(ch=='n' || ch=='N')
                                {
                                    break;
                                }
                        }while(true);

                    }
                }
              }while(choice!=1 || choice!= 2);
            }
            default:
             {
                cout<<"\nWrong Input! Try Again";
                Sleep(2000);
                system("cls");
                break;
             }
        }

    }while(true);

}


    sqlite3_close(db);

    return 0;
}
