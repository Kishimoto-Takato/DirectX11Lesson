#pragma once


class FPSCamera : public KdCamera
{
public:
	FPSCamera() {}
	~FPSCamera() {}

	void Init();
	void Update();

	const Math::Matrix GetRotationMatrix();
	const Math::Matrix GetRotationYMatrix()
	{ return Math::Matrix::CreateRotationY(DirectX::XMConvertToRadians(m_degAng.y)); }


	virtual void SetCameraMatrix(const DirectX::SimpleMath::Matrix& mWorld) override;
	void SetLocalPos(const Math::Vector3& pos) { m_localPos = pos; }

	void SetClampAngle(float minDeg, float maxDeg) {
		m_minAngleX = minDeg; 
		m_maxAngleX = maxDeg;
	}

	void SetRotationSpeed(float speed) { m_rotationSpd = speed; }

	static const POINT s_fixMousePos;

private: 
	
	Math::Vector3 m_degAng;		// カメラ回転

	// X軸の回転角度制限値
	float m_minAngleX = -FLT_MAX;
	float m_maxAngleX = FLT_MAX;

	float m_rotationSpd = 0.25f;

protected:
	Math::Vector3 m_localPos;	// ローカル座標
};
