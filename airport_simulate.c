#include <stdio.h>
#include <string.h>
#include "airport_simulate.h"
#define MAX 5
#define ARRIVE 0
#define DEPART 1

/*struct plane{
    int id ;
    int tm ;
} ;

struct queue{
    int count ;
    int front ;
    int rear ;
    struct plane p[MAX] ;
} ;*/

void initqueue ( struct queue *pq ){
    pq -> count = 0 ; //elements in queue
    pq -> front = 0 ;
    pq -> rear = -1 ;
}

void addqueue ( struct queue *pq, struct plane item ){
    if ( pq -> count >= MAX )
    {
        printf ( "\nQueue is full.\n" ) ;
        return ;
    }
    ( pq -> count )++ ;

    pq -> rear = ( pq -> rear + 1 ) % MAX ;
    pq -> p[pq -> rear] = item ;
}
struct plane delqueue ( struct queue *pq ){
    struct plane p1 ;
    if ( pq -> count <= 0 )
    {
        printf ( "\nQueue is empty.\n" ) ;
        p1.id = 0 ;
        p1.tm = 0 ;
    }
    else
    {
        ( pq -> count )-- ;
        p1 = pq -> p[pq -> front] ;
        pq -> front = ( pq -> front + 1 ) % MAX ;
    }
    return p1 ;
}
int size ( struct queue q ){
    return q.count ;
}
int empty ( struct queue q ){
    return ( q.count <= 0 ) ;
}
int full ( struct queue q ){
    return ( q.count >= MAX ) ;
}
/*struct airport {
    struct queue landing ;
    struct queue takeoff ;
    struct queue *pl ;
    struct queue *pt ;
    int idletime ;
    int landwait, takeoffwait ;
    int nland, nplanes, nrefuse, ntakeoff ;
    struct plane pln ;
};
*/
double check(char c[20]){
    int i=0,deci=0,m=0;
    double x=0.0;
    for(i=0;i<strlen(c);i++)
    {
        if(((int)c[i]<=47 || (int)c[i]>=58) && (int)c[i]!=46 || m>1)
        {
          printf("Please enter a valid input:\t");
          scanf(" %s", c);
          m=0;
          deci=0;
          i=-1;
        }
        else if((int)c[i]==46)
        {
            m+=1;
            continue;
        }
        else x=x*10+(c[i]-48);

        if(m==1) deci+=1;
    }
    for(i=1;i<=deci;i++)
        x=x/10;
    return x;
}
void initairport ( struct airport *ap ){
    initqueue ( &( ap-> landing ) ) ;
    initqueue ( &( ap -> takeoff ) ) ;

    ap -> pl = &( ap -> landing ) ;
    ap -> pt = &( ap -> takeoff ) ;
    ap -> nplanes = ap -> nland = ap -> ntakeoff = ap -> nrefuse = 0 ;
    ap -> landwait = ap -> takeoffwait = ap -> idletime = 0 ;
}
void start ( double *endtime, double *expectarrive, double *expectdepart ){
    int flag = 0;
    char x[20];
    char wish ;
    printf ( "\t\tProgram that simulates an airport with only one runway.\n" ) ;
    printf ( "\t\tOnly one plane can land or depart in each unit of time.\n" ) ;
    printf ( "Up to %d planes can be waiting to land or take off at any time.\n", MAX ) ;
    printf ( "How many minute(s) will the simulation run?(integer)     " ) ;
    scanf ( " %s", &x ) ;
    *endtime=check(x);
    endtime=(int)endtime;
    do
    {
        printf ( "Expected number of arrivals per minute:   " ) ;
        scanf ( " %s", &x ) ;
        *expectarrive=check(x);
        printf ( "Expected number of departures per minute:   " ) ;
        scanf ( " %s", &x ) ;
        *expectdepart=check(x);
        if ( *expectarrive < 0.0 || *expectdepart < 0.0 )
        {
            printf ( "These numbers must be nonnegative.\n" ) ;
            flag = 0 ;
        }
        else
        {
            if ((*expectarrive + *expectdepart) > 1.0 )
            {
                printf ( "The airport will become non-functioning.Enter 'y' to enter new values " ) ;
                scanf ( " %c", &wish ) ;
                if ( tolower ( wish ) == 'y' )
                    flag = 0 ;
                else
                    flag = 1 ;
            }
            else
                flag = 1 ;
        }
    } while ( flag == 0 ) ;
}
void newplane ( struct airport *ap, int curtime, int action ){
    ( ap -> nplanes )++ ;
    ap -> pln.id = ap -> nplanes ;
    ap -> pln.tm = curtime ;

    switch ( action )
    {
        case ARRIVE :
            printf ( "    Plane %d ready to land.\n", ap -> nplanes ) ;
            break ;

        case DEPART :
            printf ( "    Plane %d ready to take off.\n", ap -> nplanes ) ;
            break ;
    }
}
void refuse ( struct airport *ap, int action ){
    switch ( action )
    {
        case ARRIVE :

             printf ( "\tplane  %d directed to another airport.\n", ap -> pln.id ) ;
             break ;

        case DEPART :

             printf ( "\tplane %d told to try later.\n", ap -> pln.id ) ;
             break ;
    }
    ( ap -> nrefuse )++ ;
}
void land ( struct airport *ap, struct plane pl, int curtime ){
    int wait ;

    wait = curtime - pl.tm ;
    printf ( "%d: Plane %d landed ", curtime, pl.id ) ;
    printf ( "   in queue %d mins \n", wait ) ;
    ( ap -> nland ) ++ ;
    ( ap -> landwait ) += wait ;
}
void fly ( struct airport *ap, struct plane pl, int curtime ){
    int wait ;

    wait = curtime - pl.tm ;
    printf ( "%d: Plane %d took off ", curtime, pl.id ) ;
    printf ( "   in queue %d mins \n", wait ) ;
    ( ap -> ntakeoff )++ ;
    ( ap -> takeoffwait ) += wait ;
}
void idle ( struct airport *ap, int curtime ){
    printf ( "%d: Runway is idle.\n", curtime ) ;
    ap -> idletime++ ;
}
int apsize ( struct airport ap, char type ){
    switch ( tolower ( type ) )
    {
        case'l' :
              return ( size ( *( ap.pl ) ) ) ;

        case't' :
              return ( size ( *( ap.pt ) ) ) ;
    }

    return 0 ;
}

