
#define I ((float2)(0.0, 1.0))

inline float  real(float2 a){
     return a.x;
}
inline float  imag(float2 a){
     return a.y;
}

inline float cmod(float2 a){
    return (sqrt(a.x*a.x + a.y*a.y));
}

/*
 * Get the argument of a complex number (its angle):
 * http://en.wikipedia.org/wiki/Complex_number#Absolute_value_and_argument
 */
inline float carg_g(float2 a){
    if(a.x > 0){
        return atan(a.y / a.x);

    }else if(a.x < 0 && a.y >= 0){
        return atan(a.y / a.x) + PI;

    }else if(a.x < 0 && a.y < 0){
        return atan(a.y / a.x) - PI;

    }else if(a.x == 0 && a.y > 0){
        return PI/2;

    }else if(a.x == 0 && a.y < 0){
        return -PI/2;

    }else{
        return 0;
    }
}

inline float2  cmult(float2 a, float2 b){
    return (float2)( a.x*b.x - a.y*b.y, a.x*b.y + a.y*b.x);
}


inline float2 cdiv(float2 a, float2 b){
    return (float2)((a.x*b.x + a.y*b.y)/(b.x*b.x + b.y*b.y), (a.y*b.x - a.x*b.y)/(b.x*b.x + b.y*b.y));
}

/*
 *  Square root of complex number.
 *  Although a complex number has two square roots, numerically we will
 *  only determine one of them -the principal square root, see wikipedia
 *  for more info: 
 *  http://en.wikipedia.org/wiki/Square_root#Principal_square_root_of_a_complex_number
 */
 inline float2 csqrt_t(float2 a){
     return (float2)( sqrt(cmod(a)) * cos(carg_g(a)/2),  sqrt(cmod(a)) * sin(carg_g(a)/2));
 }
