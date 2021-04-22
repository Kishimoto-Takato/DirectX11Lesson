#pragma once

class GameSystem
{
public:
	GameSystem() {}		//コンストラクター
	~GameSystem() { Release(); }	//デストラクター

	void Init();		//初期化
	void Update();		//更新
	void Draw();		//描画


private:
	void Release();		//解放

	KdModelWork m_sky;	//スカイスフィア

	KdModelWork m_cube;	//キューブ

	KdCamera m_camera;	//カメラ
};

