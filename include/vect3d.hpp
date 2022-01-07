#include <valarray>
#include <math.h>
#include <iostream>

template<class T>
class vect3d {
public:
    std::valarray<T> array;
    vect3d(T x, T y, T z){
        array = std::valarray<T>(3);
        array[0] = x;
        array[1] = y;
        array[2] = z;
    };

    vect3d() : vect3d(0,0,0) {};
    vect3d(const vect3d& other){
        array = other.array;
    };

    vect3d operator=(const vect3d& other){
        if (this == &other){
            return *this;
        }
        array = other.array;
        return *this;
    };

    vect3d operator+(const vect3d& other) const {
        vect3d result;
        result.array = array + other.array;
        return result;
    }

    vect3d operator-(const vect3d& other) const {
        vect3d result;
        result.array = array - other.array;
        return result;
    }

    vect3d operator*(const T& coeff) const {
        vect3d result;
        result.array = array * coeff;
        return result;
    }

    vect3d operator/(const T& coeff) const {
        vect3d result;
        result.array = array / coeff;
        return result;
    }

    void operator+=(const vect3d& other) {
        *this = *this + other;
    }

    void operator-=(const vect3d& other) {
        *this = *this - other;
    }

    vect3d operator-() {
        vect3d result;
        result.array = -array;
        return result;
    }


    T scalar_prod(const vect3d& other) const {
        T result = array[0]*other.array[0]
                 + array[1]*other.array[1]
                 + array[2]*other.array[2];
        return result;
    }

    T norm3d() const {
        return sqrt(this->scalar_prod(*this));
    }

    friend std::ostream& operator<<(std::ostream& out, const vect3d& vec) {
        out << "x: " << vec.array[0] << ", y: " << vec.array[1] << ", z: " << vec.array[2] << ";";
        return out;
    }

    T operator[](uint index) const {
        return array[index];
    }

    T& operator[](uint index){
        return array[index];
    }

};

using vect3d_d = vect3d<double>;
using vect3d_f = vect3d<float>;