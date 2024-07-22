#include<iostream>
#include<string.h>
using namespace std;

class flight
{ 	 
    public:
        int am[10][10]; // Adjacency matrix for flight distances
        char city_index[10][10]; // Array to store city names or airport codes
        flight(); // Constructor
        int create();
        void display(int city_count); // Method to display adjacency matrix
};

// Constructor to initialize member variables
flight::flight()
{
    int i,j;
    // City_index array for placeholder values
    for(i=0;i<10;i++)
    {
        strcpy(city_index[i],"xx");
    }
    // Initialize adjacency matrix with 0 (indicating no direct flight)
    for(i=0;i<10;i++)
    {
        for(j=0;j<10;j++)
        {
            am[i][j]=0;
        }
    }
}

// Flight network
int flight::create()
{
    int city_count=0,j,si,di,wt;
    char s[10],d[10],c;
    do
    {
        cout<<"\n\tEnter Source City      : ";
        cin>>s;
        cout<<"\n\tEnter Destination City : ";
        cin>>d;
        // Check if source city is already in city_index array
        for(j=0;j<10;j++)
        {
            if(strcmp(city_index[j],s)==0)
                break;
        }
        if(j==10)
        {
            // If source city not found, add it to city_index array
            strcpy(city_index[city_count],s);
            city_count++;
        }

        // Check if destination city is already in city_index array
        for(j=0;j<10;j++)
        {
            if(strcmp(city_index[j],d)==0)
                break;
        }

        if(j==10)
        {
            // If destination city not found, add it to city_index array
            strcpy(city_index[city_count],d);
            city_count++;
        }

        // Input distance between source and destination cities
        cout<<"\n\t Enter Distance From "<<s<<" And "<<d<<": ";
        cin>>wt;

        // Find index of source and destination cities in city_index array
        for(j=0;j<10;j++)
        {
            if(strcmp(city_index[j],s)==0)
                si=j;
            if(strcmp(city_index[j],d)==0)
                di=j;
        }

        // Store distance in the adjacency matrix
        am[si][di]=wt;
        
        // Ask user if they want to add more cities
        cout<<"\n\t Do you want to add more cities.....(y/n) : ";
        cin>>c;    
    }while(c=='y'||c=='Y');
    return(city_count);
}

// Method to display the adjacency matrix
void flight::display(int city_count)
{
    int i,j;
    cout<<"\n\t Displaying Adjacency Matrix :\n\t";
    // Display column headers (city names)
    for(i=0;i<city_count;i++)
        cout<<"\t"<<city_index[i];
    cout<<"\n";

    // Display adjacency matrix
    for(i=0;i<city_count;i++)
    {
        cout<<"\t"<<city_index[i];
        for(j=0;j<city_count;j++)
        {
            // Display distance (or 0 if no direct flight)
            cout<<"\t"<<am[i][j];    
        }
        cout<<"\n";
    }
}

// Main function
int main()
{
    flight f;
    int n,city_count;
    char c;
    do
    {
        cout<<"\n\t*** Flight Main Menu *****";
        cout<<"\n\t1. Create \n\t2. Adjacency Matrix\n\t3. Exit";
        cout<<"\n\t.....Enter your choice : ";
        cin>>n;
        switch(n)
        {
            case 1:
                    // Create the flight network
                    city_count=f.create();
                    break;
            case 2:
                    // Display the adjacency matrix
                    f.display(city_count);
                    break;
            case 3:
                    // Exit the program
                    return 0;
        }
        // Ask user if they want to continue
        cout<<"\n\t Do you Want to Continue in Main Menu....(y/n) : ";
        cin>>c;
    }while(c=='y'||c=='Y');
    return 0;
}

