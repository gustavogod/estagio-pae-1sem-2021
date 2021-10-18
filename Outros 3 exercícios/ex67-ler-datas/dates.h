#ifndef __DATES_H__
#define __DATES_H__

typedef enum {
    JAN = 1,
    FEV,
    MAR,
    ABR,
    MAI,
    JUN,
    JUL,
    AGO,
    SET,
    OUT,
    NOV,
    DEZ
} month;

typedef struct {
    int day;
    month month;
    int year;
    int isValid;
} dates;

void checkDateMalloc(dates *);

dates *readDates(int const );

/**
 * Check date validity
 * if id valid, return 1
 * else, return 0
 */
int dateIsValid(dates const );

void printDates(dates const *, int const );

#endif