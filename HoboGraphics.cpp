#include <Hobo/HoboGraphics.h>

//----------------------------------------------------------------------------------
//									Window
//----------------------------------------------------------------------------------
//Input
bool HoboGraphics::Window::GetLastKeyState(HoboKey key) {
	return glfwGetKey(Screen, (int)key);
}
HoboGraphics::Cursor HoboGraphics::Window::GetCursor() {
	return HoboGraphics::Cursor(Screen);
}

//Addition
void HoboGraphics::Window::SetIcon(Hobo::Texture2D& texture) {
	if (!IsInit) {
		Hobo::Debug::LogError("[HOBO_GRAPHICS][WINDOW][SET_ICON] Window not init.");
		return;
	}
	if (texture.empty())
	{
		Hobo::Debug::LogError("[HOBO_GRAPHICS][WINDOW][SET_ICON] Texture is empty.");
		return;
	}

	GLFWimage icon;
	icon.pixels = texture.Data;
	icon.width = texture.Width;
	icon.height = texture.Height;

	glfwSetWindowIcon(Screen, 1, &icon);
}
//Basic
void HoboGraphics::Window::ResizeWindow(GLFWwindow* window, int w, int h) {
	glViewport(0, 0, w, h);
}
bool HoboGraphics::Window::IsRun() {
	return IsInit && !glfwWindowShouldClose(Screen);
}
HoboGraphics::HOBOenum HoboGraphics::Window::Init() {
	if (!glfwInit()) {
		return HoboGraphics::ERROR_GLFW_INIT;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	Screen = glfwCreateWindow(Width, Height, Title, NULL, NULL);

	if (Screen == NULL) {
		return HoboGraphics::ERROR_WINDOW_NULL;
	}

	glfwMakeContextCurrent(Screen);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		return HoboGraphics::ERROR_GLAD_LOADER;
	}

	glfwSetFramebufferSizeCallback(Screen, ResizeWindow);
	glViewport(0, 0, Width, Height);
	glEnable(GL_DEPTH_TEST);
	IsInit = true;

	return HoboGraphics::SUCCESS;
}
HoboGraphics::Window::Window(int w, int h, const char* title) {
	Width = w;
	Height = h;
	Title = title;
	IsInit = false;
	Screen = nullptr;
}

//----------------------------------------------------------------------------------
//									CURSOR
//----------------------------------------------------------------------------------
void HoboGraphics::Cursor::Update() {
	Hobo::vec2 pos = GetPosMouse();
	Delta = pos - LastPos;
	LastPos = pos;
}
Hobo::vec2 HoboGraphics::Cursor::GetPosMouse() {
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	return Hobo::vec2((float)x, (float)y);
}
void HoboGraphics::Cursor::SetMode(HoboGraphics::HOBOenum cursor_mode) {
	glfwSetInputMode(window, GLFW_CURSOR, GetMode(cursor_mode));
}
int HoboGraphics::Cursor::GetMode(HoboGraphics::HOBOenum cursor_mode) {
	switch (cursor_mode) {
	case HOBO_CURSOR_MODE_NORMAL:
		return GLFW_CURSOR_NORMAL;
	case HOBO_CURSOR_MODE_HIDDEN:
		return GLFW_CURSOR_HIDDEN;
	case HOBO_CURSOR_MODE_LOCKED:
		return GLFW_CURSOR_DISABLED;
	case HOBO_CURSOR_MODE_CAPTURE:
		return GLFW_CURSOR_CAPTURED;
	default:
		return GLFW_CURSOR_NORMAL;
	}
}
HoboGraphics::Cursor::Cursor(GLFWwindow* window) : Delta(0.0f),
LastPos(0.0f), window(window)
{}

//----------------------------------------------------------------------------------
//									Time
//----------------------------------------------------------------------------------
float HoboGraphics::Time::DeltaTime = 0.0f;
float HoboGraphics::Time::LastTime = 0.0f;

float HoboGraphics::Time::GetTime() { return glfwGetTime(); }
void HoboGraphics::Time::UpdateTime() {
	float time = GetTime();
	DeltaTime = time - LastTime;
	LastTime = time;
}

