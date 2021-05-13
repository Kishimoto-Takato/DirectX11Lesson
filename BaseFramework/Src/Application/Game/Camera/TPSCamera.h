#pragma once
#include "FPSCamera.h"

class TPSCamera : public FPSCamera
{
public:
	TPSCamera(){}
	~TPSCamera() {}

	void SetCameraMatrix(const Math::Matrix& mWorld) override;

	void SetLocalGazePos(const Math::Vector3& localPos) { m_localGazePos = localPos; }

private:
	//注視点へのローカル座標(キャラクターの原点からの中止店までの相対座標)
	Math::Vector3 m_localGazePos;
};
