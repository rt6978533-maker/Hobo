#include <Hobo/Hobo.h>

#include <math.h>

//-------------------------------------------------------------------------------
//									Vector 2
//-------------------------------------------------------------------------------
Hobo::vec2::vec2(float value) {
	x = value;
	y = value;
}
Hobo::vec2::vec2() {
	x = 0;
	y = 0;
}
Hobo::vec2::vec2(float x, float y) {
	this->x = x;
	this->y = y;
}

//-------------------------------------------------------------------------------
//									Vector 3
//-------------------------------------------------------------------------------
Hobo::vec3::vec3() {
	x = 0;
	y = 0;
	z = 0;
}
Hobo::vec3::vec3(float value) {
	x = value;
	y = value;
	z = value;
}
Hobo::vec3::vec3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}
Hobo::vec3::vec3(vec2 xy, float z) {
	x = xy.x;
	y = xy.y;
	this->z = z;
}
Hobo::vec2 Hobo::vec3::xy() {
	return vec2(x, y);
}

//-------------------------------------------------------------------------------
//									Matrix 2
//-------------------------------------------------------------------------------
Hobo::mat2  Hobo::mat2::rotate(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat2(
		c, -s,
		s, c
	);
}
Hobo::mat2  Hobo::mat2::scale(float a) {
	return mat2(
		a, 0,
		0, a
	);
}
Hobo::mat2  Hobo::mat2::scale(float x, float y) {
	return mat2(
		x, 0,
		0, y
	);
}
Hobo::mat2::mat2(float x1, float x2, float y1, float y2) {
	m00 = x1;
	m10 = y1;
	m01 = x2;
	m11 = y2;
}
Hobo::mat2::mat2(float v) {
	m00 = v;
	m10 = 0;
	m01 = 0;
	m11 = v;
}
//-------------------------------------------------------------------------------
//									Matrix 3
//-------------------------------------------------------------------------------
Hobo::mat3  Hobo::mat3::rotateX(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat3(
		1, 0, 0,
		0, c,-s,
	    0, s, c
	);
}
Hobo::mat3  Hobo::mat3::rotateY(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat3(
		c, 0, s,
		0, 1, 0,
	   -s, 0, c
	);
}
Hobo::mat3  Hobo::mat3::rotateZ(float a) {
	float c = cos(a);
	float s = sin(a);
	return mat3(
		c, -s, 0,
		s, c, 0,
		0, 0, 1
	);
}
Hobo::mat3::mat3(float x1, float x2, float x3,
	float y1, float y2, float y3,
	float z1, float z2, float z3) {
	m00 = x1; m10 = x2; m20 = x3;
	m01 = y1; m11 = y2; m21 = y3;
	m02 = z1; m12 = z2; m22 = z3;
}
Hobo::mat3::mat3(float v) {
	m00 = v; m10 = 0; m20 = 0;
	m01 = 0; m11 = v; m21 = 0;
	m02 = 0; m12 = 0; m22 = v;
}

//-------------------------------------------------------------------------------
//									Vector Method
//-------------------------------------------------------------------------------

//Lerp
Hobo::vec2 Hobo::Lerp(vec2 a, vec2 b, float t) {
	return a + (b - a) * t;
}
Hobo::vec3 Hobo::Lerp(vec3& a, vec3& b, float t) {
	return a + (b - a) * t;
}

//Magnitude
float Hobo::length(vec2& v) {
	return sqrt(v.x * v.x + v.y * v.y);
}
float Hobo::length(vec3& v) {
	return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}
float Hobo::sqrtLength(vec2& v) {
	return v.x * v.x + v.y * v.y;
}
float Hobo::sqrtLength(vec3& v) {
	return v.x * v.x + v.y * v.y + v.z * v.z;
}

//Normalize
void Hobo::normalize(vec2& v) {
	float l = length(v);
	v.x /= l;
	v.y /= l;
}
void Hobo::normalize(vec3& v) {
	float l = length(v);
	v.x /= l;
	v.y /= l;
	v.z /= l;
}

//Dot product
float Hobo::dot_product(vec2& v1, vec2& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
float Hobo::dot_product(vec3& v1, vec3& v2) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

//Clamp
float Hobo::Clamp(float value, float min, float max) {
	return std::max(std::min(value, max), min);
}