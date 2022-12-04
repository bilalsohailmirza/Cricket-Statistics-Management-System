#include <iostream>
#include<stdio.h>
#include<iomanip>
#include "sqlite3.h"

using namespace std;

//void connection();
//void readData();
sqlite3 *db;
sqlite3_stmt *stmt;
int result, result2, result3, result4;
string query, query2, query3, query4;
void connection()
{
    if(sqlite3_open("demo.db", &db) == SQLITE_OK)
    {
        cout<<"Database connected Successfully. \n";
    }
    else
    {
      cout<<"Database did not connected successfully. \n";
    }
}
class TestBatsmen
{
    public:

    TestBatsmen_readData()
    {
        query = "SELECT Rank, Name, Country, Rating FROM testBatsmen";

        result = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, NULL);

        if(result != SQLITE_OK)
        {
            cout<<"ERROR: "<< sqlite3_errmsg(db) <<"\n";
        }
        else
        {
            cout<< right<< setw(5)<< "RANK"
            << setw(20)<< "NAME"
            << setw(20)<<"COUNTRY "
            <<setw(20)<<"RATING\n";
        while( (result = sqlite3_step(stmt)) == SQLITE_ROW )
        {
         cout << setw(5)<< sqlite3_column_int(stmt, 0);
         cout<< setw(25) << sqlite3_column_text(stmt, 1);
         cout << setw(13)<< sqlite3_column_text(stmt, 2);
         cout<< setw(20) << sqlite3_column_int(stmt, 3);
         cout<<"\n";
        }
    }
    }
};

int main()
{
    TestBatsmen testBatsmen;
    connection();
    cout<<"\n\n";
    testBatsmen.TestBatsmen_readData();

    sqlite3_close(db);
    return 0;
}