void conclude ( struct airport *ap, int endtime ){
    printf ( "\tSimulation has concluded after %d units.\n", endtime ) ;
    printf ( "\tTotal number of planes processed: %d\n", ap -> nplanes ) ;
    printf ( "\tNumber of planes landed: %d\n", ap -> nland ) ;
    printf ( "\tNumber of planes taken off: %d\n", ap -> ntakeoff ) ;
    printf ( "\tNumber of planes refused use: %d\n", ap -> nrefuse ) ;
    printf ( "\tNumber left ready to land: %d\n", apsize ( *ap, 'l' ) ) ;
    printf ( "\tNumber left ready to take off: %d\n", apsize ( *ap, 't' ) ) ;

    if ( endtime > 0 )
        printf ( "\tPercentage of time runway idle: %lf \n", ( ( double ) ap -> idletime / endtime ) * 100.0 ) ;

    if ( ap -> nland > 0 )
        printf ( "\tAverage wait time to land: %lf \n", ( ( double ) ap -> landwait / ap -> nland ) ) ;

    if ( ap -> ntakeoff > 0 )
        printf ( "\tAverage wait time to take off: %lf \n", ( ( double ) ap -> takeoffwait / ap -> ntakeoff ) ) ;
}
int randomnumber(){
    int x ;
    x=rand() % 2;
        return x;
}
void apaddqueue ( struct airport *ap, char type ){
    switch ( tolower( type ) )
    {
        case'l' :
              addqueue ( ap -> pl, ap -> pln ) ;
              break ;

        case't' :
              addqueue ( ap -> pt, ap -> pln ) ;
              break ;
    }
}
struct plane apdelqueue ( struct airport *ap, char type ){
    struct plane p1 ;

    switch ( tolower ( type ) )
    {
        case'l' :
              p1 = delqueue ( ap -> pl ) ;
              break ;

        case't' :
              p1 = delqueue ( ap -> pt ) ;
              break ;
    }

    return p1 ;
}

int apfull ( struct airport ap, char type ){
    switch ( tolower ( type ) )
    {
        case'l' :
              return ( full ( *( ap.pl ) ) ) ;

        case't' :

              return ( full ( *( ap.pt ) ) ) ;
    }

    return 0 ;
}
int apempty ( struct airport ap, char type ){
    switch ( tolower ( type ) )
    {
        case'l' :
              return ( empty ( *( ap.pl ) ) ) ;

        case't' :
              return ( empty ( *( ap.pt ) ) ) ;
    }

    return 0 ;
}

