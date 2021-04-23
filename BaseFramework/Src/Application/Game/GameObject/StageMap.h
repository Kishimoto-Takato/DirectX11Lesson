#pragma once

class StageMap
{
public:
	StageMap();
	~StageMap();

	void Draw();
	void Update();
	void Init();
private:
	void Release();

	//======================================================
	// 基本は２つセットで用いる
	//======================================================
	// モデルワーク
	KdModelWork		m_modelWork;
	// 行列が必要
	DirectX::SimpleMath::Matrix m_World;
	
};
