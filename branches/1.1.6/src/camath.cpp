#include <stdio.h>
#include <time.h>

#include "camath.h"

/** Compares two float values.
    \return true if the two values differ less than the tolerance value.
*/
bool
CAMath::compFloat( float f1, float f2, float tol ) {
    float delta = f2-f1;
    return( delta>-tol && delta<tol );
}


/** Corrects an angle (to the range of 0-360)
    \return The corrected angle
*/
float
CAMath::corrAngle( float ang ) {
    float ret=ang;
    while(ret<   0.0) ret+=360.0;
    while(ret>=360.0) ret-=360.0;
    return ret;
}



/** Returns the angle (in degrees) from one point to an other.
*/
float
CAMath::getAngle( float x1, float y1, float x2, float y2 ) {
    float xdist, ydist, angle;

    xdist=x2-x1;
    ydist=y2-y1;

    if(compFloat(xdist, 0.0)) {
        if(y2<y1) angle=270.0;
        else angle=90.0;
    } else if(compFloat(ydist, 0.0)) {
        if(x2<x1) angle=180.0;
        else angle=0.0;
    } else {
        angle = atan(ydist/xdist)*ARAD;
        if(angle<0.0) angle*=-1.0;
        if(x2>x1 && y2>y1) angle =   0.0 + angle;   // 1. Quadrant
        if(x2<x1 && y2>y1) angle = 180.0 - angle;   // 2. Quadrant
        if(x2<x1 && y2<y1) angle = 180.0 + angle;   // 3. Quadrant
        if(x2>x1 && y2<y1) angle = 360.0 - angle;   // 4. Quadrant
    }

    return angle;
}



/** Returns the distance from one point to an other.
*/
float
CAMath::getDistance( float x1, float y1, float x2, float y2 ) {
    float xd2 = (x2-x1)*(x2-x1);
    float yd2 = (y2-y1)*(y2-y1);
    float d   = xd2+yd2;
    if(d<0.0) d*=-1.0;
    return(std::sqrt(d));
}



/** Get Angle difference between _a1 and _a2
   (Which angle must I add to _a1 to get _a2)
   All angles in degrees.
*/
float
CAMath::getAngleDiff( float a1, float a2 ) {
    float ret;

    if( a1>=a2 ) a2+=360.0;
    ret = a2-a1;
    if( ret>=360.0 ) ret=0.0;

    return ret;
}



/** Calculates the intersection point of two lines.
*/
bool
CAMath::getIntersection( int ax1, int ay1, int ax2, int ay2,
                         int bx1, int by1, int bx2, int by2,
                         int* ix, int* iy ) {
    if( ix && iy ) {

        int amaxx = MAX(ax1, ax2);
        int aminx = MIN(ax1, ax2);
        int amaxy = MAX(ay1, ay2);
        int aminy = MIN(ay1, ay2);

        int bmaxx = MAX(bx1, bx2);
        int bminx = MIN(bx1, bx2);
        int bmaxy = MAX(by1, by2);
        int bminy = MIN(by1, by2);

        if( amaxx<bminx || aminx>bmaxx ||
                amaxy<bminy || aminy>bmaxy    )  return false;

        int t2_divisor,
        t2_dividend;
        float t2;

        t2_dividend = (bx2-bx1)*(ay2-ay1) - (by2-by1)*(ax2-ax1);

        if( t2_dividend!=0 ) {
            t2_divisor = ax1*ay2
                         - ay1*ax2
                         - bx1*(ay2-ay1)
                         + by1*(ax2-ax1);
            t2 = (float)(t2_divisor) / t2_dividend;
        } else {
            t2 = 0.0;
        }

        *ix = (int)( bx1 + t2 * (bx2 - bx1) );
        *iy = (int)( by1 + t2 * (by2 - by1) );

        if( ((*ix<=ax1 && *ix>=ax2) || (*ix<=ax2 && *ix>=ax1)) &&
                ((*ix<=bx1 && *ix>=bx2) || (*ix<=bx2 && *ix>=bx1)) &&
                ((*iy<=ay1 && *iy>=ay2) || (*iy<=ay2 && *iy>=ay1)) &&
                ((*iy<=by1 && *iy>=by2) || (*iy<=by2 && *iy>=by1))    ) {
            return true;
        } else {
            return false;
        }
    }

    return true;
}


/** Gets a random number from 'min' to 'max'
*/
int
CAMath::getRandomNumber( int min, int max ) {
    static int counter=0;
    if( counter==1000 || counter==0 ) {
        srand( time( NULL ) );
        counter = 0;
    }
    ++counter;
    return ( (int)/*rint */( (float)(max-min + 1) / RAND_MAX * rand() ) + min );
}


/** Converts a time in millisecs to a string in the format <minutes>:<seconds>.<hundredth>. (e.g. "5:02.23")
    'string' must have at least place for 9 characters.
*/
void
CAMath::timeToString( char* string, int time ) {
    float min = (int)floor( (float)((time)/60000.0) );
    float sec = (float)((time)%60000)/1000.0;
    float hun = ((sec-floor(sec))*100);

    sprintf( string,
             "%02d:%02d.%02d",
             (int)min,
             (int)floor( sec ),
             (int)floor( hun ) );
}


// EOF
