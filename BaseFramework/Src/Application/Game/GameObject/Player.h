#pragma once

class Player
{
public:
	Player() {}
	~Player() {}

	void Draw();
	void Update();
	void Init();

	const KdCamera& GetCamera() const { return m_camera; }
	KdCamera& WorkGetCamera() { return m_camera; }
private:

	void Release();
	//======================================================
	// 基本は２つセットで用いる
	//======================================================
	// モデルワーク
	KdModelWork		m_modelWork;
	// 行列が必要
	DirectX::SimpleMath::Matrix m_mWorld;		//ゲーム内のワールド(絶対)行列

	KdCamera m_camera;	//カメラ
	Math::Matrix m_mLocalCamera;		// キャラクターのworld行列からの目の位置までの相対行列
	Math::Matrix m_RotateCamera;		// カメラのその場回転行列
};