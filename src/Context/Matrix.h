
#include "./Vec.h"
#pragma once

namespace FCT
{

	class Mat4
	{
	public:
		float m[16];

		Mat4()
		{
			identity();
		}
		Mat4(float m11, float m12, float m13, float m14,
			 float m21, float m22, float m23, float m24,
			 float m31, float m32, float m33, float m34,
			 float m41, float m42, float m43, float m44)
		{
			m[0] = m11;
			m[1] = m12;
			m[2] = m13;
			m[3] = m14;
			m[4] = m21;
			m[5] = m22;
			m[6] = m23;
			m[7] = m24;
			m[8] = m31;
			m[9] = m32;
			m[10] = m33;
			m[11] = m34;
			m[12] = m41;
			m[13] = m42;
			m[14] = m43;
			m[15] = m44;
		}

		void identity()
		{
			*this = {
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1};
		}
		void translate(float x, float y)
		{
			m[3] += x;
			m[7] += y;
		}
		void translate(float x, float y, float z)
		{
			Mat4 trans = {
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1
			};
			*this = *this * trans;
		}
		void rotateX(float degrees)
		{
			float radians = degrees * 3.14159265f / 180.0f;
			float c = cosf(radians);
			float s = sinf(radians);

			Mat4 rot = {
				1, 0, 0, 0,
				0, c, -s, 0,
				0, s, c, 0,
				0, 0, 0, 1};
			*this = *this * rot;
		}
		static Mat4 CreateTranslation(float x, float y)
		{
			Mat4 ret;
			ret.m[3] += x;
			ret.m[7] += y;
			return ret;
		}
		static Mat4 CreateScale(float scaleX, float scaleY)
		{
			Mat4 ret = {
				scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1};
			return ret;
		}
		static Mat4 Translate(float x, float y)
		{
			Mat4 ret;
			ret.m[8] += x;
			ret.m[9] += y;
			return ret;
		}
		static Mat4 Translate(float x, float y, float z)
		{
			Mat4 ret = {
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1
			};
			return ret;
		}


		static Mat4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
		{
			return Mat4(
				2.0f / (right - left), 0, 0, -(right + left) / (right - left),
				0, 2.0f / (top - bottom), 0, -(top + bottom) / (top - bottom),
				0, 0, 1.0f / (zFar - zNear), -zNear / (zFar - zNear),
				0, 0, 0, 1
			);
		}
		static Mat4 LookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
		{
			Vec3 f = (center - eye).normalize(); //z
			Vec3 s = f.cross(up).normalize(); //x
			Vec3 u = s.cross(f);

			Mat4 result = {
				s.x,  s.y,  s.z,  -s.dot(eye),
				u.x,  u.y,  u.z,  -u.dot(eye),
				f.x,  f.y,  f.z,  -f.dot(eye),
				0.0f, 0.0f, 0.0f,  1.0f
			};

			return result;
		}
		static Mat4 Scale(float scaleX, float scaleY)
		{
			Mat4 ret = {
				scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1};
			return ret;
		}
		static Mat4 Scale(float scaleX, float scaleY,float scaleZ)
		{
			Mat4 ret = {
				scaleX, 0, 0, 0,
				0, scaleY, 0, 0,
				0, 0, scaleZ, 0,
				0, 0, 0, 1};
			return ret;
		}
		static Mat4 Perspective(float fovx, float aspect, float zNear, float zFar)
		{
			float angle = fovx * 3.14159265f / 180.0f;
			float h = tanf(angle / 2.0f);
			return Mat4(
				 1 / h,		0,			0,                          0,
				 0,			aspect/ h,  0,                          0,
				 0,         0,			zFar / (zFar - zNear),     -zFar * zNear / (zFar - zNear),
				 0,         0,			1 ,                         0
			 );
		}
		void rotateY(float degrees)
		{
			float radians = degrees * 3.14159265f / 180.0f;
			float c = cosf(radians);
			float s = sinf(radians);

			Mat4 rot = {
				c, 0, s, 0,
				0, 1, 0, 0,
				-s, 0, c, 0,
				0, 0, 0, 1};
			*this = *this * rot;
		}
		void rotateZ(float degrees)
		{
			float radians = degrees * 3.14159265f / 180.0f;
			float c = cosf(radians);
			float s = sinf(radians);

			Mat4 rot = {
				c, -s, 0, 0,
				s, c, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1};
			*this = *this * rot;
		}
		Vec4 operator*(const Vec4& vec) const
		{
			return {
				m[0] * vec.x + m[1] * vec.y + m[2] * vec.z + m[3] * vec.w,    // 第1行
				m[4] * vec.x + m[5] * vec.y + m[6] * vec.z + m[7] * vec.w,    // 第2行
				m[8] * vec.x + m[9] * vec.y + m[10] * vec.z + m[11] * vec.w,  // 第3行
				m[12] * vec.x + m[13] * vec.y + m[14] * vec.z + m[15] * vec.w // 第4行
			};
		}
		void scale(float x, float y, float z)
		{
			Mat4 scl = {
				x, 0, 0, 0,
				0, y, 0, 0,
				0, 0, z, 0,
				0, 0, 0, 1};
			*this = *this * scl;
		}

		Mat4 operator*(const Mat4 &rhs) const
		{
			Mat4 result;
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
				{
					result.m[i * 4 + j] = 0.0f;
					for (int k = 0; k < 4; ++k)
					{
						result.m[i * 4 + j] += m[i * 4 + k] * rhs.m[k * 4 + j];
					}
				}
			}
			return result;
		}
		Mat4& operator*=(const Mat4 &rhs)
		{
			*this = *this * rhs;
			return *this;
		}
		friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);
	};
	inline std::ostream& operator<<(std::ostream& os, const Mat4& mat)
	{
		os << std::fixed << std::setprecision(4);
		os << "Matrix4x4:\n";
		for (int i = 0; i < 4; ++i)
		{
			os << "[ ";
			for (int j = 0; j < 4; ++j)
			{
				os << std::setw(10) << mat.m[i * 4 + j];
				if (j < 3) os << ", ";
			}
			os << " ]\n";
		}
		return os;
	}

	class Mat3 : public Mat4
	{

	};
} // namespace FCT