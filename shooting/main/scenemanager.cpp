#include <stdio.h> 
//デフォルトの抽象シーンクラス | |/ユーザーはこれを継承してシーンを実装すると楽 
class AbstractScene {
public:
	// デストラクター
	virtual ~AbstractScene() {};
	//描画以外の更新を実装する
	virtual AbstractScene* Update() = 0;
	//描画に関することを実装する
	virtual void Draw() const = 0;
};
	// シーンマネージャークラス
	// 各シーンの切り替えを管理する。
class SceneManager : public AbstractScene {
private:
	AbstractScene* mScene; // 現在のシーン 
public:
	// コンストラクタ 
	SceneManager(AbstractScene* scene) : mScene(scene) { }
	// デストラクタ 
	~SceneManager() {
		delete mScene;
	}
	//描画以外の更新を実装する
	AbstractScene* Update() override;
	//描画に関することを実装する
	void Draw() const override;
};
AbstractScene* SceneManager::Update() {
	AbstractScene* p = mScene->Update();
	if (p != mScene) {
		delete mScene;
		mScene = p;
	}
	return p;
}
void SceneManager::Draw() const {
	mScene->Draw();
}

class Title : public AbstractScene {
public:
	// デストラクタ
	virtual ~Title() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;
};
						
class GameMain : public AbstractScene {
public:
	// デストラクタ 
	virtual ~GameMain() {};

	//描画以外の更新を実装する
	virtual AbstractScene* Update() override;

	//描画に関することを実装する
	virtual void Draw() const override;
};
						
AbstractScene* Title::Update() {
	int nint;
	scanf_s("%d", &nint);
	if (nint == 1) {
		return new GameMain();
	}
	return this;
}
							
void Title::Draw() const {
	printf("Titleです。\n");
	printf("整数値を入力してください>");
}
									
AbstractScene* GameMain::Update() {
	int nint;
	scanf_s("%d", &nint); if (nint == 1) {
		return nullptr;
	}
	return this;
}
										
void GameMain::Draw() const {
	printf("GameMainです。\n");
	printf("整数値を入力してください>");
}
												
int main() {
	SceneManager sceneMng(new Title());

	printf("整数値を入力してください>");
	while (sceneMng.Update() != nullptr) {
		sceneMng.Draw();
	}

	printf("処理を終了します。\n");
	return 0;
}
