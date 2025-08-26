#include "math/vector3.h"

#define _USE_MATH_DEFINES
#define EPS 0.0000001

Vector3::Vector3() : Vector3(0) {
}

Vector3::Vector3(double a) : Vector3(a, a, a) {
}

Vector3::Vector3(double a, double b, double c) : x(a), y(b), z(c) {
}

Vector3::Vector3(const std::vector<double> &v) {
	if (v.size() < 3) throw std::invalid_argument("not enough variables in v");
	x = v[0];
	y = v[1];
	z = v[2];
}

Vector3::Vector3(const std::vector<float> &v) {
	if (v.size() < 3) throw std::invalid_argument("not enough variables in v");
	x = v[0];
	y = v[1];
	z = v[2];
}

bool Vector3::operator==(const Vector3 &v) const {
	return dist(v) < EPS;
}

double &Vector3::operator[](int i) {
	if (i < 0 || i >= 3) throw std::out_of_range("i not in range for vector");
	switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
	}
	return x;
}

double Vector3::operator[](int i) const {
	if (i < 0 || i >= 3) throw std::out_of_range("i not in range for vector");
	switch (i) {
		case 0:
			return x;
		case 1:
			return y;
		case 2:
			return z;
	}
	return x;
}

Vector3 Vector3::operator+(const Vector3 &v) const {
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator-(const Vector3 &v) const {
	return (*this) + (v * -1);
}

Vector3 Vector3::operator*(double s) const {
	return Vector3(x * s, y * s, z * s);
}

Vector3 Vector3::operator/(double s) const {
	return (*this) * (1 / s);
}

double Vector3::operator*(const Vector3 &v) const {
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::cross(const Vector3 &v) const {
	return Vector3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

double Vector3::magnitude() const {
	return sqrt(x * x + y * y + z * z);
}

Vector3 &Vector3::normalize() {
	(*this) = unit();
	return *this;
}

Vector3 Vector3::unit() const {
	if (magnitude() < EPS) return (*this);
	return (*this) / magnitude();
}

double Vector3::dist(const Vector3 &v) const {
	return ((*this) - v).magnitude();
}

std::ostream &operator<<(std::ostream &strm, const Vector3 &v) {
	return strm << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}