//----------------------------------------------------------------------------------
//									   Shaders
//----------------------------------------------------------------------------------
GLint HoboGraphics::Shader::GetUniformLocation(std::string name) {
	if (!IsCompiled) {
		Hobo::Debug::LogError("[HOBO_GRAPHICS][SHADER][GET_UNIFORM_LOCATION] Shader is not compiled.");
		return 0;
	}
	
	auto it = UniformList.find(name);
	if (it != UniformList.end()) {
		return it->second;
	}

	GLint b = glGetUniformLocation(ID, name.c_str());
	UniformList[name] = b;

	return b;
}

//Binary load
void HoboGraphics::Shader::LoadBinary(GLenum format, std::vector<uint8_t> data) {
	if (IsCompiled) {
		Hobo::Debug::LogError("[HOBO_GRAPHICS][SHADER][LOAD_BINARY] Shader is compiled.");
		return;
	}
	
	ID = glCreateProgram();

	glProgramBinary(ID, format, data.data(), data.size());

	GLint success;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		char info[500];
		glGetProgramInfoLog(ID, 500, NULL, info);
		Hobo::Debug::LogError("[HOBO_GRAPHICS][SHADER][LOAD_BINARY] LINK STATUS ERROR: ");
		Hobo::Debug::LogError(info);
		glDeleteProgram(ID);
		return;
	}

	IsCompiled = true;
}

//Float Uniforms
void HoboGraphics::Shader::UniformVec2v(std::string name, float x, float y) {
	GLint id = GetUniformLocation(name);
	glUniform2f(id, x, y);
}
void HoboGraphics::Shader::UniformVec2v(std::string name, Hobo::vec2 value) {
	GLint id = GetUniformLocation(name);
	glUniform2f(id, value.x, value.y);
}
void HoboGraphics::Shader::UniformVec3v(std::string name, float x, float y, float z) {
	GLint id = GetUniformLocation(name);
	glUniform3f(id, x, y, z);
}
void HoboGraphics::Shader::UniformVec3v(std::string name, Hobo::vec3 value) {
	GLint id = GetUniformLocation(name);
	glUniform3f(id, value.x, value.y, value.z);
}
void HoboGraphics::Shader::Uniformfv(std::string name, float value) {
	GLint id = GetUniformLocation(name);
	glUniform1f(id, value);
}
//Matrix Uniforms
void HoboGraphics::Shader::UniformMat2v(std::string name, Hobo::mat2 matrix) {
	GLint id = GetUniformLocation(name);
	glUniformMatrix2fv(id, 1, GL_FALSE, matrix.Data);
}
void HoboGraphics::Shader::UniformMat2v(std::string name, glm::mat2 matrix) {
	GLint id = GetUniformLocation(name);
	glUniformMatrix2fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}
void HoboGraphics::Shader::UniformMat3v(std::string name, glm::mat3 matrix) {
	GLint id = GetUniformLocation(name);
	glUniformMatrix3fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}
void HoboGraphics::Shader::UniformMat3v(std::string name, Hobo::mat3 matrix) {
	GLint id = GetUniformLocation(name);
	glUniformMatrix3fv(id, 1, GL_FALSE, matrix.Data);
}
void HoboGraphics::Shader::UniformMat4v(std::string name, glm::mat4 matrix) {
	GLint id = GetUniformLocation(name);
	glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(matrix));
}

//Basis Function
GLuint HoboGraphics::Shader::CreateShader(HoboGraphics::HOBOenum typeValue,
	GLenum typeShader, const char* value) {
	GLuint id = glCreateShader(typeShader);

	if (typeValue == HOBOenum::SHADER_VALUE_SOURCE) {
		glShaderSource(id, 1, &value, NULL);
	}
	else if (typeValue == HOBOenum::SHADER_VALUE_FILE_PATH || typeValue == HoboGraphics::SHADER_VALUE_BINARY_FILE) {
		std::string source = Hobo::FileManager::ReadFile(value);
		const char* v = source.c_str();
		glShaderSource(id, 1, &v, NULL);
	}

	glCompileShader(id);

	GLint success;
	char info[500];

	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(id, 500, NULL, info);
		Hobo::Debug::LogError(info);
		FreeShader(id);
		return 0;
	}

	return id;
}
void HoboGraphics::Shader::FreeShader(GLuint id) { glDeleteShader(id); }
void HoboGraphics::Shader::FreeProgram(GLuint id) { glDeleteProgram(id); }
GLuint HoboGraphics::Shader::CreateProgram(GLuint idv, GLuint idf) {
	GLuint id = glCreateProgram();

	glAttachShader(id, idv);
	glAttachShader(id, idf);

	glLinkProgram(id);
	GLint success;
	char info[500];

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(id, 500, NULL, info);
		Hobo::Debug::LogError(info);
		FreeProgram(id);
		return 0;
	}

	return id;
}
GLuint HoboGraphics::Shader::CreateProgram(GLuint idv, GLuint idf, GLuint idg) {
	GLuint id = glCreateProgram();

	glAttachShader(id, idv);
	glAttachShader(id, idf);
	glAttachShader(id, idg);

	glLinkProgram(id);
	GLint success;
	char info[500];

	glGetProgramiv(id, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(id, 500, NULL, info);
		Hobo::Debug::LogError(info);
		FreeProgram(id);
		return 0;
	}

	return id;
}

