/* Name: Prerana.M.S
Section: ‘L’
SRN: PES2UG19CS296

CODE FOR AIRPORT SIMULATION WITH ONE RUNWAY.
Assumptions:
•	Has two queues, one for landing planes and another for taking off planes
•	A queue can hold a maximum of 5 planes, above which the services will be rejected
•	The unit time taken is a minute
•	A maximum of 2 planes can request for each service per minute, with minimum being 0 */

#include <stdio.h>
#include "airport_simulate.h"
#define MAX 5 //max. planes in a queue
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
} ;

struct airport {
    struct queue landing ;
    struct queue takeoff ;
    struct queue *pl ;
    struct queue *pt ;
    int idletime ;
    int landwait, takeoffwait ;
    int nland, nplanes, nrefuse, ntakeoff ;
    struct plane pln ;
};*/

void main(){
    struct airport a;
    int i, pri, curtime,landp,departp;
    double expectarrive, expectdepart, endtime;
    struct plane temp ;
    initairport (&a);
    start ( &endtime, &expectarrive, &expectdepart ) ;
    for ( curtime = 1 ; curtime <= endtime ; curtime++ )
    {
        pri = randomnumber() ; //No. of planes ready to land
        for ( i = 1 ; i <= pri ; i++ )
        {
            newplane ( &a, curtime, ARRIVE ) ; //adding the plane to queue
            if ( apfull ( a, 'l' )  )  //if queue is full, the planes is rejected
                 refuse ( &a, ARRIVE ) ;
            else
                apaddqueue( &a, 'l' ) ;
        }

        pri = randomnumber() ; //No. of planes ready to land
        for ( i = 1 ; i <= pri ; i++ )
        {
            newplane ( &a, curtime, DEPART ) ; //adding the plane to queue
            if ( apfull ( a, 't' ) ) //if queue is full, the planes is rejected
               refuse ( &a, DEPART ) ;
            else
               apaddqueue ( &a, 't' ) ;
        }
        if (  ! ( apempty ( a, 'l' ) ) ) // giving way to land one by one
        {
            temp = apdelqueue ( &a, 'l' ) ;
            land ( &a, temp, curtime ) ;
        }
        else
        {
            if ( ! ( apempty ( a, 't' ) ) ) // taking off if land queue is empty
            {
                temp = apdelqueue ( &a, 't' ) ;
                fly ( &a, temp, curtime ) ;
            }
            else
                idle ( &a, curtime ) ; //if not both, runway is idle
        }
    }

    conclude ( &a, endtime ) ;
}
