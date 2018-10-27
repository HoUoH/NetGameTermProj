#include "stdafx.h"
#include "ScnMgr.h"
#include "Collision.h"

ScnMgr::ScnMgr()
{

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		objs[i] = NULL;
	}
	if (glewIsSupported("GL_VERSION_3_0"))
	{
		std::cout << " GLEW Version is 3.0\n ";
	}
	else
	{
		std::cout << "GLEW 3.0 not supported\n ";
	}

	// Initialize Renderer
	m_Renderer = new Renderer(WINDOW_SIZEX, WINDOW_SIZEY);
	if (!m_Renderer->IsInitialized())
	{
		std::cout << "Renderer could not be initialized.. \n";
	}
	Character_Texture = m_Renderer->CreatePngTexture("./Textures/RedCircle.png");


	for (int i = 0; i < 8; ++i) {
		objs[i] = new object();
		objs[i]->SetAcc(0, 0);
		objs[i]->SetForce(0, 0);
		objs[i]->SetCoefFriction(1.f);
		objs[i]->SetMass(4.f);
		objs[i]->SetVelocity(0, 0);
		objs[i]->SetSize(50, 50);
		objs[i]->SetKind(KIND_HERO);
		objs[i]->SetIsVisible(true);
	}
	for (int i = 8; i < MAX_OBJECTS; ++i) {
		objs[i] = new object();
		// 랜덤값으로 움직이게 만듦
		objs[i]->SetAcc(rand()%10,rand()%10);
		objs[i]->SetForce(0, 0);
		objs[i]->SetCoefFriction(0.5f);
		objs[i]->SetMass(1.f);
		objs[i]->SetVelocity(0, 0);
		objs[i]->SetSize(25, 25);
		objs[i]->SetKind(KIND_BALL);
		objs[i]->SetIsVisible(true);
	}
	// MAX_OBJECTS - 4는 벽을 제외하기 위해서
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		bool check = true;
		objs[i]->SetLocation(rand() % (WINDOW_SIZEX - 100) - 250, rand() % (WINDOW_SIZEY - 100) - 250);
		for (int j = 0; j < MAX_OBJECTS; ++j) {
			if (i != j) {
				if (CollisionCheck(objs[i], objs[j])) {
					check = false;
					break;
				}
			}
		}
		if (check == false) {
			i--;
			continue;
		}
	}

	
}
int seq = 0;
void ScnMgr::RenderScene()	//1초에 최소 60번 이상 출력되어야 하는 함수
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i]->GetIsVisible()) {
			float x, y;
			objs[i]->GetLocation(&x, &y);
			float width, height;
			objs[i]->GetSize(&width, &height);

			m_Renderer->DrawTextureRectHeight(x, y, 0, width, height, 1, 1, 1, 1, Character_Texture, 0);

		}
	}
}

ScnMgr::~ScnMgr()
{

}
float temp = 10.f;
void ScnMgr::Update(float elapsed_time_in_sec)
{
	ObjectCollision();
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i]->GetIsVisible()) {
			objs[i]->Update(elapsed_time_in_sec);
		}
	}
}


void ScnMgr::ApplyForce(float ForceX, float ForceY, float elapsed_time_in_sec)
{
	objs[HERO_ID]->ApplyForce(ForceX, ForceY, elapsed_time_in_sec);
	//float poten;
	//objs[HERO_ID]->GetPotential(&poten);
	//printf("운동량 : %f\n", poten);

}



void ScnMgr::BreakMovement(bool W_KeyIsDown, bool S_KeyIsDown, bool D_KeyIsDown, bool A_KeyIsDown, float elapsed_time_in_sec)
{
	objs[HERO_ID]->BreakMovement(W_KeyIsDown, S_KeyIsDown, D_KeyIsDown, A_KeyIsDown, elapsed_time_in_sec);
}

void ScnMgr::AddObject(float px, float py, float pz, float sx, float sy, float vx, float vy, int Kind)
{

}

void ScnMgr::Shoot(int ShootKey)
{
	if (ShootKey == SHOOT_NONE) {
		return;
	}
	float px, py;
	float sx, sy;
	float vx, vy;
	objs[HERO_ID]->GetLocation(&px, &py);
	sx = 0.1f;
	sy = 0.1f;
	objs[HERO_ID]->GetVelocity(&vx, &vy);
	switch (ShootKey) {
	case SHOOT_LEFT:
		vx += -10.f;
		vy += 0.f;
		break;
	case SHOOT_RIGHT:
		vx += 10.0f;
		vy += 0.f;
		break;
	case SHOOT_UP:
		vx += 0.f;
		vy += 10.f;
		break;
	case SHOOT_DOWN:
		vx += 0.f;
		vy += -10.f;
		break;
	}



}

void ScnMgr::DeleteObject(unsigned int id)
{

}

void ScnMgr::ObjectCollision()
{

	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i]->GetIsVisible())
			for (int j = 0; j < MAX_OBJECTS; ++j) {
				if (i != j)
					if (objs[j]->GetIsVisible()) {
						if (CollisionCheck(objs[i], objs[j])) {

							// 충돌에 의한 반응
							CollisionReaction(objs[i], objs[j]);
							
							//캐릭터 - 공(떨궈진 공-먹어지기, 쏜 공-, 먹은 공)

							//공 - 공

							//DeleteObject(j);
							std::cout << "collision" << std::endl;
						}
					}
			}
	}

}


int ScnMgr::FindEmptyObjectSlot()
{
	for (int i = 0; i < MAX_OBJECTS; ++i) {
		if (objs[i] == NULL)
			return i;
	}
	std::cout << "object list is full.\n";
	return -1;
}


