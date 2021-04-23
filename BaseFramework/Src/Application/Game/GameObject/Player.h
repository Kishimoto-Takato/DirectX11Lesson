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
	DirectX::SimpleMath::Matrix m_mWorld;

	KdCamera m_camera;	//カメラ
};