#include <Hobo/ECS/HOBO_ECS.h>

HOBO_ECS::Physics::Physics(World& world) : Mass(1), _World(world),
	Acceleration(0), Velocity(0), Force(0), bounce(1) {
	ID = _World.CreateEntity();
}
HOBO_ECS::Physics::Physics(World& world, int id) : Mass(1), _World(world), ID(id),
	Acceleration(0), Velocity(0), Force(0), bounce(1) {}

void HOBO_ECS::Physics::ApplyForce(glm::vec3 f) { Force += f; }
void HOBO_ECS::Physics::SetVelocity(glm::vec3 v) { Velocity = v; }
glm::vec3 HOBO_ECS::Physics::GetVelocity() { return Velocity; }
void HOBO_ECS::Physics::Update(float dt) {
	Acceleration = Force / Mass;
	Velocity += Acceleration * dt;

	_World.SetPosition(ID, _World.GetPosition(ID) + Velocity * dt);
	Force = glm::vec3();
}
void HOBO_ECS::Physics::ResolveCollision(Physics& obj, float r1, float r2) {
	glm::vec3 p1 = _World.GetPosition(ID);
	glm::vec3 p2 = _World.GetPosition(obj.ID);
	glm::vec3 relativePos = p1 - p2;
	float dist = length(relativePos);
	glm::vec3 n = normalize(relativePos);

	glm::vec3 v1 = GetVelocity();
	glm::vec3 v2 = obj.GetVelocity();
	glm::vec3 deltaVelocity = v1 - v2;
	float Vangle = dot(deltaVelocity, n);
	if (Vangle > 0) return;
	float invMass1 = 1 / Mass;
	float invMass2 = 1 / obj.Mass;
	float f = -(1+bounce)*Vangle/(invMass1 + invMass2);

	SetVelocity(v1 + f * invMass1 * n);
	obj.SetVelocity(v2 - f * invMass2 * n);

	float overlap = (r1 + r2) - dist;
	if (overlap > 0) {
		_World.SetPosition(ID, p1 + n * overlap);
	}
}