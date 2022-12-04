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
//#include"Rankings.h"

using namespace std;

void connection();
void readData();

sqlite3 *db;
sqlite3_stmt *stmt;
int result;
string query,query2,Query;

void connection()
{
    if(sqlite3_open("Project (final).db", &db) == SQLITE_OK)
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

        cout<<"Enter the rank you want to Insert : ";
        cin>>Ranking;
        fflush(stdin);
        while(!cin)
        {
            cout<<"Wrong Input! Try again \n";
            cout<<"\nEnter the rank you want to update: ";
            fflush(stdin);
            cin>>Ranking;
        }

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
            cout<<"\nEnter the rank you want to insert: ";
            cin>>Rating;
            fflush(stdin);
        }

        string semiColon= ";";
        string R = to_string(Ranking);

        string query1 = "INSERT INTO ";
        string query2 = "(Name , Country, Rating) VALUES (?, ?, ?);";

        string Query = query1 + tableName + query2;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

//        sqlite3_bind_int(stmt, 1, Ranking);
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
            cout<<"\nEnter the rank you want to delete: ";
            cin>>Ranking;
            fflush(stdin);
        }

        query = "DELETE FROM ";
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

class Statistics
{
    protected:

    string Name, Birth, BattingStyle, BowlingStyle, Role;
    int Age;

    public:

    int getInfo(string name)
    {
        string apos = "'";
        string semiColon = ";";

        query = "SELECT * FROM playersInfo WHERE NAME = ";
        Query = query + apos + name + apos + semiColon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            for(int i=0; i<90; i++)
                cout<<"-";
            cout<<endl<< right<< setw(5)<< "Name"
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
            return 1;
        }
    }

    virtual int getData(string name) = 0;
};

class Batsman
{
    protected:
    string Name, Birth, BattingStyle, BowlingStyle, Role;
    int Age;
    int Matches, Innings, Runs, HighScore, Hundreds, Fifties, Fours, Sixes;
    float Average, SR;

    public:

//        virtual void getMatches(string name) = 0;
//        virtual void getInnings(string name) = 0;
//        virtual void getRuns(string name) = 0;
//        virtual void getHighScore(string name) = 0;
//        virtual void getAverage(string name) = 0;
//        virtual void getStrikeRate(string name) = 0;
//        virtual void getHundreds(string name) = 0;
//        virtual void getFifties(string name) = 0;
//        virtual void getFours(string name) = 0;
//        virtual void getSixes(string name) = 0;
        virtual int getData(string name) = 0;

};

class Bowler : public Statistics
{
    protected:
    int Matches, Innings, Balls, Runs, Wickets, FiveW, TenW;
    string BBI, BBM;
    float Average, Economy, SR;

    public:

//    virtual void getMatches(string name) = 0;
//    virtual void getInnings(string name) = 0;
//    virtual void getBalls(string name) = 0;
//    virtual void getRuns(string name) = 0;
//    virtual void getWickets(string name) = 0;
//    virtual void getBestFigures(string name) = 0;
//    virtual void getAverage(string name) = 0;
//    virtual void getStrikeRate(string name) = 0;
//    virtual void getEconomy(string name) = 0;
//    virtual void getWicketHauls(string name) = 0;
      virtual int getData(string name) = 0;

};

class AllRounder : public Statistics
{
    protected:

    int Matches, BattingInnings, BattingRuns, HighScore, Hundreds, Fifties, Fours, Sixes;
    float BattingAverage, BattingSR;

    int Innings, Balls, BowlingRuns, Wickets, FiveW, TenW;
    string BBI, BBM;
    float BowlingAverage, Economy, BowlingSR;

    public:

//    virtual void getMatches(string name) = 0;
//    virtual void getInnings(string name) = 0;
//    virtual void getRuns(string name) = 0;
//    virtual void getHighScore(string name) = 0;
//    virtual void getAverage(string name) = 0;
//    virtual void getStrikeRate(string name) = 0;
//    virtual void getHundreds(string name) = 0;
//    virtual void getFifties(string name) = 0;
//    virtual void getFours(string name) = 0;
//    virtual void getSixes(string name) = 0;
//    virtual void getWickets(string name) = 0;
//    virtual void getBestFigures(string name) = 0;
//    virtual void getEconomy(string name) = 0;
    virtual int getData(string name) = 0;

};

