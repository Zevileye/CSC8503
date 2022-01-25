#pragma once

#include "TutorialGame.h"
#include "PartAGameObject.h"

namespace NCL {
	namespace CSC8503 {
		class PartA : public TutorialGame
		{
		public:

			virtual ~PartA()
			{

			}

			virtual void UpdateGame(float dt) override
			{
				UpdateViewMode(dt);
				ClickGameObject();

				physics->Update(dt);

				world->UpdateWorld(dt);
				renderer->Update(dt);

				Debug::FlushRenderables(dt);
				renderer->Render();

				UpdateTime(dt);
			}

			void setFinish()
			{
				finished = true;
			}

		protected:
			void UpdateRestart();

		protected:
			virtual void InitialiseScene() override;

			void UpdateTime(float dt)
			{
				if (finished == false)
				{
					time += dt;
				}
				int inttime = (int)time;
				char temp[256];
				_itoa_s(inttime, temp, 10);
				std::string str = "Time:";
				renderer->DrawString(str + temp, Vector2(5, 5));
				UpdateRestart();
			}
		protected:
			GameObject* AddOBBCubeToWorld(const Vector3& position, Vector3 dimensions, float inverseMass = 10.0f);
			PartAGameObject* AddPartAGameObjectToWorld(const Vector3& position, float radius, float inverseMass);

		protected:
			void InitialiseAllLevel();
			void InitialiseLevel1();
			void InitialiseLevel2();

			void UpdateViewMode(float dt)
			{
				if (Window::GetKeyboard()->KeyPressed(KeyboardKeys::Q)) {
					inSelectionMode = !inSelectionMode;
					if (inSelectionMode) {
						Window::GetWindow()->ShowOSPointer(true);
						Window::GetWindow()->LockMouseToWindow(false);
					}
					else {
						Window::GetWindow()->ShowOSPointer(false);
						Window::GetWindow()->LockMouseToWindow(true);
					}
				}

				if (!inSelectionMode) {
					world->GetMainCamera()->UpdateCamera(dt);
					renderer->DrawString("Press Q to change to select mode!", Vector2(5, 15));
				}
				else
				{
					renderer->DrawString("Press Q to change to camera mode!", Vector2(5, 15));
					renderer->DrawString("Use mouse to click the cube!", Vector2(5, 25));
				}
			}

			bool ClickGameObject()
			{
				if (Window::GetMouse()->ButtonDown(NCL::MouseButtons::LEFT)) {
					if (selectionObject) {	//set colour to deselected;
						selectionObject->GetRenderObject()->SetColour(Vector4(1, 1, 1, 1));
						selectionObject = nullptr;
						lockedObject = nullptr;
					}

					Ray ray = CollisionDetection::BuildRayFromMouse(*world->GetMainCamera());

					RayCollision closestCollision;
					if (world->Raycast(ray, closestCollision, true)) {
						GameObject* selectionObject = (GameObject*)closestCollision.node;
						OnGameObjectClick(selectionObject);
						return true;
					}
					else {
						return false;
					}
				}
			}

			void OnGameObjectClick(GameObject* obj);

			OGLTexture* tex1 = nullptr;
			GameObject* button1 = nullptr;
			GameObject* button2 = nullptr;
			GameObject* pusher1 = nullptr;
			GameObject* pusher2 = nullptr;
			PartAGameObject* pellet = nullptr;

			float time;
			bool failed;
			bool finished;
		};


	}
}