//Sugar
void HoboGraphics::Shader::CompileCreateShader(HOBOenum typeValue) {
	if (Geometry == "") {
		GLuint IDV = GenerateShaderVertex(typeValue, Vertex);
		if (!IDV) return;
		GLuint IDF = GenerateShaderFragment(typeValue, Fragment);
		if (!IDF) return;

		ID = CreateProgram(IDV, IDF);
		FreeShader(IDF);
		FreeShader(IDV);
		return;
	}
	else {
		GLuint IDV = GenerateShaderVertex(typeValue, Vertex);
		if (!IDV) return;
		GLuint IDF = GenerateShaderFragment(typeValue, Fragment);
		if (!IDF) return;
		GLuint IDG = GenerateShaderGeometry(typeValue, Geometry);
		if (!IDG) return;

		ID = CreateProgram(IDV, IDF, IDG);
		FreeShader(IDF);
		FreeShader(IDV);
		FreeShader(IDG);
		return;
	}
}
GLuint HoboGraphics::Shader::GenerateShaderVertex(HOBOenum typeValue, const char* value) {
	return CreateShader(typeValue, GL_VERTEX_SHADER, value);
}
GLuint HoboGraphics::Shader::GenerateShaderFragment(HOBOenum typeValue, const char* value) {
	return CreateShader(typeValue, GL_FRAGMENT_SHADER, value);
}
GLuint HoboGraphics::Shader::GenerateShaderGeometry(HOBOenum typeValue, const char* value)
{
	if (value == "")
		return 0;

	return CreateShader(typeValue, GL_GEOMETRY_SHADER, value);
}

//Compile
void HoboGraphics::Shader::Compile(HOBOenum typeValue) {
	if (IsCompiled) {
		Hobo::Debug::LogError("[SHADER][COMPILE] Shader is compiled.");
		return;
	}
	if (typeValue != SHADER_VALUE_FILE_PATH && typeValue != SHADER_VALUE_SOURCE && typeValue != SHADER_VALUE_BINARY_FILE) {
		Hobo::Debug::LogError("[SHADER][COMPILE] TypeValue is not support.");
		return;
	}
	if (Geometry == "") {
		if (typeValue == HoboGraphics::SHADER_VALUE_BINARY_FILE) {
			if (PathFile == "") {
				Hobo::Debug::LogError("[SHADER][COMPILE] PathFile is null.");
			}

			const char* path = PathFile.c_str();
			if (Hobo::FileManager::ExistFile(path) &&
				!Hobo::FileManager::TestWriteTime(path, Vertex) &&
				!Hobo::FileManager::TestWriteTime(path, Fragment)) {
				Hobo::FileManager::LoadShader(*this, PathFile);
				return;
			}
			else {
				CompileCreateShader(typeValue);
				if (ID == 0) return;
				IsCompiled = true;
				Hobo::FileManager::SaveShader(*this, PathFile);
				return;
			}
		}
	}
	else {
		if (typeValue == HoboGraphics::SHADER_VALUE_BINARY_FILE) {
			if (PathFile == "") {
				Hobo::Debug::LogError("[SHADER][COMPILE] PathFile is null.");
			}
			const char* path = PathFile.c_str();
			if (Hobo::FileManager::ExistFile(path) &&
				!Hobo::FileManager::TestWriteTime(path, Vertex) &&
				!Hobo::FileManager::TestWriteTime(path, Geometry) &&
				!Hobo::FileManager::TestWriteTime(path, Fragment)) {
				Hobo::FileManager::LoadShader(*this, PathFile);
				return;
			}
			else {
				CompileCreateShader(typeValue);
				if (ID == 0) return;
				IsCompiled = true;
				Hobo::FileManager::SaveShader(*this, PathFile);
				return;
			}
		}
	}
	CompileCreateShader(typeValue);
	if (ID == 0) return;

	IsCompiled = true;
}
void HoboGraphics::Shader::Hot_reload() {
	if (PathFile == "")
		return; 
	const char* path = PathFile.c_str();
	if (Hobo::FileManager::TestWriteTime(Vertex, path) ||
		Hobo::FileManager::TestWriteTime(Fragment, path)) {
		GLuint id = ID;
		IsCompiled = false;
		Compile(HoboGraphics::SHADER_VALUE_BINARY_FILE);
		if (ID != 0) {
			UniformList.clear();
			FreeProgram(id);
			Hobo::Debug::Log("[SHADER] Reload.");
			return;
		}
		else {
			ID = id;
			return;
		}
	}
}
HoboGraphics::Shader::Shader(const char* vertex, const char* fragment) {
	ID = 0;
	Geometry = "";
	Vertex = vertex;
	Fragment = fragment;
	IsCompiled = false;
}
HoboGraphics::Shader::Shader(const char* vertex, const char* fragment, const char* geometry) {
	ID = 0;
	Geometry = geometry;
	Vertex = vertex;
	Fragment = fragment;
	IsCompiled = false;
}
HoboGraphics::Shader::~Shader() {
	if (IsCompiled) {
		FreeProgram(ID);
	}
}