class TestBatsman : public Batsman
{
    public:
//    void getMatches(string name)
//    {
//       query = "SELECT Matches FROM testBatsmanStats WHERE Name = ";
//       string apos = "'",semiColon = ";";
//       Query = query + apos + name + apos + semiColon;
//
//       result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
//
//        if(result != SQLITE_OK)
//        {
//            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
//        }
//
//        else
//        {
//            for(int i=0; i<15; i++)
//                cout<<"-";
//
//            cout<<endl<< right<< setw(5)<< "Matches: ";
//            cout<< sqlite3_column_int(stmt, 0);
//            for(int i=0; i<15; i++)
//                cout<<"-";
//        }
//    }
//    void getInnings(string name)
//    {
//        query = "SELECT Innings FROM testBatsmanStats WHERE Name = ";
//       string apos = "'",semiColon = ";";
//       Query = query + apos + name + apos + semiColon;
//    }
//    void getRuns(string name)
//     {
//        query = "SELECT Runs FROM testBatsmanStats WHERE Name = ";
//       string apos = "'",semiColon = ";";
//       Query = query + apos + name + apos + semiColon;
//     }
//   void getHighScore(string name)
//    {
//        query = "SELECT HighScore FROM testBatsmanStats WHERE Name = ";
//       string apos = "'",semiColon = ";";
//       Query = query + apos + name + apos + semiColon;
//    }
//    void getAverage(string name)
//     {
//         query = "SELECT Average FROM testBatsmanStats WHERE Name = ";
//       string apos = "'",semiColon = ";";
//       Query = query + apos + name + apos + semiColon;
//     }
//    virtual void getStrikeRate(string name) = 0;
//    virtual void getHundreds(string name) = 0;
//    virtual void getFifties(string name) = 0;
//    virtual void getFours(string name) = 0;
//    virtual void getSixes(string name) = 0;

    getData(string name)
    {
        query = "SELECT * FROM testBatsmanStats WHERE Name = ";
//        query2 = ""
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
        }

        else
        {
            for(int i=0; i<90; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"RUNS"
            <<setw(6)<<"HS"
            <<setw(11)<<"AVERAGE"
            <<setw(6)<<"SR"
            <<setw(9)<<"100s"
            <<setw(9)<<"50s"
            <<setw(8)<<"4s"
            <<setw(8)<<"6s\n";;
            for(int i=0; i<90; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);
             cout<< setw(4) << sqlite3_column_int(stmt, 7);
             cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);
             cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }
        }
    }
};

class OdiBatsman: public Batsman
{
        public:

       getData(string name)
    {
        query = "SELECT * FROM odiBatsmanStats WHERE Name = ";
//        query2 = ""
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"RUNS"
            <<setw(6)<<"HS"
            <<setw(11)<<"AVERAGE"
            <<setw(6)<<"SR"
            <<setw(9)<<"100s"
            <<setw(9)<<"50s"
            <<setw(8)<<"4s"
            <<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);
             cout<< setw(4) << sqlite3_column_int(stmt, 7);
             cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);
             cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }
        return 1;
        }
    }
};

class T20Batsman : public Batsman
{
    public:

       getData(string name)
    {
        query = "SELECT * FROM t20BatsmanStats WHERE Name = ";
//        query2 = ""
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"RUNS"
            <<setw(6)<<"HS"
            <<setw(11)<<"AVERAGE"
            <<setw(6)<<"SR"
            <<setw(9)<<"100s"
            <<setw(9)<<"50s"
            <<setw(8)<<"4s"
            <<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);
             cout<< setw(4) << sqlite3_column_int(stmt, 7);
             cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);
             cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }
        return 1;
        }
    }
};

class AllFormatBatsman : public Batsman
{
    public:

