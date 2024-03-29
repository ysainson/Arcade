/*
** EPITECH PROJECT, 2019
** Arcade
** File description:
** Vector
*/

#ifndef VECTOR_HPP_
#define VECTOR_HPP_

struct Vector final {
	double x;
	double y;
	
	Vector() noexcept;
	Vector(const Vector &v) noexcept = default;
	Vector(double x, double y) noexcept;
	~Vector() = default;

	Vector &operator+=(const Vector &vec) noexcept;
	Vector &operator+=(const double &val) noexcept;
	Vector &operator-=(const Vector &vec) noexcept;
	Vector &operator-=(const double &val) noexcept;
	Vector &operator*=(const Vector &vec) noexcept;
	Vector &operator*=(const double &val) noexcept;
	Vector &operator/=(const Vector &vec);
	Vector &operator/=(const double &val);
	Vector operator+(const Vector &vec) const noexcept;
	Vector operator+(const double &val) const noexcept;
	Vector operator-(const Vector &vec) const noexcept;
	Vector operator-(const double &val) const noexcept;
	Vector operator*(const Vector &vec) const noexcept;
	Vector operator*(const double &val) const noexcept;
	Vector operator/(const Vector &vec) const;
	Vector operator/(const double &val) const;
	Vector &operator=(const Vector &vec) noexcept;
	Vector &operator=(const double &val) noexcept;
	bool operator==(const Vector &vec) const noexcept;
	bool operator!=(const Vector &vec) const noexcept;
};

#endif /* !VECTOR_HPP_ */
