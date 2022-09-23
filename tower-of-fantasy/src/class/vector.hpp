#pragma once
#include <corecrt_math_defines.h>

namespace big
{
	struct iVector2
	{
		iVector2() = default;
		iVector2(int x, int y) : x(x), y(y) {}
		int x{};
		int y{};

		iVector2 operator/(const iVector2 a) const { return { x / a.x, y / a.y }; }
	};

	struct iVector3
	{
		iVector3() = default;
		iVector3(int x, int y, int z) : x(x), y(y), z(z) {}
		int x{};
		int y{};
		int z{};
	};

	struct iVector4
	{
		int x;
		int y;
		int z;
		int w;
	};

	struct Vector2
	{
		Vector2() = default;
		Vector2(float x, float y) : x(x), y(y) {}
		float x;
		float y;

		float distance(const Vector2 b) const
		{ 
			float x = this->x - b.x;
			float y = this->y - b.y;
			return sqrtf((x * x) + (y * y)) * 0.03048f;
		}

		float dot(Vector2 vec2)
		{
			return (x * vec2.x) + (y * vec2.y);
		}
	};

	struct Vector3
	{
		Vector3() = default;
		Vector3(float x, float y, float z) : x(x), y(y), z(z) {}
		float x{};
		float y{};
		float z{};

		float dot(Vector3 vec3)
		{
			return x * vec3.x + y * vec3.y + z * vec3.z;
		}

		float distance(Vector3 v) const
		{
			float x = this->x - v.x;
			float y = this->y - v.y;
			float z = this->z - v.z;

			return sqrtf((x * x) + (y * y) + (z * z)) * 0.03048f;
		}

		Vector3 operator-(const Vector3 vec3) const { return { vec3.x - x, vec3.y - y, vec3.z - z }; }
		Vector3 operator*(const Vector3& a) const { return { x * a.x, y * a.y, z * a.z }; }
		Vector3 operator+(const Vector3& vec3) const { return { x + vec3.x, y * vec3.y, z * vec3.z }; }
		Vector3 operator/(const Vector3& vec3) const { return { vec3.x / x, vec3.y / y, vec3.z / z }; }
		bool operator==(const Vector3 a) const { return x == a.x && y == a.y && z == a.z; }
	};

	struct Rotator
	{
		Rotator() = default;
		Rotator(float pitch, float yaw, float roll) : pitch(pitch), yaw(yaw), roll(roll) {}
		float pitch{};
		float yaw{};
		float roll{};

		Rotator operator-(const Rotator vec3) const { return { vec3.pitch - pitch, vec3.yaw - yaw, vec3.roll - roll }; }
		Rotator operator*(const Rotator& a) const { return { pitch * a.pitch, yaw * a.yaw, roll * a.roll }; }
		Rotator operator+(const Rotator& vec3) const { return { pitch + vec3.pitch, yaw * vec3.yaw, roll * vec3.roll }; }
		Rotator operator/(const Rotator& vec3) const { return { vec3.pitch / pitch, vec3.yaw / yaw, vec3.roll / roll }; }
		bool operator==(const Rotator a) const { return pitch == a.pitch && yaw == a.yaw && roll == a.roll; }
	};

	struct Vector4
	{
		Vector4() = default;
		Vector4(float x, float y, float z, float w): x(x), y(y), z(z), w(w) {}
		float x{};
		float y{};
		float z{};
		float w{};

		float dot(Vector4 vec4)
		{
			return (x * vec4.x) + (y * vec4.y) + (z * vec4.z) + (w * vec4.w);
		}

		float bitwise_and_first(int v)
		{
			return float((int)x & v);
		}

		Vector4 operator&(const Vector4& v) { return {float((int)v.x & (int)x), float((int)v.y & (int)y), float((int)v.z & (int)z), float((int)v.w & (int)w) }; };
	};

	struct FVector_NetQuantize : public Vector3
	{
		FVector_NetQuantize()
		{}

		FVector_NetQuantize(float x, float y, float z)
			: Vector3(x, y, z)
		{}

		FVector_NetQuantize operator=(const Vector3 vec3) const { return { vec3.x, vec3.y, vec3.z }; }
		FVector_NetQuantize operator-() const { return { -x, -y, -z }; }
	};

	struct FVector_NetQuantizeNormal : public Vector3
	{
		FVector_NetQuantizeNormal()
		{}

		FVector_NetQuantizeNormal(float InX, float InY, float InZ)
			: Vector3(InX, InY, InZ)
		{}

		FVector_NetQuantizeNormal operator=(const Vector3 vec3) const { return { vec3.x, vec3.y, vec3.z }; }
		FVector_NetQuantizeNormal operator-() const { return { -x, -y, -z }; }
	};

	class FLinearColor 
	{
	public:
		float R, G, B, A;
		FLinearColor() : R(0.f), G(0.f), B(0.f), A(0.f) {};
		FLinearColor(float R, float G, float B, float A) : R(R), G(G), B(B), A(A) {};
	};

	struct Matrix
	{
		float m[4][4];

		Matrix() { ZeroMemory(this, sizeof(Matrix)); }
		Matrix(const Vector3& rotation, const Vector3& origin = { 0.f, 0.f, 0.f })
		{
			float radPitch = rotation.x * float(M_PI) / 180.f;
			float radYaw = rotation.y * float(M_PI) / 180.f;
			float radRoll = rotation.z * float(M_PI) / 180.f;

			float SP = sinf(radPitch);
			float CP = cosf(radPitch);
			float SY = sinf(radYaw);
			float CY = cosf(radYaw);
			float SR = sinf(radRoll);
			float CR = cosf(radRoll);

			m[0][0] = CP * CY;
			m[0][1] = CP * SY;
			m[0][2] = SP;
			m[0][3] = 0.f;
			m[1][0] = SR * SP * CY - CR * SY;
			m[1][1] = SR * SP * SY + CR * CY;
			m[1][2] = -SR * CP;
			m[1][3] = 0.f;
			m[2][0] = -(CR * SP * CY + SR * SY);
			m[2][1] = CY * SR - CR * SP * SY;
			m[2][2] = CR * CP;
			m[2][3] = 0.f;
			m[3][0] = origin.x;
			m[3][1] = origin.y;
			m[3][2] = origin.z;
			m[3][3] = 1.f;
		}

		Matrix operator*(const Matrix& m2) const
		{
			Matrix out;
			for (byte r = 0; r < 4; r++)
			{
				for (byte c = 0; c < 4; c++)
				{
					float sum = 0.f;

					for (byte i = 0; i < 4; i++)
						sum += m[r][i] * m2.m[i][c];

					out.m[r][c] = sum;
				}
			}

			return out;
		}
		__forceinline void operator*=(const Matrix& m2) { *this = this->operator*(m2); }
	};

	using FVector = Vector3;
	using FVector2D = Vector2;
}