#include <Hobo/HoboGraphics.h>
//-------------------------------------------------------------------------
// This cpp file 3D Object example vertex; elements; filters
//
//-------------------------------------------------------------------------
// - - - - - - - - - - - - - - - -|CUBE|- - - - - - - - - - - - - - - - - -
//-------------------------------------------------------------------------
std::vector<float> HoboGraphics::Object::Cube::GetVertexUV(float sizeUV) {
	return {
	//0-Position---------|-Normal----------|-UV------------| FORWARD (Z+)
	  -0.5f,-0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	   0.5f,-0.5f, 0.5f,  0.0f, 0.0f, 1.0f, sizeUV, 0.0f,
	   0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f, sizeUV, sizeUV,
	  -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f, 0.0f, sizeUV,
	//1-Position---------|-Normal----------|-UV------------| RIGHT (X+)
	   0.5f,-0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	   0.5f,-0.5f,-0.5f,  1.0f, 0.0f, 0.0f, sizeUV, 0.0f,
       0.5f, 0.5f,-0.5f,  1.0f, 0.0f, 0.0f, sizeUV, sizeUV,
	   0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f, 0.0f, sizeUV,
	//2-Position---------|-Normal----------|-UV------------| BACK (Z-)
	  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
	   0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, sizeUV, 0.0f,
	   0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, -1.0f, sizeUV, sizeUV,
	  -0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, sizeUV,
	//3-Position---------|-Normal----------|-UV------------| LEFT (X-)
	  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
	  -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, sizeUV, 0.0f,
	  -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, sizeUV, sizeUV,
	  -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, sizeUV,
    //4-Position---------|-Normal----------|-UV------------| UP (Y+)
      -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	   0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, sizeUV, 0.0f,
	   0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, sizeUV, sizeUV,
	  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, sizeUV,
	//5-Position---------|-Normal----------|-UV------------| DOWN (Y-)
	  -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f,
	   0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, sizeUV, 0.0f,
	   0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, sizeUV, sizeUV,
	  -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, sizeUV,
	};
}
std::vector<float> HoboGraphics::Object::Cube::GetVertexColor(float r, float g, float b) {
	return {
	//0-Position---------|-Normal----------|-COLOR------------| FORWARD (Z+)
	  -0.5f,-0.5f, 0.5f,  0.0f, 0.0f, 1.0f, r, g, b,
	   0.5f,-0.5f, 0.5f,  0.0f, 0.0f, 1.0f, r, g, b,
	   0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f, r, g, b,
	  -0.5f, 0.5f, 0.5f,  0.0f, 0.0f, 1.0f, r, g, b,
    //1-Position---------|-Normal----------|-COLOR------------| RIGHT (X+)
	   0.5f,-0.5f, 0.5f,  1.0f, 0.0f, 0.0f, r, g, b,
	   0.5f,-0.5f,-0.5f,  1.0f, 0.0f, 0.0f, r, g, b,
	   0.5f, 0.5f,-0.5f,  1.0f, 0.0f, 0.0f, r, g, b,
	   0.5f, 0.5f, 0.5f,  1.0f, 0.0f, 0.0f, r, g, b,
	//2-Position---------|-Normal----------|-COLOR------------| BACK (Z-)
	  -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, r, g, b,
	   0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, r, g, b,
	   0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, -1.0f, r, g, b,
	  -0.5f, 0.5f,  -0.5f, 0.0f, 0.0f, -1.0f, r, g, b,
	//3-Position---------|-Normal----------|-COLOR------------| LEFT (X-)
	  -0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, r, g, b,
	  -0.5f, -0.5f,  0.5f, -1.0f, 0.0f, 0.0f, r, g, b,
	  -0.5f,  0.5f,  0.5f, -1.0f, 0.0f, 0.0f, r, g, b,
	  -0.5f,  0.5f, -0.5f, -1.0f, 0.0f, 0.0f, r, g, b,
	//4-Position---------|-Normal----------|-COLOR------------| UP (Y+)
	  -0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
	   0.5f,  0.5f,  0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
	   0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
	  -0.5f,  0.5f, -0.5f, 0.0f, 1.0f, 0.0f, r, g, b,
	//5-Position---------|-Normal----------|-COLOR------------| DOWN (Y-)
      -0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
	   0.5f, -0.5f,  0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
	   0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
	  -0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, r, g, b,
	};
}
std::vector<unsigned int> HoboGraphics::Object::Cube::GetElements() {
	return {
		//Face 0
		0, 1, 2, 3, 0, 2,
		//Face 1
		4, 5, 6, 7, 4, 6,
		//Face 2
		8, 9, 10, 11, 10, 8,
		//Face 3
		12, 13, 14, 15, 12, 14,
		//Face 4
		16, 17, 18, 19, 18, 16,
		//Face 5
		20, 21, 22, 23, 22, 20,
	};
}
std::vector<HoboGraphics::MeshFilter> HoboGraphics::Object::Cube::GetFiltersUV() {
	return {
		HoboGraphics::MeshFilter(0, 3, 8, 0),
		HoboGraphics::MeshFilter(1, 3, 8, 3),
		HoboGraphics::MeshFilter(2, 2, 8, 6),
	};
}
std::vector<HoboGraphics::MeshFilter> HoboGraphics::Object::Cube::GetFiltersColor() {
	return {
		HoboGraphics::MeshFilter(0, 3, 9, 0),
			HoboGraphics::MeshFilter(1, 3, 9, 3),
			HoboGraphics::MeshFilter(2, 3, 9, 6),
	};
}
//-------------------------------------------------------------------------
//- - - - - - - - - - - - - - - -|PLANE|- - - - - - - - - - - - - - - - - -
//-------------------------------------------------------------------------
std::vector<unsigned int> HoboGraphics::Object::Plane::GetElements() {
	return { 0, 1, 2, 3, 0, 2 };
}
std::vector<float> HoboGraphics::Object::Plane::GetVertexUV(float sizeUV) {
	return {
		//-Position-----|-Normal-----------|-UV--------|
	   -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 
		0.5f,-0.5f, 0.0f, 0.0f, 0.0f, -1.0f, sizeUV, 0.0f,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, sizeUV, sizeUV,
	   -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, sizeUV,
	};
}
std::vector<float> HoboGraphics::Object::Plane::GetVertexColor(float r, float g, float b) {
	return {
		//-Position-----|-Normal-----------|-Color--------|
	   -0.5f,-0.5f, 0.0f, 0.0f, 0.0f, -1.0f, r, g, b, 
		0.5f,-0.5f, 0.0f, 0.0f, 0.0f, -1.0f, r, g, b,
		0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, r, g, b,
	   -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, -1.0f, r, g, b,
	};
}
std::vector<HoboGraphics::MeshFilter> HoboGraphics::Object::Plane::GetFiltersUV() {
	return {
		MeshFilter(0, 3, 8, 0),
		MeshFilter(1, 3, 8, 3),
		MeshFilter(2, 2, 8, 6),
	};
}
std::vector<HoboGraphics::MeshFilter> HoboGraphics::Object::Plane::GetFiltersColor() {
	return {
		MeshFilter(0, 3, 9, 0),
		MeshFilter(1, 3, 9, 3),
		MeshFilter(2, 3, 9, 6),
	};
}