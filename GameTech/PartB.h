#pragma once

#include "TutorialGame.h"
#include "../CSC8503Common/NavigationGrid.h"
#include "StatePlayerGameObject.h"

namespace NCL {
	namespace CSC8503 {
		class PartB : public TutorialGame
		{
		public:
			PartB()
				: TutorialGame()
				, grid(nullptr)
				, enemy(nullptr)
			{
				AddIgnoreLayer(layerCacheable, layerEnemy);
			}

			virtual ~PartB()
			{

			}

			virtual void UpdateGame(float dt);
			
			void setFinish(bool isSuccess)
			{
				if (finished == false)
				{
					finished = true;
					failed = !isSuccess;
				}
			}

			bool isFinished()
			{
				return finished;
			}

		protected:
			void ControlPlayer();

		protected:
			virtual void InitialiseScene() override;

			void UpdateTime(float dt);
			void UpdateRestart();

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
				}
			}

			StatePlayerGameObject* AddPlayerStateToWorld(const Vector3& position)
			{
				StatePlayerGameObject* sphere = new StatePlayerGameObject();

				float radius = 2.0;
				Vector3 sphereSize = Vector3(radius, radius, radius);
				SphereVolume* volume = new SphereVolume(radius);
				sphere->SetBoundingVolume((CollisionVolume*)volume);

				sphere->GetTransform()
					.SetScale(sphereSize)
					.SetPosition(position);

				sphere->SetRenderObject(new RenderObject(&sphere->GetTransform(), sphereMesh, basicTex, basicShader));
				sphere->SetPhysicsObject(new PhysicsObject(&sphere->GetTransform(), sphere->GetBoundingVolume()));

				sphere->GetPhysicsObject()->SetInverseMass(10.0);
				sphere->GetPhysicsObject()->InitSphereInertia();

				world->AddGameObject(sphere);

				return sphere;
			}

			StateGameObject* AddEnemyStateToWorld(const Vector3& position)
			{
				float meshSize = 3.0f;
				float inverseMass = 0.5f;

				StateGameObject* character = new StateGameObject();
				character->SetLayer(layerEnemy);
				AABBVolume* volume = new AABBVolume(Vector3(0.3f, 0.9f, 0.3f) * meshSize);
				character->SetBoundingVolume((CollisionVolume*)volume);

				character->GetTransform()
					.SetScale(Vector3(meshSize, meshSize, meshSize))
					.SetPosition(position);

				character->SetRenderObject(new RenderObject(&character->GetTransform(), enemyMesh, nullptr, basicShader));
				character->SetPhysicsObject(new PhysicsObject(&character->GetTransform(), character->GetBoundingVolume()));

				character->GetPhysicsObject()->SetInverseMass(inverseMass);
				character->GetPhysicsObject()->InitSphereInertia();

				world->AddGameObject(character);

				return character;
			}
		protected:
			vector < Vector3 > testNodes;
			void TestPathfinding() {
				grid = new NavigationGrid("TestGrid1.txt");

				NavigationPath outPath;

				Vector3 startPos(80, 0, 10);
				Vector3 endPos(80, 0, 80);

				bool found = grid->FindPath(startPos, endPos, outPath);

				Vector3 pos;
				while (outPath.PopWaypoint(pos)) {
					testNodes.push_back(pos);
				}
			}
			void DisplayPathfinding() {
				for (int i = 1; i < testNodes.size(); ++i) {
					Vector3 a = testNodes[i - 1];
					Vector3 b = testNodes[i];

					Debug::DrawLine(a, b, Vector4(0, 1, 0, 1));
				}
			}

			void CreateMaze()
			{
				if (grid)
				{
					int count = 0;
					GridNode* node = grid->getAllNodes();
					int nodesize = grid->getNodeSize() / 2;
					for (int i = 0; i < grid->getGridWidth() * grid->getGridHeight(); i++)
					{
						GridNode* current = &node[i];
						if (current->type == 'x')
						{
							AddCubeToWorld(Vector3(current->position.x, current->position.y, current->position.z), Vector3(nodesize, 8.0, nodesize), 0.0);
						}
						else
						{
							GameObject* obj = AddSphereToWorld(Vector3(current->position.x, current->position.y + 2.0, current->position.z), 1.0, 0.0);
							char temp[256];
							_itoa_s(i, temp, 10);
							obj->SetName(temp);
							obj->SetLayer(layerCacheable);
							obj->GetRenderObject()->SetDefaultTexture(tex2);

							count++;
						}
					}

					player->SetCount(count);
				}
			}

		protected:
			NavigationGrid* grid;
			StateGameObject* enemy;
			StatePlayerGameObject* player;
			OGLTexture* tex1;
			OGLTexture* tex2;
			float time;
			bool failed;
			bool finished;
		};
	}
}