//----------------------------------------------------------------------------------
//										Mesh
//----------------------------------------------------------------------------------

void HoboGraphics::Mesh::EnableFolder() {
	glBindVertexArray(ID_Folder);
}
void HoboGraphics::Mesh::DisableFolder() {
	glBindVertexArray(0);
}

void HoboGraphics::Mesh::SetVertex(std::vector<float> vertex) {
	EnableFolder();

	glBindBuffer(GL_ARRAY_BUFFER, ID_Buffer);
	glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(float), vertex.data(), GL_DYNAMIC_DRAW);
}

HoboGraphics::Mesh::Mesh(std::vector<float> vertex, std::vector<unsigned int> elements,
	std::vector<MeshFilter> filters) {
	Vertex = vertex;
	Elements = elements;
	Filters = filters;

	ID_Folder = 0;
	ID_Buffer = 0;
	ID_Elements = 0;

	glGenVertexArrays(1, &ID_Folder);
	glGenBuffers(1, &ID_Elements);
	glGenBuffers(1, &ID_Buffer);

	EnableFolder();

	glBindBuffer(GL_ARRAY_BUFFER, ID_Buffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex.size() * sizeof(float), Vertex.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_Elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements.size() * sizeof(unsigned int), Elements.data(), GL_STATIC_DRAW);

	for (auto& filter : Filters) {
		filter.Apply();
	}

	DisableFolder();
}
HoboGraphics::Mesh::Mesh(std::vector<float> vertex, std::vector<unsigned int> elements,
	std::vector<MeshFilter> filters, HOBOenum type) {
	Vertex = vertex;
	Elements = elements;
	Filters = filters;

	ID_Folder = 0;
	ID_Buffer = 0;
	ID_Elements = 0;

	glGenVertexArrays(1, &ID_Folder);
	glGenBuffers(1, &ID_Elements);
	glGenBuffers(1, &ID_Buffer);

	GLenum type_draw;
	if (type == HOBO_GL_DYNAMIC_DRAW) type_draw = GL_DYNAMIC_DRAW;
	else type_draw = GL_STATIC_DRAW;

	EnableFolder();

	glBindBuffer(GL_ARRAY_BUFFER, ID_Buffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex.size() * sizeof(float), Vertex.data(), type_draw);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_Elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements.size() * sizeof(unsigned int), Elements.data(), type_draw);

	for (auto& filter : Filters) {
		filter.Apply();
	}

	DisableFolder();
}
HoboGraphics::Mesh::Mesh(std::vector<float> vertex, std::vector<unsigned int> elements,
	std::vector<MeshFilter> filters, InstanceInstruct& instance) {
	Vertex = vertex;
	Elements = elements;
	Filters = filters;

	ID_Folder = 0;
	ID_Buffer = 0;
	ID_Elements = 0;

	glGenVertexArrays(1, &ID_Folder);
	glGenBuffers(1, &ID_Elements);
	glGenBuffers(1, &ID_Buffer);
	glGenBuffers(1, &instance.ID);

	EnableFolder();

	glBindBuffer(GL_ARRAY_BUFFER, ID_Buffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex.size() * sizeof(float), Vertex.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_Elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements.size() * sizeof(unsigned int), Elements.data(), GL_STATIC_DRAW);

	for (auto& filter : Filters) {
		filter.Apply();
	}

	glBindBuffer(GL_ARRAY_BUFFER, instance.ID);
	glBufferData(GL_ARRAY_BUFFER, instance.Data.size() * sizeof(float), instance.Data.data(), GL_STATIC_DRAW);

	instance.Apply(1);

	DisableFolder();
}
HoboGraphics::Mesh::Mesh(std::vector<float> vertex, std::vector<unsigned int> elements,
	std::vector<MeshFilter> filters, InstanceInstruct& instance, HOBOenum type) {
	Vertex = vertex;
	Elements = elements;
	Filters = filters;

	ID_Folder = 0;
	ID_Buffer = 0;
	ID_Elements = 0;

	glGenVertexArrays(1, &ID_Folder);
	glGenBuffers(1, &ID_Elements);
	glGenBuffers(1, &ID_Buffer);

	GLenum type_draw;
	if (type == HOBO_GL_DYNAMIC_DRAW) type_draw = GL_DYNAMIC_DRAW;
	else type_draw = GL_STATIC_DRAW;

	EnableFolder();

	glBindBuffer(GL_ARRAY_BUFFER, ID_Buffer);
	glBufferData(GL_ARRAY_BUFFER, Vertex.size() * sizeof(float), Vertex.data(), type_draw);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID_Elements);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, Elements.size() * sizeof(unsigned int), Elements.data(), type_draw);

	for (auto& filter : Filters) {
		filter.Apply();
	}

	glBindBuffer(GL_ARRAY_BUFFER, instance.ID);
	glBufferData(GL_ARRAY_BUFFER, instance.Data.size() * sizeof(float), instance.Data.data(), type_draw);

	instance.Apply(1);


	DisableFolder();
}
HoboGraphics::Mesh::~Mesh() {
	glDeleteVertexArrays(1, &ID_Folder);
	glDeleteBuffers(1, &ID_Elements);
	glDeleteBuffers(1, &ID_Buffer);
}

