#pragma once

#include <Hobo/Hobo.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace HoboGraphics {
	enum class HOBOenumType : GLenum {
		HOBO_UNSIGNED_INT = GL_UNSIGNED_INT,
		HOBO_FLOAT = GL_FLOAT,
		HOBO_INT = GL_INT,
	};
	enum HOBOenum : int {
		//Cursor
		HOBO_CURSOR_MODE_CAPTURE = 9,
		HOBO_CURSOR_MODE_LOCKED = 8,
		HOBO_CURSOR_MODE_HIDDEN = 7,
		HOBO_CURSOR_MODE_NORMAL = 6,
		//Type
		HOBO_GL_DYNAMIC_DRAW = 5,
		HOBO_GL_STATIC_DRAW = 4,
		//Shader value
		SHADER_VALUE_BINARY_FILE = 3,
		SHADER_VALUE_FILE_PATH = 2,
		SHADER_VALUE_SOURCE = 1,
		//Error
		SUCCESS = 0,
		ERROR_GLFW_INIT = -1,
		ERROR_WINDOW_NULL = -2,
		ERROR_GLAD_LOADER = -3,
	};

	struct TextureProgram {
		GLuint ID;

		void Enable();
		void Disable();
		void Activate();

		TextureProgram(Hobo::Texture2D& texture);
		TextureProgram(std::string pathFile);
		~TextureProgram();
	};

	class Shader {
	private:
		std::unordered_map<std::string, GLint> UniformList;

		void CompileCreateShader(HOBOenum typeValue);
	public:
		GLuint ID;
		bool IsCompiled;
		std::string PathFile;
		const char* Vertex, 
			      * Fragment,
				  * Geometry;

		void Compile(HOBOenum typeValue);
		void Hot_reload();
		//FLOAT UNIFORM
		void Uniformfv(std::string name, float value);
		void UniformVec2v(std::string name, float x, float y);
		void UniformVec2v(std::string name, Hobo::vec2 value);
		void UniformVec3v(std::string name, float x, float y, float z);
		void UniformVec3v(std::string name, Hobo::vec3 value);
		void UniformVec4v(std::string name, float x, float y, float z, float w);
		void UniformMat2v(std::string name, glm::mat2 matrix);
		void UniformMat2v(std::string name, Hobo::mat2 matrix);
		void UniformMat3v(std::string name, glm::mat3 matrix);
		void UniformMat3v(std::string name, Hobo::mat3 matrix);
		void UniformMat4v(std::string name, glm::mat4 matrix);
		GLint GetUniformLocation(std::string name);
		//Binary
		void LoadBinary(GLenum format, std::vector<uint8_t> data);

		//Shader
		static GLuint CreateShader(HoboGraphics::HOBOenum typeValue, GLenum typeShader, const char* value);
		static GLuint GenerateShaderVertex(HOBOenum typeValue, const char* value);
		static GLuint GenerateShaderFragment(HOBOenum typeValue, const char* value);
		static GLuint GenerateShaderGeometry(HOBOenum typeValue, const char* value);
		//Program
		static GLuint CreateProgram(GLuint idv, GLuint idf);
		static GLuint CreateProgram(GLuint idv, GLuint idf, GLuint idg);
		//Free
		static void FreeShader(GLuint id);
		static void FreeProgram(GLuint id);

		Shader(const char* vertex, const char* fragment);
		Shader(const char* vertex, const char* fragment, const char* geometry);
		~Shader();
	};

	struct InstanceInstruct {
		GLuint ID;
		int Index, Step, Count;
		HOBOenumType Type;
		std::vector<float> Data;

		void Apply(int divisior);
		void Free();

		InstanceInstruct(int index, int count, int step, std::vector<float> data);
	};

	struct MeshFilter {
		int Index, CountPoint, Step, Offset;

		void Apply();

		MeshFilter(int index, int countPoint, int step, int offset);
	};

	struct Mesh {
		GLuint ID_Folder, ID_Buffer, ID_Elements;

		std::vector<float> Vertex;
		std::vector<unsigned int> Elements;
		std::vector<MeshFilter> Filters;

		void SetVertex(std::vector<float> vertex);

		void EnableFolder();
		void DisableFolder();

		Mesh(std::vector<float> vertex, std::vector<unsigned int> elements, std::vector<MeshFilter> filters);
		Mesh(std::vector<float> vertex, std::vector<unsigned int> elements,
			std::vector<MeshFilter> filters, HOBOenum type);
		Mesh(std::vector<float> vertex, std::vector<unsigned int> elements, 
			std::vector<MeshFilter> filters, InstanceInstruct& instruct);
		Mesh(std::vector<float> vertex, std::vector<unsigned int> elements, 
			std::vector<MeshFilter> filters, InstanceInstruct& instruct, HOBOenum type);
		~Mesh();
	};

	//Input enum keys
	enum class HoboKey : int {
		//Arrows
		LEFT = GLFW_KEY_LEFT, RIGHT = GLFW_KEY_RIGHT, UP = GLFW_KEY_UP, DOWN = GLFW_KEY_DOWN,
		//One part
		Q = GLFW_KEY_Q, W = GLFW_KEY_W, E = GLFW_KEY_E, R = GLFW_KEY_R, T = GLFW_KEY_T,
		Y = GLFW_KEY_Y, U = GLFW_KEY_U, I = GLFW_KEY_I, O = GLFW_KEY_O, P = GLFW_KEY_P,
		//Two part
		A = GLFW_KEY_A, S = GLFW_KEY_S, D = GLFW_KEY_D, F = GLFW_KEY_F, G = GLFW_KEY_G,
		H = GLFW_KEY_H, J = GLFW_KEY_J, K = GLFW_KEY_K, L = GLFW_KEY_L,
		//Three part
		Z = GLFW_KEY_Z, X = GLFW_KEY_X, C = GLFW_KEY_C, V = GLFW_KEY_V, B = GLFW_KEY_B,
		N = GLFW_KEY_N, M = GLFW_KEY_M,
		//Addition
		SPACE = GLFW_KEY_SPACE, ESC = GLFW_KEY_ESCAPE, BACK_SPACE = GLFW_KEY_BACKSPACE,
		SHIFT_R = GLFW_KEY_RIGHT_SHIFT, SHIFT_L = GLFW_KEY_LEFT_SHIFT, SHIFT = GLFW_KEY_LEFT_SHIFT,
		CTRL_L = GLFW_KEY_LEFT_CONTROL, CTRL_R = GLFW_KEY_RIGHT_CONTROL, CTRL = GLFW_KEY_LEFT_CONTROL, 
		ALT = GLFW_KEY_RIGHT_ALT, ALT_L = GLFW_KEY_RIGHT_ALT, ALT_R = GLFW_KEY_RIGHT_ALT,
	};

	//Cursor
	class Cursor {
	private:
		GLFWwindow* window;
	public:
		Hobo::vec2 LastPos, Delta;

		void Update();
		void SetMode(HOBOenum cursor_mode);
		int GetMode(HOBOenum cursor_mode);

		Hobo::vec2 GetPosMouse();

		Cursor(GLFWwindow* window);
	};

	//Window
	struct Window {
		GLFWwindow* Screen;
		const char* Title;
		int Width, Height;
		bool IsInit;

		//Basic
		bool IsRun();
		HOBOenum Init();
		//Add method
		void SetIcon(Hobo::Texture2D& texture);

		//Input
		bool GetLastKeyState(HoboKey key);
		Cursor GetCursor();

		static void ResizeWindow(GLFWwindow* window, int w, int h);
		Window(int w, int h, const char* title);
	};
	
	//Time
	static class Time {
	public:
		static float DeltaTime;
		static float LastTime;

		static float GetTime();
		static void UpdateTime();
	};

	//-----------------------
	//			DOD
	//-----------------------
	//Group Render
	struct GroupShader {
		GLuint ID_Shader;
		int size;
		std::vector<GLuint> Ids;
		std::vector<GLsizei> SizeElements;

		void Set(int index, Mesh& mesh);
		void Remove(int index);
		void Clear();
		void UseShader();
		int Add(Mesh& mesh);
		//Addition
		void RenderDefualt(int count);
		void RenderDefualtShaderUse(int count);

		GroupShader(GLuint idShader);
		GroupShader(Shader& shader);
	};

	namespace Renderer {
		void Clear();
		void ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		void PollEvents();
		void FlipWindow(GLFWwindow* screen);

		//New frame
		void NewFrame(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
		void EndFrame(GLFWwindow* screen);

		//Shader
		void UseShader(Shader& shader);
		//Draw:
			//Draw Mesh
		void DrawMesh(Mesh& mesh);
		void DrawMeshPoint(Mesh& mesh, float size);
		void DrawMeshInstanced(Mesh& mesh, int count);
			//Draw Mesh Texture
		void DrawMeshTexture(Mesh& mesh, TextureProgram& texture);
		void DrawMeshTextureInstanced(Mesh& mesh, TextureProgram& texture, int count);
			//Draw Object
		void DrawObject(GLuint vao, GLsizei sizeElements);
		void DrawObjectInstanced(GLuint vao, GLsizei sizeElements, int count);
	}
	namespace Object {
		namespace Cube {
			std::vector<float> GetVertexUV(float sizeUV = 1.0f);
			std::vector<float> GetVertexColor(float r, float g, float b);
			std::vector<unsigned int> GetElements();
			std::vector<MeshFilter> GetFiltersUV();
			std::vector<MeshFilter> GetFiltersColor();
		}
		namespace Plane {
			std::vector<float> GetVertexColor(float r, float g, float b);
			std::vector<MeshFilter> GetFiltersColor();
			std::vector<float> GetVertexUV(float sizeUV=1.0f);
			std::vector<MeshFilter> GetFiltersUV();
			std::vector<unsigned int> GetElements();
		}
	}
}

namespace Hobo {
	namespace FileManager {
		void SaveShader(HoboGraphics::Shader& shader, std::string filePath);
		void LoadShader(HoboGraphics::Shader& shader, std::string filePath);
	}
}