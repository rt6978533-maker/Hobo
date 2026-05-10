#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

namespace HOBO_ECS {
	class World {
		std::vector<glm::vec3> Position;
		std::vector<glm::vec3> Rotation;
		std::vector<glm::vec3> Scale;

		std::vector<int> FreeSlots;
	public:
		float G;
		int Size;

		//System
		std::vector<glm::mat4> SysGetModelsMatrix();

		//Controller
		//Position
		void SetPosition(int index, glm::vec3 position);
		void SetPositions(int* indexs, glm::vec3 position, int countSize);
		void SetPositions(int* indexs, glm::vec3* positions, int countSize);
		glm::vec3 GetPosition(int index);
		//Rotation
		void SetRotation(int index, glm::vec3 rotation);
		void SetRotations(int* indexs, glm::vec3 rotation, int countSize);
		void SetRotations(int* indexs, glm::vec3* rotations, int countSize);
		glm::vec3 GetRotation(int index);
		//Scale
		void SetScale(int index, glm::vec3 scale);
		void SetScales(int* indexs, glm::vec3 scale, int countSize);
		void SetScales(int* indexs, glm::vec3* scales, int countSize);
		glm::vec3 GetScale(int index);
		//ModelMatrix
		glm::mat4 GetModelMatrix(int index);

		//Basic
		void FreeEntity(int index);
		int CreateEntity();
		World();
	};

	//Addition
	struct Physics {
	private:
		glm::vec3 Force, Acceleration, Velocity;
		World& _World;
	public:
		int ID;
		float Mass, bounce;

		glm::vec3 GetVelocity();
		void SetVelocity(glm::vec3 v);

		void ResolveCollision(Physics& obj, float r1, float r2);
		void ApplyForce(glm::vec3 f);
		void Update(float dt);

		Physics(World& world);
		Physics(World& world, int idObject);
	};

	struct Camera3D {
		World& World_;
		int ID;
		float Fov, Aspect;

		/// <summary>
		/// Projection * View matrix
		/// </summary>
		glm::mat4 GetCamMatrix();

		Camera3D(World& world, glm::vec3 position, glm::vec3 rotation, float fov, int w, int h);
	};
}