//----------------------------------------------------------------------------------
//									MeshFilter
//----------------------------------------------------------------------------------
void HoboGraphics::MeshFilter::Apply() {
	glVertexAttribPointer(Index, CountPoint, GL_FLOAT, GL_FALSE,
		Step * sizeof(float), (void*)(Offset * sizeof(float)));
	glEnableVertexAttribArray(Index);
}
HoboGraphics::MeshFilter::MeshFilter(int index, int countPoint, int step, int offset) {
	Index = index;
	CountPoint = countPoint;
	Step = step;
	Offset = offset;
}

//----------------------------------------------------------------------------------
//								 Instanced Instruct
//----------------------------------------------------------------------------------
HoboGraphics::InstanceInstruct::InstanceInstruct(int index, int count, int step, std::vector<float> data)
	: Index(index), ID(0), Data(data), Step(step), Count(count),
	Type(HOBOenumType::HOBO_FLOAT) {}
void HoboGraphics::InstanceInstruct::Apply(int divisior) {
	glEnableVertexAttribArray(Index);
	glVertexAttribPointer(Index, Count, GL_FLOAT, GL_FALSE, sizeof(float) * Step, (void*)0);

	glVertexAttribDivisor(Index, divisior);
}
void HoboGraphics::InstanceInstruct::Free() {
	if (ID != 0) glDeleteBuffers(1, &ID);
}
//----------------------------------------------------------------------------------
//									Texture Program
//----------------------------------------------------------------------------------

void HoboGraphics::TextureProgram::Activate() {
	glActiveTexture(GL_TEXTURE0);
}
void HoboGraphics::TextureProgram::Enable() {
	glBindTexture(GL_TEXTURE_2D, ID);
}
void HoboGraphics::TextureProgram::Disable() {
	glBindTexture(GL_TEXTURE_2D, 0);
}

