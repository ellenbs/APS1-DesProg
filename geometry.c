#include <math.h>
#include "geometry.h"

int verify_double(double number1, double number2)
{
    double module = (double)fabs(number1 - number2);
    if (module < 0.00000001)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void categorize_points(point *p_low, point *p_high, point a, point b)
{
    if (a.y >= b.y)
    {
        p_high->y = a.y;
        p_high->x = a.x;
        p_low->y = b.y;
        p_low->x = b.x;
    }
    else
    {
        p_high->y = b.y;
        p_high->x = b.x;
        p_low->y = a.y;
        p_low->x = a.x;
    }
}

void line_equation(double *angular_coeficient, double *linear_coeficient, double *constant_x, point p_low, point p_high)
{
    /*
    Checks if a division by 0 shall occour
    This implies that the segment is parallel to the x axis.
    */
    if (p_high.x - p_low.x != 0)
    {
        *angular_coeficient = (double)(p_high.y - p_low.y) / (p_high.x - p_low.x);
        *linear_coeficient = (double)p_high.y - (*angular_coeficient * p_high.x);
        *constant_x = NAN; // represents that the line is not a constant
    }
    else
    {
        *angular_coeficient = NAN;
        *linear_coeficient = (double)p_high.y;
        *constant_x = p_high.x; // represents that the line is constant
    }
}

double calculate_projected_for_p_y(double constant_x, double a, double b, point p)
{

    if (isnan(constant_x)) //Checks if x is not constant
    {
        if (a == 0)
        {
            return b;
        }
        else
        {
            return (p.y - b) / a;
        }
    }
    else
    {
        return constant_x;
    }
}

int compare_projected_with_p_x(double projected, point p, point p_high, point p_low)
{
    /*Checks if the the point is on top of the projected one*/
    if (verify_double(projected, (double)p.x))
    {
        //Assures the point p is between p_high and p_low, meaning, it is on top of the line
        if ((p.x >= p_low.x && p.x <= p_high.x) || (p.x <= p_low.x && p.x >= p_high.x))
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }
    /*Checks if the projected point is at the left of the point*/
    else if (projected < p.x)
    {
        /*As it is possible for the segment to be paralle to the x axis, 
        and the chosen point beeing to the left, it is needed to check
        if it is on top of the segment. 
        */
        if (verify_double(projected, (double)p_high.y) && verify_double(projected, (double)p_low.y))
        {
            if ((p.x >= p_low.x && p.x <= p_high.x) || (p.x <= p_low.x && p.x >= p_high.x))
            {
                return 2;
            }
        }
        return 0;
    }
    /*The projected point at the right of the point p*/
    else
    {
        return 1;
    }
}

int type_of_projected(int projected, point p, point p_low, point p_high)
{
    //Checks if the projection crosses any of the points
    if (verify_double(projected, p_low.x) || (verify_double(projected, p_high.x)))
    {
        if (p.y > p_low.y) //If it does, elevate the p_low and p_high in the y axis (perturbation)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        if (projected == p_low.y && projected == p_high.y) 
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

/*
Auxiliary function.
Returns if the point projection crosses an especific line
*/
int verify(point p, point a, point b)
{
    point p_low, p_high;
    double angular_coeficient, linear_coeficient, constant_x, projected;
    int relative_position;

    //Categorizes which point has a bigger value in terms of the Y axis.
    categorize_points(&p_low, &p_high, a, b);

    /*
    Verify if p.y is above p_high.y or below p_low.y. 
    If this occours, the line segment between p_high and p_low 
    is, respectively, over or under the point. 
    This means that the point projection toward +x will never cross 
    the line segment. Therefore, the function should return 0.
    */
    if (p.y > p_high.y || p.y < p_low.y)
    {
        return 0;
    }
    else
    {
        /*Calculates the line segment between p_low and p_high.*/
        line_equation(&angular_coeficient, &linear_coeficient, &constant_x, p_low, p_high);

        /*Calculates the projected value for the given point, using the line equation.*/
        projected = calculate_projected_for_p_y(constant_x, angular_coeficient, linear_coeficient, p);

        /* 
        Compares projected value with given point (p), returning the relative position:
        0: projected is at the left of given point;
        1: projected is at the right of given point;
        2: projected in on top of given point.
        */
        relative_position = compare_projected_with_p_x(projected, p, p_high, p_low);
        if (relative_position == 1)
        {
            /*Calculates how projected point behaves, retriving a final relative position.*/
            relative_position = type_of_projected(projected, p, p_low, p_high);
        }
        return relative_position;
    }
}

/* Main function.
Checks if a point is inside a polygon using the ray casting algorithm. 
*/
int inside(point p, point poly[], int n)
{
    int cross = 0; //Amount of times the propagation of p crosses a line in the right.
    int verifying;
    int received_two = 0;
    point list[n + 1];

    //Create a new list based on poly, adding the first point at the end.
    for (int i = 0; i < n; i++)
    {
        list[i] = poly[i];
    }
    list[n] = poly[0];

    //Iterate in list, checking every pair n, n+1.
    for (int i = 0; i < n; i++)
    {
        //Checks how the point p is positione relative to the segment list[i], list[i+1].
        verifying = verify(p, list[i], list[i + 1]);

        if (verifying == 1)
        {
            //If point propagation to the right crosses segment.
            cross++;
        }
        else if (verifying == 2)
        {
            //If point is on top of a line
            received_two = 1;
        }
    }
    if (received_two)
    {
        //Inside due to beeing on top of line
        return 1;
    }
    else if ((cross % 2) == 0)
    {
        //Outside due to amount of lines crossed by projection beeing pair
        return 0;
    }
    else
    {
        //Inside due to amount of lines crossed by projection beeing even
        return 1;
    }
}