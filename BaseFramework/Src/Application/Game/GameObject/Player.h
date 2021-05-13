#pragma once

class TPSCamera;

class Player
{
public:
	Player() {}
	~Player() {}

	void Draw();
	void Update();
	void Init();

	const TPSCamera* GetCamera() const { return m_pCamera; }
	TPSCamera* WorkGetCamera() { return m_pCamera; }

	//static const POINT s_fixMousePos;

private:

	void Release();
	//======================================================
	// 基本は２つセットで用いる
	//======================================================
	// モデルワーク
	KdModelWork		m_modelWork;
	KdModelWork		m_robot;	//キューブ

	//KdCamera m_camera;	//カメラ

	DirectX::SimpleMath::Matrix m_robotMat;	//キューブのワールド行列
	// 行列が必要
	DirectX::SimpleMath::Matrix m_mWorld;		//ゲーム内のワールド(絶対)行列

	TPSCamera* m_pCamera;	//カメラ


};