HoboGraphics::TextureProgram::TextureProgram(Hobo::Texture2D& texture) {
	ID = 0;
	if (texture.empty()) {
		Hobo::Debug::LogError("[HOBO_GRAPHICS][TEXTURE_PROGRAM] Texture is null.");
		return;
	}

	glGenTextures(1, &ID);
	
	Enable();
	//Params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Create
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Width, texture.Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, texture.Data);
	glGenerateMipmap(GL_TEXTURE_2D);
	Disable();
}
HoboGraphics::TextureProgram::TextureProgram(std::string pathFile) {
	ID = 0;
	Hobo::Texture2D texture(pathFile.c_str());
	if (texture.empty()) {
		Hobo::Debug::LogError("[HOBO_GRAPHICS][TEXTURE_PROGRAM] Texture is not loaded.");
		return;
	}

	glGenTextures(1, &ID);
	
	Enable();
	//Params
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//Create
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.Width, texture.Height,
		0, GL_RGBA, GL_UNSIGNED_BYTE, texture.Data);
	glGenerateMipmap(GL_TEXTURE_2D);
	Disable();
}
HoboGraphics::TextureProgram::~TextureProgram() {
	glDeleteTextures(1, &ID);
}
//----------------------------------------------------------------------------------
//					Data-Oriented Desig: GROUP SHADER
//----------------------------------------------------------------------------------
void HoboGraphics::GroupShader::UseShader() {
	glUseProgram(ID_Shader);
}
void HoboGraphics::GroupShader::RenderDefualt(int count) {
	for (int index = 0; index < size; index++) {
		Renderer::DrawObjectInstanced(Ids[index], SizeElements[index], count);
	}
	
	glBindVertexArray(0);
}
void HoboGraphics::GroupShader::RenderDefualtShaderUse(int count) {
	glUseProgram(ID_Shader);

	RenderDefualt(count);
	glUseProgram(0);
}
void HoboGraphics::GroupShader::Set(int index, Mesh& mesh) {
	if (index < 0 || index >= size)
	{
		Hobo::Debug::LogError("[GROUP_SHADER][SET] Index is out of range.");
		return;
	}

	Ids[index] = mesh.ID_Folder;
	SizeElements[index] = mesh.Elements.size();
}
void HoboGraphics::GroupShader::Remove(int index) {
	if (index < 0 || index >= size)
	{
		Hobo::Debug::LogError("[GROUP_SHADER][REMOVE] Index is out of range.");
		return;
	}

	Ids.erase(Ids.begin() + index);
	SizeElements.erase(SizeElements.begin() + index);
}
int HoboGraphics::GroupShader::Add(Mesh& mesh) {
	int s = size;
	size++;
	Ids.push_back(mesh.ID_Folder);
	SizeElements.push_back(mesh.Elements.size());
	return s;
}
void HoboGraphics::GroupShader::Clear() {
	size = 0;
	Ids.clear();
	SizeElements.clear();
}
HoboGraphics::GroupShader::GroupShader(Shader& shader) {
	size = 0;
	if (!shader.IsCompiled) {
		Hobo::Debug::LogError("[GROUP_SHADER] Shader is not compiled.");
		ID_Shader = 0;
		return;
	}

	ID_Shader = shader.ID;
}
HoboGraphics::GroupShader::GroupShader(GLuint shader) {
	size = 0;
	ID_Shader = shader;
}
//----------------------------------------------------------------------------------
//									Renderer
//----------------------------------------------------------------------------------
//Basic Method
void HoboGraphics::Renderer::Clear() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void HoboGraphics::Renderer::ClearColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	glClearColor(r, g, b, a);
}
void HoboGraphics::Renderer::FlipWindow(GLFWwindow* screen) { glfwSwapBuffers(screen); }
void HoboGraphics::Renderer::PollEvents() { glfwPollEvents(); }
void HoboGraphics::Renderer::NewFrame(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	Clear();
	ClearColor(r, g, b, a);
}
void HoboGraphics::Renderer::EndFrame(GLFWwindow* screen) {
	FlipWindow(screen);
	PollEvents();
}

