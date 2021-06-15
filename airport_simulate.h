#include <stdio.h>
#include <string.h>
#define MAX 5

struct plane{
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
};


void initqueue ( struct queue * ) ;
void addqueue ( struct queue *, struct plane ) ;
struct plane delqueue ( struct queue * ) ;
int size ( struct queue ) ;
int empty ( struct queue );
int full ( struct queue);
double check(char* );
void initairport ( struct airport *ap ) ;
void start ( double *, double *, double * ) ;
void newplane ( struct airport *, int, int ) ;
void refuse ( struct airport *, int ) ;
void land ( struct airport *, struct plane, int ) ;
void fly ( struct airport *, struct plane, int ) ;
void idle ( struct airport *, int ) ;
void conclude ( struct airport *, int ) ;
int randomnumber() ;
void apaddqueue ( struct airport *, char ) ;
struct plane apdelqueue ( struct airport *, char ) ;
int apsize ( struct airport, char ) ;
int apfull ( struct airport, char ) ;
int apempty ( struct airport, char ) ;
