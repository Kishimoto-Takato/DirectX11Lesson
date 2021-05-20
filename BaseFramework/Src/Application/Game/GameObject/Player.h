#pragma once

class TPSCamera;

class Player
{
public:
	Player() {}
	~Player() {}

	void Draw();
	void Update();
	void Init();		//初期化：カメラの初期化・モデルの読み込み

	const TPSCamera* GetCamera() const { return m_pCamera; }
	TPSCamera* WorkGetCamera() { return m_pCamera; }

	//static const POINT s_fixMousePos;

private:

	void Release();

	void UpdateMove(Math::Vector3& dstMove);
	void UpdateRotate(const Math::Vector3& srcMove);

	//======================================================
	// 基本は２つセットで用いる
	//======================================================
	// モデルワーク
	KdModelWork		m_modelWork;
	KdModelWork		m_robot;	//キューブ

	//KdCamera m_camera;	//カメラ

	Math::Vector3 m_worldPos;			// world行列を作るための座標
	Math::Vector3 m_worldRot;			//　world行列を瑠来るためのそれぞれの軸の回転

	DirectX::SimpleMath::Matrix m_robotMat;	//キューブのワールド行列
	// 行列が必要
	DirectX::SimpleMath::Matrix m_mWorld;		//ゲーム内のワールド(絶対)行列

	TPSCamera* m_pCamera;	//カメラ


};