       getData(string name)
    {
        query = "SELECT * FROM odiBatsmanStats WHERE NAME = ";
        query2 = "SELECT * FROM t20BatsmanStats WHERE NAME = ";
        string query3 = "SELECT * FROM testBatsmanStats WHERE NAME = ";



        string apos = "'",semiColon = ";";
        string Query1 = query + apos + name + apos + semiColon;
        string Query2 = query2 + apos + name + apos + semiColon;
        string Query3 = query3 + apos + name + apos + semiColon;
        int result2, result3;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
        result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);
        result3 = sqlite3_prepare_v2(db, Query3.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            cout<<"\n\n\t\t\t\tODI STATS\n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "<< setw(9)<< "INNINGS "<<setw(6)<<"RUNS"<<setw(6)<<"HS"<<setw(11)<<"AVERAGE"<<setw(6)<<"SR"<<setw(9)<<"100s"<<setw(9)<<"50s"<<setw(8)<<"4s"<<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
            while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
            cout<< setw(11)<< sqlite3_column_text(stmt, 0);cout<< setw(5) << sqlite3_column_int(stmt, 1);cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);cout<< setw(8) << sqlite3_column_int(stmt, 4);cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);cout<< setw(4) << sqlite3_column_int(stmt, 7);cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }
        }
        if(result2 != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
             cout<<"\n\n\t\t\t\tT20 STATS\n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "<< setw(9)<< "INNINGS "<<setw(6)<<"RUNS"<<setw(6)<<"HS"<<setw(11)<<"AVERAGE"<<setw(6)<<"SR"<<setw(9)<<"100s"<<setw(9)<<"50s"<<setw(8)<<"4s"<<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
            while((result2 = sqlite3_step(stmt)) == SQLITE_ROW )
            {
            cout<< setw(11)<< sqlite3_column_text(stmt, 0);cout<< setw(5) << sqlite3_column_int(stmt, 1);cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);cout<< setw(8) << sqlite3_column_int(stmt, 4);cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);cout<< setw(4) << sqlite3_column_int(stmt, 7);cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }

        }  if(result3 != SQLITE_OK)
            {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
            }

            else
            {
            cout<<"\n\n\t\t\t\tTEST STATS\n\n";
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "<< setw(9)<< "INNINGS "<<setw(6)<<"RUNS"<<setw(6)<<"HS"<<setw(11)<<"AVERAGE"<<setw(6)<<"SR"<<setw(9)<<"100s"<<setw(9)<<"50s"<<setw(8)<<"4s"<<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
                while((result3 = sqlite3_step(stmt)) == SQLITE_ROW )
                {
                cout<< setw(11)<< sqlite3_column_text(stmt, 0);cout<< setw(5) << sqlite3_column_int(stmt, 1);cout<< setw(9)<< sqlite3_column_int(stmt, 2);
                 cout<< setw(11) << sqlite3_column_int(stmt, 3);cout<< setw(8) << sqlite3_column_int(stmt, 4);cout<< setw(8) << sqlite3_column_double(stmt, 5);
                 cout<< setw(10) << sqlite3_column_double(stmt, 6);cout<< setw(4) << sqlite3_column_int(stmt, 7);cout<< setw(4) << sqlite3_column_int(stmt, 8);
                 cout<< setw(5) << sqlite3_column_int(stmt, 9);cout<< setw(5) << sqlite3_column_int(stmt, 10);
                 cout<<"\n";
                }
            }

    }
};

class TestBowler :public Bowler
{
    public:

       getData(string name)
    {
        query = "SELECT * FROM testBowlerStats WHERE Name = ";
//        query2 = ""
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"
            <<setw(6)<<"RUNS"
            <<setw(6)<<"WICKETS"
            <<setw(9)<<"BBI"
            <<setw(9)<<"BBM"
            <<setw(11)<<"AVERAGE"
            <<setw(8)<<"Economy"
            <<setw(8)<<"SR\n"
            <<setw(4)<<"5W"
            <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);
             cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8);
             cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10);
             cout<< setw(5) << sqlite3_column_int(stmt, 11);
             cout<< setw(5) << sqlite3_column_int(stmt, 112);
             cout<<"\n";
            }
        return 1;
        }
    }
};

class OdiBowler : public Bowler
{
    public:

       getData(string name)
    {
        query = "SELECT * FROM odiBowlerStats WHERE Name = ";
//        query2 = ""
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"
            <<setw(6)<<"RUNS"
            <<setw(6)<<"WICKETS"
            <<setw(9)<<"BBI"
            <<setw(9)<<"BBM"
            <<setw(11)<<"AVERAGE"
            <<setw(8)<<"Economy"
            <<setw(8)<<"SR\n"
            <<setw(4)<<"5W"
            <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);
             cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8);
             cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10);
             cout<< setw(5) << sqlite3_column_int(stmt, 11);
             cout<< setw(5) << sqlite3_column_int(stmt, 112);
             cout<<"\n";
            }
        return 1;
        }
    }
};

class T20Bowler : public Bowler
{
    public:

       getData(string name)
    {
        query = "SELECT * FROM t20BowlerStats WHERE Name = ";
//        query2 = ""
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;

        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
//        int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"
            <<setw(6)<<"RUNS"
            <<setw(6)<<"WICKETS"
            <<setw(9)<<"BBI"
            <<setw(9)<<"BBM"
            <<setw(11)<<"AVERAGE"
            <<setw(8)<<"Economy"
            <<setw(8)<<"SR\n"
            <<setw(4)<<"5W"
            <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);
             cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8);
             cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10);
             cout<< setw(5) << sqlite3_column_int(stmt, 11);
             cout<< setw(5) << sqlite3_column_int(stmt, 112);
             cout<<"\n";
            }
        return 1;
        }
    }
};

class AllFormatBowler : public Bowler
{
    public:

