#include <Hobo/ECS/HOBO_ECS.h>
#include <iostream>

//----------------------------------------------------------------------------------
//					Data-Oriented Desig (ECS) World
//----------------------------------------------------------------------------------
HOBO_ECS::World::World() {
	Size = 0;
	Position = std::vector<glm::vec3>();
	Rotation = std::vector<glm::vec3>();
	Scale = std::vector<glm::vec3>();
	FreeSlots = std::vector<int>();
}

void HOBO_ECS::World::FreeEntity(int index) {
	if (index < 0 || index >= Size) {
		std::cout << "\033[31m[ERROR][ECS][WORLD][FREE_ENTITY] Index out of range." << "\033[0m\n";
		return;
	}

	Position[index] = glm::vec3(0.0f);
	Rotation[index] = glm::vec3(0.0f);
	Scale[index] = glm::vec3(1.0f);
	FreeSlots.push_back(index);
}
int HOBO_ECS::World::CreateEntity() {
	if (FreeSlots.empty()) {
		int old = Size;
		Position.push_back(glm::vec3(0.0f));
		Rotation.push_back(glm::vec3(0.0f));
		Scale.push_back(glm::vec3(1.0f));
		Size++;
		return old;
	}
	else {
		int index = FreeSlots.back();
		FreeSlots.pop_back();
		return index;
	}
}
//Position
glm::vec3 HOBO_ECS::World::GetPosition(int index) {
	if (index < 0 || index >= Size) {
		std::cout << "\033[31m[ERROR][ECS][WORLD][GET_POSITION] Index out of range." << "\033[0m\n";
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return Position[index];
}
void HOBO_ECS::World::SetPosition(int index, glm::vec3 newPosition) {
	if (index < 0 || index >= Size) {
		std::cout << "\033[31m[ERROR][ECS][WORLD][SET_POSITION] Index out of range." << "\033[0m\n";
		return;
	}
	Position[index] = newPosition;
}
void HOBO_ECS::World::SetPositions(int* indexs, glm::vec3 position, int countSize) {
	for (int index = 0; index < countSize; index++) {
		SetPosition(indexs[index], position);
	}
}
void HOBO_ECS::World::SetPositions(int* indexs, glm::vec3* positions, int countSize) {
	for (int index = 0; index < countSize; index++) {
		SetPosition(indexs[index], positions[index]);
	}
}
//Rotate
glm::vec3 HOBO_ECS::World::GetRotation(int index) {
	if (index < 0 || index >= Size) {
		std::cout << "\033[31m[ERROR][ECS][WORLD][GET_ROTATION] Index out of range." << "\033[0m\n";
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return Rotation[index];
}
void HOBO_ECS::World::SetRotation(int index, glm::vec3 newRotation) {
	if (index < 0 || index >= Size) {
		std::cout << "\033[31m[ERROR][ECS][WORLD][SET_ROTATION] Index out of range." << "\033[0m\n";
		return;
	}
	Rotation[index] = newRotation;
}
void HOBO_ECS::World::SetRotations(int* indexs, glm::vec3 rotation, int countSize) {
	for (int index = 0; index < countSize; index++) {
		SetRotation(indexs[index], rotation);
	}
}
void HOBO_ECS::World::SetRotations(int* indexs, glm::vec3* rotations, int countSize) {
	for (int index = 0; index < countSize; index++) {
		SetRotation(indexs[index], rotations[index]);
	}
}
//Scale
glm::vec3 HOBO_ECS::World::GetScale(int index) {
	if (index < 0 || index >= Size) {
		std::cout << "\033[31m[ERROR][ECS][WORLD][GET_SCALE] Index out of range." << "\033[0m\n";
		return glm::vec3(0.0f, 0.0f, 0.0f);
	}
	return Scale[index];
}
void HOBO_ECS::World::SetScale(int index, glm::vec3 newScale) {
	if (index < 0 || index >= Size) {
		std::cout << "\033[31m[ERROR][ECS][WORLD][SET_SCALE] Index out of range." << "\033[0m\n";
		return;
	}
	Scale[index] = newScale;
}
void HOBO_ECS::World::SetScales(int* indexs, glm::vec3 scale, int countSize) {
	for (int index = 0; index < countSize; index++) {
		SetScale(indexs[index], scale);
	}
}
void HOBO_ECS::World::SetScales(int* indexs, glm::vec3* scales, int countSize) {
	for (int index = 0; index < countSize; index++) {
		SetScale(indexs[index], scales[index]);
	}
}

//Function
glm::mat4 HOBO_ECS::World::GetModelMatrix(int index) {
	glm::mat4 transform(1.0f);
	transform = glm::translate(transform, GetPosition(index));
	glm::vec3 rotate = GetRotation(index);
	transform = glm::rotate(transform, rotate.x, glm::vec3(1.0f, 0.0f, 0.0f));
	transform = glm::rotate(transform, rotate.y, glm::vec3(0.0f, 1.0f, 0.0f));
	transform = glm::rotate(transform, rotate.z, glm::vec3(0.0f, 0.0f, 1.0f));
	transform = glm::scale(transform, GetScale(index));
	return transform;
}
std::vector<glm::mat4> HOBO_ECS::World::SysGetModelsMatrix() {
	if (Size <= 0)
		return std::vector<glm::mat4>();

	std::vector<glm::mat4> matrix(Size);

	for (int i = 0; i < Size; i++) {
		matrix[i] = GetModelMatrix(i);
	}

	return matrix;
}
//----------------------------------------------------------------------------------
//					Data-Oriented Desig (ECS) Camera3D
//----------------------------------------------------------------------------------
glm::mat4 HOBO_ECS::Camera3D::GetCamMatrix() {
	glm::vec3 pos = World_.GetPosition(ID);
	glm::mat4 v = glm::lookAt(pos, pos + World_.GetRotation(ID), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 p = glm::perspective(Fov, Aspect, 0.1f, 100.0f);

	return p * v;
}
HOBO_ECS::Camera3D::Camera3D(World& world, glm::vec3 position, glm::vec3 dir, float fov, int w, int h)
	: World_(world) {
	Fov = glm::radians(fov);
	Aspect = (float)w / h;
	ID = world.CreateEntity();
	world.SetPosition(ID, position);
	world.SetRotation(ID, dir);
	world.SetScale(ID, glm::vec3(1.0f));
}