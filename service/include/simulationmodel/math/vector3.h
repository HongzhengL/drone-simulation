#ifndef VECTOR3_H_
#define VECTOR3_H_

#include <cmath>
#include <iostream>
#include <vector>

/**
 * @class Vector3
 * @brief a simple class used for vector math, most function are self explanatory
 */
class Vector3 {
   public:
	double x = 0;
	double y = 0;
	double z = 0;

	/**
	 * @brief Default constructor.
	 */
	Vector3();

	/**
	 * @brief Parameter constructor
	 *
	 * @param[in] a x, y, and z-coordinate
	 */
	Vector3(double a);

	/**
	 * @brief Parameter constructor.
	 *
	 * @param[in] a x-coordinate
	 * @param[in] b y-coordinate
	 * @param[in] c z-coordinate
	 */
	Vector3(double a, double b, double c);

	/**
	 * @brief Parameter constructor
	 *
	 * @param[in] v The vector containing double-value xyz coordinates
	 */
	Vector3(const std::vector<double> &v);

	/**
	 * @brief Parameter constructor
	 *
	 * @param[in] v The vector containing float-value xyz coordinates
	 */
	Vector3(const std::vector<float> &v);

	/**
	 * @brief Overrides comparison operator
	 *
	 * @param v The Vector3 object you would like to compare to this Vector3
	 */
	bool operator==(const Vector3 &v) const;

	/**
	 * @brief Overrides indexing operator
	 *
	 * @param i The index you want to return
	 */
	double &operator[](int i);

	/**
	 * @brief Overrides const indexing operator
	 *
	 * @param i The index you want to return
	 */
	double operator[](int i) const;

	/**
	 * @brief Overrides + operator.
	 * @param[in] v The Vector3 object you would like to add to this Vector3
	 * object
	 * @return The Vector3 Object comprised of the sum of the two objects
	 */
	Vector3 operator+(const Vector3 &v) const;

	/**
	 * @brief Overrides - operator.
	 * @param[in] v The Vector3 object you would like to subtract to this Vector3
	 * object
	 * @return The Vector3 Object comprised of the subtraction of the two objects
	 */
	Vector3 operator-(const Vector3 &v) const;

	/**
	 * @brief Overrides * operator.
	 * @param[in] v The Vector3 object you would like to multiply to this Vector3
	 * object
	 * @return The Vector3 Object comprised of the multiplication of the two
	 * objects
	 */
	Vector3 operator*(double s) const;

	/**
	 * @brief Overrides / operator.
	 * @param[in] v The Vector3 object you would like to divide to this Vector3
	 * object
	 * @return The Vector3 Object comprised of the division of the two objects
	 */
	Vector3 operator/(double s) const;

	/**
	 * @brief Dot product
	 * @param[in] The Vector3 object you would like to use to dot product with this Vector3
	 * @return The Vector3 object comprised of the dot product of the two objects
	 */
	double operator*(const Vector3 &v) const;

	/**
	 * @brief return std::vector version of this Vector3
	 * template function should be defined in same file
	 * with template keyword
	 */
	template <class T>
	std::vector<T> vec() const {
		return {static_cast<T>(x), static_cast<T>(y), static_cast<T>(z)};
	}

	/**
	 * @brief Cross product
	 * @param[in] The Vector3 object you would like to use to cross product with this Vector3
	 * @return The Vector3 object comprised of the cross product of the two objects
	 */
	Vector3 cross(const Vector3 &v) const;

	/**
	 * @brief Returns the magnitude of the Vector3 object
	 */
	double magnitude() const;

	/**
	 * @brief Normalizes the Vector3 object
	 */
	Vector3 &normalize();

	/**
	 * @brief Normalizes the vector in the same direction
	 */
	Vector3 unit() const;

	/**
	 * @brief Finds the distance between two vectors
	 * @param[in] v The Vector3 object you would like to find the distance between with this Vector3
	 */
	double dist(const Vector3 &v) const;

	/**
	 * @brief << operator for Vector3 objects
	 * @param[in] strm The given output stream
	 * @param[in] v The given Vector3 object to output
	 */
	friend std::ostream &operator<<(std::ostream &strm, const Vector3 &v);
};

#endif