       getData(string name)
    {
        query = "SELECT * FROM testBowlerStats WHERE Name = ";
        query2 = "SELECT * FROM odiBowlerStats Where Name = ";
        string query3 = "SELECT * FROM t20BowlerStats Where Name = ";
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;

        string Query2 = query2 + apos + name + apos + semiColon;
        string Query3 = query3 + apos + name + apos + semiColon;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
        int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);
        int result3 = sqlite3_prepare_v2(db, Query3.c_str(), -1, &stmt, NULL);
        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {


            cout<<"\n\n\t\t\t\tTEST STATS\n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"<< setw(15)<<"MATCHES "<< setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"<<setw(6)<<"RUNS"<<setw(6)<<"WICKETS"<<setw(9)<<"BBI"
            <<setw(9)<<"BBM" <<setw(11)<<"AVERAGE"<<setw(8)<<"Economy"<<setw(8)<<"SR\n"
            <<setw(4)<<"5W" <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);  cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);  cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);  cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);  cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8); cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10); cout<< setw(5) << sqlite3_column_int(stmt, 11);
              cout<< setw(5) << sqlite3_column_int(stmt, 12);
             cout<<"\n";
            }
//        return 1;
        }
//           result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);

        if(result2 != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }
        else
        {
            cout<<"\n\n\t\t\t\tODI STATS\n\n";

            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"<< setw(15)<<"MATCHES "<< setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"<<setw(6)<<"RUNS"<<setw(6)<<"WICKETS"<<setw(9)<<"BBI"
            <<setw(9)<<"BBM" <<setw(11)<<"AVERAGE"<<setw(8)<<"Economy"<<setw(8)<<"SR\n"
            <<setw(4)<<"5W" <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
            while((result2 = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);  cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);  cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);  cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);  cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8); cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10); cout<< setw(5) << sqlite3_column_int(stmt, 11);
              cout<< setw(5) << sqlite3_column_int(stmt, 12);
             cout<<"\n";
            }
        }
//        int result3 = sqlite3_prepare_v2(db, Query3.c_str(), -1, &stmt, NULL);
        if(result3 != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }
        else
        {
            cout<<"\n\n\t\t\t\tT20 STATS\n\n";

            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"<< setw(15)<<"MATCHES "<< setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"<<setw(6)<<"RUNS"<<setw(6)<<"WICKETS"<<setw(9)<<"BBI"
            <<setw(9)<<"BBM" <<setw(11)<<"AVERAGE"<<setw(8)<<"Economy"<<setw(8)<<"SR\n"
            <<setw(4)<<"5W" <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
            while((result3 = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);  cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);  cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);  cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);  cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8); cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10); cout<< setw(5) << sqlite3_column_int(stmt, 11);
              cout<< setw(5) << sqlite3_column_int(stmt, 12);
             cout<<"\n";
            }
        }
    }

};

class OdiAllRounder : public AllRounder
{
   public:

       getData(string name)
        {
        query = "SELECT * FROM odiBowlerStats WHERE Name = ";
        query2 = "SELECT * FROM odiBatsmanStats WHERE Name = ";
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;
    string Query2 = query2 + apos + name + apos + semiColon;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
            int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);
//        int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {   cout<<"\n\n\t\t\t\tBOWLING STATS \n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"
            <<setw(6)<<"RUNS"
            <<setw(6)<<"WICKETS"
            <<setw(9)<<"BBI"
            <<setw(9)<<"BBM"
            <<setw(11)<<"AVERAGE"
            <<setw(8)<<"Economy"
            <<setw(8)<<"SR\n"
            <<setw(4)<<"5W"
            <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);
             cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8);
             cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10);
             cout<< setw(5) << sqlite3_column_int(stmt, 11);
             cout<< setw(5) << sqlite3_column_int(stmt, 112);
             cout<<"\n";
            }
        return 1;
        }

        if(result2 != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            cout<<"\n\n\t\t\t\tBATTING STATS\n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"RUNS"
            <<setw(6)<<"HS"
            <<setw(11)<<"AVERAGE"
            <<setw(6)<<"SR"
            <<setw(9)<<"100s"
            <<setw(9)<<"50s"
            <<setw(8)<<"4s"
            <<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result2 = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);
             cout<< setw(4) << sqlite3_column_int(stmt, 7);
             cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);
             cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }
        return 1;
        }
    }
};

class T20AllRounder : public AllRounder
{
    public:

       getData(string name)
        {
        query = "SELECT * FROM t20BowlerStats WHERE Name = ";
        query2 = "SELECT * FROM t20BatsmanStats WHERE Name = ";
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;
    string Query2 = query2 + apos + name + apos + semiColon;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
        int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);
//        int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {   cout<<"\n\n\t\t\t\tBOWLING STATS \n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"
            <<setw(6)<<"RUNS"
            <<setw(6)<<"WICKETS"
            <<setw(9)<<"BBI"
            <<setw(9)<<"BBM"
            <<setw(11)<<"AVERAGE"
            <<setw(8)<<"Economy"
            <<setw(8)<<"SR\n"
            <<setw(4)<<"5W"
            <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);
             cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8);
             cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10);
             cout<< setw(5) << sqlite3_column_int(stmt, 11);
             cout<< setw(5) << sqlite3_column_int(stmt, 112);
             cout<<"\n";
            }
        return 1;
        }

        if(result2 != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            cout<<"\n\n\t\t\t\tBATTING STATS\n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"RUNS"
            <<setw(6)<<"HS"
            <<setw(11)<<"AVERAGE"
            <<setw(6)<<"SR"
            <<setw(9)<<"100s"
            <<setw(9)<<"50s"
            <<setw(8)<<"4s"
            <<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result2 = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);
             cout<< setw(4) << sqlite3_column_int(stmt, 7);
             cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);
             cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }
        return 1;
        }
    }

};

