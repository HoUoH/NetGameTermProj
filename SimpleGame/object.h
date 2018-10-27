#pragma once
class object
{
	int hp;
	float posX, posY;
	float pre_posX, pre_posY;
	float sizeX, sizeY, maxX, maxY;

	float velX, velY;

	float preVelMag;
	float newVelMag;

	float accX, accY;
	float ForceX, ForceY;
	
	float frictionX;
	float frictionY;
	float mass;
	float coefFriction;
	float elapsed_time_in_sec;

	int kind;

	bool isVisible;
public:
	object();
	~object();
	void Update(float elapsed_time_in_sec);

	void SetLocation(float x, float y);
	void GetLocation(float *x,float *y);

	void SetPreLocation(float x, float y);
	void GetPreLocation(float *x, float *y);
	
	void SetSize(float size_x, float size_y);
	void GetSize(float *size_x, float *size_y);

	void SetVelocity(float velX, float velY);
	void GetVelocity(float *velX, float *velY);

	void SetAcc(float acc_x, float acc_y);
	void GetAcc(float *acc_x, float *acc_y);
	
	void SetForce(float ForceX, float ForceY);
	void GetForce(float *ForceX, float *ForceY);

	void SetMass(float Mass);
	void GetMass(float *Mass);

	void SetCoefFriction(float coefFriction	);
	void GetCoefFriction(float *coefFriction);

	void SetKind(int kind);
	void GetKind(int *kind);

	void SetIsVisible(bool isVisible);
	bool GetIsVisible();

	void ApplyForce(float ForceX, float ForceY,float elapsed_time_in_sec);
	void BreakMovement(bool W_KeyIsDown, bool S_KeyIsDown, bool D_KeyIsDown, bool A_KeyIsDown, float elapsed_time_in_sec);



};