//Draw Mesh&Object
void HoboGraphics::Renderer::DrawMesh(Mesh& mesh) {
	mesh.EnableFolder();

	glDrawElements(GL_TRIANGLES, mesh.Elements.size(), GL_UNSIGNED_INT, 0);

	mesh.DisableFolder();
}
void HoboGraphics::Renderer::DrawMeshPoint(Mesh& mesh, float size) {
	mesh.EnableFolder();
	
	glPointSize(size);
	glDrawArrays(GL_POINTS, 0, mesh.Elements.size());

	mesh.DisableFolder();
}
void HoboGraphics::Renderer::DrawMeshInstanced(Mesh& mesh, int count) {
	mesh.EnableFolder();

	glDrawElementsInstanced(GL_TRIANGLES, mesh.Elements.size(), GL_UNSIGNED_INT, 0, count);

	mesh.DisableFolder();
}
void HoboGraphics::Renderer::DrawMeshTexture(Mesh& mesh, TextureProgram& texture) {
	mesh.EnableFolder();
	texture.Activate();
	texture.Enable();

	glDrawElements(GL_TRIANGLES, mesh.Elements.size(), GL_UNSIGNED_INT, 0);

	texture.Disable();
	mesh.DisableFolder();
}
void HoboGraphics::Renderer::DrawMeshTextureInstanced(Mesh& mesh, TextureProgram& texture, int count) {
	mesh.EnableFolder();
	texture.Activate();
	texture.Enable();

	glDrawElementsInstanced(GL_TRIANGLES, mesh.Elements.size(), GL_UNSIGNED_INT, 0, count);

	texture.Disable();
	mesh.DisableFolder();
}
void HoboGraphics::Renderer::DrawObject(GLuint vao, GLsizei sizeElements) {
	glBindVertexArray(vao);

	glDrawElements(GL_TRIANGLES, sizeElements, GL_UNSIGNED_INT, 0);
}
void HoboGraphics::Renderer::DrawObjectInstanced(GLuint vao, GLsizei sizeElements, int count) {
	glBindVertexArray(vao);

	glDrawElementsInstanced(GL_TRIANGLES, sizeElements, GL_UNSIGNED_INT, 0, count);
}
//Shader
void HoboGraphics::Renderer::UseShader(Shader& shader) {
	if (!shader.IsCompiled) {
		Hobo::Debug::LogError("[RENDERER][USE_PROGRAM] Shader is not compiled.");
		return;
	}

	glUseProgram(shader.ID);
}

//----------------------------------------------------------------------------------
//							File Manager (HoboGraphics.h)
//----------------------------------------------------------------------------------

#include <fstream>

void Hobo::FileManager::SaveShader(HoboGraphics::Shader& shader, std::string filePath) {
	GLint NumSupportGPUFormat = 0;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &NumSupportGPUFormat);
	if (NumSupportGPUFormat < 1) {
		Debug::LogError("[FILE_MANAGER][SAVE_SHADER] GPU dont support binary formats.");
		return;
	}
	
	if (!shader.IsCompiled) {
		Debug::LogError("[FILE_MANAGER][SAVE_SHADER] shader is not compiled.");
		return;
	}
	
	std::ofstream file(filePath, std::ios::out | std::ios::binary);

	if (file.is_open()) {
		GLint length;
		glGetProgramiv(shader.ID, GL_PROGRAM_BINARY_LENGTH, &length);

		std::vector<uint8_t> buffer(length);
		GLenum format;
		glGetProgramBinary(shader.ID, length, NULL, &format, buffer.data());

		file.write(reinterpret_cast<char*>(&format), sizeof(format));
		file.write(reinterpret_cast<char*>(buffer.data()), buffer.size());

		file.close();
	}
	else {
		Debug::LogError("[FILE_MANAGER][SAVE_SHADER] file dont exist & dont create.");
		return;
	}
}
void Hobo::FileManager::LoadShader(HoboGraphics::Shader& shader, std::string filePath) {
	GLint NumSupportGPUFormat = 0;
	glGetIntegerv(GL_NUM_PROGRAM_BINARY_FORMATS, &NumSupportGPUFormat);
	if (NumSupportGPUFormat < 1) {
		Debug::LogError("[FILE_MANAGER][SAVE_SHADER] GPU dont support binary formats.");
		return;
	}

	if (shader.IsCompiled) {
		Debug::LogError("[FILE_MANAGER][SAVE_SHADER] shader is compiled.");
		return;
	}

	std::ifstream file(filePath, std::ios::ate | std::ios::binary);

	if (file.is_open()) {
		size_t length = file.tellg();
		file.seekg(0, std::ios::beg);
		
		GLenum format;
		file.read(reinterpret_cast<char*>(&format), sizeof(format));

		size_t sizeBuffer = length - sizeof(format);
		std::vector<uint8_t> buffer(sizeBuffer);

		file.read(reinterpret_cast<char*>(buffer.data()), buffer.size());

		file.close();

		shader.LoadBinary(format, buffer);
		return;
	}
	else {
		return;
	}
}