class TestAllRounder : public AllRounder
{
    public:

       getData(string name)
        {
        query = "SELECT * FROM t20BowlerStats WHERE Name = ";
        query2 = "SELECT * FROM t20BatsmanStats WHERE Name = ";
        string apos = "'",semiColon = ";";
        Query = query + apos + name + apos + semiColon;
    string Query2 = query2 + apos + name + apos + semiColon;
        result = sqlite3_prepare_v2(db, Query.c_str(), -1, &stmt, NULL);
       int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);
//        int result2 = sqlite3_prepare_v2(db, Query2.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {   cout<<"\n\n\t\t\t\tBOWLING STATS \n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"BALLS"
            <<setw(6)<<"RUNS"
            <<setw(6)<<"WICKETS"
            <<setw(9)<<"BBI"
            <<setw(9)<<"BBM"
            <<setw(11)<<"AVERAGE"
            <<setw(8)<<"Economy"
            <<setw(8)<<"SR\n"
            <<setw(4)<<"5W"
            <<setw(4)<<"10W";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_int(stmt, 5);
             cout<< setw(10) << sqlite3_column_text(stmt, 6);
             cout<< setw(4) << sqlite3_column_text(stmt, 7);
             cout<< setw(4) << sqlite3_column_double(stmt, 8);
             cout<< setw(5) << sqlite3_column_double(stmt, 9);
             cout<< setw(5) << sqlite3_column_double(stmt, 10);
             cout<< setw(5) << sqlite3_column_int(stmt, 11);
             cout<< setw(5) << sqlite3_column_int(stmt, 112);
             cout<<"\n";
            }
        return 1;
        }
        if(result2 != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
            return 0;
        }

        else
        {
            cout<<"\n\n\t\t\t\tBATTING STATS\n\n";
            for(int i=0; i<95; i++)
                cout<<"-";
            cout<<endl<< right<< setw(6)<< "Name"
            << setw(15)<<"MATCHES "
            << setw(9)<< "INNINGS "
            <<setw(6)<<"RUNS"
            <<setw(6)<<"HS"
            <<setw(11)<<"AVERAGE"
            <<setw(6)<<"SR"
            <<setw(9)<<"100s"
            <<setw(9)<<"50s"
            <<setw(8)<<"4s"
            <<setw(8)<<"6s\n";;
            for(int i=0; i<95; i++)
                cout<<"-";

            cout<<endl;
        while((result2 = sqlite3_step(stmt)) == SQLITE_ROW )
            {
             cout<< setw(11)<< sqlite3_column_text(stmt, 0);
             cout<< setw(5) << sqlite3_column_int(stmt, 1);
             cout<< setw(9)<< sqlite3_column_int(stmt, 2);
             cout<< setw(11) << sqlite3_column_int(stmt, 3);
             cout<< setw(8) << sqlite3_column_int(stmt, 4);
             cout<< setw(8) << sqlite3_column_double(stmt, 5);
             cout<< setw(10) << sqlite3_column_double(stmt, 6);
             cout<< setw(4) << sqlite3_column_int(stmt, 7);
             cout<< setw(4) << sqlite3_column_int(stmt, 8);
             cout<< setw(5) << sqlite3_column_int(stmt, 9);
             cout<< setw(5) << sqlite3_column_int(stmt, 10);
             cout<<"\n";
            }
        return 1;
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
//    int c_ranking_stats,c_team_player_rank,c_operation;
    int user;
    string username,password,table;

    connection();
//    this_thread::sleep_for(std::chrono::milliseconds(2000));
    system("cls");

//    TestBatsman testBatsman;
//    TestBowler testBowler;
//    TestAllRounder testAllRounder;
    PlayerRankings player;
    TeamRankings team;

//    radio *rad = new radio();

//    Statistics *testBatStats;
    Batsman *bat1,*bat2,*bat3,*bat4;
    TestBatsman testBat;
    OdiBatsman odiBat;
    T20Batsman  t20Bat;
    AllFormatBatsman allBat;
    bat1 = &testBat; bat2 = &odiBat;bat3 = &t20Bat;bat4 = &allBat;

    Bowler *bowl1,*bowl2,*bowl3,*bowl4;
    TestBowler testBowl;
    OdiBowler odiBowl;
    T20Bowler t20Bowl;
    AllFormatBowler allBowl;
    bowl1= &testBowl;bowl2= &odiBowl;bowl3 = &t20Bowl;bowl4 = &allBowl;

    AllRounder *all1,*all2,*all3,*all4;
    TestAllRounder testAll;
    OdiAllRounder odiAll;
    T20AllRounder t20All;

    all1 = &testAll;all2 = &odiAll;all3 = &t20All;

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
        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t\t\tAre you a user or Admin? \n\n";
        cout<<"\t\t\t\t\t\t\t\t1. Admin\n\t\t\t\t\t\t\t\t2. User \n ";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"Enter Your Choice: "; cin>>choice;
        cout<<endl<<endl;

        while(!cin)
        {
            cout<<"\n--Invalid input! Only enter the given numeric options-- \n--Try Again--\n ";
            cin.clear();
            fflush(stdin);
            cin>>choice;
        }
        switch(choice)
        {
           do
           {
                case 1:
                    system("pause");cout<<endl;
                    system("cls");
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
                                cout<<"\n--Invalid Username or Password-- \n--Try again--\n";
                                Sleep(2000);
                                system("cls");
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
                            cout<<"\nLogging in ... ";
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
            point1:
            system("cls");
        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"\t\t\t\t\t\t\tWhat do you want to access\n\n";
        cout<<"\t\t\t\t\t\t\t\t1. Rankings\n\t\t\t\t\t\t\t\t2. Statistics \n ";
        cout<<"--------------------------------------------------------------------------------------------------------------------------------------"<<endl;
        cout<<"\nEnter Your Choice: ";cin>>choice;    // choice between ranking and statistics
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
                        point2:
                        system("cls");
                        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                        cout<<"\t\t\t\t\t\t\t   What do you want to access\n\n";
                        cout<<"\t\t\t\t\t\t\t\t1. Team Rankings\n\t\t\t\t\t\t\t\t2. Player Rankings \n ";
                        cout<<"--------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                        cout<<"Enter Your Choice: ";cin>>choice;
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
                                        cout<<endl;
                                        system("pause");
                                        system("cls");
                                        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                        cout<<"\t\t\t\t\t\tT  E  A  M \tR  A  N  K  I  N  G  S";
                                        cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;

                                        cout<<"\t\t\t\t\t\t\t\t1. View Records\n\t\t\t\t\t\t\t\t2. Update Records \n\t\t\t\t\t\t\t\t3. Insert Records \n\t\t\t\t\t\t\t\t4. Delete Records \n ";
                                        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                        cout<<"\nEnter your choice: ";cin>>operationChoice;
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
                                            cout<<endl;
                                            system("pause");
                                            system("cls");
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                            cout<<"\t\t\t\t\t\tV  I  E  W  I  N  G \tR  E  C  O  R  D  S";
                                            cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
                                            cout<<"\t\t\t\t\t\t\t\t1. Test\n\t\t\t\t\t\t\t\t2. ODI \n\t\t\t\t\t\t\t\t3. T20 \n\t\t\t\t\t\t\t\t4. Delete Records \n ";
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;

                                           cout<<"Enter Your Choice: ";cin>>choice;
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
                                            cout<<endl;
                                            system("pause");
                                            system("cls");
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                            cout<<"\t\t\t\t\t\tU  P  D  A  T  I  N  G \tR  E  C  O  R  D  S";
                                            cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
                                            cout<<"\t\t\t\t\t\t\t\t1. Test\n\t\t\t\t\t\t\t\t2. ODI \n\t\t\t\t\t\t\t\t3. T20 \n\t\t\t\t\t\t\t\t4. Delete Records \n ";
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                            cout<<"\nEnter Your Choice: ";cin>>choice;
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
                                        cout<<endl;
                                            system("pause");
                                            system("cls");
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                            cout<<"\t\t\t\t\t\tI  N  S  E  R  T  I  N  G \tR  E  C  O  R  D  S";
                                            cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
                                            cout<<"\t\t\t\t\t\t\t\t1. Test\n\t\t\t\t\t\t\t\t2. ODI \n\t\t\t\t\t\t\t\t3. T20 \n\t\t\t\t\t\t\t\t4. Delete Records \n ";
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;

                                           cout<<"\NEnter Your Choice: ";cin>>choice;
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
                                            cout<<endl;
                                            system("pause");
                                            system("cls");
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                            cout<<"\t\t\t\t\t\tD  E  L  E  T  I  N  G\tR  E  C  O  R  D  S";
                                            cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
                                            cout<<"\t\t\t\t\t\t\t\t1. Test\n\t\t\t\t\t\t\t\t2. ODI \n\t\t\t\t\t\t\t\t3. T20 \n\t\t\t\t\t\t\t\t4. Delete Records \n ";
                                            cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                            cout<<"Enter Your Choice: ";cin>>choice;

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


                                    case 2:
                                        point3:  // for player rankings
                                        cout<<endl;
                                       // system("pause");
                                        system("cls");
                                        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                        cout<<"\t\t\t\t\t\tP  L  A  Y  E  R \tR  A  N  K  I  N  G  S";
                                        cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;

                                        cout<<"\t\t\t\t\t\t\t\t1. View Records\n\t\t\t\t\t\t\t\t2. Update Records \n\t\t\t\t\t\t\t\t3. Insert Records \n\t\t\t\t\t\t\t\t4. Delete Records \n ";
                                        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                        cout<<"\nEnter your choice: ";cin>>operationChoice;

                                            switch(operationChoice)
                                            {
                                                case 1:		// for viewing records
                                                    while(true)
                                                    {
                                                    cout<<endl;
                                                       cout<<"\nEnter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);
                                                       cout<<endl;
                                                       if(!isValidTableName(table))
                                                        {
                                                             break;  //continue;
                                                        }
                                                       else
                                                        {
                                                          player.readData(table);
                                                          cout<<"\n\nIf you want to view any more records or wanna go back ? (y/n): ";
                                                          cin>>ch;
                                                          cout<<endl;
                                                           system("cls");
                                                          if(ch=='n'||ch=='N')
                                                          {
                                                              break;
                                                          }
                                                          else
                                                          {

                                                              system("cls");
                                                              goto point3;
                                                          }
                                                          cout<<"\n\n";
                                                        }
                                                     }
                                                    if(ch=='n'||ch=='N')
                                                          {
                                                              system("cls");
                                                              break;    // breaking case 1
                                                          }

                                                case 2:		// for updating records

                                                    while(true)
                                                    {
                                                        cout<<endl;
                                                        cout<<"\nEnter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);
                                                       cout<<endl;
                                                       fflush(stdin);

//
                                                          player.updateData(table);
                                                          cout<<"\n\nIf you want to view any more records or wanna go back ? (y/n): ";
                                                          cin>>ch;
                                                          cout<<endl;
                                                          system("cls");
                                                          if(ch=='n'||ch=='N')
                                                          {
                                                              break;
                                                          }
                                                          else
                                                          {
                                                              system("pause");
                                                              system("cls");
                                                              goto point3;
                                                          }
                                                          cout<<"\n\n";

                                                    }
                                                    if(ch=='n'||ch=='N')
                                                          {
                                                              system("cls");
                                                              break;    // breaking case 2
                                                          }


                                                case 3:

                                                    while(true)
                                                    {
                                                        cout<<"\nEnter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);
                                                       fflush(stdin);

                                                          player.insertData(table);

                                                       cout<<"\n\nIf you want to view any more records or wanna go back ? (y/n): ";
                                                       cin>>ch;
                                                          if(ch=='n'||ch=='N')
                                                          {
                                                              break;
                                                          }
                                                          else
                                                          {
                                                                system("pause");
                                                              system("cls");
                                                              goto point3;
                                                          }
                                                          cout<<"\n\n";

                                                     }  //edning while loop
                                                        if(ch=='n'||ch=='N')
                                                          {
                                                              system("cls");
                                                              break;    // breaking case 3
                                                          }


                                                 case 4:

                                                    while(true)
                                                    {
                                                        cout<<"\nEnter Table Name: ";
                                                       fflush(stdin);
                                                       getline(cin,table);


                                                          player.deleteData(table);
                                                        cout<<"\n\nIf you want to view any more records or wanna go back ? (y/n): ";
                                                        cin>>ch;
                                                          if(ch=='n'||ch=='N')
                                                          {
                                                              break;
                                                          }
                                                          else
                                                          {
                                                                system("pause");
                                                                system("cls");
                                                                goto point3;
                                                          }
                                                          cout<<"\n\n";

                                                     }
                                                    if(ch=='n'||ch=='N')
                                                          {
                                                              system("cls");
                                                              break;    // breaking case 4
                                                          }

                                            }
                                                 default:
                                                    cout<<"\nInvalid Input \n";
                                                    system("pause");
                                                    system("cls");
                                                    goto point2;

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

                                    case 2:     // for Statistics

                            cout<<endl;
                                        system("pause");
                                        system("cls");
                                        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                        cout<<"\t\t\t\t\t\t\tS  T  A  T  I  S  T  I  C  S";
                                        cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;

                                        cout<<"\t\t\t\t\t\t\t\t1. View Records\n\t\t\t\t\t\t\t\t2. Update Records \n\t\t\t\t\t\t\t\t3. Insert Records \n\t\t\t\t\t\t\t\t4. Delete Records \n ";
                                        cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                        cout<<"Enter Your Choice: ";cin>>choice;
                                       fflush(stdin);
                                       while(!cin)
                                        {
                                            cout<<"\nWrong input! Try Again\n ";
                                            cin>>choice;
                                            fflush(stdin);
                                        }

                                            switch(choice)
                                            {

                                                case 1:     // for Viewing Statistics Records
                                                {
                                                    point4:
                                                    system("cls");
                                                    cout<<"---------------------------------------------------------------------------------------------------------------------------------------"<<endl;
                                                    cout<<"\t\t\t\t\tP  A  K \t P  L  A  Y  E  R \t S  T  A  T S";
                                                    cout<<"\n---------------------------------------------------------------------------------------------------------------------------------------"<<endl<<endl;
                                                    cout<<endl<<"1. Shan Masood\n2. Fakhar Zaman\n3. Muhammad Rizwan\n4. Babar Azam"
                                                      <<"\n5. Naseem Shah\n6. Haris Rauf\n7. Muhammad Wasim Jr.\n8. Shaheen Afridi"
                                                      <<"\n9. Muhammad Nawaz\n10. Imad Wasim\n11. Muhammad Nawaz\n12. Faheem Ashraf\n\n";

                                                   cout<<"Enter Your Choice: ";cin>>choice;
                                                   fflush(stdin);
                                                   while(!cin || choice<1 || choice>12)
                                                   {
                                                       cout<<endl<<endl;
                                                       cout<<"Wrong Input! Try Again\n";
                                                       cout<<"\nEnter Your Choice: ";
                                                       cin>>choice;
                                                       fflush(stdin);
                                                   }

                                                    if(choice==1)   // testBatsman
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------S H A N    M A S O O D------------------------------------------------------------"<<endl<<endl<<endl;
                                                        bat1->getData("Shan Masood");cout<<endl<<endl;
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 2)    // odi batsman
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------F A K H A R    Z A M A N---------------------------------------------------------"<<endl<<endl<<endl;
                                                        bat2->getData("Fakhar Zaman");cout<<endl<<endl;
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 3)    // t20 batsman
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------M U H A M M A D    R I Z W A N --------------------------------------------------"<<endl<<endl<<endl;
                                                        bat3->getData("Muhammad Rizwan");cout<<endl<<endl;
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if( choice == 4) // all foramt batsman
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------B A B A R    A Z A M ----------------------=-------------------------------------"<<endl<<endl<<endl;
                                                        bat4->getData("Babar Azam");cout<<endl<<endl;
                                                        system("pause");
                                                        goto point4;

                                                    }
                                                    else if(choice == 5)    // test bowler
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------N A S E E M    S H A H-----------------------------------------------------------"<<endl<<endl<<endl;
                                                        bowl1->getData("Naseem Shah");-
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 6)    // odi bowler
                                                    {
                                                        system("cls");
                                                         cout<<"----------------------------------------------------H A R I S    R A U F------------------------------------------------------------"<<endl<<endl<<endl;
                                                        bowl2->getData("Haris Rauf");
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 7)    // t20 bowler
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------M U H A M M A D   W A S I M -----------------------------------------------------"<<endl<<endl<<endl;
                                                        bowl3->getData("Muhammad Wasim");
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 8)    // all format bowler
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------S H A H E E N    A F R I D I-----------------------------------------------------"<<endl<<endl<<endl;
                                                        bowl4->getData("Shaheen Afridi");
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 9)    // test allrounder
                                                    {
                                                        system("cls");
                                                         cout<<"---------------------------------------------------M U H A M M A D   N A W A Z------------------------------------------------------"<<endl<<endl<<endl;
                                                        all1->getData("Muhammad Nawaz");
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 10)   // odi allrounder
                                                    {
                                                        system("cls");
                                                         cout<<"-----------------------------------------------------I M A D   W A S I M -----------------------------------------------------------"<<endl<<endl<<endl;
                                                        all2->getData("Imad Wasim");
                                                        system("pause");
                                                        goto point4;

                                                    }
                                                    else if(choice == 11)   //t20 allrounder
                                                    {
                                                        system("cls");
                                                         cout<<"--------------------------------------------------M U H A M M A D    N A W A Z------------------------------------------------------"<<endl<<endl<<endl;
                                                        all1->getData("Muhammad Nawaz");
                                                        system("pause");
                                                        goto point4;
                                                    }
                                                    else if(choice == 12)   //all format allrounder
                                                    {
                                                         cout<<"\n\nInvalid Input\n";
                                                        system("cls");
                                                        goto point1;
                                                    }

                                                }

                                            }

                                }   // while loop for rankings ending here
                                        break;  // breaking while loop of rankings choice

//                                    if(ch=='y'||ch=='Y')
//                                    {
//                                        break;  // breaking the switch (choice) for team rankings or player rankings
//                                    }


                                  default:
                                        cout<<"\nWrong Input\n";
                                        system("pause");
                                        system("cls");
                                        goto point1;
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

                  }while(choice==1 || choice== 2);

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
