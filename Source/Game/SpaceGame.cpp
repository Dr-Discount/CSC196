#include "SpaceGame.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/Scene.h"
#include "Core/Random.h"
#include "Engine.h"

bool SpaceGame::Initialize() {
	m_scene = std::make_unique<viper::Scene>();


    std::vector<vec2> points = {
        {-5, -5},
        {5, -5},
        {5, 5},
        {-5, 5},
        {-5, -5}
    };

    std::vector<vec2> arrowPoints = {
        {5, 0},
        {1, 4},
        {1, 2},
        {-4, 2},
        {-4, -2},
        {1, -2},
        {1, -4},
        {5, 0}
    };

    viper::Model model{ points, { 0, 0, 255.0f} };
    std::shared_ptr<viper::Model> arrow = std::make_shared < viper::Model>(arrowPoints, vec3{ 0, 0, 255 });

    for (int i = 0; i < 10; ++i) {
        viper::Transform transform{ vec2{ viper::random::getRandomFloat() * 1200 , viper::random::getRandomFloat() * 1024 }, 0, 10 };
        std::unique_ptr<Player> player = std::make_unique<Player>(transform, arrow);
        m_scene->AddActor(std::move(player));
    }

	return true;
}

void SpaceGame::Update() {

    vec3 color{ 1, 0, 0 };

    viper::GetEngine().GetRenderer().SetColor((float)color.r, color.g, color.b);
    viper::GetEngine().GetRenderer().Clear();

    if (viper::GetEngine().GetInputSystem().GetMouseButtonPressed(viper::InputSystem::MouseButton::Left)) {
        vec2 position = viper::GetEngine().GetInputSystem().GetMousePosition();
        if (points.empty()) {
            points.push_back(position);
        }
        else if ((position - points.back()).Length() > 10) {

            points.push_back(position);
        }
    }
    for (int i = 0; i < (int)points.size() - 1; i++) {
        viper::GetEngine().GetRenderer().SetColor((uint8_t)viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), viper::random::getRandomInt(0, 255), 255);
        viper::GetEngine().GetRenderer().DrawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
    }
}

void Draw() {

}

void SpaceGame::Shutdown() {
	m_scene.reset();
}
