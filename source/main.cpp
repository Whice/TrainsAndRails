#include "framework/engine.h"
#include "framework/utils.h"
#include "CatmullRomSpline.h"
#include "Train.h"
#include "Sleepers.h"
#include "Rails.h"

using namespace std;
using namespace glm;

/*
* Coordinate system:
* x - right
* y - up
* z - backward
*/


int main()
{
	// initialization
	Engine *engine = Engine::get();
	engine->init(1600, 900, "UNIGINE Test Task");

	// set up camera
	Camera &cam = engine->getCamera();
	cam.Position = vec3(0.0f, 12.0f, 17.0f);
	cam.Yaw = -90.0f;
	cam.Pitch = -45.0f;
	cam.UpdateCameraVectors();

	// create shared meshes
	Mesh plane_mesh = createPlane();
	Mesh sphere_mesh = createSphere();
	Mesh cube_mesh = createCube();

	// create background objects
	Object *plane = engine->createObject(&plane_mesh);
	plane->setColor(0.2f, 0.37f, 0.2f); // green
	plane->setPosition(0, -0.5f, 0);
	plane->setRotation(-90.0f, 0.0f, 0.0f);
	plane->setScale(20.0f);

	// path
	const vector<vec3> path = {
		vec3(0.0f, -0.375f,  7.0f), // 1
		vec3(-6.0f, -0.375f,  5.0f), // 2
		vec3(-8.0f, -0.375f,  1.0f), // 3
		vec3(-4.0f, -0.375f, -6.0f),// 4
		vec3(0.0f, -0.375f, -7.0f), // 5
		vec3(1.0f, -0.375f, -4.0f), // 6
		vec3(4.0f, -0.375f, -3.0f), // 7
		 vec3(8.0f, -0.375f,  7.0f) // 8
	};

	//Построение сплайна.
	CatmullRomSpline crSpline;
	crSpline.Init(VectorVec3ToVec2(path), 0.4f, true, 100);
	crSpline.Calculate();
	vector<vec3> spline = VectorVec2ToVec3(crSpline.GetCurvePoints());

	Train train = Train(crSpline, engine, cube_mesh, 30, 0.3f, 5, 7);
	Sleepers slep = Sleepers(crSpline, engine, cube_mesh, -0.375f);
	Rails rails = Rails(crSpline, 0.3f, 0.1f);
	vector<vec3> railsSpline1 = VectorVec2ToVec3(rails.GetRailsOuterCountour1());
	vector<vec3> railsSpline2 = VectorVec2ToVec3(rails.GetRailsOuterCountour2());
	vector<vec3> railsSpline3 = VectorVec2ToVec3(rails.GetRailsInnerCountour1());
	vector<vec3> railsSpline4 = VectorVec2ToVec3(rails.GetRailsInnerCountour2());

	vector<Object *> points;
	for (int i = 0; i < path.size(); i++)
	{
		Object *sphere = engine->createObject(&sphere_mesh);
		sphere->setColor(1, 0, 0);
		sphere->setPosition(path[i].x, path[i].y, path[i].z);
		sphere->setScale(0.25f);
		points.push_back(sphere);
	}
	LineDrawer path_drawer(path, true);
	LineDrawer spline_drawer(spline, true);

	vec3 railsColor = vec3(0.6f, 0.6f, 0.6f);
	LineDrawer railsSpline1_drawer(railsSpline1, true);
	LineDrawer railsSpline2_drawer(railsSpline2, true);
	LineDrawer railsSpline3_drawer(railsSpline3, true);
	LineDrawer railsSpline4_drawer(railsSpline4, true);
	railsSpline1_drawer.setColor(railsColor);
	railsSpline2_drawer.setColor(railsColor);
	railsSpline3_drawer.setColor(railsColor);
	railsSpline4_drawer.setColor(railsColor);

	float lastFrame = 0;
	float currentFrame;
	float deltaTime;
	// main loop
	while (!engine->isDone())
	{
		// per-frame time logic
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		engine->update();
		engine->render();

		train.Update(deltaTime);
		//path_drawer.draw();
		//spline_drawer.draw();
		railsSpline1_drawer.draw();
		railsSpline2_drawer.draw();
		railsSpline3_drawer.draw();
		railsSpline4_drawer.draw();
		
		engine->swap();
	}

	engine->shutdown();
	return 0;
}
