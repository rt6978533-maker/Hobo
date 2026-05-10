#pragma once

#include <string>
#include <vector>

namespace Hobo {
	//Vectors
	struct vec2 {
		float x, y;

		vec2();
		vec2(float value);
		vec2(float x, float y);

		inline vec2 operator-(const vec2& b) const {
			return vec2(this->x - b.x, this->y - b.y);
		}
		inline vec2 operator+(const vec2& b) const {
			return vec2(this->x + b.x, this->y + b.y);
		}
		inline vec2 operator*(const float v) const {
			return vec2(this->x * v, this->y * v);
		}
	};
	struct vec3 {
		float x, y, z;

		vec2 xy();

		vec3();
		vec3(float value);
		vec3(float x, float y, float z);
		vec3(vec2 xy, float z);

		inline vec3 operator-(const vec3& b) const {
			return vec3(this->x - b.x, this->y - b.y, this->z - b.z);
		}
		inline vec3 operator+(const vec3& b) const {
			return vec3(this->x + b.x, this->y + b.y, this->z + b.z);
		}
		inline vec3 operator*(const float v) const {
			return vec3(this->x * v, this->y * v, this->z * v);
		}
	};
	struct mat2 {
		union {
			float Data[4];

			struct {
				float m00, m10,
					m01, m11;
			};
		};
		
		
		static mat2 rotate(float a);
		static mat2 scale(float a);
		static mat2 scale(float x, float y);

		mat2(float v);
		mat2(float x1, float x2, float y1, float y2);

		inline vec2 operator*(const vec2& v) const {
			return vec2(
				m00 * v.x + m01 * v.y,
				m10 * v.x + m11 * v.y
			);
		}
		inline mat2 operator*(const mat2& v) const {
			return mat2(
				v.m00*m00+v.m10*m10, v.m01*m00+v.m11*m10,
				v.m00*m10+v.m10*m11, v.m01*m10+v.m11*m11
			);
		}
	};
	struct mat3 {
		union {
			float Data[9];

			struct {
				float m00, m10, m20,
					m01, m11, m21,
					m02, m12, m22;
			};
		};

		static mat3 rotateX(float a);
		static mat3 rotateY(float a);
		static mat3 rotateZ(float a);

		mat3(float x1, float x2, float x3,
			 float y1, float y2, float y3,
			 float z1, float z2, float z3);
		mat3(float a);

		inline vec3 operator*(const vec3& v) const {
			return vec3(
				m00*v.x+m01*v.x+m02*v.x,
				m10*v.y+m11*v.y+m12*v.y,
				m20*v.z+m21*v.z+m22*v.z
			);
		}
		inline mat3 operator*(const mat3& v) const {
			return mat3(
				v.m00 * m00 + v.m10 * m10 + v.m20 * m20, v.m01 * m00 + v.m11 * m10 + v.m21 * m20, v.m02 * m00 + v.m12 * m10 + v.m22 * m20,
				v.m00 * m01 + v.m10 * m11 + v.m20 * m21, v.m01 * m01 + v.m11 * m11 + v.m21 * m21, v.m02 * m01 + v.m12 * m11 + v.m22 * m21,
				v.m00 * m02 + v.m10 * m12 + v.m20 * m22, v.m01 * m02 + v.m11 * m12 + v.m21 * m22, v.m02 * m02 + v.m12 * m12 + v.m22 * m22
			);
		}
	};
	//Matematic
	vec2 Lerp(vec2 a, vec2 b, float t);
	vec3 Lerp(vec3& a, vec3& b, float t);
	float length(vec2& v);
	float length(vec3& v);
	float sqrtLength(vec2& v);
	float sqrtLength(vec3& v);
	void normalize(vec2& v);
	void normalize(vec3& v);
	float dot_product(vec2& v1, vec2& v2);
	float dot_product(vec3& v1, vec3& v2);
	float Clamp(float value, float min, float max);
	//Texture
	struct Texture2D {
		unsigned char* Data;
		int Width, Height;

		bool empty();

		Texture2D(const char* pathFile);
		~Texture2D();
	};

	//Debug
	struct Debug {
		static bool IsCrash;

		static void Log(std::string value);
		static void Log(float value);
		static void LogError(std::string value);
		static void LogError(float value);
	};

	//FileManager
	namespace FileManager {
		//Texture
		void STBI_FLIP_TEXTURE(bool value);
		void LoadTexture(Texture2D& texture, std::string pathFile);
		void FreeTexture(Texture2D& texture);
		//Basic
		bool TestWriteTime(const char* pathFile, const char* pathFileTwo);
		bool ExistFile(const char* pathFile);
		void CreateDirectory(const char* pathCreate);
		std::string ReadFile(std::string pathFile);
		//Gebrid
		void TestDirectory(const char* pathCreate);
	}
}